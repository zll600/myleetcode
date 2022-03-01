# [341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/)

## 题目

You are given a nested list of integers `nestedList`. Each element is either an integer or a list whose elements may also be integers or other lists. Implement an iterator to flatten it.

Implement the `NestedIterator` class:

- `NestedIterator(List<NestedInteger> nestedList)` Initializes the iterator with the nested list `nestedList`.
- `int next()` Returns the next integer in the nested list.
- `boolean hasNext()` Returns `true` if there are still some integers in the nested list and `false` otherwise.

Your code will be tested with the following pseudocode:

```
initialize iterator with nestedList
res = []
while iterator.hasNext()
    append iterator.next() to the end of res
return res
```

If `res` matches the expected flattened list, then your code will be judged as correct. 

**Example 1:**

```
Input: nestedList = [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].
```

**Example 2:**

```
Input: nestedList = [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].
```

 

**Constraints:**

- `1 <= nestedList.length <= 500`
- The values of the integers in the nested list is in the range `[-106, 106]`.

## 题目大意

给定一个嵌套的整数列表，nestList，每个元素要么是一个整数，要么是一个列表；该列表的元素也可能是整数或者是其他列表。请你实现一个迭代器将其扁平化，使之能够遍历这个列表中的所有整数。

实现扁平迭代器类 `NestedIterator` ：

* `NestedIterator(List<NestedInteger> nestedList)` 用嵌套列表 `nestedList` 初始化迭代器
* `int next()` 返回嵌套列表的下一个整数
* `boolean hasNext()` 如果仍然存在待迭代的整数，返回 `true` ；否则，返回 `false` 

## 解题思路

这道题目我们面临的问题是

* 需要针对 整数和嵌套列表采用不同的方式进行遍历
* 嵌套列表中还有可能含有嵌套列表，有可能需要考虑递归，

### Solution 1: 在初始化的时候将嵌套列表进行扁平化

这里采用的方式利用队列来存储遍历之后的结果，在初始化时，进行扁平化，

```c++
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        DFS(nestedList);
    }
    
    int next() {
        int ret = data_.front();
        data_.pop();
        return ret;
    }
    
    bool hasNext() {
        return !data_.empty();
    }
    
 private:
    queue<int> data_;
    
    void DFS(const vector<NestedInteger>& nestedList) {
        for (const auto& nested : nestedList) {
            if (nested.isInteger()) {
                data_.push(nested.getInteger());
            } else {
                DFS(nested.getList());
            }
        }
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
```

### Solution 2: 在遍历的过程中进行扁平化

这种解法在调用 `hasNext()`和`next()`时进行扁平化，

具体做法是：

* 在初始化时，将当前列表的各个元素逆序推入栈中
* 在 `hasNext()`中进行判断，如果是整数就可以直接返回，如果列表，则进行展开，直到产生整数，或者列表为空

这里放上一个例子：`[[1,1],2,[1,1]]`，可以跟着代码走一遍

```c++
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        const int len = nestedList.size();
        // 这里是逆序插入
        for (int i = len - 1; i >= 0; --i) {
            data_.push(nestedList[i]);
        }
    }
    
    int next() {
        NestedInteger res = data_.top();
        data_.pop();
        return res.getInteger();
    }
    
    bool hasNext() {
       while (!data_.empty()) {
           // 如果是整数，直接返回
           NestedInteger cur = data_.top();
           if (cur.isInteger()) {
               return true;
           }
           
           data_.pop();
           // 这里逆序插入
           vector<NestedInteger> arr = cur.getList();
           const int len = arr.size();
           for (int i = len - 1; i >= 0; --i) {
               data_.push(arr[i]);
           }
        }
        return false;
    }
    
 private:
    stack<NestedInteger> data_;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
```

