# [879. Profitable Schemes](https://leetcode.com/problems/profitable-schemes/)

## 题目

There is a group of `n` members, and a list of various crimes they could commit. The `ith` crime generates a `profit[i]` and requires `group[i]` members to participate in it. If a member participates in one crime, that member can't participate in another crime.

Let's call a **profitable scheme** any subset of these crimes that generates at least `minProfit` profit, and the total number of members participating in that subset of crimes is at most `n`.

Return the number of schemes that can be chosen. Since the answer may be very large, **return it modulo** `109 + 7`.

 

**Example 1:**

```
Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
Output: 2
Explanation: To make a profit of at least 3, the group could either commit crimes 0 and 1, or just crime 1.
In total, there are 2 schemes.
```

**Example 2:**

```
Input: n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
Output: 7
Explanation: To make a profit of at least 5, the group could commit any crimes, as long as they commit one.
There are 7 possible schemes: (0), (1), (2), (0,1), (0,2), (1,2), and (0,1,2).
```

 

**Constraints:**

- `1 <= n <= 100`
- `0 <= minProfit <= 100`
- `1 <= group.length <= 100`
- `1 <= group[i] <= 100`
- `profit.length == group.length`
- `0 <= profit[i] <= 100`

## 题目大意

这里有一组打工人，他们可以产生各种各样的工作，第 i 项工作产生 profit[i] 的利润，需要 group[i] 的人，一个打工人如果参与一项工作，就不能参与另一项工作，我们把完成这些 工作且产生至少 minProft利润，需要至多 n 个打工人的任何子集，称为盈利计划，返回有多少种可能的盈利计划，

## 解题思路

* 这是一道 DP 01 背包的问题，可以参考这篇题解：https://leetcode-cn.com/problems/profitable-schemes/solution/gong-shui-san-xie-te-shu-duo-wei-fei-yon-7su9/
* 状态的定义：`dp[i][j][k]`表示考虑前 i 件物品，使用人数不超过 j, 所得利润至少为 k 的方案数
* 状态转移：这里空一行，避免分类讨论，
  * 不选：`dp[i - 1][j][k]`
  * 选：人数需要满足要求（j >= group[i - 1]），还需要考虑【至少利润】可不可以为负的情况
    * `dp[i - 1][j - group[i - 1]][max(k - profit[i]), 0]`
* 初始化：结合状态定义来看，如果不选任何任务，那么不论使用多少人，利润都为 0，`dp[0][x][0] = 1`

## 代码

````c++
class Solution {
public:
    int profitableSchemes1(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int m = group.size();
        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(minProfit + 1)));

        for (int i = 0; i <= n; ++i) {
            dp[0][i][0] = 1;
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= minProfit; ++k) {
                    dp[i][j][k] = dp[i - 1][j][k];

                    if (j >= group[i - 1]) {
                        dp[i][j][k] += dp[i - 1][j - group[i - 1]][max(k - profit[i - 1], 0)];
                    }
                    dp[i][j][k] %= mod;
                }
            }
        }
        return dp[m][n][minProfit];
    }
    
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int m = group.size();
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        
        for (int i = 1; i <= m; ++i) {
            for (int j = n; j >= group[i - 1]; --j) {
                for (int k = minProfit; k >= 0; --k) {
                    dp[j][k] += dp[j - group[i - 1]][max(k - profit[i - 1], 0)];
                    dp[j][k] %= mod;
                }
            }
        }
        return dp[n][minProfit];
    }
    
 private:
    static const int mod = 1e9 + 7;
};c
````

