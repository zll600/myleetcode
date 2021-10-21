# [934. Shortest Bridge](https://leetcode-cn.com/problems/shortest-bridge/)

## 题目

In a given 2D binary array `grid`, there are two islands. (An island is a 4-directionally connected group of `1`s not connected to any other 1s.)

Now, we may change `0`s to `1`s so as to connect the two islands together to form 1 island.

Return the smallest number of `0`s that must be flipped. (It is guaranteed that the answer is at least 1.)

 

**Example 1:**

```
Input: grid = [[0,1],[1,0]]
Output: 1
```

**Example 2:**

```
Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
Output: 2
```

**Example 3:**

```
Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1
```

 

**Constraints:**

- `2 <= grid.length == grid[0].length <= 100`
- `grid[i][j] == 0` or `grid[i][j] == 1`

## 题目大意

在一个二维的二进制数组 grid中，有两个岛（岛是由四面相连的 `1` 形成的一个最大组），

我们将 现在，我们可以将 `0` 变为 `1`，以使两座岛连接起来，变成一座岛。

返回必须翻转的 `0` 的最小数目。（可以保证答案至少是 `1` 。）

## 解题思路

这道题可以联系第 542 题，都使用 bfs，不过这道题还使用了 DFS

### Solution 1: BFS + DFS

具体思路就是先用 DFS 将任意一个岛中的所有元素反转为 2，顺便记录此岛周围的所有 0，

接下来就是和第 542 题一样的过程了， BFS 搜索直到找到第一个 1 为止，直接返回，如果是 2 直接跳过，如果是0，则反转为 2，加入队列中

更多的细节，看一参考代码

 ````c++
 class Solution {
 public:
     int shortestBridge(vector<vector<int>>& grid) {
         rows_ = grid.size();  // 求行数
         cols_ = grid[0].size();  // 求列数
         
         // 先找到任意一个岛，DFS将其所有元素反转为 2
         bool flipped = false;  // 是否已经找到一个岛
         for (int i = 0; i < rows_; ++i) {
             if (flipped) {
                 break;
             }
             for (int j = 0; j < cols_; ++j) {
                 if (grid[i][j] == 1) {
                     DFS(grid, i, j);  // 这里使用 DFS 来遍历反转一个岛的所有元素
                     flipped = true;
                 }
             }
         }
         
         // BFS 来求最短路径
         int level = 0;
         while (!que_.empty()) {
             ++level;
             const int size = que_.size();  // 一次遍历一层
             for (int i = 0; i < size; ++i) {
                 pair<int, int> item = que_.front();
                 que_.pop();
                 int x = item.first;
                 int y = item.second;
                 
                 // 状态转移
                 for (const auto& dir : dirs_) {
                     int nx = x + dir[0];
                     int ny = y + dir[1];
                     
                     // 下标越界 或者 是本岛中的元素，直接跳过
                     if (!IsInGrid(nx, ny) || grid[nx][ny] == 2) {
                         continue;
                     }
                     // 如果是 1，说明找到了另一个岛，直接返回
                     if (grid[nx][ny] == 1) {
                         return level;
                     }
                     // 如果是 0，将 0 反转为 2，并入本岛
                     grid[nx][ny] = 2;
                     que_.push(make_pair(nx, ny));
                 }
             }
         }
         
         return 0;
     }
     
  private:
     vector<vector<int>> dirs_ = {
         {1, 0},
         {-1, 0},
         {0, 1},
         {0, -1}
     };
     
     int rows_;
     int cols_;
     
     queue<pair<int, int>> que_;
     
     bool IsInGrid(int x, int y) {
         return x >= 0 && x < rows_ && y >= 0 && y <= cols_;
     }
     
     void DFS(vector<vector<int>>& grid, int x, int y) {
         // 反转
         grid[x][y] = 2;
         // 状态转移
         for (const auto& dir : dirs_) {
             int nx = x + dir[0];
             int ny = y + dir[1];
             
             // 下标越界 或者已经反转过了，直接跳过
             if (!IsInGrid(nx, ny) || grid[nx][ny] == 2) {
                 continue;
             }
             
             // 将岛周围的 0 全部加入到 队列中
             if (grid[nx][ny] == 0) {
                 que_.push(make_pair(nx, ny));
                 continue;
             }
             
             // 沿着岛中的 1 继续深搜
             DFS(grid, nx, ny);
         }
     }
 };
 ````



