# [1027. Longest Arithmetic Subsequence](https://leetcode.cn/problems/longest-arithmetic-subsequence/)

## 题目

Given an array `nums` of integers, return the **length** of the longest arithmetic subsequence in `nums`.

Recall that a *subsequence* of an array `nums` is a list `nums[i1], nums[i2], ..., nums[ik]` with `0 <= i1 < i2 < ... < ik <= nums.length - 1`, and that a sequence `seq` is *arithmetic* if `seq[i+1] - seq[i]` are all the same value (for `0 <= i < seq.length - 1`).

 

**Example 1:**

```
Input: nums = [3,6,9,12]
Output: 4
Explanation: 
The whole array is an arithmetic sequence with steps of length = 3.
```

**Example 2:**

```
Input: nums = [9,4,7,2,10]
Output: 3
Explanation: 
The longest arithmetic subsequence is [4,7,10].
```

**Example 3:**

```
Input: nums = [20,1,15,3,10,5,8]
Output: 4
Explanation: 
The longest arithmetic subsequence is [20,15,10,5].
```

 

**Constraints:**

- `2 <= nums.length <= 1000`
- `0 <= nums[i] <= 500`

## 题目大意

给你一个整数数组 nums，返回 nums 中最长等差子序列的长度。

回想一下，nums 的子序列是一个列表 nums[i1], nums[i2], ..., nums[ik] ，且 0 <= i1 < i2 < ... < ik <= nums.length - 1。并且如果 seq[i+1] - seq[i]( 0 <= i < seq.length - 1) 的值都相同，那么序列 seq 是等差的

## 解题思路


### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/longest-arithmetic-subsequence/solution/zui-chang-deng-chai-shu-lie-by-192324634-5sin/)

这里定义 `dp[i][step]` 为 nums[i] 结尾，公差为 step 的最长等差数列的长度，这里需要注意的是 公差可能是负数，

`dp[i][step] = max(dp[i][step], dp[j][step] + 1) for j range(i)`

````c++
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        const int len = nums.size();
        if (len == 1) {
            return 0;
        }
        if (len == 2) {
            return 2;
        }
        vector<vector<int>> dp(len, vector<int>(1001, 1));
        
        int ans = 0;
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < i; ++j) {
                int steps = nums[i] - nums[j] + 500;
                dp[i][steps] = max(dp[i][steps], dp[j][steps] + 1);
                ans = max(ans, dp[i][steps]);
            }
        }
        return ans;
    }
};
````
