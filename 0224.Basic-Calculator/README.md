# [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/)

## 题目

Given a string `s` representing a valid expression, implement a basic calculator to evaluate it, and return *the result of the evaluation*.

**Note:** You are **not** allowed to use any built-in function which evaluates strings as mathematical expressions, such as `eval()`.

 

**Example 1:**

```
Input: s = "1 + 1"
Output: 2
```

**Example 2:**

```
Input: s = " 2-1 + 2 "
Output: 3
```

**Example 3:**

```
Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
```

 

**Constraints:**

- `1 <= s.length <= 3 * 105`
- `s` consists of digits, `'+'`, `'-'`, `'('`, `')'`, and `' '`.
- `s` represents a valid expression.
- `'+'` is not used as a unary operation.
- `'-'` could be used as a unary operation but it has to be inside parentheses.
- There will be no two consecutive operators in the input.
- Every number and running calculation will fit in a signed 32-bit integer.

## 题目大意

给定一个字符串 s，表示一个有效的表达式，实现一个基本的计算器来对它求值，返回评估的结果

注意：这里不能使用库函数 

输入字符串中只有 '+','_','(', ')', 和 ‘ ’，s 是一个有效的表达式，‘+’不做为一元运算符，即不表示正号， ‘-’ 可以被用作一元运算符，但是必须是在括号中

## 解题思路

这道题可以参考第 227 题的题解

``````c++
class Solution {
 public:
 	int calculate(string str) {
        PreProcess(str);
        stack<char> ops;
        stack<int> vals;
        vals.push(0); 
        
        const int size = str.size();
        for (int i = 0; i < size; ++i) {
            char c = str[i];
            
            if (c == '(') {
                ops.push(c);
            } else if (c == ')') {
                while (!ops.empty()) {
                    if (ops.top() == '(') {
                        ops.pop();
                        break;
                    }
                    Calc(ops, vals);
                }
            } else {
                if (isdigit(c)) {
                    int num = 0;
                    int j = i;
                    while (j < size && isdigit(str[j])) {
                        num = num * 10 + (str[j] - '0');
                        ++j;
                    }
                    vals.push(num);
                    i = j - 1;
                } else {
                    if (i > 0 && str[i - 1] == '(') {  // 如果左括号后面紧跟一个符号，一定是 '-'，作为一元运算符
                        vals.push(0);
                    }
                    
                    while (!ops.empty() && ops.top() != '(') {
                        Calc(ops, vals);
                    }
                    ops.push(c);
                }
            }
        }
        while (!ops.empty()) {
            Calc(ops, vals);
        }
        
        return vals.top();
    }
    
 private:
    void PreProcess(string& str) {
        int pos = str.find(" ");
        while (pos != -1) {
            str.replace(pos, 1, "");
            pos = str.find(" ");
        }
    }
    
    void Calc(stack<char>& ops, stack<int>& vals) {
        if (ops.empty() && vals.size() < 2) {
            return;
        }
        
        int second = vals.top();
        vals.pop();
        int first = vals.top();
        vals.pop();
        
        char op = ops.top();
        ops.pop();
        
        if (op == '+') {
            vals.push(first + second);
            return;
        }
        vals.push(first - second);
    }
};
``````

