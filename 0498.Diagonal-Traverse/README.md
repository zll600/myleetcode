# [498. Diagonal Traverse](https://leetcode.com/problems/diagonal-traverse/)

## 题目

Given an `m x n` matrix `mat`, return *an array of all the elements of the array in a diagonal order*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/10/diag1-grid.jpg)

```
Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]
```

**Example 2:**

```
Input: mat = [[1,2],[3,4]]
Output: [1,2,3,4]
```

 

**Constraints:**

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n <= 104`
- `1 <= m * n <= 104`
- `-105 <= mat[i][j] <= 105`

## 题目大意

给定一个 m x n 的矩阵 mat，返回这个矩阵按照对角线遍历的结果

### 解题思路

对于模拟题，一定要分清楚阶段，定义合理的阶段很重要

拿这道题来说，有四个阶段：

* 水平向左
* 沿左下
* 垂直向下
* 沿右上

只要分清楚这四个阶段，分别进行判断就可以了

### 解法1： 

````c++
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        int x = 0;
        int y = 0;
        vector<int> res;
        bool is_left_down = false;
        for (int k = 0; k < rows * cols; ++k) {
            res.push_back(matrix[x][y]);
            
            if (is_left_down && x < rows - 1 && y > 0) {  // 沿左下方向
                ++x;
                --y;
            } else if (!is_left_down && x > 0 && y < cols - 1) {  // 沿右上方向
                --x;
                ++y;
            } else {
                if ((x == 0 || x == rows - 1) && y < cols - 1) {  // 水平向左
                    ++y;
                } else if ((y == 0 || y == cols - 1) && x < rows - 1) {  // 垂直向下
                    ++x;
                }
                is_left_down = !is_left_down;  // 取反
            }
        }
        
        return res;  // 返回结果
    }
};
````

