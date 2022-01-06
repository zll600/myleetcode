# [385. Mini Parser](https://leetcode.com/problems/mini-parser/)

## 题目

Given a string s represents the serialization of a nested list, implement a parser to deserialize it and return *the deserialized* `NestedInteger`.

Each element is either an integer or a list whose elements may also be integers or other lists.

 

**Example 1:**

```
Input: s = "324"
Output: 324
Explanation: You should return a NestedInteger object which contains a single integer 324.
```

**Example 2:**

```
Input: s = "[123,[456,[789]]]"
Output: [123,[456,[789]]]
Explanation: Return a NestedInteger object containing a nested list with 2 elements:
1. An integer containing value 123.
2. A nested list containing two elements:
    i.  An integer containing value 456.
    ii. A nested list with one element:
         a. An integer containing value 789
```

 

**Constraints:**

- `1 <= s.length <= 5 * 104`
- `s` consists of digits, square brackets `"[]"`, negative sign `'-'`, and commas `','`.
- `s` is the serialization of valid `NestedInteger`.
- All the values in the input are in the range `[-106, 106]`.

## 题目大意

给定一个嵌套列表序列化后的字符串表示，实现一个解析器可以反序列化，并返回反序列化后的

NestInteger。

列表中的每个元素只可能是整数或整数嵌套列表

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/mini-parser/solution/385-cchao-100de-zhan-jie-fa-by-ffreturn-ou1g/

这道题可以利用递归，来做，不断的分级，然后从底向上构造，后出先进，可以利用栈来做

举例来说，对于 `"[123,[456,[789]]]"`

第一级：`123, [456, [789]]`

第二级：`456,[789]`

第三季：`789`

只有构造完第三季，才能构造完第二级，才能构造完第一级，所以这里可以考虑用栈来做，用DF S，肯定也可以做

### Solution 1: 利用栈

这里将负数不作为特殊情况来处理

分类如下

* 对于 `'['`, 认为是新的嵌套列表的开始

* 对于 `'','`，认为是嵌套列表中一个整数解析完成
* 对于 `']'`，认为是一个嵌套列表的结束，这里可能有更高一级嵌套列表，所以会需要合并



```c++
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    NestedInteger deserialize(string s) {
        // 这里使用数组来模拟栈
        vector<NestedInteger> cache; // 最后一项就是最终的结果
        string str = ""; // 结果字符串
        
        for (char c : s) {
            if (c == '[') {
                // 如果是 '['，那就新建一个嵌套列表
                cache.push_back(NestedInteger());
            } else if (c == ',') {
                // 一个数字结束了
                if (!str.empty()) {
                    // 说明是一个列表
                    cache.back().add(stoi(str));
                    str.clear();
                }
            } else if (c == ']') {
                // 一个嵌套列表的结束，
                if (!str.empty()) {
                    cache.back().add(stoi(str));
                    str.clear();
                }
                
                if (cache.size() > 1) {
                    // 有多重嵌套
                    NestedInteger tmp = cache.back(); // 取出小的
                    cache.pop_back();
                    cache.back().add(tmp);
                }
            } else {
                // 这里是可以处理负数的情况的
                // 当前遍历的是数字，直接累加即可
                str.append(1, c);
            }
        }
        if (!str.empty()) {
            // 如果没有出现 '[' 或者 ']' 字符
            cache.push_back(NestedInteger(stoi(str)));
        }
        
        return cache.back();
    }
};
```

### Solution 2: DFS

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/mini-parser/solution/dui-bu-qi-ge-wei-liao-wo-shi-ge-zhi-zhan-cglh/

递归对应的就是分级来解决问题，

```python
# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
#class NestedInteger:
#    def __init__(self, value=None):
#        """
#        If value is not specified, initializes an empty list.
#        Otherwise initializes a single integer equal to value.
#        """
#
#    def isInteger(self):
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        :rtype bool
#        """
#
#    def add(self, elem):
#        """
#        Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
#        :rtype void
#        """
#
#    def setInteger(self, value):
#        """
#        Set this NestedInteger to hold a single integer equal to value.
#        :rtype void
#        """
#
#    def getInteger(self):
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        :rtype int
#        """
#
#    def getList(self):
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        :rtype List[NestedInteger]
#        """

class Solution:
    def deserialize(self, s: str) -> NestedInteger:
        def dfs(elem):
            if type(elem) == int:
                # 如果是数字直接构建
                return NestedInteger(elem)
            
            # 否则需要递归构建
            li = NestedInteger()
            for e in elem:
                li.add(dfs(e))
            return li
        
        return dfs(eval(s))
                    
        
```

