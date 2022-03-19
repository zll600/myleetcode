# [561. Array Partition I](https://leetcode.com/problems/array-partition-i/)

## 题目

Given an integer array `nums` of `2n` integers, group these integers into `n` pairs `(a1, b1), (a2, b2), ..., (an, bn)` such that the sum of `min(ai, bi)` for all `i` is **maximized**. Return *the maximized sum*.

 

**Example 1:**

```
Input: nums = [1,4,3,2]
Output: 4
Explanation: All possible pairings (ignoring the ordering of elements) are:
1. (1, 4), (2, 3) -> min(1, 4) + min(2, 3) = 1 + 2 = 3
2. (1, 3), (2, 4) -> min(1, 3) + min(2, 4) = 1 + 2 = 3
3. (1, 2), (3, 4) -> min(1, 2) + min(3, 4) = 1 + 3 = 4
So the maximum possible sum is 4.
```

**Example 2:**

```
Input: nums = [6,2,6,5,1,2]
Output: 9
Explanation: The optimal pairing is (2, 1), (2, 5), (6, 6). min(2, 1) + min(2, 5) + min(6, 6) = 1 + 2 + 6 = 9.
```

 

**Constraints:**

- `1 <= n <= 104`
- `nums.length == 2 * n`
- `-104 <= nums[i] <= 104`

## 题目大意

给定一个长度为 `2n` 的整数数组，将这些数字分为 `n` 对，找出所有 `min(ai, bi)` 的和，返回这个和的最大值

## 解题思路 

这里的话我是觉得，要让最终的结果最大，那么就需要尽可能的让较小的值，不影响到较大的值，这样我们就可以利用较大值来增加最终的结果

### Solution 1: Sort


````c++
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        int sum = 0;
        // 先排序
        sort(nums.begin(), nums.end());

        const int len = nums.size();
        for (int i = 0; i < len; i += 2) {
            // 每一对里面选最小的
            sum += min(nums[i], nums[i + 1]);
        }

        return sum;
    }
};
````
