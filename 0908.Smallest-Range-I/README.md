# [908. Smallest Range I](https://leetcode-cn.com/problems/smallest-range-i/)

## 题目

You are given an integer array `nums` and an integer `k`.

In one operation, you can choose any index `i` where `0 <= i < nums.length` and change `nums[i]` to `nums[i] + x` where `x` is an integer from the range `[-k, k]`. You can apply this operation **at most once** for each index `i`.

The **score** of `nums` is the difference between the maximum and minimum elements in `nums`.

Return *the minimum **score** of* `nums` *after applying the mentioned operation at most once for each index in it*.

 

**Example 1:**

```
Input: nums = [1], k = 0
Output: 0
Explanation: The score is max(nums) - min(nums) = 1 - 1 = 0.
```

**Example 2:**

```
Input: nums = [0,10], k = 2
Output: 6
Explanation: Change nums to be [2, 8]. The score is max(nums) - min(nums) = 8 - 2 = 6.
```

**Example 3:**

```
Input: nums = [1,3,6], k = 3
Output: 0
Explanation: Change nums to be [4, 4, 4]. The score is max(nums) - min(nums) = 4 - 4 = 0.
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `0 <= nums[i] <= 104`
- `0 <= k <= 104`

## 题目大意

给定一个数组 `nums` 和 一个整数 `k`，在每一次操作中，你可以选择任意下标 `i(0 <= i < nums.length)` 并且改变 `nums[i] 至 nums[i] + x` 其中 `x` 是一个 `[-k, k]` 中的整数，你可以对每个下标 `i`，至多应用一次操作

分数是指 `nums` 中最大值和最小值的差值

返回在对每个下标应用至多一次操作后的最低分数

## 解题思路

首先必须先找到最大值和最小值，然后想办法在这两个值上面应用上述操作使得差值缩小

### Solution 1:


````c++
class Solution {
public:
    int smallestRangeI(vector<int>& nums, int k) {
        // 求出最大值，最小值
        int max_val = *max_element(nums.begin(), nums.end());
        int min_val = *min_element(nums.begin(), nums.end());

        int diff = max_val - min_val;
        // 如果差值 小于 2k
        if (diff > 2 * k) {
            return diff - 2 * k;
        }
        return 0;
    }
};
````
