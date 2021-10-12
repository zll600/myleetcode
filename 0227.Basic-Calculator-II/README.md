# [227. Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/)

## 题目

Given a string `s` which represents an expression, *evaluate this expression and return its value*. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of `[-231, 231 - 1]`.

**Note:** You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as `eval()`.

 

**Example 1:**

```
Input: s = "3+2*2"
Output: 7
```

**Example 2:**

```
Input: s = " 3/2 "
Output: 1
```

**Example 3:**

```
Input: s = " 3+5 / 2 "
Output: 5
```

 

**Constraints:**

- `1 <= s.length <= 3 * 105`
- `s` consists of integers and operators `('+', '-', '*', '/')` separated by some number of spaces.
- `s` represents **a valid expression**.
- All the integers in the expression are non-negative integers in the range `[0, 231 - 1]`.
- The answer is **guaranteed** to fit in a **32-bit integer**.

## 题目大意

给定一个字符串 s ，代表一个表达式，对这个表达式求值，然后返回它的值

整数除法应该趋零截断

字符之间可以用任意数量的空格分开，s 保证是一个合法的表达式，表达式中的所有数都是非负数

## 解题思路

### 解法1

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/basic-calculator-ii/solution/shi-yong-shuang-zhan-jie-jue-jiu-ji-biao-c65k/

这道题和第 244 题相同，大致思路都是利用双栈法来解决的：

* vals 存储所有的值
* ops 存储所有的操作符

在处理之前先预处理字符串，去掉其中的空格（也可以在遍历的过程中跳过，这里采用预处理的方式），

处理空格之后

* 空格（可以预处理）直接跳过
* 左括号：入栈
* 数字，处理整个数值，
* 右括号：將对应括号中的式子都计算
* 操作符：根据优先级先将能算的都算，然后入栈

注意，这道题保证不会有负数，所以不用担心 ‘-’ 左一元运算符了

````c++
class Solution {
public:
    int calculate(string s) {
        stack<int> vals;  // 数值
        stack<char> ops;  // 操作符
        PreProcess(s);  // 预处理字符
        
        const int size = s.size();
        for (int i = 0; i < size; ++i) {
            char c = s[i];
            
            if (c == '(') {  // 左括号直接入栈
                ops.push(c);
            } else if (c == ')') {  // 右括号，能计算就计算
                while (!ops.empty()) {  // 先检查是否为空，因为后面有一个弹出的操作
                    if (ops.top() == '(') {
                        ops.pop(); // 弹出对应左括号
                        break;
                    }
                    Calc(ops, vals);
                }
            } else {
                if (isdigit(c)) {
                    int num = 0;
                    int j = i;
                    while (j < size && isdigit(s[j])) {  // 拿出数值
                        num = num * 10 + (s[j] - '0');
                        ++j;
                    }
                    vals.push(num);
                    i = j - 1;  // 回退一步，对应 for 循环
                } else {
                    // 当有新运算符要入栈时，先將能算的都算
                    // 这里要注意优先级的判断，先判断，在计算
                    while (!ops.empty() && ops.top() != '(') {  // 对比上一个循环
                        if (oprands.at(c) > oprands.at(ops.top())) {
                            break;
                        }
                        Calc(ops, vals);
                    }
                    ops.push(c);  // 新操作符入栈
                }
            }
        }
        // 將剩余的计算
        while (!ops.empty()) {
            Calc(ops, vals);
        }
        
        return vals.top();
    }
    
 private:
    unordered_map<char, int> oprands = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2}
    };
    
    void PreProcess(string& str) {
        int pos = str.find(" ");
        while (pos != -1) {
            str.replace(pos, 1, "");
            pos = str.find(" ");
        }
    }
    
    void Calc(stack<char>& ops, stack<int>& vals) {
        // 先检查再计算
        if (vals.size() < 2 || ops.empty()) {
            return;
        }
        
        int second = vals.top();  // 第二个操作数
        vals.pop();
        int first = vals.top();  // 第一个操作数
        vals.pop();
        
        char op = ops.top();
        ops.pop();
        switch (op) {
            case '+':
                vals.push(first + second);
                return;
            case '-':
                vals.push(first - second);
                return;
            case '*':
                vals.push(first * second);
                return;
            case '/':
                vals.push(first / second);
                return;
        }
    }
};
````

