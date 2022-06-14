# [1124. Longest Well-Performing Interval](https://leetcode.cn/problems/longest-well-performing-interval/)

## 题目

We are given `hours`, a list of the number of hours worked per day for a given employee.

A day is considered to be a *tiring day* if and only if the number of hours worked is (strictly) greater than `8`.

A *well-performing interval* is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.

Return the length of the longest well-performing interval.

 

**Example 1:**

```
Input: hours = [9,9,6,0,6,6,9]
Output: 3
Explanation: The longest well-performing interval is [9,9,6].
```

**Example 2:**

```
Input: hours = [6,6,6]
Output: 0
```

 

**Constraints:**

- `1 <= hours.length <= 104`
- `0 <= hours[i] <= 16`


## 题目大意

给你一份工作时间表 `hours`，上面记录着某一位员工每天的工作小时数

我们认为当员工一天中的工作小时数大于 `8` 小时的时候，那么这一天就是「劳累的一天」

所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」

请你返回「表现良好时间段」的最大长度

## 题目大意

这道题目刚开始想到的是使用滑动窗口，但是无法确定窗口滑动的条件

这里只需要关注 每天的工作时长是否大于 8，而不用在于具体的值，所以这里将数据做一个处理，大于 8 的赋值为1，小于 8 的赋值为 -1

那么表现良好的时间段，就是这段区间的数组元素值大于0，区间求和，不难想到使用前缀和来做预处理 `i...j` 的区间和就是 `prefix_sum[j] - prefix_sum[i]`

### Solution 1: Prefix(TLE)


`````c++
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        const int len = hours.size();
        vector<int> records(len);
        for (int i = 0; i < len; ++i) {
            if (hours[i] > 8) {
                records[i] = 1;
            } else {
                records[i] = -1;
            }
        }
        
        vector<int> prefix_sum(len + 1, 0);
        // i...j = dp[j] - dp[i]
        for (int i = 0; i < len; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + records[i];
        }
        
        int res = 0;
        for (int i = 0; i <= len; ++i) {
            for (int j = i + 1; j <= len; ++j) {
                if (prefix_sum[i] < prefix_sum[j]) {
                    res = max(res, j - i);
                }
            }
        }
        return res;
    }
};
````
