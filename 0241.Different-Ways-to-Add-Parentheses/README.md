# [241. Different Ways to Add Parentheses](https://leetcode.com/problems/different-ways-to-add-parentheses/)

## 题目

Given a string `expression` of numbers and operators, return *all possible results from computing all the different possible ways to group numbers and operators*. You may return the answer in **any order**.

 

**Example 1:**

```
Input: expression = "2-1-1"
Output: [0,2]
Explanation:
((2-1)-1) = 0 
(2-(1-1)) = 2
```

**Example 2:**

```
Input: expression = "2*3-4*5"
Output: [-34,-14,-10,-10,10]
Explanation:
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10
```

 

**Constraints:**

- `1 <= expression.length <= 20`
- `expression` consists of digits and the operator `'+'`, `'-'`, and `'*'`.

## 题目大意

给定一个包括数字和操作符的字符串表达式，计算所有可能的组织数字和操作符的方法得到的结果，

## 解题思路

这道题可以用分治的方法来解决，对于式子 x op y 来说，最终的结果式 x 和 y 结果的组合数，

这样问题就转化为了，通过运算符来分割整个式子来得到最终的结果，子问题就是不断通过运算符来分割算式

这里可以参考这篇题解：https://leetcode-cn.com/problems/different-ways-to-add-parentheses/solution/pythongolang-fen-zhi-suan-fa-by-jalan/

## 代码

````c++
class Solution {
public:
    // 分治法，自顶向下的递归，
    vector<int> diffWaysToCompute(string expression) {  
        vector<int> res;
        
        int len = expression.size();
        for (int i = 0; i < len; ++i) {
            char c = expression[i];
            
            if (!isdigit(c)) {
                vector<int> left_res = diffWaysToCompute(expression.substr(0, i));  // 前 I 个字符
                vector<int> right_res = diffWaysToCompute(expression.substr(i + 1));    // 后面所有字符
                
                for (int left : left_res) {
                    for (int right : right_res) {
                        int tmp = 0;
                        if (c == '+') {
                            tmp = left + right;
                        } else if (c == '-') {
                            tmp = left - right;
                        } else {
                            tmp = left * right;
                        }
                        res.push_back(tmp);
                    }
                }
            }
        }
        
        if (res.empty()) {
           res.push_back(stoi(expression)); // 这里注意，如果 expression 中包含除数字之外的其他字符，会报错，
        }
        
        return res;
    }
};
````



