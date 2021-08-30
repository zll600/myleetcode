# [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)

## 题目

Given an array `nums` which consists of non-negative integers and an integer `m`, you can split the array into `m` non-empty continuous subarrays.

Write an algorithm to minimize the largest sum among these `m` subarrays.

 

**Example 1:**

```
Input: nums = [7,2,5,10,8], m = 2
Output: 18
Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
```

**Example 2:**

```
Input: nums = [1,2,3,4,5], m = 2
Output: 9
```

**Example 3:**

```
Input: nums = [1,4,4], m = 3
Output: 4
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `0 <= nums[i] <= 106`
- `1 <= m <= min(50, nums.length)`

## 题目大意

给定一个非负整数数组和一个整数 m，你将这个数组切分为 m 个非空的连续字数组，写一个算法最小化这 m 个子数组的最大和

## 解题思路

* 这道题目可以用动态规划来解，
* 也可以用“二分搜索”来解，这是一道二分搜索中的最大值最下化的题目，题目可以转换为在 m 个非空子数组中，求一个最大值 x，且满足对于每个划分出来的子数组有 sum <= x，使满足条件的 x 最小，x 的取值范围为 [max_num , all_sum]，求满足条件的的最小值，

## 代码

`````c++
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int lo = 0;
        int hi = 0;
        for (int i : nums) {
            hi += i;
            if (i > lo) {
                lo = i;
            }
        }
        
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (Check(nums, mid, m)) {	// 找到满足条件的最小的一个，也就是大于等于的最后一个，
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }
    
 private:
    int Check(vector<int>& nums, int mid, int m) {
        int count = 1;
        int sum = 0;
        
        for (int num : nums) {
            sum += num;
            
            if (sum > mid) {
                ++count;
                sum = num;
                
                if (count > m) {	// 当划分的子数组多于 题目要求，则返回 false，说明当前 mid 太小
                    return false;
                }
            }
        }
        
        return true;
    }
};
`````



