# [983. Minimum Cost For Tickets](https://leetcode-cn.com/problems/minimum-cost-for-tickets/)

## 题目

You have  planned some train traveling one year in advance. The days of the year  in which you will travel are given as an integer array `days`. Each day is an integer from `1` to `365`.

Train tickets are sold in **three different ways**:

- a **1-day** pass is sold for `costs[0]` dollars,
- a **7-day** pass is sold for `costs[1]` dollars, and
- a **30-day** pass is sold for `costs[2]` dollars.

The passes allow that many days of consecutive travel.

- For example, if we get a **7-day** pass on day `2`, then we can travel for `7` days: `2`, `3`, `4`, `5`, `6`, `7`, and `8`.

Return *the minimum number of dollars you need to travel every day in the given list of days*.

 

**Example 1:**

```
Input: days = [1,4,6,7,8,20], costs = [2,7,15]
Output: 11
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
In total, you spent $11 and covered all the days of your travel.
```

**Example 2:**

```
Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
Output: 17
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
In total, you spent $17 and covered all the days of your travel.
```

 

**Constraints:**

- `1 <= days.length <= 365`
- `1 <= days[i] <= 365`
- `days` is in strictly increasing order.
- `costs.length == 3`
- `1 <= costs[i] <= 1000`

## 题目大意

在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行。在接下来的一年里，你要旅行的日子将以一个名为 `days` 的数组给出。每一项是一个从 `1` 到 `365` 的整数。

火车票有 三种不同的销售方式 ：

- 一张 *为期一天* 的通行证售价为 `costs[0]` 美元；
- 一张 *为期七天* 的通行证售价为 `costs[1]` 美元；
- 一张 *为期三十天* 的通行证售价为 `costs[2]` 美元。

通行证允许数天无限制的旅行。 例如，如果我们在第 `2` 天获得一张 为期 `7` 天 的通行证，那么我们可以连着旅行 `7` 天：第 `2` 天、第 `3` 天、第 `4` 天、第 `5` 天、第 `6` 天、第 `7` 天和第 `8` 天。

返回 你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费

## 解题思路

Minimum (Maximum) Path to Reach a Target

### Solution 1: DP

这里注意一下状态转移的写法，i - 7 和 i - 30 可能是在第一个 7 天和 第一个 30 天内，此时是由第 0 天（没有实际意义）转移而来的

````c++
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int last = days.back();
        // dp[i]  表示到第 i 天为止的花费
        vector<int> dp(last + 1, 0);

        int idx = 0;
        for (int i = 1; i <= last; ++i) {
            if (i == days[idx]) {
                // 如果当前去旅游
                dp[i] = dp[i - 1] + costs[0];

                dp[i] = min(dp[i - 7 > 0 ? i - 7 : 0] + costs[1], dp[i]);
                dp[i] = min(dp[i], dp[i - 30 > 0 ? i - 30 : 0] + costs[2]);

                ++idx;
            } else {
                // 如果当天不去旅游
                dp[i] = dp[i - 1];
            }
        }

        return dp[last];
    }
};
````


