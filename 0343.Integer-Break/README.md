# [343. Integer Break](https://leetcode.com/problems/integer-break/)

Given an integer `n`, break it into the sum of `k` **positive integers**, where `k >= 2`, and maximize the product of those integers.

Return *the maximum product you can get*.

 

**Example 1:**

```
Input: n = 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.
```

**Example 2:**

```
Input: n = 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
```

 

**Constraints:**

- `2 <= n <= 58`

## 题目大意

给定一个整数 n，将他拆分为 k 个正整数的和，k >= 2，并使这些整数的乘积最大，返回最大乘积