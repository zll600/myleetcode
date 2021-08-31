# [1021. Remove Outermost Parentheses](https://leetcode.com/problems/remove-outermost-parentheses/)

## 题目

A valid parentheses string is either empty `""`, `"(" + A + ")"`, or `A + B`, where `A` and `B` are valid parentheses strings, and `+` represents string concatenation.

- For example, `""`, `"()"`, `"(())()"`, and `"(()(()))"` are all valid parentheses strings.

A valid parentheses string `s` is primitive if it is nonempty, and there does not exist a way to split it into `s = A + B`, with `A` and `B` nonempty valid parentheses strings.

Given a valid parentheses string `s`, consider its primitive decomposition: `s = P1 + P2 + ... + Pk`, where `Pi` are primitive valid parentheses strings.

Return `s` *after removing the outermost parentheses of every primitive string in the primitive decomposition of* `s`.

 

**Example 1:**

```
Input: s = "(()())(())"
Output: "()()()"
Explanation: 
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".
```

**Example 2:**

```
Input: s = "(()())(())(()(()))"
Output: "()()()()(())"
Explanation: 
The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".
```

**Example 3:**

```
Input: s = "()()"
Output: ""
Explanation: 
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is either `'('` or `')'`.
- `s` is a valid parentheses string.

## 题目大意

有效括号字符串可以为空、`"(" + A + ")"` 或 `A + B` ，其中 `A` 和 `B` 都是有效的括号字符串，`+` 代表字符串的连接。

* 例如： `""`, `"()"`, `"(())()"`, and `"(()(()))"` 都是有效的括号字符串

如果不存在一种方法可以将括号字符串 s 拆分为 s = A + B（A、B均为非空的有效括号字符串） ，称 s 为 primitive，

给出一个非空有效字符串 `s`，考虑将其作primitive 分解，使得：`s = P1 + P2 + ... + Pk`，其中 `Pi` 是 primitiva。

去掉字符串 s 的每个primitive 的最外层括号，返回新的s

## 解题思路

* 遍历括号字符串时，跳过最外围的左括号和右括号。下面的两种方法的思想都是一样的。

## 代码

````c++
class Solution {
public:
    // 解法一：
    /*
    string removeOuterParentheses(string str) {
        string res = "";
        string cur = "";
        int  count = 0;
        
        for (char c : str) {
            if (c == '(') {
                ++count;
            } else if (c == ')') {
                --count;
            }
            
            cur += c;
            if (count == 0) {
                res.insert(res.end(), cur.begin() + 1, cur.end() - 1);
                cur = "";
            }
        }
        
        return res;
    }*/
    
    // 解法二：
    string removeOuterParentheses(string str) {
        string res = "";
        stack<char> sta;
        int count = 0;
        
        for (char c : str) {
            if (count == 0 && sta.size() == 1 && c == ')') {
                sta.pop();
                continue;
            }
            if (sta.empty() && c == '(') {
                sta.push(c);
                continue;
            }
            
            if (!sta.empty()) {
                if (c == '(') {
                    ++count;
                    res += c;
                } else {
                    --count;
                    res += c;
                }
            }
        }
        
        return res;
    }
};
````

