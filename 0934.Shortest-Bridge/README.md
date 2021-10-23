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

这种解法，可以参考这篇题解：https://leetcode-cn.com/problems/shortest-bridge/solution/dfszhao-di-yi-ge-dao-bfszhao-zui-duan-ju-9vz5/

具体思路就是先用 DFS 将任意一个岛中的所有元素反转为 2，顺便记录此岛周围的所有 0，

接下来就是和第 542 题一样的过程了， BFS 搜索直到找到第一个 1 为止，直接返回，如果是 2 直接跳过，如果是0，则反转为 2，加入队列中

更多的细节，看一参考代码

 ````c++
 class Solution {
 public:
     int shortestBridge(vector<vector<int>>& grid) {
         rows_ = grid.size();
         cols_ = grid[0].size();
         
         // 找到任意一个岛，反转所有元素
         bool flipped = false;
         for (int i = 0; i < rows_; ++i) {
             if (flipped == true) {
                 break;
             }
             for (int j = 0; j < cols_; ++j) {
                 if (grid[i][j] == 1) {
                     DFS(grid, i, j);
                     flipped = true;
                     break;  // 确保这个 if 只执行一次
                 }
             }
         }
         
         // 距离
         int level = 0;
         while (!points_.empty()) {
             ++level;
             // cout << level << endl;
             // 遍历整层
             const int len = points_.size();
             for (int i = 0; i < len; ++i) {
                 pair<int, int> item = points_.front();
                 points_.pop();
                 
                 int x = item.first;
                 int y = item.second;
                 
                 for (const vector<int>& dir : dirs_) {
                     int nx = x + dir[0];
                     int ny = y + dir[1];
                     
                     // 如果下标不合法或者值为 2，跳过
                     if (!IsValid(nx, ny) || grid[nx][ny] == 2) {
                         continue;
                     }
                     // 如果值为 1，直接返回结果
                     if (grid[nx][ny] == 1) {
                         return level;
                     }
                     // 如果值为 0
                     grid[nx][ny] = 2;
                     points_.push(make_pair(nx, ny));
                 }
             }
         }
         
         return 0;
     }
     
  private:
     vector<vector<int>> dirs_ = {
         {1, 0},
         {-1, 0},
         {0, -1},
         {0, 1}
     };
     
     int rows_;  // 网格的行数
     int cols_;  // 网格的列数
     queue<pair<int, int>> points_;  // 队列
     
     // 检验下标是否合法
     bool IsValid(int x, int y) {
         return x >= 0 && x < rows_ && y >= 0 && y < cols_;
     }
     
     // DFS 反转一个岛的值为 2，并将周围的 0 加入队列中
     void DFS(vector<vector<int>>& grid, int x, int y) {
         // 如果下标越界，或者就是岛的一部分跳过
         if (!IsValid(x, y) || grid[x][y] == 2) {
             return;
         }
         // 如果是岛周围的 0，加入队列中
         if (grid[x][y] == 0) {
             points_.push(make_pair(x, y));
             return;
         }
         
         // 反转
         grid[x][y] = 2;
         // 状态转移
         for (const vector<int>& dir : dirs_) {
             DFS(grid, x + dir[0], y + dir[1]);
         }
     }
 };
 ````



