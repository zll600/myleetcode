# [1288. Remove Covered Intervals](https://leetcode.cn/problems/remove-covered-intervals/)

## 题目

Given an array `intervals` where `intervals[i] = [li, ri]` represent the interval `[li, ri)`, remove all intervals that are covered by another interval in the list.

The interval `[a, b)` is covered by the interval `[c, d)` if and only if `c <= a` and `b <= d`.

Return *the number of remaining intervals*.

 

**Example 1:**

```
Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
```

**Example 2:**

```
Input: intervals = [[1,4],[2,3]]
Output: 1
```

 

**Constraints:**

- `1 <= intervals.length <= 1000`
- `intervals[i].length == 2`
- `0 <= li < ri <= 105`
- All the given intervals are **unique**.



### 题目大意

给你一个区间列表，请你删除列表中被其他区间所覆盖的区间。

只有当 `c <= a` 且 `b <= d` 时，我们才认为区间 `[a,b)` 被区间 `[c,d)` 覆盖

在完成所有删除操作后，请你返回列表中剩余区间的数目

#### Solution 1:

这道题目可以利用类似单调栈的思想来做，先将 `intervals` 数组排序

排序规则是：先按照 left 升序排序，left 相同的按照 right 降序排序，然后将第一个元素入栈，依次遍历元素进行判断（好像这个 栈也可以优化掉，使用两个变量即可 ^-^）

````c++
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            if (lhs[0] == rhs[0]) {
                return lhs[1] > rhs[1];
            }
            return lhs[0] < rhs[0];
        });
        
        stack<pair<int, int>> sta;
        sta.emplace(intervals[0][0], intervals[0][1]);
        
        const int len = intervals.size();
        for (int i = 0; i < len; ++i) {
            auto cur = sta.top();
            if (cur.first <= intervals[i][0] && cur.second >= intervals[i][1]) {
                continue;
            }
            sta.emplace(intervals[i][0], intervals[i][1]);
        }
        return sta.size();
    }
};
````

