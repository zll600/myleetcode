# [494. Target Sum](https://leetcode.com/problems/target-sum/)

## 题目

You are given an integer array `nums` and an integer `target`.

You want to build an **expression** out of nums by adding one of the symbols `'+'` and `'-'` before each integer in nums and then concatenate all the integers.

- For example, if `nums = [2, 1]`, you can add a `'+'` before `2` and a `'-'` before `1` and concatenate them to build the expression `"+2-1"`.

Return the number of different **expressions** that you can build, which evaluates to `target`.

 

**Example 1:**

```
Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
```

**Example 2:**

```
Input: nums = [1], target = 1
Output: 1
```

 

**Constraints:**

- `1 <= nums.length <= 20`
- `0 <= nums[i] <= 1000`
- `0 <= sum(nums[i]) <= 1000`
- `-1000 <= target <= 1000`

## 题目大意

给定一个整数数组 nums 和一个整数 k，你可以通过给每个数字前面增加‘+’或者‘-’，来构造一个表达式，返回你能构造多少种表达式，可以使表达式的值等于 target，

## 解题思路

* 这是一道 DP 01 背包的问题，
* 状态的定义是 `dp[i][j]` 在[0, i] 的区间中和为 j的方法数
* 最终答案为 `dp[size][target]`
* 初始化，这里利用一个哨兵值，多设置一行，`dp[0][0] = 1` 表示没有数字的情况下凑成0 的方案数为1，
* 状态转移方程为 `dp[i][j] = dp[i - 1][j - nums[i]] + dp[i - 1][j + nums[i]]`
* 这道题目还需要注意的一点是 第二维度的取值范围是：sum 为数组所有元素的总和，j 的范围是 `[-sum, sum]`



这道题目dp 还可以优化，留待以后实现

## 代码

`````
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        
        if (target < -sum || target > sum) {
            return 0;
        }
        
        int size = nums.size();
        vector<vector<int>> dp(size + 1, vector<int>(2 * sum + 1));
        dp[0][0 + sum] = 1;	// 加上一个偏移，将负数部分转化为非负数部分，
        
        for (int i = 1; i <= size; ++i) {
            for (int j = -sum; j <= sum; ++j) {
                if (j - nums[i - 1] + sum >= 0) {
                    dp[i][j + sum] += dp[i - 1][j - nums[i - 1] + sum];
                }
                if (j + nums[i - 1] + sum <= 2 * sum) {
                    dp[i][j + sum] += dp[i - 1][j + nums[i - 1] + sum];
                }
            }
        }
        return dp[size][target + sum];
    }
};
`````

