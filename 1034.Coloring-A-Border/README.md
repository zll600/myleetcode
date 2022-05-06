# [1034. Coloring A Border](https://leetcode.com/problems/coloring-a-border/)

You are given an `m x n` integer matrix `grid`, and three integers `row`, `col`, and `color`. Each value in the grid represents the color of the grid square at that location.

Two squares belong to the same **connected component** if they have the same color and are next to each other in any of the 4 directions.

The **border of a connected component** is all the squares in the connected component that are either **4-directionally** adjacent to a square not in the component, or on the boundary of the grid (the first or last row or column).

You should color the **border** of the **connected component** that contains the square `grid[row][col]` with `color`.

Return *the final grid*.

 

**Example 1:**

```
Input: grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
Output: [[3,3],[3,2]]
```

**Example 2:**

```
Input: grid = [[1,2,2],[2,3,2]], row = 0, col = 1, color = 3
Output: [[1,3,3],[2,3,3]]
```

**Example 3:**

```
Input: grid = [[1,1,1],[1,1,1],[1,1,1]], row = 1, col = 1, color = 2
Output: [[2,2,2],[2,1,2],[2,2,2]]
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 50`
- `1 <= grid[i][j], color <= 1000`
- `0 <= row < m`
- `0 <= col < n`

## 题目大意

给你一个大小为 `m x n` 的整数矩阵 `grid` ，表示一个网格。另给你三个整数 `row`、`col` 和 `color` 。网格中的每个值表示该位置处的网格块的颜色。

当两个网格块的 *颜色相同* ，而且在四个方向中任意一个方向上 *相邻时，它们属于同一连通分量

边界：在连通分量的块中（前提）并且满足以下条件之一：


（1）要么上下左右存在一个块不在连通分量里面 

（2）要么这个块的位置在整个grid的边框上

请你使用指定颜色 color 为所有包含网格块 `grid[row][col]` 的连通分量的边界进行着色，并返回最终的网格 grid 

## 解题思路

这道题关键在于搞清楚题意，这里我花了很长时间，才搞清楚题意

- 找到给定点所在的连通分量
- 找到给定的连通分量边界
- 最后进行染色就可以了

这里不要在 bfs 的过程中进行染色，回影响到后面的判断条件

### Solution 1: BFS

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/coloring-a-border/solution/shua-ti-ri-ji-day2-by-youngzz-2-4hin/)

````c++
class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        // 访问限制
        const int rows = grid.size(), cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        // BFS
        queue<pair<int, int>> que;
        que.emplace(row, col);

        // 记录需要染色的地方
        vector<pair<int, int>> changes;
        while (!que.empty()) {
            auto [x, y] = que.front();
            que.pop();

            // 防止循环访问
            if (visited[x][y]) {
                continue;
            }

            // cout << x << " -- " << y << " === ";

            visited[x][y] = true;
            // 判断这个点是不是连通分量边界
            bool flag = false;
            // 遍历
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs_[i];
                int ny = y + dirs_[i + 1];

                // 如果处于边界，那么任何的移动都会导致越界，所有提前判断
                if (x == 0 || y == 0 || x == rows - 1 || y == cols - 1) {
                    flag = true;
                }

                // 越界，或者已经访问过了
                if (nx < 0 || nx >= rows || ny < 0 || ny >= cols || visited[nx][ny]) {
                    continue;
                }

                // 如果属于这个连通分量，就加入到队列中
                if (grid[x][y] == grid[nx][ny]) {
                    que.emplace(nx, ny);
                }

                // 如果不属于连通分量
                if (grid[x][y] != grid[nx][ny]) {
                    // cout << x << " -- " << y << endl;
                    flag = true;
                }
            }

            if (flag) {
                changes.emplace_back(x, y);
            }
            // cout << endl;
        }

        for (auto&& [x, y] : changes) {
            grid[x][y] = color;
        }

        return grid;
    }

 private:
    vector<int> dirs_ = { 0, 1, 0, -1, 0 };
};
````
