# [313. Super Ugly Number](https://leetcode-cn.com/problems/super-ugly-number/)

## 题目

A **super ugly number** is a positive integer whose prime factors are in the array `primes`.

Given an integer `n` and an array of integers `primes`, return *the* `nth` ***super ugly number***.

The `nth` **super ugly number** is **guaranteed** to fit in a **32-bit** signed integer.

 

**Example 1:**

```
Input: n = 12, primes = [2,7,13,19]
Output: 32
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 super ugly numbers given primes = [2,7,13,19].
```

**Example 2:**

```
Input: n = 1, primes = [2,3,5]
Output: 1
Explanation: 1 has no prime factors, therefore all of its prime factors are in the array primes = [2,3,5].
```

 

**Constraints:**

- `1 <= n <= 106`
- `1 <= primes.length <= 100`
- `2 <= primes[i] <= 1000`
- `primes[i]` is **guaranteed** to be a prime number.
- All the values of `primes` are **unique** and sorted in **ascending order**.

## 题目大意

一个超级丑数是一个正整数，其中的质因数都在数组 primes 中，给你一个整数 `n` 和一个整数数组 `primes` ，返回第 `n` 个 **超级丑数** 。题目数据保证第 `n` 个 **超级丑数** 在 **32-bit** 带符号整数范围内。

## 解题思路

