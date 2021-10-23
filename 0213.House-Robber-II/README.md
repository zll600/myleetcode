# [213. House Robber II](https://leetcode.com/problems/house-robber-ii/)

## 题目

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are **arranged in a circle.** That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and **it will automatically contact the police if two adjacent houses were broken into on the same night**.

Given an integer array `nums` representing the amount of money of each house, return *the maximum amount of money you can rob tonight **without alerting the police***.

 

**Example 1:**

```
Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
```

**Example 2:**

```
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
```

**Example 3:**

```
Input: nums = [1,2,3]
Output: 3
```

 

**Constraints:**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 1000`

## 题目大意

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都**围成一圈**，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警**。

给定一个代表每个房屋存放金额的非负整数数组，计算你**在不触动警报装置的情况下**，能够偷窃到的最高金额。

## 解题思路

这道题目和第 193 题很像，但是第一间房屋和最后一间房屋不能同时选，这里直接将这两种方法分开来算，取其中最大的结果，

这道题建议看一下这篇题解，解释的很清楚：https://leetcode-cn.com/problems/house-robber-ii/solution/213-da-jia-jie-she-iidong-tai-gui-hua-jie-gou-hua-/

### Solution 1:

````c++
class Solution {
public:
    int rob(vector<int>& nums) {
        const int size = nums.size();
        if (size == 1) {
            return nums[0];
        }
        if (size == 2) {
            return max(nums[0], nums[1]);
        }
        // 这里保证至少有三个元素
        
        return max(rob(nums, 0, size - 2), rob(nums, 1, size - 1));
    }
    
 private:
    // 利用第 198 题的解法
    int rob(vector<int>& nums, int start, int end) {
        int first = nums[start];
        int second = max(first, nums[start + 1]);
        
        for (int i = start + 2; i <= end; ++i) {
            int cur = max(second, first + nums[i]);
            first = second;
            second = cur;
        }
        
        return second;
    }
};
````

