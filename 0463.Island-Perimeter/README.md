# [463. Island Perimeter](https://leetcode-cn.com/problems/island-perimeter/)

## 题目

You are given `row x col` `grid` representing a map where `grid[i][j] = 1` represents land and `grid[i][j] = 0` represents water.

Grid cells are connected **horizontally/vertically** (not diagonally). The `grid` is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).

The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/10/12/island.png)

```
Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
Output: 16
Explanation: The perimeter is the 16 yellow stripes in the image above.
```

**Example 2:**

```
Input: grid = [[1]]
Output: 4
```

**Example 3:**

```
Input: grid = [[1,0]]
Output: 4
```

 

**Constraints:**

- `row == grid.length`
- `col == grid[i].length`
- `1 <= row, col <= 100`
- `grid[i][j]` is `0` or `1`.
- There is exactly one island in `grid`.

## 题目大意

给定一个 `row x col` 的二维网格地图 `grid` ，其中：`grid[i][j] = 1` 表示陆地， `grid[i][j] = 0` 表示水域。

网格中的格子 **水平和垂直** 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。

岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。



## 解题思路

这道题目转化一下就是计算与水相接的边的数目，

### Solution 1:

```c++
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        const int rows = grid.size();
        const int cols = grid[0].size();
        int counter = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1) {
                    if (i - 1 < 0 || grid[i - 1][j] == 0) {
                        ++counter;
                    }
                    if (i + 1 >= rows || grid[i + 1][j] == 0) {
                        ++counter;
                    }
                    if (j - 1 < 0 || grid[i][j - 1] == 0) {
                        ++counter;
                    }
                    if (j + 1 >= cols || grid[i][j + 1] == 0) {
                        ++counter;
                    }
                }
            }
        }
        return counter;
    }
};
```

