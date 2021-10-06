# [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)

## 题目

You are given an integer array `prices` where `prices[i]` is the price of a given stock on the `ith` day.

On each day, you may decide to buy and/or sell the stock. You can only hold **at most one** share of the stock at any time. However, you can buy it then immediately sell it on the **same day**.

Find and return *the **maximum** profit you can achieve*.

 

**Example 1:**

```
Input: prices = [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Total profit is 4 + 3 = 7.
```

**Example 2:**

```
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Total profit is 4.
```

**Example 3:**

```
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.
```

 

**Constraints:**

- `1 <= prices.length <= 3 * 104`
- `0 <= prices[i] <= 104`

## 题目大意

给定一个整数数组prices，其中 prices[i] 表示第 i 天的股票价格，

每一天，你可以决定买入或者卖出股票，任何时候，你最多只能持有一支股票，设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

返回你可以得到的最大的利润，

## 解题思路

这道题目是股票系列的第二到题目，相比 第122 题，这道题交易次数是无限次，因此可以交易无数次，

这道题可以参考这篇题解：https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/submissions/

### 解法1（DFS（TLE））

使用最简单的方法，枚举所有可能出现的结果，

``````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        
        res = 0;
        DFS(prices, 0, 0, 0);
        return res;
    }
    
 private:
    int res;
    
    void DFS(const vector<int>& prices, int idx, int status, int profit) {
        if (idx == price.size()) {  // 遍历完整个数组，得到答案
            res = max(res, profit);
            return;
        }
        
        // 维持前一天的状态
        DFS(prices, idx + 1, status, profit);
        
        // 这个分支只会走一条路
        // 改变前一天的状态
        if (status == 0) {
            DFS(prices, idx + 1, 1, profit - nums[idx]);
        } else {
            DFS(prices, idx + 1, 0, profit + nums[idx]);
        }
    }
};
``````

### 解法2（动态规划）

状态定义： `dp[i][0]`表示第 i 天不持有股票时的利润，`dp[i][1]`表示第 i 天持有股票时的利润

状态转移、初始化可以参考代码

``````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {  // 边界判断
            return 0;
        }
        
        vector<vector<int>> dp(prices.size(), vector<int>(2));
        dp[0][0] = 0;  // 初始化，第 0 天不持有股票
        dp[0][1] = -prices[0];  // 第 0 天持有股票，此时利润为负
        
        for (int i = 1; i < prices.size(); i++) {
            // 第 i 天不持有股票，来自
            // 第 i - 1 天不持有股票
            // 第 i - 1 天持有股票
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            
            // 第 i 天不持有股票，来自
            // 第 i - 1 天持有股票
            // 第 i - 1 天不持有股票
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        
        return dp[prices.size() - 1][0];
    }
};
``````

### 解法3

将状态数组分开来定义

`````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {  // 边界判断
            return 0;
        }
        
        // 持有现金
        vector<int> cash(prices.size());
        cash[0] = 0;
        // 持有股票
        vector<int> hold(prices.size());
        hold[0] = -prices[0];
        
        for (int i = 1; i < prices.size(); i++) {
            // 今天持有的现金
            // 前天持有的现金
            // 前天的股票卖出
            cash[i] = max(cash[i - 1], hold[i - 1] + prices[i]);
            // 金台你持有股票
            // 前天持有的股票
            // 前天的现金买入
            hold[i] = max(hold[i - 1], cash[i - 1] - prices[i]);
        }
        
        return cash[prices.size() - 1];
    }
};
`````

### 解法3优化

将两个 状态数组使用有限的变量来代替，因为当前这一天的状态只由前一天转移而来

````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {  // 边界判断
            return 0;
        }
        
        int cash = 0;  // 持有现金
        int hold = -prices[0];  // 持有股票
        
        int pre_cash = cash;  // 前一天的 cash
        int pre_hold = hold;  // 前一天的 hold
        for (int i = 1; i < prices.size(); i++) {
            cash = max(cash, pre_hold + prices[i]);
            hold = max(hold, pre_cash - prices[i]);
            pre_cash = cash;
            pre_hold = hold;
        }
        
        return cash;
    }
};
````

###  解法4（贪心）

贪心的策略来自于：不限制交易次数，则只要今天比昨天股价高，就交易

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {  // 边界判断
            return 0;
        }
        
        int res = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            // 对于 今天 - 昨天
            // 只加正的
            res += max(prices[i] - prices[i - 1], 0);
        }
        
        return res;
    }
};
```

