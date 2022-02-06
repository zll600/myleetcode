# [532. K-diff Pairs in an Array](https://leetcode-cn.com/problems/k-diff-pairs-in-an-array/)

## 题目

Given an array of integers `nums` and an integer `k`, return *the number of **unique** k-diff pairs in the array*.

A **k-diff** pair is an integer pair `(nums[i], nums[j])`, where the following are true:

- `0 <= i < j < nums.length`
- `|nums[i] - nums[j]| == k`

**Notice** that `|val|` denotes the absolute value of `val`.

 

**Example 1:**

```
Input: nums = [3,1,4,1,5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
```

**Example 2:**

```
Input: nums = [1,2,3,4,5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
```

**Example 3:**

```
Input: nums = [1,3,1,5,4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-107 <= nums[i] <= 107`
- `0 <= k <= 107`

## 题目大意

给定一个整数数组 `nums` 和 一个整数 `k`，返回 **不同** 的 k-diff 数对的数目，

一个 **k-diff** 数对是一个整数书对 `(nums[i], nums[j])`，满足下面的要求:

- `0 <= i < j < nums.length`
- `|nums[i] - nums[j]| == k`

## 解题思路

这道题目有个难点在于 数字是可以重复出现的，所以要避免重复计算，同时要添加条件的时候要避免误伤，

这道题目只与值有关，而与 下标无关，所以可以先排序，在考虑


### Solution 1:


````c++
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        // 先排序，将相等的值会放在一起
        sort(nums.begin(), nums.end());

        int res = 0;
        const int len = nums.size();
        for (int i = 0; i < len - 1; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                // 这里跳过相同的起点
                continue;
            }
            for (int j = i + 1; j < len; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    // 这里跳过相同的终点
                    continue;
                }
                if (abs(nums[i] - nums[j]) == k) {
                    ++res;
                }
            }
        }
        return res;
    }
};
````
