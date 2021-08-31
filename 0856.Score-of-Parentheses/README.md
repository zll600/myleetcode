# [856. Score of Parentheses](https://leetcode.com/problems/score-of-parentheses/)

## 题目

Given a balanced parentheses string `s`, return *the **score** of the string*.

The **score** of a balanced parentheses string is based on the following rule:

- `"()"` has score `1`.
- `AB` has score `A + B`, where `A` and `B` are balanced parentheses strings.
- `(A)` has score `2 * A`, where `A` is a balanced parentheses string.

 

**Example 1:**

```
Input: s = "()"
Output: 1
```

**Example 2:**

```
Input: s = "(())"
Output: 2
```

**Example 3:**

```
Input: s = "()()"
Output: 2
```

**Example 4:**

```
Input: s = "(()(()))"
Output: 6
```

 

**Constraints:**

- `2 <= s.length <= 50`
- `s` consists of only `'('` and `')'`.
- `s` is a balanced parentheses string.

## 题目大意

给定一个平衡的字符串，计算并返回其分数，

一个平衡的括号字符串满足下列条件：

* “()” 代表分数1
* AB 代表 A + B，A 和 B 分别是已经满足匹配规则的括号组。
* (A) 代表 2 * A，其中 A 也是已经满足匹配规则的括号组

## 解题思路

* 这道题需要用到栈来模拟，遇到“(”，则压入一个标志，遇到“)”，需要判断它的上一个是“(”还是“)”，分情况讨论。

## 代码

````c++
class Solution {
public:
    int scoreOfParentheses(string str) {
        stack<int> sta;
        
        for (char c : str) {
            if (c == '(') {
                sta.push(-1);
            } else {
                if (sta.top() == -1) {
                    sta.pop();
                    sta.push(1);
                } else {
                    int tmp = 0;
                    while (!sta.empty() && sta.top() != -1) {
                        tmp += sta.top();
                        sta.pop();
                    }
                    sta.pop();
                    
                    sta.push(2 * tmp);
                }
            }
        }
        
        int res = 0;
        while (!sta.empty()) {
            res += sta.top();
            sta.pop();
        }
        
        return res;
    }
};
````

