# [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)

Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return *the number of islands*.

An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

**Example 1:**

```
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
```

**Example 2:**

```
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 300`
- `grid[i][j]` is `'0'` or `'1'`.

## 题目大意

给定一个由“1（陆地）”，“0（水）”组成的二维网格，返回岛屿的数目，一个岛被水包围，由垂直或者水平链接的岛屿构成，你可以认为岛屿的四周都是水，

## 解题思路

* 这道题可以类比第 733题使用DFS 来解决，同样不需要撤销对状态的改变，
* 这道题目也可以使用 BFS 来求解
* 这道题目还可以使用 并查集来解决（留待以后更新）

## 代码

````c++
class Solution {
 public:
    int numIslands(vector<vector<char>>& grid) {
        rows = grid.size();
        cols = grid[0].size();
        
        vector<vector<bool>> visit(rows, vector<bool>(cols, false));
        int res = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!visit[i][j] && grid[i][j] == '1') {    // 剪枝条件
                    //Search(grid, visit, i, j);
                    BFS(grid, visit, i, j);
                    ++res;
                }
            }
        }
        
        return res;
    }
 private:
    int rows;
    int cols;
    
    vector<vector<int>> dirs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    bool IsValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
    
    // DFS
    void Search(const vector<vector<char>>& grid, vector<vector<bool>>& visit,
               int x, int y) {
        if (grid[x][y] == '0') {
            return;
        }
        
        visit[x][y] = true;
        for (const vector<int>& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            
            if (IsValid(nx, ny) && !visit[nx][ny]) {
                Search(grid, visit, nx, ny);
            }
        }
    }
    
    // BFS
    void BFS(const vector<vector<char>>& grid, vector<vector<bool>>& visit,
            int x, int y) {
        queue<pair<int, int>> que;
        que.push(make_pair(x, y));
        visit[x][y] = true;
        
        while (!que.empty()) {
            pair<int, int> item = que.front();
            que.pop();
            
            for(const vector<int>& dir : dirs) {
                int nx = item.first + dir[0];
                int ny = item.second + dir[1];
                
                if (IsValid(nx, ny) && !visit[nx][ny]
                   && grid[nx][ny] == '1') {
                    que.push(make_pair(nx, ny));
                    visit[nx][ny] = true;   // 这里需要注意，在放入队列时，就标记为访问过，否则会出现重复入队的情况
                }
            }
        }
    }
};
````



