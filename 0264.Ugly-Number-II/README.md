# [264. Ugly Number II](https://leetcode.com/problems/ugly-number-ii/)

## 题目

An **ugly number** is a positive integer whose prime factors are limited to `2`, `3`, and `5`.

Given an integer `n`, return *the* `nth` ***ugly number***.

 

**Example 1:**

```
Input: n = 10
Output: 12
Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.
```

**Example 2:**

```
Input: n = 1
Output: 1
Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.
```

 

**Constraints:**

- `1 <= n <= 1690`

## 题目大意

一个丑数只能被 2，3， 5 整除，给定一个整数，返回第 n 个丑数

## 解题思路

### Solution 1: Brute force

````c++
class Solution {
public:
    int nthUglyNumber(int n) {
        if (n == 1) {
            return 1;
        }
        
        set<int> res;  // 这里使用 set 来去重
        // 三层循环枚举所有的可能，为了避免溢出，全部用 long long 
        for (long long i = 1; i <= INT_MAX; i *= 2) {
            for (long long j = i; j <= INT_MAX; j *= 3) {
                for (long long k = j; k <= INT_MAX; k *= 5) {
                    res.insert(k);
                }
            }
        }
        
        // 利用 set 的有序性来做
        int idx = 1;
        for (int i : res) {
            if (idx == n) {
                return i;
            }
            ++idx;
        }
        
        return -1;
    }
};
````

## Solution 2:

这里用外层循环控制循环次数，没次循环，扩展一次，每次都选出最小数并删除

````c++
class Solution {
public:
    int nthUglyNumber(int n) {
        if (n == 1) {
            return 1;
        }
        
        set<long long> ht;  // 用 set 来去重
        vector<int> factors = {2, 3, 5};
        long long cur = 1;
        for (int i = 1; i < n; ++i) {
            for (int factor : factors) {  // 每次同上一次的最小数扩这三个
                ht.insert(cur * factor);
            }
            cur = *ht.cbegin();  // 取最小的数
            ht.erase(cur);  // 删除最小的数，不然后面最小值就不会更新
        }
        return cur;  // 返回最后一次的最小值，就是最终结果
    }
};
````

### Solution 3: DP

```c++
class Solution {
public:
    int nthUglyNumber(int n) {
        if (n == 1) {
            return 1;
        }
        
        vector<int> dp(n);
        dp[0] = 1;
        int p_2 = 0;
        int p_3 = 0;
        int p_5 = 0;
        
        for (int i = 1; i < n; ++i) {
            // 每次存最小的
            dp[i] = min(2 * dp[p_2], min(3 * dp[p_3], 5 * dp[p_5]));
            
            if (dp[i] == 2 * dp[p_2]) {
                ++p_2;
            }
            
            if (dp[i] == 3 * dp[p_3]) {
                ++p_3;
            }
            if (dp[i] == 5 * dp[p_5]) {
                ++p_5;
            }
        }
        
        return dp[n - 1];
    }
};
```

