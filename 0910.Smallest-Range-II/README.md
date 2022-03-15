# [910. Smallest Range II](https://leetcode.com/problems/smallest-range-ii/)

## 题目

You are given an integer array `nums` and an integer `k`.

For each index `i` where `0 <= i < nums.length`, change `nums[i]` to be either `nums[i] + k` or `nums[i] - k`.

The **score** of `nums` is the difference between the maximum and minimum elements in `nums`.

Return *the minimum **score** of* `nums` *after changing the values at each index*.

 

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
Output: 3
Explanation: Change nums to be [4, 6, 3]. The score is max(nums) - min(nums) = 6 - 3 = 3.
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `0 <= nums[i] <= 104`
- `0 <= k <= 104`

## 题目大意

给定一个整数数组 `nums` 和一个整数 `k`，对于每一个下标 `i`，其中 `0 <= i < nums.length` 改变 `nums[i]` 为 `nums[i] - k` 或者 `nums[i] + k`,

分数是指 `nums` 中最大值和最小值的差

返回在对每一个下标应用一次操作后的最小分数

## 解题思路


### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0910.Smallest-Range-II/)

先进行排序，然后双指针，使得每个值都可以与最大值和最小值相比较，不断更新差值

````c++
class Solution {
public:
    int smallestRangeII(vector<int>& nums, int k) {
        // 先排序
        sort(nums.begin(), nums.end());
        const int len = nums.size();

        // 初始化 差值
        int diff = nums[len - 1] - nums[0];
        // 双指针
        // 让每个值都可以有可能成为最大值或者最小值
        for (int i = 0; i < len - 1; ++i) {
            // 第 i 項尝试做较大值
            int high = max(nums[len - 1] - k, nums[i] + k);
            // 第 i + 1 項尝试做较小值
            int low = min(nums[0] + k, nums[i + 1] - k);
            diff = min(diff, high - low);
        }

        return diff;
    }
};
````
