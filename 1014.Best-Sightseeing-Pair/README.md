# [1014. Best Sightseeing Pair](https://leetcode.cn/problems/best-sightseeing-pair/)

## 题目

You are given an integer array `values` where values[i] represents the value of the `ith` sightseeing spot. Two sightseeing spots `i` and `j` have a **distance** `j - i` between them.

The score of a pair (`i < j`) of sightseeing spots is `values[i] + values[j] + i - j`: the sum of the values of the sightseeing spots, minus the distance between them.

Return *the maximum score of a pair of sightseeing spots*.

 

**Example 1:**

```
Input: values = [8,1,5,2,6]
Output: 11
Explanation: i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11
```

**Example 2:**

```
Input: values = [1,2]
Output: 2
```

 

**Constraints:**

- `2 <= values.length <= 5 * 104`
- `1 <= values[i] <= 1000`

## 题目大意

给你一个正整数数组 `values`，其中 `values[i]` 表示第 `i` 个观光景点的评分，并且两个景点 `i` 和 `j` 之间的 距离 为 `j - i`

一对景点 `（i < j）` 组成的观光组合的得分为 `values[i] + values[j] + i - j` ，也就是景点的评分之和 减去 它们两者之间的距离

返回一对观光景点能取得的最高分

## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/best-sightseeing-pair/solution/python-jie-fa-by-jiayangwu/)

这道题目的暴力解法不难想到是两层循环来做，

但是内层循环的次数会逐渐减少，所以这里利用一个变量维护遍历过的最大值，这样变化的就只有 `values[j] 和 j` 了，这样只需一层循环就可以了

````c++
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int res = 0;
        int pre_max = values[0];

        for (int i = 1; i < values.size(); ++i) {
            res = max(res, pre_max + values[i] - i);
            pre_max = max(pre_max, values[i] + i);
        }
        return res;
    }
};
````
