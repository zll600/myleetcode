# [1219. Path with Maximum Gold](https://leetcode.cn/problems/path-with-maximum-gold/)

## 题目

In a gold mine `grid` of size `m x n`, each cell in this mine has an integer representing the amount of gold in that cell, `0` if it is empty.

Return the maximum amount of gold you can collect under the conditions:

- Every time you are located in a cell you will collect all the gold in that cell.
- From your position, you can walk one step to the left, right, up, or down.
- You can't visit the same cell more than once.
- Never visit a cell with `0` gold.
- You can start and stop collecting gold from **any** position in the grid that has some gold.

 

**Example 1:**

```
Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
Output: 24
Explanation:
[[0,6,0],
 [5,8,7],
 [0,9,0]]
Path to get the maximum gold, 9 -> 8 -> 7.
```

**Example 2:**

```
Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
Output: 28
Explanation:
[[1,0,7],
 [2,0,6],
 [3,4,5],
 [0,3,0],
 [9,0,20]]
Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 15`
- `0 <= grid[i][j] <= 100`
- There are at most **25** cells containing gold.

## 题目大意

你要开发一座金矿，地质勘测学家已经探明了这座金矿中的资源分布，并用大小为 `m * n` 的网格 `grid` 进行了标注。每个单元格中的整数就表示这一单元格中的黄金数量；如果该单元格是空的，那么就是 `0`

为了使收益最大化，矿工需要按以下规则来开采黄金：

-   每当矿工进入一个单元，就会收集该单元格中的所有黄金。
-   矿工每次可以从当前位置向上下左右四个方向走。
-   每个单元格只能被开采（进入）一次。
-   不得开采（进入）黄金数目为 0 的单元格。
-   矿工可以从网格中 任意一个 有黄金的单元格出发或者是停止

## 解题思路

### Solution 1:

这种解法利用返回值，不断更新最大值，可以节省 保存DFS结果的空间 

````c++
class Solution {
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int ans = 0;
        const int rows = grid.size();
        const int cols = grid[0].size();
        vector<vector<int>> visited(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!grid[i][j]) {
                    continue;
                }
                visited[i][j] = true;
                ans = max(ans, DFS(grid, i, j, visited));
                visited[i][j] = false;
            }
        }
        return ans;
    }
    
 private:
    vector<int> dirs_ = { 0, 1, 0, -1, 0};
    
    int DFS(const vector<vector<int>>& grid, int x, int y, 
            vector<vector<int>>& visited) {
        int ans = grid[x][y];
        for (int i = 0; i < 4; ++i) {
            int nx = x + dirs_[i];
            int ny = y + dirs_[i + 1];
            if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()
                || !grid[nx][ny] || visited[nx][ny]) {
                continue;
            }
            visited[nx][ny] = true;
            ans = max(ans, grid[x][y] + DFS(grid, nx, ny, visited));
            visited[nx][ny] = false;
        }
        return ans;
    }
};
````



