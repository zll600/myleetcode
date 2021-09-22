# [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)

## 题目

Given an array of `intervals` where `intervals[i] = [starti, endi]`, merge all overlapping intervals, and return *an array of the non-overlapping intervals that cover all the intervals in the input*.

 

**Example 1:**

```
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
```

**Example 2:**

```
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
```

 

**Constraints:**

- `1 <= intervals.length <= 104`
- `intervals[i].length == 2`
- `0 <= starti <= endi <= 104`

## 题目大意

给定一个数组 intervals，其中 intervals[i] = [starti, endi]，合并所有重叠的 intervals，然后没有重叠 intervals 通过覆盖输入

## 解题思路

区间类问题一般需要画图来进行思考的，这篇题解中有需要画图思考的相关的算法题：https://leetcode-cn.com/problems/merge-intervals/solution/tan-xin-suan-fa-java-by-liweiwei1419-3/

这道题也是用贪心的思想来解决的，具体步骤是先按照区间的左端点按照升序排序，判断下一个区间的左端点和结果集中最后一个区间的右端点的大小，

这里注意在合并区间的时候，新的右边界取的是二者中的最大值

* note ：这道题的 C++ 代码写的不是很理想，以后修正

## 代码

`````c++
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() < 2) {
            return intervals;
        }
        
        // 按照每个区间的左端点升序排序
        sort(intervals.begin(), intervals.end(), [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            return lhs[0] < rhs[0];
        });
        
        int size = intervals.size();
        vector<vector<int>> res;
        res.push_back(intervals[0]);
        
        for (int i = 1; i < intervals.size(); ++i) {
            // 拿出队尾的那一项
            vector<int> tmp = res.back();
            
            if (intervals[i][0] > tmp[1]) {
                res.push_back(intervals[i]);
            } else {
                // 注意这里应该取二者中的最大值
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
        }
        
        
        return res;
    }
};
`````



