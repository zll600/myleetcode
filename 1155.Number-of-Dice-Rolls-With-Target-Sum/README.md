# [1155. Number of Dice Rolls With Target Sum](https://leetcode-cn.com/problems/number-of-dice-rolls-with-target-sum/)

## 题目

You have `n` dice and each die has `k` faces numbered from `1` to `k`.

Given three integers `n`, `k`, and `target`, return *the number of possible ways (out of the* `kn` *total ways)* *to roll the dice so the sum of the face-up numbers equals* `target`. Since the answer may be too large, return it **modulo** `109 + 7`.

 

**Example 1:**

```
Input: n = 1, k = 6, target = 3
Output: 1
Explanation: You throw one die with 6 faces.
There is only one way to get a sum of 3.
```

**Example 2:**

```
Input: n = 2, k = 6, target = 7
Output: 6
Explanation: You throw two dice, each with 6 faces.
There are 6 ways to get a sum of 7: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1.
```

**Example 3:**

```
Input: n = 30, k = 30, target = 500
Output: 222616187
Explanation: The answer must be returned modulo 109 + 7.
```

 

**Constraints:**

- `1 <= n, k <= 30`
- `1 <= target <= 1000`

## 题目大意

这里有 `n` 个一样的骰子，每个骰子上都有 `k` 个面，分别标号为 `1 到 k` 

给定三个整数 `n ,  k 和 target` ，返回可能的方式(从总共 `kn` 种方式中)滚动骰子的数量，使正面朝上的数字之和等于 `target` 。

答案可能很大，你需要对 `10^9 + 7` 取模 。


## 解题思路

注：这道题目在快手 一面的时候遇到过，打个标记


## 解题思路



### Solution:

这种解法可以参考 [这篇题解](https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/submissions/)

````c++
class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        // dp[i][j] 表示使用前 i 个，骰子形成和 j 的所有可能数
        vector<vector<int>> dp(n + 1, vector<int>(k * n + 1, 0));
        // 初始化
        for (int i = 1; i <= k; ++i) {
            dp[1][i] = 1;
        }

        for (int i = 2; i <= n; ++i) {
            // 这里注意起始下标
            for (int j = i; j <= k * n; ++j) {
                // 这里注意防止下标越界
                for (int m = 1; j - m > 0 && m <= k; ++m) {
                    // 这里同样注意防止下标越界
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - m]) % mod_;
                }
            }
        }

        if (target > k * n) {
            // 这里注意防止下标
            return 0;
        }
        return dp[n][target];
    }

 private:
    const int mod_ = 1000000007;
};
