# [334. Increasing Triplet Subsequence](https://leetcode-cn.com/problems/increasing-triplet-subsequence/)

## 题目

Given an integer array `nums`, return `true` *if there exists a triple of indices* `(i, j, k)` *such that* `i < j < k` *and* `nums[i] < nums[j] < nums[k]`. If no such indices exists, return `false`.

 

**Example 1:**

```
Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.
```

**Example 2:**

```
Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.
```

**Example 3:**

```
Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.
```

 

**Constraints:**

- `1 <= nums.length <= 5 * 105`
- `-231 <= nums[i] <= 231 - 1`

 

**Follow up:** Could you implement a solution that runs in `O(n)` time complexity and `O(1)` space complexity?

## 

给你一个整数数组 `nums` ，判断这个数组中是否存在长度为 3 的递增子序列。

如果存在这样的三元组下标 `(i, j, k)` 且满足 `i < j < k` ，使得 `nums[i]` < `nums[j]` < `nums[k]`，返回 `true` ；否则，返回 `false` 。

##



 
