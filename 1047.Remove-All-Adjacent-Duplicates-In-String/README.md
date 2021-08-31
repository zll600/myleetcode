# [1047. Remove All Adjacent Duplicates In String](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/)

## 题目

You are given a string `s` consisting of lowercase English letters. A **duplicate removal** consists of choosing two **adjacent** and **equal** letters and removing them.

We repeatedly make **duplicate removals** on `s` until we no longer can.

Return *the final string after all such duplicate removals have been made*. It can be proven that the answer is **unique**.

 

**Example 1:**

```
Input: s = "abbaca"
Output: "ca"
Explanation: 
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".
```

**Example 2:**

```
Input: s = "azxxzy"
Output: "ay"
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s` consists of lowercase English letters.

## 题目大意

给定一个包含小写字母的字符串，重复删除操作会选择两个相同且相邻的对象然后删除它们，在字符串 s 上重复执行删除操作，知道我们无法继续执行。

返回执行完所有重复删除操作后，剩下的最终的字符串，

## 解题思路

* 用栈进行模拟，如果当期元素于栈顶元素相同，则将栈顶元素弹出，作删除操作
* 可以用数组模拟栈（C++ STL 的 stack 的底层是 deque），

````c++
class Solution {
public:
    // 使用 stl 栈
    /*
    string removeDuplicates(string str) {
        stack<char> sta;
        
        for (char c : str) {
            if (!sta.empty() && sta.top() == c) {
                sta.pop();
            } else {
                sta.push(c);
            }
        }
        
        string res = "";
        while (!sta.empty()) {
            res += sta.top();
            sta.pop();
        }
        
        reverse(res.begin(), res.end());
        return res;
    }*/
    
    // 使用 vector 模拟栈操作
    string removeDuplicates(string str) {
        vector<char> sta;
        
        for (char c : str) {
            if (!sta.empty() && sta.back() == c) {
                sta.pop_back();
            } else {
                sta.push_back(c);
            }
        }
        
        return string(sta.begin(), sta.end());
    }
};
````

