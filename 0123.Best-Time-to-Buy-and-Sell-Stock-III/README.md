# [123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)

## 题目

You are given an array `prices` where `prices[i]` is the price of a given stock on the `ith` day.

Find the maximum profit you can achieve. You may complete **at most two transactions**.

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

**Example 1:**

```
Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
```

**Example 2:**

```
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
```

**Example 3:**

```
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
```

**Example 4:**

```
Input: prices = [1]
Output: 0
```

 

**Constraints:**

- `1 <= prices.length <= 105`
- `0 <= prices[i] <= 105`

## 题目大意

给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

## 解题思路

这道题相比第 122 题多了一个状态变量，我们需要考虑交易次数的限制

### 解法1（动态规划）

* 状态定义：`dp[i][j][k]`表示，在区间 [0, i] 中，进行了 j 次交易，状态为 k 是的利润，其中

  * j 代表第几次交易：
    * 0 表示没有发生交易
    * 1 表示当前k的状态处于第 1 次交易
    * 2 表示当前k 的状态处于第 2 次交易

  * k 表示持有股票的状态：
    * 0 表示没有持有股票
    * 1 表示持有股票

* 状态转移方程：参考代码
* 初始化：我个人的观点是初始化，必须要能让整个递推进行下去，所以可以根据状态转移方程来进行初始化，还可以考虑实际意义，我通常采用二者结合
  * 对于这道题目来说，想要使的递推进行下去，只需要设置两个值，其余默认即可
    * `dp[0][1][1] = prices[0]` 表示第 0 天，处于第 1 次交易时，持股，代码中的第一个递推要用到
    * `dp[0][2][1] = INT_MIN` 表示第 0 天，处于第2 次交易中，持股，根据实际意义来说，这是不可能的，但是为了让递推进行下去，所以要设一个初值
  * 其余初值的解释
    * `dp[0][0][0] = 0` 表示第0 天，处于第 0 次交易，不持股，这显然不可能，而且递推用不到，所以默认0 即可
    * `dp[0][0][1] = 0`表示第0 天，处于第 0 次交易，持股，这显然不可能，而且递推用不到，所以默认 0 即可
    * `dp[0][1][0] = 0` 表示第0 天，处于第 1 次交易，不持股，**这个不影响，递推要用到**，但是初始化为 0 即可（或许这里初始化为负无穷更好一点）
    * `dp[0][2][0] = 0`表示第 0 天，处于第2 次交易，不持股，**这个显然不可能，但是递推要用到**，所以默认为0 即可（或许这里初始化为负无穷更好一点）

`````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        // 第一维表示第 i 天
        // 第二维表示处于第 j 次交易，显然 0 没有意义，起码处于第一次交易中
        // 第三维表示持股的状态
        vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(3, vector<int>(2)));
        dp[0][1][1] = -prices[0];  // 第 0 天，处于第一次交易中，持股
        dp[0][2][1] = INT_MIN;  // 第 0 天，处于第二次交易中，持股，显然不可能存在这种情况，但是状态转移需要用到，
                                // 所以这里必须设定初值（要求是不影响状态转移即可，
                                // 这道题中只要保证比 dp[i][1][0] + prices[i] 小即可），只是为了递推下去，
        
        
        for (int i = 1; i < prices.size(); i++) {
            // 每一次交易，必须现持股，然后才能不持股，这里的顺序不能颠倒
            dp[i][1][1] = max(dp[i - 1][1][1], -prices[i]);
            dp[i][1][0] = max(dp[i - 1][1][0], dp[i][1][1] + prices[i]);
            dp[i][2][1] = max(dp[i - 1][2][1], dp[i][1][0] - prices[i]);
            dp[i][2][0] = max(dp[i - 1][2][0], dp[i][2][1] + prices[i]);
        }
        
        return max(dp[prices.size() - 1][1][0], dp[prices.size() - 1][2][0]);
    }
};
`````

### 优化

````c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        
        // 使用滚动数组惊醒优化 
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(3, vector<int>(2)));
        dp[0][1][1] = -prices[0];
        dp[0][2][1] = INT_MIN;
        for (int i = 1; i < prices.size(); i++) {
            dp[i % 2][1][1] = max(dp[(i - 1) % 2][1][1], -prices[i]);
            dp[i % 2][1][0] = max(dp[(i - 1) % 2][1][0], dp[(i - 1) % 2][1][1] + prices[i]);
            dp[i % 2][2][1] = max(dp[(i - 1) % 2][2][1], dp[(i - 1) % 2][1][0] - prices[i]);
            dp[i % 2][2][0] = max(dp[(i - 1) % 2][2][0], dp[(i - 1) % 2][2][1] + prices[i]);
        }
        
        return max(dp[(prices.size() - 1) % 2][1][0], dp[(prices.size() - 1) % 2][2][0]);
    }
};
````

### 优化

因为今天值参考了昨天的状态，这里的代码直接去掉了一维

````java
public class Solution {

    public int maxProfit(int[] prices) {
        int len = prices.length;
        if (len < 2) {
            return 0;
        }

        int[][] dp = new int[3][2];
        dp[1][1] = -prices[0];
        dp[2][1] = Integer.MIN_VALUE;
        for (int i = 1; i < len; i++) {
            dp[1][1] = Math.max(dp[1][1], -prices[i]);
            dp[1][0] = Math.max(dp[1][0], dp[1][1] + prices[i]);
            dp[2][1] = Math.max(dp[2][1], dp[1][0] - prices[i]);
            dp[2][0] = Math.max(dp[2][0], dp[2][1] + prices[i]);
        }
        return Math.max(dp[1][0], dp[2][0]);
    }
}
````

