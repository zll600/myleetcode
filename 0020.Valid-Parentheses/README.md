# [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)

## 题目

Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.

 



Example 1:

Input: s = "()"
Output: true

Example 2:

Input: s = "()[]{}"
Output: true

Example 3:

Input: s = "(]"
Output: false

Example 4:

Input: s = "([)]"
Output: false

Example 5:

Input: s = "{[]}"
Output: true

 

Constraints:

    1 <= s.length <= 104
    s consists of parentheses only '()[]{}'.

## 题目大意

给定一个只包含各种括号的字符串，判断这个字符串是否有效

## 解题思路

* 如果想要判断和法比较困难，那就先判断不合法。
  1. 如果第一个括号是一个右括号，
  2. 如果最后一个括号是一个左括号
  3. 连续的括号不匹配
* 遇到左括号就push 。遇到右括号，需要看栈顶有没有对应的左括号，如果有就pop，如果栈为空，就直接返回错误。（解决情况2）
* 便利完字符串之后，如果栈为空，则返回 true。（解决情况1、3）

## 代码

````c++
class Solution {
public:
    bool isValid(string s) {
        stack<char> data;
        
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                data.push(c);
            } else if ((c == ')' && !data.empty() && data.top() == '(')
                      || (c == ']' && !data.empty() && data.top() == '[')
                      || (c == '}' && !data.empty() && data.top() == '{')) {
                data.pop();
            } else {
                return false;
            }
        }
        
        return data.empty();
    }
};
````

