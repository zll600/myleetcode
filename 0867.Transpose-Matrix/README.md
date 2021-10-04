# [867. Transpose Matrix](https://leetcode.com/problems/transpose-matrix/)

Given a 2D integer array `matrix`, return *the **transpose** of* `matrix`.

The **transpose** of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.

![img](https://assets.leetcode.com/uploads/2021/02/10/hint_transpose.png)

 

**Example 1:**

```
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]
```

**Example 2:**

```
Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 1000`
- `1 <= m * n <= 105`
- `-109 <= matrix[i][j] <= 109`

## 题目大意

给定一个二维数组的整数矩阵，返回转置后的矩阵

矩阵的 **转置** 是指将矩阵的主对角线翻转，交换矩阵的行索引与列索引。

## 解题思路

将矩阵沿对角线调换位置，这里需要注意的一点是，因为矩阵的行数和列数不一定相等，所以最好新建一个矩阵，而不要原地改动

## 解法1

`````c++
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        // 因为行数不等于列数，所以只能新建一个数组来表示
        vector<vector<int>> res(cols, vector<int>(rows));
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                res[i][j] = matrix[j][i];
            }
        }
        return res;
    
        /* 这种方法只适合于行数等于列数
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            // 内层循环从 i + 1 开始
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        return matrix;
        */
    }
};
`````

