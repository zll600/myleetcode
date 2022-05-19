# [1260. Shift 2D Grid](https://leetcode.com/problems/shift-2d-grid/)

Given a 2D `grid` of size `m x n` and an integer `k`. You need to shift the `grid` `k` times.

In one shift operation:

- Element at `grid[i][j]` moves to `grid[i][j + 1]`.
- Element at `grid[i][n - 1]` moves to `grid[i + 1][0]`.
- Element at `grid[m - 1][n - 1]` moves to `grid[0][0]`.

Return the *2D grid* after applying shift operation `k` times.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/11/05/e1.png)

```
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[9,1,2],[3,4,5],[6,7,8]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/11/05/e2.png)

```
Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]
```

**Example 3:**

```
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
Output: [[1,2,3],[4,5,6],[7,8,9]]
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m <= 50`
- `1 <= n <= 50`
- `-1000 <= grid[i][j] <= 1000`
- `0 <= k <= 100`

##

给你一个 `m` 行 `n` 列的二维网格 `grid` 和一个整数 `k`。你需要将 `grid` 迁移 `k` 次。每次「迁移」操作将会引发下述活动：

- 位于 `grid[i][j]` 的元素将会移动到 `grid[i][j + 1]`
- 位于 `grid[i][n - 1]` 的元素将会移动到 `grid[i + 1][0]`
- 位于 `grid[m - 1][n - 1]` 的元素将会移动到 `grid[0][0]`

请你返回 `k` 次迁移操作后最终得到的 二维网格。

##

这道题目就是按照一定的规则，来移动矩阵里的数据，按照题意模拟即可，这里还要注意的就是第 2 、3 条规则注意边界的判断

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1200~1299/1260.Shift-2D-Grid/)

````c++
class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 行的偏移量
                int nx = k / n + i;
                // 这里要注意边界
                if (j + (k % n) >= n) {
                    ++nx;
                }
                // 注意不要越界，和运算符的顺序
                ans[nx % m][(j + (k % n)) % n] = grid[i][j];
            }
        }
        return ans;
    }
};
```
