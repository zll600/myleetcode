# [1289. Minimum Falling Path Sum II](https://leetcode.com/problems/minimum-falling-path-sum-ii/)

## 题目

Given an `n x n` integer matrix `grid`, return *the minimum sum of a **falling path with non-zero shifts***.

A **falling path with non-zero shifts** is a choice of exactly one element from each row of `grid` such that no two elements chosen in adjacent rows are in the same column.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/08/10/falling-grid.jpg)

```
Input: arr = [[1,2,3],[4,5,6],[7,8,9]]
Output: 13
Explanation: 
The possible falling paths are:
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
The falling path with the smallest sum is [1,5,7], so the answer is 13.
```

**Example 2:**

```
Input: grid = [[7]]
Output: 7
```

 

**Constraints:**

- `n == grid.length == grid[i].length`
- `1 <= n <= 200`
- `-99 <= grid[i][j] <= 99`

## 题目大意

给定一个 n x n 的整数网格，返回非零偏移的最小路径和，

非零偏移的最小路径就是，从网格中的每一行中选出一个数，且相邻两行选出的数不再同一列，

## 解题思路

* 这道题也是一道路径 DP 问题，不过如果采用通常解法，遍历每一行需要找到当前行的前一行的最小值，时间复杂度是O(n^3),
* 优化方法是采用两个常量作记录，分别记录上一行的最小值和次小值，

## 代码

`````c++
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        int first = -1;     // 记录最小值
        int second = -1;    // 记录次小值
        for (int i = 0; i < n; ++i) {
            dp[0][i] = grid[0][i];
            if (grid[0][i] < (first == -1 ? INT_MAX : grid[0][first])) {
                second = first;
                first = i;
            } else if (grid[0][i] < (second == -1 ? INT_MAX : grid[0][second])) {
                second = i;
            }
        }
        
        for (int i = 1; i < n; ++i) {
            int new_first = -1; // 更新最小值
            int new_second = -1;    // 更新最小值
            for (int j = 0; j < n; ++j) {
                if (j != first) {
                    dp[i][j] = dp[i - 1][first] + grid[i][j];
                } else {
                    dp[i][j] = dp[i - 1][second] + grid[i][j];
                }
                
                if (dp[i][j] < (new_first == -1 ? INT_MAX : dp[i][new_first])) {
                    new_second = new_first;
                    new_first = j;
                } else if (dp[i][j] < (new_second == -1 ? INT_MAX : dp[i][new_second])) {
                    new_second = j;
                }
            }
            first = new_first;
            second = new_second;
        }
        
        int res = INT_MAX;
        for (int i = 0; i < n; ++i) {
            res = min(res, dp[n - 1][i]);
        }
        
        return res;
    }
};
`````

