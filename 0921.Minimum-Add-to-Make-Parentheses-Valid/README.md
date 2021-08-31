# [921. Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/)

## 题目

A parentheses string is valid if and only if:

- It is the empty string,
- It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are valid strings, or
- It can be written as `(A)`, where `A` is a valid string.

You are given a parentheses string `s`. In one move, you can insert a parenthesis at any position of the string.

- For example, if `s = "()))"`, you can insert an opening parenthesis to be `"(**(**)))"` or a closing parenthesis to be `"())**)**)"`.

Return *the minimum number of moves required to make* `s` *valid*.

 

**Example 1:**

```
Input: s = "())"
Output: 1
```

**Example 2:**

```
Input: s = "((("
Output: 3
```

**Example 3:**

```
Input: s = "()"
Output: 0
```

**Example 4:**

```
Input: s = "()))(("
Output: 4
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `s[i]` is either `'('` or `')'`.

## 题目大意

一个括号字符串是有效的需要满足以下条件：

* 是一个空字符串
* 如果 A、B 都是有效的字符窗，则可以重写为 AB，
* 如果A是一个有效的字符串，则(A)也是一个有效的字符串

给定一个括号字符串，每次都可以在字符串的任意位置插入一个字符串，返回可以使这个字符串有效的插入最小值。

## 解题思路

* 这道题目可以用“栈”来解决，先利用栈来匹配括号，最后栈中剩下的就是需要添加的。

## 代码

````c++
class Solution {
public:
    int minAddToMakeValid(string str) {
        stack<char> sta;
        
        for (char c : str) {
            if (c == '(') {
                sta.push(c);
            } else if (c == ')' && !sta.empty() && sta.top() == '(') {
                sta.pop();
            } else {
                sta.push(c);
            }
        }
        
        return sta.size();
    }
};
````

