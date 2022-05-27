# [1744. Can You Eat Your Favorite Candy on Your Favorite Day?](https://leetcode.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/)

## 题目

You are given a **(0-indexed)** array of positive integers `candiesCount` where `candiesCount[i]` represents the number of candies of the `ith` type you have. You are also given a 2D array `queries` where `queries[i] = [favoriteTypei, favoriteDayi, dailyCapi]`.

You play a game with the following rules:

- You start eating candies on day `**0**`.
- You **cannot** eat **any** candy of type `i` unless you have eaten **all** candies of type `i - 1`.
- You must eat **at least** **one** candy per day until you have eaten all the candies.

Construct a boolean array `answer` such that `answer.length == queries.length` and `answer[i]` is `true` if you can eat a candy of type `favoriteTypei` on day `favoriteDayi` without eating **more than** `dailyCapi` candies on **any** day, and `false` otherwise. Note that you can eat different types of candy on the same day, provided that you follow rule 2.

Return *the constructed array* `answer`.

 

**Example 1:**

```
Input: candiesCount = [7,4,5,3,8], queries = [[0,2,2],[4,2,4],[2,13,1000000000]]
Output: [true,false,true]
Explanation:
1- If you eat 2 candies (type 0) on day 0 and 2 candies (type 0) on day 1, you will eat a candy of type 0 on day 2.
2- You can eat at most 4 candies each day.
   If you eat 4 candies every day, you will eat 4 candies (type 0) on day 0 and 4 candies (type 0 and type 1) on day 1.
   On day 2, you can only eat 4 candies (type 1 and type 2), so you cannot eat a candy of type 4 on day 2.
3- If you eat 1 candy each day, you will eat a candy of type 2 on day 13.
```

**Example 2:**

```
Input: candiesCount = [5,2,6,4,1], queries = [[3,1,2],[4,10,3],[3,10,100],[4,100,30],[1,3,1]]
Output: [false,true,true,false,false]
```

 

**Constraints:**

- `1 <= candiesCount.length <= 105`
- `1 <= candiesCount[i] <= 105`
- `1 <= queries.length <= 105`
- `queries[i].length == 3`
- `0 <= favoriteTypei < candiesCount.length`
- `0 <= favoriteDayi <= 109`
- `1 <= dailyCapi <= 109`

## 题目大意

给你一个下标从 `0`  开始的正整数数组 `candiesCount` ，其中 `candiesCount[i]` 表示你拥有的第 `i` 类糖果的数目

同时给你一个二维数组 `queries` ，其中 `queries[i] = [favoriteTypei, favoriteDayi, dailyCapi]` 。你按照如下规则进行一场游戏：

- 你从第 `0` 天开始吃糖果。
- 你在吃完 所有 第 `i - 1` 类糖果之前，不能 吃任何一颗第 i 类糖果。
- 在吃完所有糖果之前，你必须每天 至少 吃 一颗 糖果。

请你构建一个布尔型数组 `answer` ，满足 `answer.length == queries.length` 。`answer[i]` 为 `true` 的条件是：在每天吃 不超过  `dailyCapi` 颗糖果的前提下，你可以在第 `favoriteDayi` 天吃到第 `favoriteTypei` 类糖果；否则  `answer[i]` 为 `false` 。注意，只要满足上面 `3`  条规则中的第二条规则，你就可以在同一天吃不同类型的糖果。请你返回得到的数组 `answer`

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/solution/ni-neng-zai-ni-zui-xi-huan-de-na-tian-ch-ql68/)

首先跟着题目的几个例子，分析一下，就可以得出，这里其实有两个边界，只要在这个范围内，就可以满足条件，然后对比暴力解，这里可以使用前缀和来优化

到第 favoriteDayi 天，可以吃糖果的数量，落在区间 `[favoriteDayi + 1, (favoriteDayi + 1) * dailyCapi]` 中，只要一颗 favoriteTypei 糖果落在这个区间中，既可以满足

然后根据前缀和可以得出每种糖果的范围 `[prefix_sum[favoriteTypei - 1], prefix_sum[favoriteTypei]]`，特殊的 favoriteTypei == 0 时，左边界为 1，然后两个区间取交集就可以了

### Solution 1: PrefixSum


````c++
class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        const int n = candiesCount.size();
        // 前缀和数组
        vector<long long> prefix_sum(n);
        prefix_sum[0] = candiesCount[0];
        for (int i = 1; i < n; ++i) {
            prefix_sum[i] = prefix_sum[i - 1] + candiesCount[i];
        }

        // 遍历来得出结果
        vector<bool> ans;
        for (const auto& query : queries) {
            int favorite_type = query[0], favorite_day = query[1], daily_cap = query[2];

            long long x1 = favorite_day + 1, y1 = x1 * daily_cap;
            long long x2 = favorite_type == 0 ? 1 : prefix_sum[favorite_type - 1] + 1, y2 = prefix_sum[favorite_type];

            // 通过判断不相交取反
            ans.push_back(!(x1 > y2 || x2 > y1));
        }
        return ans;
    }
};
````



