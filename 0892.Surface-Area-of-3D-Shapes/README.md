# [892. Surface Area of 3D Shapes](https://leetcode.com/problems/surface-area-of-3d-shapes/)

## 题目

You are given an `n x n` `grid` where you have placed some `1 x 1 x 1` cubes. Each value `v = grid[i][j]` represents a tower of `v` cubes placed on top of cell `(i, j)`.

After placing these cubes, you have decided to glue any directly  adjacent cubes to each other, forming several irregular 3D shapes.

Return *the total surface area of the resulting shapes*.

**Note:** The bottom face of each shape counts toward its surface area.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/08/tmp-grid2.jpg)

```
Input: grid = [[1,2],[3,4]]
Output: 34
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/01/08/tmp-grid4.jpg)

```
Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
Output: 32
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/01/08/tmp-grid5.jpg)

```
Input: grid = [[2,2,2],[2,1,2],[2,2,2]]
Output: 46
```

 

**Constraints:**

- `n == grid.length == grid[i].length`
- `1 <= n <= 50`
- `0 <= grid[i][j] <= 50`

##  题目大意

在 `N * N` 的网格上，我们放置一些 `1 * 1 * 1`  的立方体。每个值 `v = grid[i][j]` 表示 `v` 个正方体叠放在对应单元格 `(i, j)` 上。

请你返回最终形体的表面积。

## 解题思路

这道题如果正向思考去累加每一个面，反而不好做，但是可以反向减来做

### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0892.Surface-Area-of-3D-Shapes/)

````c++
class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int area = 0;

        const int n = grid.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    continue;
                }

                // 侧面 + 2 个底面
                area += grid[i][j] * 4 + 2;

                // up
                if (i > 0) {
                    int diff = min(grid[i][j], grid[i - 1][j]);
                    area -= diff;
                }

                // down
                if (i < n - 1) {
                    int diff = min(grid[i][j], grid[i + 1][j]);
                    area -= diff;
                }

                // left
                if (j > 0) {
                    int diff = min(grid[i][j], grid[i][j - 1]);
                    area -= diff;
                }

                // right
                if (j < n - 1) {
                    int diff = min(grid[i][j], grid[i][j + 1]);
                    area -= diff;
                }
            }
        }

        return area;
    }
};
````
