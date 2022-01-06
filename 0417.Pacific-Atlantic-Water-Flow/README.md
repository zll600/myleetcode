# [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)

## 题目

There is an `m x n` rectangular island that borders both the **Pacific Ocean** and **Atlantic Ocean**. The **Pacific Ocean** touches the island's left and top edges, and the **Atlantic Ocean** touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an `m x n` integer matrix `heights` where `heights[r][c]` represents the **height above sea level** of the cell at coordinate `(r, c)`.

The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is **less than or equal to** the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.

Return *a **2D list** of grid coordinates* `result` *where* `result[i] = [ri, ci]` *denotes that rain water can flow from cell* `(ri, ci)` *to **both** the Pacific and Atlantic oceans*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/06/08/waterflow-grid.jpg)

```
Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
```

**Example 2:**

```
Input: heights = [[2,1],[1,2]]
Output: [[0,0],[0,1],[1,0],[1,1]]
```

 

**Constraints:**

- `m == heights.length`
- `n == heights[r].length`
- `1 <= m, n <= 200`
- `0 <= heights[r][c] <= 105`

## 题目大意

给定一个 m x n 的非负整数矩阵来表示一片大陆上各个单元格的高度。“太平洋”处于大陆的左边界和上边界，而“大西洋”处于大陆的右边界和下边界。

规定水流只能按照上、下、左、右四个方向流动，且只能从高到低或者在同等高度上流动。

请找出那些水流既可以流动到“太平洋”，又能流动到“大西洋”的陆地单元的坐标。

## 解题思路

这道题目可以参考花花的题解：https://www.bilibili.com/video/BV1Kb411K7ty

### Solution 1: Backtracking（TLE）

遍历每一个节点，对其中进行 DFS，判断其能否满足条件，

````c++
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> res;
        const int rows = heights.size();
        const int cols = heights[0].size();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (DFS(heights, i, j, heights[i][j]) == 3) {
                    res.push_back(vector<int>({i, j}));
                }
            }
        }
        return res;
    }
    
    
 private:
    vector<vector<int>> dirs_ = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    int DFS(vector<vector<int>>& heights, int x, int y, int level) {
        if (x < 0 || y < 0) {
            // 可以到达 pacific
            return 1;
        }
        if (x >= heights.size() || y >= heights[0].size()) {
            // 可以到达 atlantic
            return 2;
        }
        
        if (heights[x][y] > level) {
            return 0;
        }
        
        level = heights[x][y];
        heights[x][y] = INT_MAX; // 标记访问过了
        int valid = 0;
        for (const vector<int>& dir : dirs_) {
            // 1 | 2 = 3
            valid |= DFS(heights, x + dir[0], y + dir[1], level);
        }
        heights[x][y] = level; // 回溯
        return valid;
    }
};
````

### Solution 2: 双向 DFS

这种解法，从四条边开始向中间往上爬，然后对于结果取交集

```c++
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> res;
        const int rows = heights.size();
        const int cols = heights[0].size();
        
        vector<vector<bool>> pacific(rows, vector<bool>(cols, false));
        vector<vector<bool>> atlantic(rows, vector<bool>(cols, false));
        
        for (int row = 0; row < rows; ++row) {
            DFS(heights, row, 0, 0, pacific); // left
            DFS(heights, row, cols - 1, 0, atlantic); // right
        }
        
        for (int col = 0; col < cols; ++col) {
            DFS(heights, 0, col, 0, pacific); // top
            DFS(heights, rows - 1, col, 0, atlantic); // bottom 
        }
        
        vector<vector<int>> ans;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (pacific[i][j] && atlantic[i][j]) {
                    ans.emplace_back(vector<int>({i, j}));
                }
            }
        }
        return ans;
    }
    
    
 private:
    vector<vector<int>> dirs_ = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    void DFS(const vector<vector<int>>& heights, int x, int y,
            int level, vector<vec/tor<bool>>& visited) {
        if (x < 0 || y < 0 || x >= heights.size() || y >= heights[0].size()) {
            // 如果下标越界，就直接返回
            return;
        }
        
        if (visited[x][y] || heights[x][y] < level) {
            // 如果已经访问过了，或者不可达，
            return;
        }
        
        visited[x][y] = true;
        for (const vector<int>& dir : dirs_) {
            // 向四个方向转移
            DFS(heights, x + dir[0], y + dir[1], heights[x][y], visited);
        }
    }
};
```

### Solution 3: 双向 BFS

这种方法和方法 2 一样，不过这里使用了 BFS

````c++
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> res;
        const int rows = heights.size(); // 行数
        const int cols = heights[0].size(); // 列数
        
        const vector<int> dirs = {0, 1, 0, -1, 0}; // 方向数组
        
        auto bfs = [&](queue<vector<int>>& q, vector<vector<bool>>& v) {
            while (!q.empty()) {
                const int x = q.front()[0];
                const int y = q.front()[1];
                q.pop();
                
                const int level = heights[x][y];
                // 下面这个优化比较小，可以注释掉
                // if (v[x][y]) continue;
                v[x][y] = true;
                for (int i = 0; i < 4; ++i) {
                    int tx = x + dirs[i];
                    int ty = y + dirs[i + 1];
                    if (tx < 0 || ty < 0 || tx == rows || ty == cols) {
                        continue;
                    }
                    if (v[tx][ty] || heights[tx][ty] < level) {
                        continue;
                    }
                    // 注意这里同一个位置，可以被加入多次，
                    q.push({tx, ty});
                }
            }
        };
        
        queue<vector<int>> qp;
        queue<vector<int>> qa;
        vector<vector<bool>> vp(rows, vector<bool>(cols, false));
        vector<vector<bool>> va(rows, vector<bool>(cols, false));
        
        for (int col = 0; col < cols; ++col) {
            qp.push({0, col}); // top 
            qa.push({rows - 1, col}); // bottom
        }
        
        for (int row = 0; row < rows; ++row) {
            qp.push({row, 0}); // left
            qa.push({row, cols - 1}); // right
        }
        
        bfs(qp, vp);
        bfs(qa, va);
        
        vector<vector<int>> ans;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (vp[i][j] && va[i][j]) {
                    ans.emplace_back(vector<int>({i, j}));
                }
            }
        }
        return ans;
    }
};
````

