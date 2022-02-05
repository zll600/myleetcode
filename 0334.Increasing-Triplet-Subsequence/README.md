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

## 题目大意

给你一个整数数组 `nums` ，判断这个数组中是否存在长度为 3 的递增子序列。

如果存在这样的三元组下标 `(i, j, k)` 且满足 `i < j < k` ，使得 `nums[i]` < `nums[j]` < `nums[k]`，返回 `true` ；否则，返回 `false` 。

## 解题思路

这道题目最开始的想法是利用单调栈，查询是否可以存在单调递增的一个三元组，但是单调栈的限制在于，只能选择从开始的出发的三元祖，如果途中遇到更小的数，则无法满足题意，例如`[20,100,10,12,5,13]`

### Solution 1:

这种解法剋参考这篇题解：https://leetcode-cn.com/problems/increasing-triplet-subsequence/solution/c-xian-xing-shi-jian-fu-za-du-xiang-xi-jie-xi-da-b/

题解中说的很详细，这里维护一个最小值，和一个次小值，如果出现比次小值大的数，则说明存在满足题意的三元组，这种解法可以解决上述单调栈出现的问题，如果后面出现比最小值还小的值，不回影响最后的结果

```c++
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        const int len = nums.size();
        if (len < 3) {
            // 处理特殊情况
            return false;
        }
        
        int small = INT_MAX, mid = INT_MAX; // 初始时，赋予最大值
        for (int num : nums) {
            if (num <= small) {
                // 如果比最小值小，则更新最小值
                small = num;
            } else if (num <= mid) {
                // 如果比中值小，则更新中值
                mid = num;
            } else if (num > mid) {
                // 遇到比中值大的，说明可以满足题意，直接返回
                return true;
            }
        }
        return false;
    }
};
```



 
