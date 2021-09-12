# [518. Coin Change 2](https://leetcode.com/problems/coin-change-2/)

You are given an integer array `coins` representing coins of different denominations and an integer `amount` representing a total amount of money.

Return *the number of combinations that make up that amount*. If that amount of money cannot be made up by any combination of the coins, return `0`.

You may assume that you have an infinite number of each kind of coin.

The answer is **guaranteed** to fit into a signed **32-bit** integer.

 

**Example 1:**

```
Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
```

**Example 2:**

```
Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.
```

**Example 3:**

```
Input: amount = 10, coins = [10]
Output: 1
```

 

**Constraints:**

- `1 <= coins.length <= 300`
- `1 <= coins[i] <= 5000`
- All the values of `coins` are **unique**.
- `0 <= amount <= 5000`

## 题目大意

给定一个代表不同面值硬币的整数数组 coins，和一个总数amount，求组成 amount 的最大方案数，你可以假定每种硬币有无数个

## 解题思路

* 这是一道 DP 完全背包的问题，
* 状态的定义：`dp[i][j]`表示只考虑前 i 件物品，凑成总和为 j 的方案数目，
* 初始化：为了方便初始化，这里让 `dp[0][x]`，不代表任何物品的情况，初始条件为 `dp[0][0] = 1`,任何硬币都不使用你个，也是一种情况，`dp[0][x] = 0`。
* 递推方程：
  * 不选当前硬币：`dp[i][j] = dp[i - 1][j]`
  * 选当前硬币;这里需要对所有符合条件的情况进行求和

## 代码

`````c++
class Solution {
public:
	// 二维朴素
    int change1(int amount, vector<int>& coins) {
        int size = coins.size();
        vector<vector<int>> dp(size + 1, vector<int>(amount + 1, 0));
        dp[0][0] = 1;
        
        for (int i = 1; i <= size; ++i) {
            for (int j = 0; j <= amount; ++j) {
                dp[i][j] = dp[i - 1][j];
                
                for (int k = 1; k * coins[i - 1] <= j; ++k) {
                    dp[i][j] += dp[i - 1][j - k * coins[i - 1]];
                }
            }
        }
        
        return dp[size][amount];
    }
    // 一维优化
    int change(int amount, vector<int>& coins) {
        int size = coins.size();
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= size; ++i) {
            for (int j = coins[i - 1]; j <= amount; ++j) {
                dp[j] += dp[j - coins[i - 1]];
            }
        }
        return dp[amount];
    }
};
`````

