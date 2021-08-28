# [643. Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/)

## 题目

You are given an integer array `nums` consisting of `n` elements, and an integer `k`.

Find a contiguous subarray whose **length is equal to** `k` that has the maximum average value and return *this value*. Any answer with a calculation error less than `10-5` will be accepted.

 

**Example 1:**

```
Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75
```

**Example 2:**

```
Input: nums = [5], k = 1
Output: 5.00000
```

 

**Constraints:**

- `n == nums.length`
- `1 <= k <= n <= 105`
- `-104 <= nums[i] <= 104`

## 题目大意

给定一个长度为 n 的整数数组，找出该数组中平均数最大的子数组，并返回该平均值

## 解题思路

这道题可以利用“滑动窗口”，求出窗口的和的最大值，就是要求的最大平均值，

先将窗口填满，然后滑动窗口，不断更新最大和，

## 代码

````c++
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int size = nums.size();
        long sum = 0;
        long res = 0;
        
        for (int i = 0; i < k; ++i) {
            sum += nums[i];
        }
        
        res = sum;
        for (int i = k; i < size; ++i) {
            sum = sum - nums[i - k] + nums[i];
            res = max(res, sum);
        }
        
        return res * 1.0 / k;
    }
};
````

