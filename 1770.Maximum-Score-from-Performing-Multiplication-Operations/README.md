## [1770. Maximum Score from Performing Multiplication Operations](https://leetcode-cn.com/problems/maximum-score-from-performing-multiplication-operations/)

You are given two integer arrays `nums` and `multipliers` of size `n` and `m` respectively, where `n >= m`. The arrays are **1-indexed**.

You begin with a score of `0`. You want to perform **exactly** `m` operations. On the `ith` operation **(1-indexed)**, you will:

- Choose one integer `x` from **either the start or the end** of the array `nums`.
- Add `multipliers[i] * x` to your score.
- Remove `x` from the array `nums`.

Return *the **maximum** score after performing* `m` *operations.*

 

**Example 1:**

```
Input: nums = [1,2,3], multipliers = [3,2,1]
Output: 14
Explanation: An optimal solution is as follows:
- Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
- Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
- Choose from the end, [1], adding 1 * 1 = 1 to the score.
The total score is 9 + 4 + 1 = 14.
```

**Example 2:**

```
Input: nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]
Output: 102
Explanation: An optimal solution is as follows:
- Choose from the start, [-5,-3,-3,-2,7,1], adding -5 * -10 = 50 to the score.
- Choose from the start, [-3,-3,-2,7,1], adding -3 * -5 = 15 to the score.
- Choose from the start, [-3,-2,7,1], adding -3 * 3 = -9 to the score.
- Choose from the end, [-2,7,1], adding 1 * 4 = 4 to the score.
- Choose from the end, [-2,7], adding 7 * 6 = 42 to the score. 
The total score is 50 + 15 - 9 + 4 + 42 = 102.
```

 

**Constraints:**

- `n == nums.length`
- `m == multipliers.length`
- `1 <= m <= 103`
- `m <= n <= 105```
- `-1000 <= nums[i], multipliers[i] <= 1000`

## 题目大意

给定两个长度分别为 `n` 和 `m` 的数组 `nums` 和 `multipliers`，其中 `n >= m`，数组下标从 `1` 开始计数

初始时，你的分数为 `0` 。你需要执行恰好 `m` 步操作。在第 `i` 步操作（从 `1` 开始 计数）中，需要：

- 选择数组 `nums` 开头处或者末尾处 的整数 `x` 。
- 你获得 `multipliers[i] * x` 分，并累加到你的分数中。
- 将 `x` 从数组 `nums` 中移除。

在执行 m 步操作后，返回 最大 分数。

## 解题思路

这道题是存在重复的子问题的，问题的最优解取决于每个子问题的最优解，这里的状态可以理解为每次从开头取还是从结尾取，取的总数是 `m`，

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/)


````c++
class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size();
        int m = multipliers.size();
        
        // 这里由题目的范围，可以设置 dp 数组的大小
        // dp[i][j] 表示 从开头去 i 个，从结尾取 j 个，
        vector<vector<int>> dp(1002, vector<int>(1002, 0));
        int res = INT_MIN; // 取最大值，初始化为最小值
        
        for (int k = 1; k <= m; ++k) {    
            for (int i = 0; i <= k; ++i) {
                if (i == 0) {
                    // 全部从末尾取
                    dp[i][k - i] = dp[i][k - i - 1] + nums[n - k + i] * multipliers[k - 1];
                } else if (i == k) {
                    // 全部从开头取
                    dp[i][k - i] = dp[i - 1][k - i] + nums[i - 1] * multipliers[k - 1];
                } else {
                    // 从中间取
                    dp[i][k - i] = max(dp[i][k - i - 1] + nums[n - k + i] * multipliers[k - 1],
                                      dp[i - 1][k - i] + nums[i - 1] * multipliers[k - 1]);
                }
                
                if (k == m) {
                    // 取够 k 个的时候，就可以更新结果
                    res = max(res, dp[i][k - i]);
                }
            }
        }
        
        return res;
    }
};
````
