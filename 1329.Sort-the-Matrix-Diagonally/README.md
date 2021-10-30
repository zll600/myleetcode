# [1329. Sort the Matrix Diagonally](https://leetcode.com/problems/sort-the-matrix-diagonally/)

## 题目

A **matrix diagonal** is a diagonal line of cells starting from some cell in either the topmost row or leftmost column and going in the bottom-right direction until reaching the matrix's end. For example, the **matrix diagonal** starting from `mat[2][0]`, where `mat` is a `6 x 3` matrix, includes cells `mat[2][0]`, `mat[3][1]`, and `mat[4][2]`.

Given an `m x n` matrix `mat` of integers, sort each **matrix diagonal** in ascending order and return *the resulting matrix*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/01/21/1482_example_1_2.png)

```
Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
```

**Example 2:**

```
Input: mat = [[11,25,66,1,69,7],[23,55,17,45,15,52],[75,31,36,44,58,8],[22,27,33,25,68,4],[84,28,14,11,5,50]]
Output: [[5,17,4,1,52,7],[11,11,25,45,8,69],[14,23,25,44,58,15],[22,27,31,36,50,66],[84,28,75,33,55,68]]
```

 

**Constraints:**

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n <= 100`
- `1 <= mat[i][j] <= 100`

## 题目大意

矩阵的对角线是指从最顶部的一行或者最左边的一列开始向右下方向，直到到达矩阵的最底端，

给定一个 m x n 的整数矩阵 mat，将矩阵的每条对角线按照升序排序，然会结果矩阵

## 解题思路

### Solution 1:

这种解法可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/1300~1399/1329.Sort-the-Matrix-Diagonally/

记录每一条对角线，然后排序，还原到原矩阵，覆盖原矩阵

```c++
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        
        // 收集每个对角线上的所有元素
        unordered_map<int, deque<int>> diagonals;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                diagonals[i - j].push_back(mat[i][j]);
            }
        }
        
        // 对每组元素进行排序
        for (auto& diagonal : diagonals) {
            sort(diagonal.second.begin(), diagonal.second.end());
        }
        
        // 还原，覆盖原来的位置
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat[i][j] = diagonals[i - j].front();
                diagonals[i - j].pop_front();
            }
        }
        
        return mat;
    }
};
```

### Solution 2:

这种解法和上一种解法的思路是一样的，但是这里利用  vector 代替 deque ，效率更高一些，另外这里就需要注意排序的问题

````c++
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        
        // 保存每一条对角线和其元素的集合
        unordered_map<int, vector<int>> diagonals;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                diagonals[i - j].push_back(mat[i][j]);
            }
        }
        // 对每一条对角线进行排序
        for (auto& diagonal : diagonals) {
            auto func = [](int a, int b) -> bool {
                return a > b;
            };
            
            // 按照逆序排序
            sort(diagonal.second.begin(), diagonal.second.end(), func);
        }
        
        // 恢复
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat[i][j] = diagonals[i - j].back();
                diagonals[i - j].pop_back();
            }
        }
        
        return mat;
    }
};
````

