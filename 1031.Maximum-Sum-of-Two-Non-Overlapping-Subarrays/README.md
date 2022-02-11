# [1031. Maximum Sum of Two Non-Overlapping Subarrays](https://leetcode-cn.com/problems/maximum-sum-of-two-non-overlapping-subarrays/)

## 题目

Given an integer array `nums` and two integers `firstLen` and `secondLen`, return *the maximum sum of elements in two non-overlapping **subarrays** with lengths* `firstLen` *and* `secondLen`.

The array with length `firstLen` could occur before or after the array with length `secondLen`, but they have to be non-overlapping.

A **subarray** is a **contiguous** part of an array.

 

**Example 1:**

```
Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
Output: 20
Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
```

**Example 2:**

```
Input: nums = [3,8,1,3,2,1,8,9,0], firstLen = 3, secondLen = 2
Output: 29
Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.
```

**Example 3:**

```
Input: nums = [2,1,5,6,0,9,5,0,3,8], firstLen = 4, secondLen = 3
Output: 31
Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [3,8] with length 3.
```

 

**Constraints:**

- `1 <= firstLen, secondLen <= 1000`
- `2 <= firstLen + secondLen <= 1000`
- `firstLen + secondLen <= nums.length <= 1000`
- `0 <= nums[i] <= 1000`

## 题目大意

给定一个整数数组 `nums`和两个整数 `firstLen` 和 `secondLen`，返回两个长度分别为 `firstLen` 和 `secondLen` 非重叠子数组中的元素最大和，

## 解题思路

这里我的解法是暴力来解，枚举所有的可能，然后选出结果


### Solution 1: PrefixSum

先使用前缀和进行预处理，降低整体的时间复杂度


````c++
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        const int len = nums.size();
        // 利用前缀和进行预处理
        vector<int> prefix_sum(len + 1, 0);
        for (int i = 1; i <= len; ++i) {
            prefix_sum[i] = nums[i - 1] + prefix_sum[i - 1];
        }
        
        int res = 0;
        {
            // first_sum -> second_sum
            int first_sum = 0;
            // 枚举每一个可能的位置
            for (int i = firstLen; i <= len - secondLen; ++i) {
                first_sum = max(first_sum, prefix_sum[i] - prefix_sum[i - firstLen]);
                res = max(res, first_sum  + prefix_sum[i + secondLen]  -  prefix_sum[i]);
            }
        }
        
        {
            // second_sum -> first_sum
            int second_sum = 0;
            for (int i = secondLen; i <= len - firstLen; ++i) {
                second_sum = max(second_sum, prefix_sum[i] - prefix_sum[i - secondLen]);
                res = max(res, second_sum + prefix_sum[i + firstLen] - prefix_sum[i]);
            }
        }
        
        return res;
    }
};
````
