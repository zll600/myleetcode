# [1175. Prime Arrangements](https://leetcode.com/problems/prime-arrangements/)

## 题目

Return the number of permutations of 1 to `n` so that prime numbers are at prime indices (1-indexed.)

*(Recall that an integer is prime if and only if it is greater  than 1, and cannot be written as a product of two positive integers both smaller than it.)*

Since the answer may be large, return the answer **modulo `10^9 + 7`**.

 

**Example 1:**

```
Input: n = 5
Output: 12
Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is not because the prime number 5 is at index 1.
```

**Example 2:**

```
Input: n = 100
Output: 682289015
```

 

**Constraints:**

- `1 <= n <= 100`

## 题目大意

返回 `1` 到 `n` 的所有排序的数目，其中所有的质数位于质数索引（下标从 `1` 开始）

让我们一起来回顾一下「质数」：质数一定是大于 `1` 的，并且不能用两个小于它的正整数的乘积来表示

因为结果可能很大，对结果取模 `1e9+7`

## 解题思路


### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1100~1199/1175.Prime-Arrangements/)

````c++
class Solution {
public:
    int numPrimeArrangements(int n) {
        int cnt = 0;
        for (int prime : primes) {
            if (prime <= n) {
                ++cnt;
            } else {
                break;
            }
        }

        // 质数的数目的排列 X 非质数数的排列
        return 1L * factorial(cnt) * factorial(n - cnt) % mod_;
    }

 private:
    const int mod_ = 1e9 + 7;
    // 根据题目，我们可以直接列出所有可能出现的质数
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

    // 计算阶乘
    int factorial(int num) {
        if (num == 1 || num == 0) {
            return 1;
        }

        return 1L * num * factorial(num - 1) % mod_;
    }
};
````
