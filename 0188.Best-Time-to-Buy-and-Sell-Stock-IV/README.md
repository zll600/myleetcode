# [188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)

## 题目

You are given an integer array `prices` where `prices[i]` is the price of a given stock on the `ith` day, and an integer `k`.

Find the maximum profit you can achieve. You may complete at most `k` transactions.

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

**Example 1:**

```
Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
```

**Example 2:**

```
Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
```

 

**Constraints:**

- `0 <= k <= 100`
- `0 <= prices.length <= 1000`
- `0 <= prices[i] <= 1000`

## 题目大意

给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 ### 解题思路

这道题目对比 122 题，多了一个限制条件，即最多只能交易 k 次，所以我们需要将交易次数，设为一个维度

这里放上一篇参考的题解：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/solution/dong-tai-gui-hua-by-liweiwei1419-4/

### 解法1

* 理解状态转移方程：
  * 人为规定：如果当天买入股票的时候记录「交易发生一次」，如果当天卖出股票，不增加交易次数；
  * 买入股票，手上持有的现金数减少（减去当天股价），相应地，卖出股票，手上持有的现金数增加（加上当天股价）；
  * 难点：还没发生的交易，并且还规定了当天必须持股的状态值应该设置为负无穷。

`````c++
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        // 边界情况
        if (k == 0 || prices.size() < 2) {
            return 0;
        }
        
        // 每次交易至少需要两天
        // 如果交易次数大于天数的一半，可以认为最多无数次，转化为第 122 题
        // 这里使用贪心来解决
        if (k > prices.size() / 2) {
            return Greedy(prices);
        }
        
        // 状态数组
        // 第一维表示第 i - 1 天的情况，这里设为 prices.size() + 1,
        // 第二维表示第 j 次交易, 这里设为 j + 1,
        // 第三维表示持股的状态
        vector<vector<vector<int>>> dp(prices.size() + 1, vector<vector<int>>(k + 1, vector<int>({0, INT_MIN})));
        /*
        
        // 初始化
        // 将所有持有股票的状态设为 无穷小，不能影响状态转移
        for (int i = 0; i < prices.size(); i++) {
            for (int j = 0; j < prices.size(); j++) {
                dp[i][j][1] = INT_MIN;
            }
        }*/
        
        for (int i = 1; i <= prices.size(); i++) {
            for (int j = 1; j <= k; j++) {
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i - 1]);
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
            }
        }
        
        // 第一维和第二维的状态都有前缀性质，直接输出不持股的最后一个状态即可
        return dp[prices.size()][k][0];
    }
    
 private:
    int Greedy(const vector<int>& prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            res += max(prices[i] - prices[i - 1], 0);
        }
        
        return res;
    }
};
`````

####  解法1空间优化

因为今天的状态只参考了昨天，所以可以直接去掉第一个维度

`````c++
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        // 边界情况
        if (k == 0 || prices.size() < 2) {
            return 0;
        }
        
        // 每次交易至少需要两天
        // 如果交易次数大于天数的一半，可以认为最多无数次，转化为第 122 题
        // 这里使用贪心来解决
        if (k > prices.size() / 2) {
            return Greedy(prices);
        }
        

        vector<vector<int>> dp(k + 1, vector<int>({0, INT_MIN}));
        
        for (int i = 1; i <= prices.size(); i++) {
            for (int j = 1; j <= k; j++) {
                dp[j][1] = max(dp[j][1], dp[j - 1][0] - prices[i - 1]);
                dp[j][0] = max(dp[j][0], dp[j][1] + prices[i - 1]);
            }
        }
        
        return dp[k][0];
    }
    
 private:
    int Greedy(const vector<int>& prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            res += max(prices[i] - prices[i - 1], 0);
        }
        
        return res;
    }
};
`````

### 解法2

状态定义于上面有所不同

````c++
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        // 边界情况
        if (k == 0 || prices.size() < 2) {
            return 0;
        }
        
        if (k >= prices.size() / 2) {
            return Greedy(prices);
        }
        
        vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(k + 1, vector<int>(2)));
        for (int i = 0; i <= k; i++) {
            dp[0][i][0] = 0;
            dp[0][i][1] = -prices[0];
        }
        
        
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 1; j <= k; j++) {
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
            }
        }
        
        return dp[prices.size() - 1][k][0];
    }
    
 private:
    int Greedy(const vector<int>& prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            res += max(prices[i] - prices[i - 1], 0);
        }
        
        return res;
    }
};
````

