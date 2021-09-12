# [322. Coin Change](https://leetcode.com/problems/coin-change/)

You are given an integer array `coins` representing coins of different denominations and an integer `amount` representing a total amount of money.

Return *the fewest number of coins that you need to make up that amount*. If that amount of money cannot be made up by any combination of the coins, return `-1`.

You may assume that you have an infinite number of each kind of coin.

 

**Example 1:**

```
Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
```

**Example 2:**

```
Input: coins = [2], amount = 3
Output: -1
```

**Example 3:**

```
Input: coins = [1], amount = 0
Output: 0
```

**Example 4:**

```
Input: coins = [1], amount = 1
Output: 1
```

**Example 5:**

```
Input: coins = [1], amount = 2
Output: 2
```

 

**Constraints:**

- `1 <= coins.length <= 12`
- `1 <= coins[i] <= 231 - 1`
- `0 <= amount <= 104`

## 题目大意

给定一个数表示不同面值的货币，和一个整数表示不同大小的货币之和，

返回组成total 的最少货币数，如果不能组成返回 -1

你可假定每种货币有无数个

## 解题思路

* 这是一道 DP 的完全背包问题
* 状态定义 `dp[i][j]`为只使用前 i 中面值的货币，凑成总和为 j 的最少货币数，
* 初始化 `dp[0][x]`表示不选任何货币的情况 所以 `dp[0][0] = 0 ，dp[0][x] = INT_MAX`，这里求的最小值，所以要让初始化不影响最终的结果，
* 状态转移 
  * 不使用该硬币`dp[i][j] = dp[i - 1][j]`
  * 使用该硬币 `dp[i][j] = min(dp[i - 1][j - k * coins[i - 1]])`

## 代码

````c++
class Solution {
public:
    // 二维 DP ，超时
    int coinChange1(vector<int>& coins, int amount) {
        int size = coins.size();
        vector<vector<int>> dp(size + 1, vector<int>(amount + 1, INT_MAX));
        dp[0][0] = 0;
        
        for (int i = 1; i  <= size; ++i) {
            for (int j = 0; j <= amount; ++j) {
                dp[i][j] = dp[i - 1][j];
                
                for (int k = 1; k * coins[i - 1] <= j; ++k) {
                    if (dp[i - 1][j - k * coins[i - 1]] != INT_MAX) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j - k * coins[i - 1]] + k);
                    }
                }
            }
        }
        return dp[size][amount] == INT_MAX ? -1 : dp[size][amount];
    }
    
    // 优化后一维 DP
    int coinChange(vector<int>& coins, int amount) {
        int size = coins.size();
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= size; ++i) {
            for (int j = coins[i - 1]; j <= amount; ++j) {
                if (dp[j - coins[i - 1]] != INT_MAX) {
                    dp[j] = min(dp[j], dp[j - coins[i - 1]] + 1);
                }
            }
        }
        
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};
````

