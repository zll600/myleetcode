# [63. Unique Paths II](https://leetcode.com/problems/unique-paths-ii/)

## 题目

A robot is located at the top-left corner of a `m x n` grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as `1` and `0` respectively in the grid.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/04/robot1.jpg)

```
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/11/04/robot2.jpg)

```
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
```

 

**Constraints:**

- `m == obstacleGrid.length`
- `n == obstacleGrid[i].length`
- `1 <= m, n <= 100`
- `obstacleGrid[i][j]` is `0` or `1`.

## 题目大意

机械人位于一个m x n 的网格的左上角，在图中标记为 start，机械人每次只能向左或者向右运动一步，机械人试图到达图中的右下角，标记为 finish，如果路径上有障碍，有多少中不同的路径，1 表示障碍，0 表示空白，

## 解题思路

* 这是一道dp 路径问题，是第63题的加强版，
* 在初始化时，障碍物的地方 `dp[i][j] = 0`
* 注意起点就是障碍物的情况，

## 代码

````c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int rows = obstacleGrid.size();
         int cols = obstacleGrid[0].size();
         vector<vector<int>> dp(rows, vector<int>(cols, 0));
         dp[0][0] = obstacleGrid[0][0] == 1 ? 0 : 1;    // 这里要特殊处理起点就是障碍物的情况

         for (int i = 1; i < cols; ++i) {
            if (obstacleGrid[0][i] == 1) {  // 障碍物后面都不可达
               break;
            }   
            dp[0][i] = dp[0][i - 1];
         } 
         for (int i = 1; i < rows; ++i) {
            if (obstacleGrid[i][0] == 1) {  // 障碍物后面都不可达
               break;
            }   
            dp[i][0] = dp[i - 1][0];
         } 

         for (int i = 1; i < rows; ++i) {
            for (int j = 1; j < cols; ++j) {
               if (obstacleGrid[i][j] != 1) {
                  dp[i][j] = dp[i - 1][j] + dp[i][j - 1]; 
               }   
            }   
         }   
         return dp[rows - 1][cols - 1];
    }
};
````

