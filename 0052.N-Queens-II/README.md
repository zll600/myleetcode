# [52. N-Queens II](https://leetcode.com/problems/n-queens-ii/)

## 题目

The **n-queens** puzzle is the problem of placing `n` queens on an `n x n` chessboard such that no two queens attack each other.

Given an integer `n`, return *the number of distinct solutions to the **n-queens puzzle***.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/13/queens.jpg)

```
Input: n = 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
```

**Example 2:**

```
Input: n = 1
Output: 1
```

 

**Constraints:**

- `1 <= n <= 9`

## 题目大意

给定一个整数 n ，返回 n 皇后问题解的个数

## 解题思路

* 这道题目可以参考第 51 题，两道题很像

## 代码

````c++
class Solution {
public:
    int totalNQueens(int n) {
        res = 0;
        vector<string> chessboard(n, string(n, '.'));
        Backtracking(chessboard, n, 0);
        return res;
    }
    
 private:
    int res;
    
    bool IsValid(const vector<string>& chessboard, int row, int col) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < chessboard.size(); ++j) {
                if (chessboard[i][j] == 'Q' && (j == col || (abs(row - i) == abs(col - j)))) {
                    return false;
                }
            }
        }
        return true;
    }
    
    void Backtracking(vector<string>& chessboard, int n, int row) {
        if (row == n) {
            ++res;
        }
        
        for (int i = 0; i < chessboard.size(); ++i) {
            if (IsValid(chessboard, row, i)) {
                chessboard[row][i] = 'Q';
                Backtracking(chessboard, n, row + 1);
                chessboard[row][i] = '.';
            }
        }
    }
};
````

