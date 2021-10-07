# [309. Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

## 题目

You are given an array `prices` where `prices[i]` is the price of a given stock on the `ith` day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:

- After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

**Example 1:**

```
Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
```

**Example 2:**

```
Input: prices = [1]
Output: 0
```

 

**Constraints:**

- `1 <= prices.length <= 5000`
- `0 <= prices[i] <= 1000`

## 题目大意

给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
**卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)**

## 解题思路

### 解法1

这道题目相比第 122 题多了冷冻期的限制

如果单独把冷冻起用一个状态变量来表示，状态数组必须要再加一个维度，这样不太利于推导状态转移方程，所以这里给持股状态再加一种状态，表示冷冻期

* 状态定义：`dp[i][j]`表示 [0,, i] 区间中，处于 j 状态的利润，其中 j 有三种状态：
  * 0 表示不是因为卖出股票而不持有
  * 1 表示持有股票
  * 2 表示因为卖出股票而不持有（即冷冻期）

* 转移方程：这里可以参考代码
* 初始化：这里的初始化，只要保证，整个递推可以进行下去即可
* 最终结果：在两个不持有股票的结果中，选出最大的一个



`````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        
        vector<vector<int>> dp(prices.size(), vector<int>(3));
        // 初始化，这里的初始化需要保证整个递推可以进行下去
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        dp[0][2] = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            // 当前不持股有两个来源
            // 1、前一天不是因为卖出不持股
            // 2、前一天卖出处于冷冻期
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][2]);
            // 当前持股
            // 1、前一天持股
            // 2、前一天不是因为卖出不持股，不处于冷冻期
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
            // 当前处于卖出而处于冷冻期
            // 前一天持股，
            dp[i][2] = dp[i - 1][1] + prices[i];
        }
        
        // 最终结果可能来自于
        // 1、不是因为卖出而不持有股票
        // 2、因为卖出而处于冷冻期
        return max(dp[prices.size() - 1][0], dp[prices.size() - 1][2]);
    }
};
`````

### 优化

使用滚动数组进行空间优化

`````c++
class Solution {
public:    
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        
        vector<vector<int>> dp(2, vector<int>(3));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        dp[0][2] = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            dp[i % 2][0] = max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][2]);
            dp[i % 2][1] = max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][0] - prices[i]);
            dp[i % 2][2] = dp[(i - 1) % 2][1] + prices[i];
        }
        
        return max(dp[(prices.size() - 1) % 2][0], dp[(prices.size() - 1) % 2][2]);
    }
};
`````

### 优化

可以使用有限的变量来替代第一个维度

`````c++
class Solution {
public:    
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        
        vector<int> dp(3);
        dp[0] = 0;
        dp[1] = -prices[0];
        dp[2] = 0;
        
        int pre_zero = dp[0];
        int pre_one = dp[1];
        for (int i = 1; i < prices.size(); i++) {
            dp[0] = max(dp[0], dp[2]);
            dp[1] = max(dp[1], pre_zero - prices[i]);
            dp[2] = pre_one + prices[i];
            
            pre_zero = dp[0];
            pre_one = dp[1];
        }
        
        return max(dp[0], dp[2]);
    }
};
`````

