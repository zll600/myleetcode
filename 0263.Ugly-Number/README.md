# [263. Ugly Number](https://leetcode.com/problems/ugly-number/)

## 题目

An **ugly number** is a positive integer whose prime factors are limited to `2`, `3`, and `5`.

Given an integer `n`, return `true` *if* `n` *is an **ugly number***.

 

**Example 1:**

```
Input: n = 6
Output: true
Explanation: 6 = 2 × 3
```

**Example 2:**

```
Input: n = 8
Output: true
Explanation: 8 = 2 × 2 × 2
```

**Example 3:**

```
Input: n = 14
Output: false
Explanation: 14 is not ugly since it includes the prime factor 7.
```

**Example 4:**

```
Input: n = 1
Output: true
Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.
```

 

**Constraints:**

- `-231 <= n <= 231 - 1`

## 题目大意

一个丑陋的数是一个正数，其中它的质因数只限于 2, 3 和 5；

给定一个数，判断它是否是丑数

## 解题思路

### 解法1

判断是否能被2， 3， 5 整除，如果可以，最终的结果应该是 1，

`````
class Solution {
public:
    bool isUgly(int n) {
        if (n <= 0) {
            return false;
        }
        
        while  (n % 2 == 0) {
            n /= 2;
        }
        while (n % 3 == 0) {
            n /= 3;
        }
        while (n % 5 == 0) {
            n /= 5;
        }
        
        return n == 1;
    }
};
`````

