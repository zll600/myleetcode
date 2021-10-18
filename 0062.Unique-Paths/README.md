# [62. Unique Paths](https://leetcode.com/problems/unique-paths/)

## 题目

A robot is located at the top-left corner of a `m x n` grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/10/22/robot_maze.png)

```
Input: m = 3, n = 7
Output: 28
```

**Example 2:**

```
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down
```

**Example 3:**

```
Input: m = 7, n = 3
Output: 28
```

**Example 4:**

```
Input: m = 3, n = 3
Output: 6
```

 

**Constraints:**

- `1 <= m, n <= 100`
- It's guaranteed that the answer will be less than or equal to `2 * 109`.

## 题目大意

一个机器人位于一个 m x n 的网格中，起始点位于左上角，机器人每次只能向右或者向下运动，到达目的地右下角，问共有多少条不同的路。

## 解题思路

* 这是一道 dp 路径问题，求方案数，我们要做到不重不漏

**状态定义**：`dp[i][j]` 表示从起点到 [i, j]位置的路径数，

**状态转移**: 

````
dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
````

**初始化**：

从状态转移方程可以得出，我们要想让递推进行下去，则必须要初始化第一行，第一列，所以这些地方全部初始化为 1；

### Solution 1: DP

`````c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;
		
        // 初始化
        for (int i = 1; i < n; ++i) {
            dp[0][i] = dp[0][i - 1]; 
        }
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0];
        }
		
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j];  // 状态转移
            }
        }
        return dp[m - 1][n - 1];   
    }
};
`````

### Solution: 空间优化

````c++
class Solution {
public:
	int uniquePaths(int m, int n) {
		vector<int> dp(n, 1);

        for (int row = 1; row < m; ++row) {
            for (int col = 1; col < n; ++col) {
                dp[col] = dp[col] + dp[col - 1];
            }
        }

        return dp[n - 1];
    }
};
````

