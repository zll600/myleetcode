# [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

## 题目

You are given an array `prices` where `prices[i]` is the price of a given stock on the `ith` day.

You want to maximize your profit by choosing a **single day** to buy one stock and choosing a **different day in the future** to sell that stock.

Return *the maximum profit you can achieve from this transaction*. If you cannot achieve any profit, return `0`.

 

**Example 1:**

```
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
```

**Example 2:**

```
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
```

 

**Constraints:**

- `1 <= prices.length <= 105`
- `0 <= prices[i] <= 104`

## 题目大意

给定一个数组 prices 其中 prices[i] 是一支给定股票第 i 天的价格，

你想通过在某一天买入一支股票然后在未来的某一天卖出来获得最大利润

返回通过这次交易您呢个获得的最大利润，如果你不能获得任何利润，返回0，

## 解题思路

这道题就是著名的股票问题

### 解法1（暴力（TLE））

这里需要特别注意的就是对边界情况的处理，此时是不能发生交易的

`````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {  // 特殊情况，不能发生交易
            return 0;
        }
        
        // 枚举所有的结果
        int res = 0;
        for (int i = 0; i < prices.size() - 1; i++) {
            for (int j = i + 1; j < prices.size(); j++) {
                res = max(res, prices[j] - prices[i]);
            }
        }
        
        return res;
    }
};
`````

### 解法2（动态规划）

动态规划的做法，可以参考这篇题解：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/bao-li-mei-ju-dong-tai-gui-hua-chai-fen-si-xiang-b/

这里买卖股票有两个限制：

* 卖出股票之前必须持有股票
* 只能进行最多一次交易

因此这道题的状态转移涉及到两个变量，一是当前是第几天，二是持有股票的状态

* 状态定义：
  * `dp[i][0]`表示当前不持股
  * `dp[i][1]`表示当前持股
  * **注意**：这个状态具有前缀性质，下标为 `i` 的这一天的计算结果包含了区间 `[0, i]` 所有的信息，因此最后输出 `dp[len - 1][0]`
* 状态转移方程：
  * 如果当前不持股：
    * 前一天就不持股
    * 前一天持股，今天卖出
  * 如果当前持股：
    * 前一天已经持股
    * 前一天没有持股，今天买入
* 初始化：
  * 第 0 天买入
  * 第 0 天不买入



`````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {  // 特殊情况，不能发生交易
            return 0;
        }
        
        int size = prices.size();
        vector<vector<int>> dp(size, vector<int>(2));
        // dp[i][0] 表示第 i 天不持股的利润
        // dp[i][1] 表示第 i 天持股的利润
        
        dp[0][0] = 0;  // 第 0 天不买
        dp[0][1] = -prices[0];  // 第 0 天买
        
        for (int i = 1; i < size; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], -prices[i]);
        }
        
        return dp[size - 1][0];
    }
};
`````

#### 解法2优化

因为当前的状态之取决于前一天的状态，因此可以使用滚动数组

`````class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {  // 特殊情况，不能发生交易
            return 0;
        }
        
        int size = prices.size();
        vector<vector<int>> dp(2, vector<int>(2));
        
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        
        for (int i = 1; i < size; i++) {
            dp[i % 2][0] = max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1] + prices[i]);
            dp[i % 2][1] = max(dp[(i - 1) % 2][1], -prices[i]); 
        }
        
        return dp[(size - 1) % 2][0];
    }
};`
`````

**说明**：`% 2` 还可以写成 `& 1`

### 解法2优化

**注意空间优化只看状态转移方程**

`````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {  // 特殊情况，不能发生交易
            return 0;
        }
        
        vector<int> dp(2);
        dp[0] = 0;  // 不持有股票
        dp[1] = -prices[0];  // 持有股票
        
        for (int i = 1; i < prices.size(); i++) {
            dp[0] = max(dp[0], dp[1] + prices[i]);
            dp[1] = max(dp[1], -prices[i]);
        }
        
        return dp[0];
    }
};
`````

