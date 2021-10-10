# [698. Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/)

##

Given an integer array `nums` and an integer `k`, return `true` if it is possible to divide this array into `k` non-empty subsets whose sums are all equal.

 

**Example 1:**

```
Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
```

**Example 2:**

```
Input: nums = [1,2,3,4], k = 3
Output: false
```

 

**Constraints:**

- `1 <= k <= nums.length <= 16`
- `1 <= nums[i] <= 104`
- The frequency of each element is in the range `[1, 4]`.

## 

给定一个整数数组 nums 和一个整数 k，如果可以将这个数组分为 k 个非空的子数组，且他们的和都是相等的，就返回 true，否则返回 false

## 

