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

实现几个基本的计算器，计算一个简单的表达式，返回则会个表达的值

## 解题思路

