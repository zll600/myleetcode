# [665. Non-decreasing Array](https://leetcode.com/problems/non-decreasing-array/)

## 题目

Given an array `nums` with `n` integers, your task is to check if it could become non-decreasing by modifying **at most one element**.

We define an array is non-decreasing if `nums[i] <= nums[i + 1]` holds for every `i` (**0-based**) such that (`0 <= i <= n - 2`).

 

**Example 1:**

```
Input: nums = [4,2,3]
Output: true
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
```

**Example 2:**

```
Input: nums = [4,2,1]
Output: false
Explanation: You can't get a non-decreasing array by modify at most one element.
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 104`
- `-105 <= nums[i] <= 105`

## 题目

给定一个含有 `n` 个数的整数数组 `nums`，你的人物是检查能否通过最多只更改一个元素使其变得非递减，

如果 `nums[i] <= nums[i + 1]` 对于每一个 `i`(0 为初始下标) 中 `0 <= i <= n - 2`

## 解题思路

要解决这道题目就是要找出数组中有多少个递减区间，

如果递减区间有多个，且在我们在第一次我们修改元素之后还会遇到，返回 false

这里注意如果要修改数组元素，如果存在 `nums[i] > nums[i + 1] && i > 0 && nums[i + 1] < nums[i - 1]` 那么需要将右侧的这个较小值变为一个较大值

### Solution 1:


````c++
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        const int len = nums.size();
            
        int cnt = 0;
        for (int i = 0; i < len - 1; ++i) {
            if (nums[i] > nums[i + 1]) {
                // 如果出现递减
                ++cnt;
                if (cnt > 1) {
                    // 出现的递减超过两处
                    return false;
                }
                
                if (i > 0 && nums[i + 1] < nums[i - 1]) {
                    // 如果 nums[i] 是一个峰值，那么让右侧这个较小值变大
                    nums[i + 1] = nums[i];
                }
            }
        }
        
        return true;
    }
};
````
