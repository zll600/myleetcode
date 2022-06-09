# [994. Rotting Oranges](https://leetcode.cn/problems/rotting-oranges/)

## 题目

You are given an `m x n` `grid` where each cell can have one of three values:

- `0` representing an empty cell,
- `1` representing a fresh orange, or
- `2` representing a rotten orange.

Every minute, any fresh orange that is **4-directionally adjacent** to a rotten orange becomes rotten.

Return *the minimum number of minutes that must elapse until no cell has a fresh orange*. If *this is impossible, return* `-1`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/02/16/oranges.png)

```
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
```

**Example 2:**

```
Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
```

**Example 3:**

```
Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 10`
- `grid[i][j]` is `0`, `1`, or `2`.

## 题目大意

在给定的 `m x n` 网格 `grid` 中，每个单元格可以有以下三个值之一：

-   值 0 代表空单元格；
-   值 1 代表新鲜橘子；
-   值 2 代表腐烂的橘子。

每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂

返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1

## 解题思路

其实看到这道题目第一反应是并查集，但是并查集只能判断最后有没有新鲜橘子，对于求解最小分钟树没有帮助

这道题目求最小分钟数，其实也就是求 腐烂橘子到新鲜橘子的最短路径

### Solution 1:

这里注意 BFS 的执行条件，一定要考虑 fresh 的大小，

````c++
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        
        queue<pair<int, int>> que;
        int fresh = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    ++fresh;
                } else if (grid[i][j] == 2) {
                    que.emplace(i, j);
                }
            }
        }
        
        int minutes = 0;
        while (fresh > 0 && !que.empty()) {
            ++minutes;
            
            const int len = que.size();
            for (int i = 0; i < len; ++i) {
                auto& [row, col] = que.front();
                que.pop();
                
                for (int i = 0; i < 4; ++i) {
                    int nx = row + dirs_[i];
                    int ny = col + dirs_[i + 1];
                    // 这里将 1 表示为 2，就是在做标记，所以不用担心循环入队问题
                    if (IsValid(m, n, nx, ny) && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2;
                        --fresh;
                        que.emplace(nx, ny);
                    }
                }
            }
        }
        return fresh > 0 ? -1 : minutes;
    }
    
 private:
    vector<int> dirs_ = { 0, 1, 0, -1, 0 };
    
    bool IsValid(int m, int n, int row, int col) {
        return row >= 0 && row < m && col >= 0 && col < n;
    }
};
````
