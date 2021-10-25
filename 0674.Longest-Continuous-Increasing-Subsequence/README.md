# [674. Longest Continuous Increasing Subsequence](https://leetcode.com/problems/longest-continuous-increasing-subsequence/)

## 题目

Given an unsorted array of integers `nums`, return *the length of the longest **continuous increasing subsequence** (i.e. subarray)*. The subsequence must be **strictly** increasing.

A **continuous increasing subsequence** is defined by two indices `l` and `r` (`l < r`) such that it is `[nums[l], nums[l + 1], ..., nums[r - 1], nums[r]]` and for each `l <= i < r`, `nums[i] < nums[i + 1]`.

 

**Example 1:**

```
Input: nums = [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5] with length 3.
Even though [1,3,5,7] is an increasing subsequence, it is not continuous as elements 5 and 7 are separated by element
4.
```

**Example 2:**

```
Input: nums = [2,2,2,2,2]
Output: 1
Explanation: The longest continuous increasing subsequence is [2] with length 1. Note that it must be strictly
increasing.
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`

## 题目大意

给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，都有 nums[i] < nums[i + 1] ，那么子序列 [nums[l], nums[l + 1], …, nums[r - 1], nums[r]] 就是连续递增子序列。

## 解题思路

这道题和第 300 题很像，但是其要求连续

### Solution 1: DP

```c++
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        const int size = nums.size();
        if (size < 2) {  // 边界情况
            return 1;
        }
        
        // dp[i] 表示i 结尾的最长递增自序列的长度
        vector<int> dp(size, 1);
        // 根据状态定义，每一项可以初始化为 0
        
        int res = dp[0];
        for (int i = 1; i < size; ++i) {
            // 状态转移
            if (nums[i] > nums[i - 1]) {
                dp[i] = dp[i - 1] + 1;
            }
            
            // 更新结果
            res = max(res, dp[i]);
        }
        
        return res;
    }
};
```

### Solution 2: 动态维护一个长度

````c++
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        const int size = nums.size();
        if (size < 2) {  // 边界情况
            return 1;
        }
        
        int res = 0;
        int len = 1;
        for (int i = 1; i < size; ++i) {
            if (nums[i] > nums[i - 1]) {
                ++len;
            } else {
                len = 1;
            }
            
            res = max(res, len);
        }
        
        return res;
    }
};
````

