# [678. Valid Parenthesis String](https://leetcode-cn.com/problems/valid-parenthesis-string/)

## 题目

Given a string `s` containing only three types of characters: `'('`, `')'` and `'*'`, return `true` *if* `s` *is **valid***.

The following rules define a **valid** string:

- Any left parenthesis `'('` must have a corresponding right parenthesis `')'`.
- Any right parenthesis `')'` must have a corresponding left parenthesis `'('`.
- Left parenthesis `'('` must go before the corresponding right parenthesis `')'`.
- `'*'` could be treated as a single right parenthesis `')'` or a single left parenthesis `'('` or an empty string `""`.

 

**Example 1:**

```
Input: s = "()"
Output: true
```

**Example 2:**

```
Input: s = "(*)"
Output: true
```

**Example 3:**

```
Input: s = "(*))"
Output: true
```

 

**Constraints:**

- `1 <= s.length <= 100`
- `s[i]` is `'('`, `')'` or `'*'`.

## 题目大意

给定一个只包含三种字符的字符串：`（ `，`）` 和 `*`，写一个函数来检验这个字符串是否为有效字符串。有效字符串具有如下规则：

 一个有效的字符串遵循以下规则：

* 任何左括号 `(` 必须有相应的右括号 `)`。
* 任何右括号 `)` 必须有相应的左括号 `(` 。

* 左括号 `(` 必须在对应的右括号之前 `)`。

* 可以被视为单个右括号`)` ，或单个左括号 `(` ，或一个空字符串。
一个空字符串也被视为有效字符串。

## 解题思路

### Solution1:

这种解法使用两个栈来解决，在遍历完整个字符串之后，与其他的括号匹配不同的是，这次还要判断 '*' 能否匹配，这里要注意调整

`````c++
class Solution {
public:
    bool checkValidString(string s) {
        stack<char> left_parenthesis;
        stack<char> stars;
        
        const int size = s.size();
        for (int i = 0; i < size; ++i) {
            if (s[i] == '(') {
                // 左括号直接入栈
                left_parenthesis.push(i);
            } else if (s[i] == '*') {
                // 星号直接入栈
                stars.push(i);
            } else {
                if (!left_parenthesis.empty()) {
                    // 有括号就弹出括号
                    left_parenthesis.pop();
                } else if (!stars.empty()) {
                    // 没括号就弹出星号
                    stars.pop();
                } else {
                    // 如果没有可以匹配的，就直接返回
                    return false;
                }
            }
        }
        
        // 如果左括号栈不为空，可以检测能否用 '*' 匹配
        while (!left_parenthesis.empty()) {
            int left = left_parenthesis.top();
            if (stars.empty()) {
                return false;
            }
            int start = stars.top();
            // 两者都不为空，且位置满足大小关系，才可以同时出栈
            if (start > left) {
                left_parenthesis.pop();
                stars.pop();
            } else {
                return false;
            }
        }
        
        return true;
    }
};
`````



