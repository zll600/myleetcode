# [331. Verify Preorder Serialization of a Binary Tree](https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/)

## 题目

One way to serialize a binary tree is to use **preorder traversal**. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as `'#'`.

![img](https://assets.leetcode.com/uploads/2021/03/12/pre-tree.jpg)

For example, the above binary tree can be serialized to the string `"9,3,4,#,#,1,#,#,2,#,6,#,#"`, where `'#'` represents a null node.

Given a string of comma-separated values `preorder`, return `true` if it is a correct preorder traversal serialization of a binary tree.

It is **guaranteed** that each comma-separated value in the string must be either an integer or a character `'#'` representing null pointer.

You may assume that the input format is always valid.

- For example, it could never contain two consecutive commas, such as `"1,,3"`.

**Note:** You are not allowed to reconstruct the tree.

 

**Example 1:**

```
Input: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
Output: true
```

**Example 2:**

```
Input: preorder = "1,#"
Output: false
```

**Example 3:**

```
Input: preorder = "9,#,#,1"
Output: false
```

 

**Constraints:**

- `1 <= preorder.length <= 104`
- `preorder` consist of integers in the range `[0, 100]` and `'#'` separated by commas `','`.

## 题目大意

给定一串以逗号分隔的序列，验证它是否是正确的二叉树的前序序列化。编写一个在不重构树的条件下的可行算法。

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/verify-preorder-serialization-of-a-binary-tree/solution/pai-an-jiao-jue-de-liang-chong-jie-fa-zh-66nt/



### Solution 1: 入度和出度

这里利用二叉树的入度之和等于出度之和的特点，



这里使用的 分割字符串的方法可以参考这里：https://segmentfault.com/a/1190000020863841###

````c++
class Solution {
public:
    bool isValidSerialization(string preorder) {
        vector<string> tokens;
        Split(preorder, tokens, ",");
        // 根结点没有入度，所以这里 初始化为 1
        int diff = 1; // diff = 出度 - 入度
        for (const auto& token : tokens) {
            --diff; // 递减入度
            if (diff < 0) {
                // 遍历的过程中 diff 应该始终大于等于 0
                return false;
            }
            
            if (token != "#") {
                // 增加出度
                diff += 2;
            }
        }
        
        return diff == 0; // 二叉树的入度之和等于出度
    }
    
 private:
    void Split(const string& str, vector<string>& tokens, 
           const string delim = " ") {
        tokens.clear();
    
        auto start = str.find_first_not_of(delim, 0);       // 分割到的字符串的第一个字符
        auto position = str.find_first_of(delim, start);    // 分隔符的位置
        while (position != string::npos || start != string::npos) {
            // [start, position) 为分割下来的字符串
            tokens.emplace_back(move(str.substr(start, position - start)));
            start = str.find_first_not_of(delim, position);
            position = str.find_first_of(delim, start);
        }
    }
};
````

### Solution 2: Stack

这种解法利用栈的「自底向上」的特性来完成，

````c++
class Solution {
public:
    bool isValidSerialization(string preorder) {
        vector<string> tokens;
        Split(preorder, tokens, ",");
        vector<string> sta;
        const int len = tokens.size();
        for (const auto& token : tokens) {
            sta.push_back(token);
            while (sta.size() >= 3
                   && *sta.crbegin() == "#"
                   && *(sta.crbegin() + 1) == "#"
                   && *(sta.crbegin() + 2) != "#") {
                sta.pop_back();
                sta.pop_back();
                sta.pop_back();
                sta.push_back("#");
            }
        }
        
        return sta.size() == 1 && sta.back() == "#";
    }
    
 private:
    void Split(const string& str, vector<string>& tokens, 
           const string delim = " ") {
        tokens.clear();
    
        auto start = str.find_first_not_of(delim, 0);       // 分割到的字符串的第一个字符
        auto position = str.find_first_of(delim, start);    // 分隔符的位置
        while (position != string::npos || start != string::npos) {
            // [start, position) 为分割下来的字符串
            tokens.emplace_back(move(str.substr(start, position - start)));
            start = str.find_first_not_of(delim, position);
            position = str.find_first_of(delim, start);
        }
    }
};
````





这道题目也可以学习一个c++分割字符串的新方法：

这种方法 可以参考这里：https://www.zhihu.com/question/36642771/answer/865135551

````c++
void Split(const string& str, vector<string>& tokens, 
           const string delim = " ") {
        tokens.clear();
    
        auto start = str.find_first_not_of(delim, 0);       // 分割到的字符串的第一个字符
        auto position = str.find_first_of(delim, start);    // 分隔符的位置
        while (position != string::npos || start != string::npos) {
            // [start, position) 为分割下来的字符串
            tokens.emplace_back(move(str.substr(start, position - start)));
            start = str.find_first_not_of(delim, position);
            position = str.find_first_of(delim, start);
        }
    }
````

