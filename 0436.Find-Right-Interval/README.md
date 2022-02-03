# [436. Find Right Interval](https://leetcode.com/problems/find-right-interval/)

## 题目

You are given an array of `intervals`, where `intervals[i] = [starti, endi]` and each `starti` is **unique**.

The **right** **interval** for an interval `i` is an interval `j` such that `startj`` >= endi` and `startj` is **minimized**.

Return *an array of **right interval** indices for each interval `i`*. If no **right interval** exists for interval `i`, then put `-1` at index `i`.

 

**Example 1:**

```
Input: intervals = [[1,2]]
Output: [-1]
Explanation: There is only one interval in the collection, so it outputs -1.
```

**Example 2:**

```
Input: intervals = [[3,4],[2,3],[1,2]]
Output: [-1,0,1]
Explanation: There is no right interval for [3,4].
The right interval for [2,3] is [3,4] since start0 = 3 is the smallest start that is >= end1 = 3.
The right interval for [1,2] is [2,3] since start1 = 2 is the smallest start that is >= end2 = 2.
```

**Example 3:**

```
Input: intervals = [[1,4],[2,3],[3,4]]
Output: [-1,2,-1]
Explanation: There is no right interval for [1,4] and [3,4].
The right interval for [2,3] is [3,4] since start2 = 3 is the smallest start that is >= end1 = 3.
```

 

**Constraints:**

- `1 <= intervals.length <= 2 * 104`
- `intervals[i].length == 2`
- `-106 <= starti <= endi <= 106`
- The start point of each interval is **unique**.

## 题目大意

给定一组区间，对于每一个区间 i，检查是否存在一个区间 j，它的起始点大于或等于区间 i 的终点，这可以称为 j 在 i 的“右侧”。

对于任何区间，你需要存储的满足条件的区间 j 的最小索引，这意味着区间 j 有最小的起始点可以使其成为“右侧”区间。如果区间 j 不存在，则将区间 i 存储为 -1。最后，你需要输出一个值为存储的区间值的数组。



给定一组区间 `intervals`,其中 `intervals[i] = [starti, endi]`，每一个 `starti` 都是唯一的。

`interval` i 的右侧区间 `interval` j 满足 `startj >= endi`，并且 `startj` 是最下的，

返回数组中每个 `interval`i 的右侧区间的下标，如果没有，返回 -1，



## 解题思路



### Solution 1:

这里先给出暴力解法：会超时，时间复杂度 `O(n^2)`， 空间复杂度 `O(n)`

```c++
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        const int len = intervals.size();
        vector<int> res(len, -1);
        for (int i = 0; i < len; ++i) {
            int bound = INT_MAX; // 这里设定上边界
            for (int j = 0; j < len; ++j) {
                if (i == j) {
                    continue;
                }
                
                if (intervals[j][0] >= intervals[i][1] && intervals[j][0] < bound) {
                    // 同时更新结果和上边界
                    res[i] = j;
                    bound = intervals[j][0];
                }
            }
        }
        
        return move(res);
    }
};
```



### Solution 2: BinarySearch

这种解法，可以参考霜神的 [题解](https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0436.Find-Right-Interval/)
使用二分搜索来降低时间复杂度，那么就需要对原数组进行排序，这里排序之前需要先复制一份，由于这里是不一定能找到，因此可以分三段


````c++
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        const int len = intervals.size();
        // 这里复制一份，留待后面使用
        vector<vector<int>> cache;
        
        // 这里使用哈希来维护原来的索引
        unordered_map<int, int> relat; // key 是 start， val 是 下标
        for (int i = 0; i < len; ++i) {
            relat[intervals[i][0]] = i;
            cache.push_back({intervals[i]});
        }
        
        // 按照 start 升序排序
        sort(intervals.begin(), intervals.end());
        
        vector<int> res(len);
        for (int i = 0; i < len; ++i) {
            res[i] = BinarySearch(intervals, cache[i][1], relat);
        }
        return res;
    }
    
 private:
    // 找到第一个 大于等于 end 的
    int BinarySearch(const vector<vector<int>>& intervals, int bound,
                    const unordered_map<int, int>& relat) {
        const int len = intervals.size();
        int left = 0, right = len - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (intervals[mid][0] >= bound) {
                if (mid == 0 || intervals[mid - 1][0] < bound) {
                    return relat.at(intervals[mid][0]);
                }
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return -1;
    }
};
````

