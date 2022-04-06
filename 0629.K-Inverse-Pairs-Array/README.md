# [629. K Inverse Pairs Array](https://leetcode-cn.com/problems/k-inverse-pairs-array/)

## 题目 

For an integer array `nums`, an **inverse pair** is a pair of integers `[i, j]` where `0 <= i < j < nums.length` and `nums[i] > nums[j]`.

Given two integers n and k, return the number of different arrays consist of numbers from `1` to `n` such that there are exactly `k` **inverse pairs**. Since the answer can be huge, return it **modulo** `109 + 7`.

 

**Example 1:**

```
Input: n = 3, k = 0
Output: 1
Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pairs.
```

**Example 2:**

```
Input: n = 3, k = 1
Output: 2
Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
```

 

**Constraints:**

- `1 <= n <= 1000`
- `0 <= k <= 1000`

## 题目大意

对于一个数组 `nums` 来说，一个逆序对是一组整数 `[i, j]` 其中 `0 <= i < j < nums.length` 且 `nums[i] > nums[j]`

给定两个数 `n` 和 `k`，返回包含所有的 `1` 到 `n` 的数，且有 `k` 个逆序对的数组的个数，对结果 `10^9 + 7`,

## 解题思路



### Solution 1: DFS

这种解法最终会 `TLE`

这种解法中，我们利用 `1~n`中有 `k` 个逆序对，可以由 `1~n - ` 中，分别有 `0, 1, ... k` 个逆序对来得出，所以这里的DFS 过程可以理解为一棵 叉数，

````c++
class Solution {
public:
    int kInversePairs(int n, int k) {
        return DFS(n, k);
    }

 private:
    const int mod_ = 1e9 + 7;

    int DFS(int n, int k) {
        // 1 ~ n 最多可以产生 n * (n - 1) / 2 个逆序对
        if (k > n * (n - 1) / 2) {
            return 0;
        }

        // 如果 数组中只有一个元素，那么只查看 k 的取值即可
        if (n == 1) {
            return k == 0 ? 1 : 0;
        }

        // 这里的状态转移是 1 ～ n -1 中有 i 个逆序对，来凑成 1 ~ n 中有 k 个逆序对
        int ans = 0;
        // 这里可以这样理解前 n -1 个数有 i 个逆序对，那么增加第 n 个数，最多只能增加 n - 1 个逆序对，
        // 所以这里要求 n - 1 + i >= k 才可以
        for (int i = max(0, k - n + 1); i <= k; ++i) {
            ans = (1L * ans + DFS(n - 1, i)) % mod_;
        }

        return ans % mod_;
    }
};
````

### Solution 2: DFS + memo

这种解法最终会 `TLE`

````c++
class Solution {
public:
    int kInversePairs(int n, int k) {
        cache_ = vector<vector<int>>(n + 1, vector<int>(k + 1, -1));

        return DFS(n, k);
    }

 private:
    const int mod_ = 1e9 + 7;
    vector<vector<int>> cache_;

    int DFS(int n, int k) {
        // 1 ~ n 最多可以产生 n * (n - 1) / 2 个逆序对
        if (k > n * (n - 1) / 2) {
            return 0;
        }

        // 如果 数组中只有一个元素，那么只查看 k 的取值即可
        if (n == 1) {
            return k == 0 ? 1 : 0;
        }

        if (cache_[n][k] != -1) {
            return cache_[n][k];
        }

        // 这里的状态转移是 1 ～ n -1 中有 i 个逆序对，来凑成 1 ~ n 中有 k 个逆序对
        int ans = 0;
        // 这里可以这样理解前 n -1 个数有 i 个逆序对，那么增加第 n 个数，最多只能增加 n - 1 个逆序对，
        // 所以这里要求 n - 1 + i >= k 才可以
        for (int i = max(0, k - n + 1); i <= k; ++i) {
            ans = (1L * ans + DFS(n - 1, i)) % mod_;
        }

        cache_[n][k] = ans % mod_;
        return ans % mod_;
    }
};
````

### Solution 3： DP

这种解法也会 `TLE`，可以由记忆化递归转化而来

````c++
class Solution {
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        dp[1][0] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j <= min(k, i * (i - 1) / 2); ++j) {
                for (int m = max(0, j - i + 1); m <= j; ++m) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][m]) % mod_;
                }
            }
        }

        return dp[n][k];
    }

 private:
    const int mod_ = 1e9 + 7;
};
````

### Solution 4: DP

这种将改变了递推公式，降低了时间复杂度，这次是可以通过的

````
dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + ... + dp[i-1][j-(i-1)]

同样地，dp[i][j-1] = dp[i-1][j-1] + ... + dp[i-1][j-1-(i-1-1)] + dp[i-1][j-1-(i-1)]

由上式减下式可以得到 dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1]

````

````c++
class Solution {
public:
    int kInversePairs(int n, int k) {
        // dp 数组
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        // 初始化，使得递推可以进行下去
        dp[1][0] = 1;
        // 状态转移
        for (int i = 2; i <= n; ++i) {
            // 这里的 k 有上限
            for (int j = 0; j <= min(k, i * (i - 1) / 2); ++j) {
                // dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1-i-1]
                dp[i][j] = (1L * (j >= 1 ? dp[i][j - 1] : 0)
                            + dp[i - 1][j]
                            - (j >= i ? dp[i - 1][j - i] : 0) + mod_) % mod_;
            }
        }

        return dp[n][k];
    }

 private:
    const int mod_ = 1e9 + 7;
};
````
