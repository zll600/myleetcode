# [714. Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

You are given an array `prices` where `prices[i]` is the price of a given stock on the `ith` day, and an integer `fee` representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

**Example 1:**

```
Input: prices = [1,3,2,8,4,9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
- Buying at prices[0] = 1
- Selling at prices[3] = 8
- Buying at prices[4] = 4
- Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
```

**Example 2:**

```
Input: prices = [1,3,7,5,10,3], fee = 3
Output: 6
```

 

**Constraints:**

- `1 <= prices.length <= 5 * 104`
- `1 <= prices[i] < 5 * 104`
- `0 <= fee < 5 * 104`

## 题目大意

给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费

## 解题思路

这道题目和第 122 题相同，多了一个计算手续费的过程，这里我们规定在买入股票的时候计算手续费

### 解法1

* 状态定义：`dp[i][j]`表示 [0, i] 区间内，状态为j 时的利润，其中 j 的定义如下：
  * 0 表示当前不持有股票
  * 1 表示当前持有股票
* 状态转移方程，参考代码
* 初始化：`dp[0][0] = 0`表示第 0 天，不持有股票的情况，此时利润为0，`dp[0][1] = -prices[0] - fee`，表示第 0 天，持有股票，此时需要计算手续费

````c++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int size = prices.size();
        if (size < 2) {
            return 0;
        }
        
        // 这里我们规定在卖出股票的时候计算手续费
        vector<vector<int>> dp(size, vector<int>(2));
        dp[0][0] = 0;
        dp[0][1] = -prices[0] - fee;
        
        for (int i = 1; i < size; i++) {
            // 当前不持有股票
            // 1、前一天不持有股票
            // 2、前一天持有股票，卖出
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            
            // 当前持有股票
            // 1、前一天不持有股票，今天买入，
            // 2、前一天持有股票，
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i] - fee);
        }
        
        return dp[size - 1][0];
    }
};
````

#### 优化

这里利用有限变量，去掉了状态数组的第一个维度

````c++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int size = prices.size();
        if (size < 2) {
            return 0;
        }
        
        vector<int> dp(2);
        dp[0] = 0;
        dp[1] = -prices[0] - fee;
        
        int pre_zero = dp[0];
        int pre_one = dp[1];
        for (int i = 1; i < size; i++) {
            dp[0] = max(dp[0], pre_one + prices[i]);
            dp[1] = max(dp[1], pre_zero - prices[i] - fee);
            
            pre_zero = dp[0];
            pre_one = dp[1];
        }
        
        return dp[0];
    }
};
````

