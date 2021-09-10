# [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)

## 题目

Given a `m x n` `grid` filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

**Note:** You can only move either down or right at any point in time.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/05/minpath.jpg)

```
Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
```

**Example 2:**

```
Input: grid = [[1,2,3],[4,5,6]]
Output: 12
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 200`
- `0 <= grid[i][j] <= 100`

## 题目大意

给定只包含非负整数的 m x n 的网格，返回从左上角到右下角的最小路径和，每次你只能向右或者向下一移动一步

## 解题思路

* 这道题目是第62题升级版，

 ## 代码

`````c++
class Solution {
public:
    // 使用一个二维数组
    /*
    int minPathSum(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        vector<vector<int>> dp(rows, vector<int>(cols,0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < rows; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < cols; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        
        for (int i = 1; i < rows; ++i) {
            for (int j = 1; j < cols; ++j) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[rows - 1][cols - 1];
    }*/
    
    // 优化之后的结果
    int minPathSum(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        vector<int> dp(cols, 0);
        dp[0] = grid[0][0];
        for (int j = 1; j < cols; ++j) {
            dp[j] = dp[j - 1] + grid[0][j];
        }
        
        for (int i = 1; i < rows; ++i) {
            dp[0] += grid[i][0];	// 注意这里必须处理每一行的第一项
            for (int j = 1; j < cols; ++j) {
                dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
            }
        }
        return dp[cols - 1];
    }
};
`````

