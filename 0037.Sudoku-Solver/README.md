# [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)

## 题目

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy **all of the following rules**:

1. Each of the digits `1-9` must occur exactly once in each row.
2. Each of the digits `1-9` must occur exactly once in each column.
3. Each of the digits `1-9` must occur exactly once in each of the 9 `3x3` sub-boxes of the grid.

The `'.'` character indicates empty cells.

 

**Example 1:**

```
Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
Explanation: The input board is shown above and the only valid solution is shown below:
```

 

**Constraints:**

- `board.length == 9`
- `board[i].length == 9`
- `board[i][j]` is a digit or `'.'`.
- It is **guaranteed** that the input board has only one solution.

## 题目大意

编写一个程序，通过填充空白的格子来解决数独问题

一个数独的解法必须遵循如下规则：

1. 数字1-9在每一行只能出现一次。
2. 数字1-9在每一列只能出现一次
3. 数字1-9在每一个9宫格只能出现一次

`'.'`表示空白格

## 解体思路

* 用DFS暴力回溯，填充每一个空格，利用回溯的返回值判断是否找到对应的解决方案
* 检查每个空格的值都满足要求
* 题目要求只有一个答案，回溯的过程中，找到一个答案就直接返回

## 代码

````c++
class Solution {
public:    
    bool IsValid(int row, int col, char val, const vector<vector<char>>& board) {
        // 检查行是否有重复
        for (int j = 0; j < 9; ++j) {
            if ( board[row][j] == val) {
                return false;
            }
        }
        
        //检查列是否有重复
        for (int i = 0; i < 9; ++i) {
            if (board[i][col] == val) {
                return false;
            }
        }
        
        //检查九宫格是否有重复
        int sub_row = (row / 3) * 3;
        int sub_col = (col / 3) * 3;
        for (int i = sub_row; i < sub_row + 3; ++i) {
            for (int j = sub_col; j < sub_col + 3; ++j) {
                if (board[i][j] == val) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    bool Backtracking(vector<vector<char>>& board) {       
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    continue;
                }
                
                for (char k = '1'; k <= '9'; ++k) {
                    if (IsValid(i, j, k, board)) {
                        board[i][j] = k;
                        if (Backtracking(board)) {
                            return true; // 只有一种解法，找到就直接返回 
                        }
                        board[i][j] = '.';
                    }
                }
                return false; // 一种解法也没找到，直接返回
            }
        }
        return true;
    }
    
    void solveSudoku(vector<vector<char>>& board) {
        Backtracking(board);        
    }
};
````



