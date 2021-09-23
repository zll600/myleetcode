# [1833. Maximum Ice Cream Bars](https://leetcode.com/problems/maximum-ice-cream-bars/)

## 题目

It is a sweltering summer day, and a boy wants to buy some ice cream bars.

At the store, there are `n` ice cream bars. You are given an array `costs` of length `n`, where `costs[i]` is the price of the `ith` ice cream bar in coins. The boy initially has `coins` coins to spend, and he wants to buy as many ice cream bars as possible. 

Return *the **maximum** number of ice cream bars the boy can buy with* `coins` *coins.*

**Note:** The boy can buy the ice cream bars in any order.

 

**Example 1:**

```
Input: costs = [1,3,2,4,1], coins = 7
Output: 4
Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.
```

**Example 2:**

```
Input: costs = [10,6,8,7,7,8], coins = 5
Output: 0
Explanation: The boy cannot afford any of the ice cream bars.
```

**Example 3:**

```
Input: costs = [1,6,3,1,2,5], coins = 20
Output: 6
Explanation: The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1 + 2 + 5 = 18.
```

 

**Constraints:**

- `costs.length == n`
- `1 <= n <= 105`
- `1 <= costs[i] <= 105`
- `1 <= coins <= 108`

## 题目大意

夏日炎炎，小男孩 Tony 想买一些雪糕消消暑。

在商店里，有 n 个雪糕，一个长度为 n 的数组 cost 表示每个雪糕的价格，其中 cost[i] 表示第 i 个雪糕的价格，这个小男孩初始时有 coins 的钱，他想买尽可能多的雪糕，

返回这个小男孩用 coins 的钱可以买到的最多的雪糕，

## 解题思路

这道题目可以用贪心来解决，思路也不难，每次尽量先买小的，买的数目就是最多的，

* 但是这道题其实也是一道 01 背包的题目，不过，我确实没有想到，这里的具体分析及贪心的证明思路，可以参考这篇题解：https://leetcode-cn.com/problems/maximum-ice-cream-bars/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-yrhjx/

## 代码

`````c++
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(), costs.end());
        
        int res = 0;
        for (int cost : costs) {
            if (coins >= cost) {
                coins -= cost;
                ++res;
            } else {    // 如果当前的都买不了，后面的也肯定买不了了
                break;
            }
        }
        
        return res;
    }
};
`````

