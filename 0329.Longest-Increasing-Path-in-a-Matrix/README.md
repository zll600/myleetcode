# [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

## 题目

Given an `m x n` integers `matrix`, return *the length of the longest increasing path in* `matrix`.

From each cell, you can either move in four directions: left, right, up, or down. You **may not** move **diagonally** or move **outside the boundary** (i.e., wrap-around is not allowed).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/05/grid1.jpg)

```
Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/01/27/tmp-grid.jpg)

```
Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
```

**Example 3:**

```
Input: matrix = [[1]]
Output: 1
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 200`
- `0 <= matrix[i][j] <= 231 - 1`

## 题目大意

给定一个 m x n 的矩阵，返回最长的递增路径的长度，

每个位置，你可以向上、下、左、右四个方向，你不能沿着对角线移动，或者越界

## 解题思路

虽然这道题是一道 hard 题，但是不要害怕，核心思路还是可以想到的，DFS算出每个格子为 起点的最长递增路经，

### Solution 1: DFS + 记忆化

直接 DFS 的话，会超时，加上记忆化，减少不必要的计算

````c++
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        rows_ = matrix.size();
        cols_ = matrix[0].size();
        // 缓存
        vector<vector<int>> cache(rows_, vector<int>(cols_, 0));
        
        // 遍历每个位置，更新最后的结果
        int res = 0;
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                SearchPath(matrix, i, j, INT_MIN, cache);
                res = max(res, cache[i][j]);
            }
        }
        
        return res;
    }
    
 private:
    // 方向数组
    vector<vector<int>> dirs_ = {
        {1, 0},
        {-1, 0},
        {0, -1},
        {0, 1}
    };
    
    int rows_;  // 行数
    int cols_;  // 列数
    
    // 检查下标是否合理
    bool IsInMatrix(int x, int y) {
        return x >= 0 && x < rows_ && y >= 0 && y < cols_;
    }
    
    // DFS 查找递增路径
    int SearchPath(const vector<vector<int>>& matrix, int x, int y,
                  int last_num, vector<vector<int>>& cache) {
        // 如果小于等于，则说明，不可达
        if (matrix[x][y] <= last_num) {
            return 0;
        }
        // 如果已经计算过，直接返回
        if (cache[x][y] > 0) {
            return cache[x][y];
        }
        
        // 初始化为 1
        int count = 1;
        // 状态转移
        for (const vector<int>& dir : dirs_) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            
            if (IsInMatrix(nx, ny)) {
                // 更新 count
                count = max(count, SearchPath(matrix, nx, ny, matrix[x][y], cache) + 1);
            }
        }
        cache[x][y] = count;
        return count;
    }
};
````

