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

这道题目可以联系第 264题，263 题来考虑

### Solution 1:Dynamic Programming

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/super-ugly-number/solution/dong-tai-gui-hua-java-by-liweiwei1419-1yna/

`indexes[i]` 表示下一个丑数如果选择了 `primes[i]` 是基于哪一个下标的超级丑数得到的。

这里如果不理解 index数组的意义，可以自己举几个例子来看，每一个完美丑数都是基于之前的一个完美丑数和某一个 `primes[i]`，这里是满足递推条件的

```c++
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        if (n == 1) { // 1 是第一个完美丑数
            return 1;
        }
        
        const int len = primes.size();
        vector<int> indexes(len);
        vector<int> dp(n);
        dp[0] = 1; // 初始化
        for (int i = 1; i < n; ++i) {
            dp[i] = INT_MAX; // 取最小，设最大
            for (int j = 0; j < len;  ++j) {
                dp[i] = min(dp[i], dp[indexes[j]] * primes[j]);
            }
            
            for (int j = 0; j < len; ++j) {
                // dp[i] 是之前的哪个丑数乘以对应的 primes[j] 选出来的，给它加 1，转移到下一个
                if (dp[i] == dp[indexes[j]] * primes[j]) {
                    // 注意这里增加了可能不止一次，
                    ++indexes[j];
                }
            }
        }
        
        return dp[n - 1];
    }
};
```

### Solution 2:

这种解法是基于上一种解法做了一些优化，可以参考同一篇题解

````c++
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        if (n == 1) { // 1 是第一个完美丑数
            return 1;
        }
        
        const int len = primes.size();
        vector<int> indexes(len);
        vector<int> dp(n);
        dp[0] = 1; // 初始化
        for (int i = 1; i < n; ++i) {
            int valid_j = 0;
            dp[i] = dp[indexes[0]] * primes[0];
            for (int j = 1; j < len; ++j) {
                int cur = dp[indexes[j]] * primes[j]; // 从最小的开始
                if (cur == dp[i - 1]) {
                    // 如果想等就需要更新
                    ++indexes[j];
                    cur = dp[indexes[j]] * primes[j];
                }
                if (cur < dp[i]) {
                    // 可以更新当前的数，以及记录的下标
                    dp[i] = cur;
                    valid_j = j;
                }
            }
            ++indexes[valid_j];
        }
        
        return dp[n - 1];
    }
};
````

