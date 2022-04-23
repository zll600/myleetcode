# [885. Spiral Matrix III](https://leetcode.com/problems/spiral-matrix-iii/)

## 题目

You start at the cell `(rStart, cStart)` of an `rows x cols` grid facing east. The northwest corner is at the first row and column  in the grid, and the southeast corner is at the last row and column.

You will walk in a clockwise spiral shape to visit every position in  this grid. Whenever you move outside the grid's boundary, we continue  our walk outside the grid (but may return to the grid boundary later.).  Eventually, we reach all `rows * cols` spaces of the grid.

Return *an array of coordinates representing the positions of the grid in the order you visited them*.

 

**Example 1:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/08/24/example_1.png)

```
Input: rows = 1, cols = 4, rStart = 0, cStart = 0
Output: [[0,0],[0,1],[0,2],[0,3]]
```

**Example 2:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/08/24/example_2.png)

```
Input: rows = 5, cols = 6, rStart = 1, cStart = 4
Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
```

 

**Constraints:**

- `1 <= rows, cols <= 100`
- `0 <= rStart < rows`
- `0 <= cStart < cols`

## 题目大意

在 R 行 C 列的矩阵上，我们从 (r0, c0) 面朝东面开始。这里，网格的西北角位于第一行第一列，网格的东南角位于最后一行最后一列。现在，我们以顺时针按螺旋状行走，访问此网格中的每个位置。每当我们移动到网格的边界之外时，我们会继续在网格之外行走（但稍后可能会返回到网格边界）。最终，我们到过网格的所有 R * C 个空间。

要求输出按照访问顺序返回表示网格位置的坐标列表。

## 解题思路

这种题目需要按照一定的规律来做，这里我们需要控制的有：

- 遍历的方向
- 在这个方向上的步进
- 只将合法的位置添加到结果集中

### Solution 1: 

这道题目可以参考 [这篇题解](https://leetcode.com/problems/spiral-matrix-iii/)

````c++
class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int r_start, int c_start) {
        // 结果集
        vector<vector<int>> res;

        res.push_back({r_start, c_start});
        // 第几轮
        int round = 0;
        // 外层循环控制方向，内层循环控制步进
        for (int i = 0; res.size() < rows * cols; ++i) {
            for (int j = 0; j < i / 2 + 1; ++j) {
                r_start += dirs_[round % 4][0];
                c_start += dirs_[round % 4][1];

                if (r_start >= 0 && r_start < rows && c_start >= 0 && c_start < cols) {
                    res.push_back({r_start, c_start});
                }
            }
            ++round;
        }
        return res;
    }

 private:
    // 方向数组
    const vector<vector<int>> dirs_ =  {
        // 向左
        {0, 1},
        // 向下
        {1, 0},
        // 向右
        {0, -1},
        // 向上
        {-1, 0}
    };
};
````
