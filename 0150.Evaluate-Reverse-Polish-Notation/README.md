# [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)

## 题目

Evaluate the value of an arithmetic expression in [Reverse Polish Notation](http://en.wikipedia.org/wiki/Reverse_Polish_notation).

Valid operators are `+`, `-`, `*`, and `/`. Each operand may be an integer or another expression.

**Note** that division between two integers should truncate toward zero.

It is guaranteed that the given RPN expression is always valid. That means the expression would always evaluate to a result, and there will not be any division by zero operation.

 

**Example 1:**

```
Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
```

**Example 2:**

```
Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
```

**Example 3:**

```
Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
```

 

**Constraints:**

- `1 <= tokens.length <= 104`
- `tokens[i]` is either an operator: `"+"`, `"-"`, `"*"`, or `"/"`, or an integer in the range `[-200, 200]`.

## 题目大意

使用 “逆波兰表达式”拉计算一个算术表达式的值，有效的操作符有 ‘ +’、‘-’、‘*’、‘/’，操作数时一个整数或者时另一个表达式，除法应该采用趋零截断，

题目保证表达时可定时有效的。

## 解题思路

* 这道题目就是考察栈的相关操作，

## 代码

````c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> vals;
        
        for (string str : tokens) {
            if (str == "+" || str == "-"
                || str == "*" || str == "/") {
                int b = vals.top();
                vals.pop();
                int a = vals.top();
                vals.pop();
                
                if (str == "+") {
                    vals.push(a + b);
                } else if (str == "-") {
                    vals.push(a - b);
                } else if (str == "*") {
                    vals.push(a * b);
                } else if (str == "/") {
                    vals.push(a / b);
                }
            } else {
                vals.push(stoi(str));
            }
        }
        
        return vals.top();
    }
};
````

