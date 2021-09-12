# [576. Out of Boundary Paths](https://leetcode.com/problems/out-of-boundary-paths/)

## 题目

There is an `m x n` grid with a ball. The ball is initially at the position `[startRow, startColumn]`. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply **at most** `maxMove` moves to the ball.

Given the five integers `m`, `n`, `maxMove`, `startRow`, `startColumn`, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it **modulo** `109 + 7`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/28/out_of_boundary_paths_1.png)

```
Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
Output: 6
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/04/28/out_of_boundary_paths_2.png)

```
Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
Output: 12
```

 

**Constraints:**

- `1 <= m, n <= 50`
- `0 <= maxMove <= 50`
- `0 <= startRow < m`
- `0 <= startColumn < n`

## 题目大意

在一个 m x n 的网格中有一个球，初始位置位于 [startrow, startcol]，你可以将这个球，向相邻的四个方格移动（可能会出界），你最多只能移动 maxmoves 次球，返回将球移出边界的路径数目，

## 解题思路

* 因为这道题目的递推公式和初始化不容易看出和猜出，可以先想以下记忆化搜索，不用实现，来确定dp数组的定义和递推公式，

## 代码

`````c++
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        rows = m;
        cols = n;
        steps = maxMove;
        
        // 这里将一个三维的数组转化为二维
        vector<vector<int>> dp(rows * cols, vector<int>(maxMove + 1, 0));
        
        // 初始化边缘的位置
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i == 0) {
                    Add(i, j, dp);
                }
                if (i == rows - 1) {
                    Add(i, j, dp);
                }
                if (j == 0) {
                    Add(i, j, dp);
                }
                if (j == cols - 1) {
                    Add(i, j, dp);
                }   
            }
        }

        for (int step = 1; step <= steps; ++step) {
            for (int pos = 0; pos < rows * cols; ++pos) {
                int x = ParseIndex(pos).first;
                int y = ParseIndex(pos).second;

                for (const vector<int>& dir : dirs) {
                    int nx = x + dir[0];
                    int ny = y + dir[1];
                 
                 
                    if (IsValid(nx, ny)) {
                        dp[pos][step] += dp[GetIndex(nx, ny)][step - 1];
                        dp[pos][step] %= mod;
                    }
                }
            }
        }
        return dp[GetIndex(startRow, startColumn)][steps];
    }

    static const int mod = 1000000007;
 private:
    int rows;
    int cols;
    int steps;

    vector<vector<int>> dirs = {
       {1, 0},
       {-1, 0},
       {0, 1},
       {0, -1}
    };

    bool IsValid(int x, int y) {
       return x >= 0 && x < rows && y >= 0 && y < cols;
    }

    // 将 （x, y）转化为 index
    int GetIndex(int x, int y) {
       return x * cols + y;
    }

    // 将 idx 转化为 (x, y)
    pair<int, int> ParseIndex(int idx) {
       return pair<int, int>(idx / cols, idx % cols);
    }
    
    void Add(int x, int y, vector<vector<int>>& dp) {
       int idx = GetIndex(x, y);
       for (int step = 1; step <= steps; ++step) {
          ++dp[idx][step];
       }
    }
};
`````

