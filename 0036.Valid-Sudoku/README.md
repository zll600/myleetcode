# [36. Valid Sudoku](https://leetcode.com/problems/valid-sudoku/)

## 题目

Determine if a `9 x 9` Sudoku board is valid. Only the filled cells need to be validated **according to the following rules**:

1. Each row must contain the digits `1-9` without repetition.
2. Each column must contain the digits `1-9` without repetition.
3. Each of the nine `3 x 3` sub-boxes of the grid must contain the digits `1-9` without repetition.

**Note:**

- A Sudoku board (partially filled) could be valid but is not necessarily solvable.
- Only the filled cells need to be validated according to the mentioned rules.

**Example 1**:

```
Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true
```

**Example 2**:

```
Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being 
    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.
```

**Note**:

- A Sudoku board (partially filled) could be valid but is not necessarily solvable.
- Only the filled cells need to be validated according to the mentioned rules.
- The given board contain only digits `1-9` and the character `'.'`.
- The given board size is always `9x9`.

## 题目大意

判断一个9*9的数独是否有效，根据以下规则，只需要判断已经填入的数独是否有效

	* 数字1-9在每一行只能出现一次
	* 数字1-9在每一列只能出现一次
	* 数字1-9在一个3*3的宫格内只能出现一次

## 解题思路

* 按照题目要求，暴力解，每行不能重复，每列不能重复，每个9宫格不能重复
* 设置缓存，以空间换时间
  * 整个`board`有9个9宫格，每个子九宫格由`row`和`col`的组合唯一确定，
  * 第一个维度只确定行、列、子九宫格，第二个维度标记出现过的数

## 代码

````c++
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        /*
        // 解法一：Brute force
        
        // 判断行
        for (int i = 0; i < 9; ++i) {
            vector<bool> used(10, false);
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    int cur = board[i][j] - '0';
                    
                    if (cur > 9 || cur < 1) {
                        return false;
                    } else if (used[cur] == true) {
                        return false;
                    }
                    used[cur] = true;
                }
            }
        }
        
        // 判断列
        for (int col = 0; col < 9; ++col) {
            vector<bool> used(10, false);
            for (int row = 0; row < 9; ++row) {
                if (board[row][col] != '.') {
                    int cur = board[row][col] - '0';
                    
                    if (cur > 9 || cur < 1) {
                        return false;
                    } else if (used[cur] == true) {
                        return false;
                    }
                    used[cur] = true;
                }
            }
        }
        
        // 判断每一个九宫格
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                vector<bool> used(10, false);
                for (int subrow = row * 3; subrow < row * 3 + 3; ++subrow) {
                    for (int subcol = col * 3; subcol < col * 3 + 3; ++subcol) {
                        if (board[subrow][subcol] != '.') {
                            int cur = board[subrow][subcol] - '0';
                            
                            if (cur > 9 || cur < 1) {
                                return false;
                            } else if (used[cur] == true) {
                                return false;
                            }
                            
                            used[cur] = true;
                        }
                    }
                }
            }
        }
        
        return true;
        */
        
        // 解法二：利用缓存
        vector<vector<bool>> row_buf(9, vector<bool>(10, false));
        vector<vector<bool>> col_buf(9, vector<bool>(10, false));
        vector<vector<bool>> sub_buf(9, vector<bool>(10, false));
        
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] != '.') {
                    int cur = board[row][col] - '0';
                    if (row_buf[row][cur] || col_buf[col][cur]
                        || sub_buf[row / 3 * 3 + col / 3][cur]) {
                        return false;
                    }
                    row_buf[row][cur] = col_buf[col][cur] = true;
                    
                    //这里求九宫格位置的方法，相当于将一个三维数组化为二维数组，
                    sub_buf[(row / 3) * 3 + col / 3][cur] = true;
                }
            }
        }
        return true;
    }
};
````



