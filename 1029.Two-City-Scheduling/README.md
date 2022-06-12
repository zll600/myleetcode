# [1029. Two City Scheduling](https://leetcode.cn/problems/two-city-scheduling/)

## 题目

A company is planning to interview `2n` people. Given the array `costs` where `costs[i] = [aCosti, bCosti]`, the cost of flying the `ith` person to city `a` is `aCosti`, and the cost of flying the `ith` person to city `b` is `bCosti`.

Return *the minimum cost to fly every person to a city* such that exactly `n` people arrive in each city.

 

**Example 1:**

```
Input: costs = [[10,20],[30,200],[400,50],[30,20]]
Output: 110
Explanation: 
The first person goes to city A for a cost of 10.
The second person goes to city A for a cost of 30.
The third person goes to city B for a cost of 50.
The fourth person goes to city B for a cost of 20.

The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.
```

**Example 2:**

```
Input: costs = [[259,770],[448,54],[926,667],[184,139],[840,118],[577,469]]
Output: 1859
```

**Example 3:**

```
Input: costs = [[515,563],[451,713],[537,709],[343,819],[855,779],[457,60],[650,359],[631,42]]
Output: 3086
```

 

**Constraints:**

- `2 * n == costs.length`
- `2 <= costs.length <= 100`
- `costs.length` is even.
- `1 <= aCosti, bCosti <= 1000`

## 题目大意

公司计划面试 `2n` 人。给你一个数组 `costs` ，其中 `costs[i] = [aCosti, bCosti]` 。第 `i` 人飞往 `a` 市的费用为 `aCosti` ，飞往 `b` 市的费用为 `bCosti`

返回将每个人都飞到 `a` 、`b` 中某座城市的最低费用，要求每个城市都有 `n` 人抵达

## 解题思路


### Solution 1: 

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/two-city-scheduling/solution/cji-hu-shuang-bai-de-pai-xu-jie-fa-by-ff-boss/)

可以先假设将所有的人飞到 a 地 花费 price0，然后将 n 个人再飞到 b 地，花费price1，那么要使得最终结果最小，就需要使得 price1 - price0 最小

这道题就是要设法将两种花费联系起来，单独按照 aCost 或者 bCost 排序都不能较为容易的解决这道题目

如果还是比较难理解，就看看 [这篇证明](https://leetcode.cn/problems/two-city-scheduling/solution/liang-di-diao-du-zhi-you-hua-suan-fa-by-yi-di-ji-m/)

````c++
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        sort(costs.begin(), costs.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[1] - lhs[0] < rhs[1] - rhs[0];
        });
        
        const int len = costs.size();
        int res = 0;
        for (int i = 0; i < len / 2; ++i) {
            res += costs[i][1];
        }
        for (int i = len / 2; i < len; ++i) {
            res += costs[i][0];
        }
        return res;
    }
};
````
