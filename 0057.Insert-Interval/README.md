# [57. Insert Interval](https://leetcode-cn.com/problems/insert-interval/)

## 题目

You are given an array of non-overlapping intervals `intervals` where `intervals[i] = [starti, endi]` represent the start and the end of the `ith` interval and `intervals` is sorted in ascending order by `starti`. You are also given an interval `newInterval = [start, end]` that represents the start and end of another interval.

Insert `newInterval` into `intervals` such that `intervals` is still sorted in ascending order by `starti` and `intervals` still does not have any overlapping intervals (merge overlapping intervals if necessary).

Return `intervals` *after the insertion*.

 

**Example 1:**

```
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
```

**Example 2:**

```
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
```

**Example 3:**

```
Input: intervals = [], newInterval = [5,7]
Output: [[5,7]]
```

**Example 4:**

```
Input: intervals = [[1,5]], newInterval = [2,3]
Output: [[1,5]]
```

**Example 5:**

```
Input: intervals = [[1,5]], newInterval = [2,7]
Output: [[1,7]]
```

 

**Constraints:**

- `0 <= intervals.length <= 104`
- `intervals[i].length == 2`
- `0 <= starti <= endi <= 105`
- `intervals` is sorted by `starti` in **ascending** order.
- `newInterval.length == 2`
- `0 <= start <= end <= 105`

## 题目大意

给出多个没有重叠的区间，然后再给一个区间，要求把如果有重叠的区间进行合并

## 解题思路

这道题目可以联系第 56 题一起来做，比较像

### Solution 1:

这种解法可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0001~0099/0057.Insert-Interval/

这种解法的思路，是将整个过程分为3 个部分来做，第一个部分，不涉及到合并区间，第二部分需要合并区间，第三部分添加剩余的元素

````c++
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& new_interval) {
        vector<vector<int>> res;
        if (intervals.empty()) {  // 边界情况，
            res.push_back(new_interval);
            return res;
        }
        const int size = intervals.size();
        int idx = 0;
        // 遍历需要合并之前的部分，注意这里的比较条件
        while (idx < size && intervals[idx].back() < new_interval.front()) {
            res.push_back(intervals[idx]);
            ++idx;
        }
        // 遍历需要合并的部分，注意这里的比较条件
        while (idx < size && intervals[idx].front() <= new_interval.back()) {
            new_interval[0] = min(intervals[idx][0], new_interval[0]);
            new_interval[1] = max(intervals[idx][1], new_interval[1]);
            ++idx;
        }
        res.push_back(new_interval);
        
        // 添加剩余部分
        while (idx < size) {
            res.push_back(intervals[idx]);
            ++idx;
        }
        
        return res;
    }
};
````

