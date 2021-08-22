# [713. Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/)

## 题目

Given an array of integers `nums` and an integer `k`, return *the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than* `k`.

 

**Example 1:**

```
Input: nums = [10,5,2,6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
```

**Example 2:**

```
Input: nums = [1,2,3], k = 0
Output: 0
```

 

**Constraints:**

- `1 <= nums.length <= 3 * 104`
- `1 <= nums[i] <= 1000`
- `0 <= k <= 106`

## 题目大意

给定一个正整数数组（限制中提到每个元素都大于 1）和一个整数值，返回累乘结果严格小`k`的窗口数

## 解题思路

利用滑动窗口，如果当前窗口的累乘小于 k， 就扩大窗口，否则就缩小窗口, 如果当前窗口只有一个值而且不满足要求，此时这个值不会进行累乘，只需将左右边界同时右移（代码中给出了说明）。

## 代码

````c++
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) {
            return 0;
        }
        int size = nums.size();
        
        int res = 0;
        int left = 0;
        int right = 0;
        int prod = 1;
        
        /*
        while (left < size) {
            if (right < size && prod * nums[right] < k) {
                prod *= nums[right];
                ++right;                    // 这里窗口就成为了一个左闭右开区间
            } else if (left == right) {     // 这里是一个左闭右闭区间，窗口只有一个元素，且不满足条件
                ++right;					// 这个值不会进行累乘（可以自己举例[5, 2, 6, 100]）
                ++left;
            } else {
                res += right - left;    // 这里是以右边界（此时是左闭右开区间）
                prod /= nums[left];     // 为结尾的当前窗口的子数组的书目之和，
                ++left;                 // 如：[5, 2, 6], [6], [2, 6]
            }
        }
        
        return res;
        */
        
        for (; right < size; ++right) {
            prod *= nums[right];
            while (prod >= k) {
                prod /= nums[left];
                ++left;
            }
            res += right - left + 1;
        }
        
        return res;
    }
};
````

