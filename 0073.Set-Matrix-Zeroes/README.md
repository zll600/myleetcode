# [73. Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/)

## 题目

Given an `m x n` integer matrix `matrix`, if an element is `0`, set its entire row and column to `0`'s, and return *the matrix*.

You must do it [in place](https://en.wikipedia.org/wiki/In-place_algorithm).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/08/17/mat1.jpg)

```
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/08/17/mat2.jpg)

```
Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[0].length`
- `1 <= m, n <= 200`
- `-231 <= matrix[i][j] <= 231 - 1`

 

**Follow up:**

- A straightforward solution using `O(mn)` space is probably a bad idea.
- A simple improvement uses `O(m + n)` space, but still not the best solution.
- Could you devise a constant space solution?

## 题目大意

给定一个 m x n 的矩阵，如果一个元素为0，则将整个行和列都设为 0，必须原地解决，

## 解题思路

这是一道模拟题，更重要的是考查的对程序的控制能力，而非算法，

### 解法1

这种解法采用缓存的方法，需要扫描两遍，一边记录0，一边置0；

`````c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        unordered_set<int> zero_row;  // 这里存放有 0 的行
        unordered_set<int> zero_col;  // 这里存放有 0 的列
        
        // 记录 0 出现的位置
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 0) {
                    zero_row.insert(i);
                    zero_col.insert(j);
                }
            }
        }
        
        // 置 0，凡是坐标中的行或列出现在 zero_row或者 zero_col 中的都置为0
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (zero_row.find(i) != zero_row.end()
                   || zero_col.find(j) != zero_col.end()) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
`````

### 解法2

优化的思路就是避免使用(m + n)的额外空间，

这里的关键思路就是用第一行和第一列来记录其余位置所在的行或者 列有没有出现 0，如果其他位置出现0，只需在第一行和第一列作标记即可

另外还需要判断第一行第一列本身是否含有 0，如果含有 0，则直接将 第一行、第一列置为0，

`````c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        bool row_zero = false;
        bool col_zero = false;
        // 记录第一列
        for (int i =  0; i < rows; i++) {
            if (matrix[i][0] == 0) {
                col_zero = true;
                break;
            }
        }
        
        // 记录第一行
        for (int j = 0; j < cols; j++) {
            if (matrix[0][j] == 0) {
                row_zero = true;
                break;
            }
        }
        
        // 记录其他位置
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }
        
        // 置 0
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // 第一列清 0
        if (col_zero) {
            for (int i = 0; i < rows; i++) {
                matrix[i][0] = 0;
            }
        }
        
        // 第一行清 0
        if (row_zero) {
            for (int j = 0; j < cols; j++) {
                matrix[0][j] = 0;
            }
        }
    }
};
`````

