# [51. N-Queens](https://leetcode.com/problems/n-queens/)

## 题目

The **n-queens** puzzle is the problem of placing `n` queens on an `n x n` chessboard such that no two queens attack each other.

Given an integer `n`, return *all distinct solutions to the **n-queens puzzle***. You may return the answer in **any order**.

Each solution contains a distinct board configuration of the n-queens' placement, where `'Q'` and `'.'` both indicate a queen and an empty space, respectively.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/13/queens.jpg)

```
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
```

**Example 2:**

```
Input: n = 1
Output: [["Q"]]
```

 

**Constraints:**

- `1 <= n <= 9`

## 题目大意

n 皇后问题是在一个 n x n 的棋盘上，放置 n 个皇后的问题，任意两个皇后不能相邻，即不在同一行，不在同一列，不在同一对角线，

给定一个整数 n 返回所有不同的 n 皇后问题的解，‘Q‘和’,‘分别代表皇后和空格

## 解题思路

* 这道题做的时候采用的逐行放，所以只需要判断列上和对角线上是否有重复，
* 这道题目有进阶的位运算写法（留待以后实现）

## 代码

````c++
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        std::vector<std::string> chessboard(n, std::string(n, '.'));
        Backtracking(chessboard, n, 0);
        
        return res;
    }
    
private:
    vector<vector<string>> res;
    
    bool IsValid(const vector<string>& chessboard, int row, int col) {
        // 只需要判断之前出现
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < chessboard.size(); ++j) {
                // 这里判断同一列和对角线能不能放
                if (chessboard[i][j] == 'Q' && (j == col || (abs(row - i) == abs(col - j)))) {
                    return false;
                }
            }
        }
                    
        return true;
    }
        
    void Backtracking(vector<string>& chessboard, int n, int row) {
        if (row == n) {
            res.push_back(chessboard);
            return;
        }
        
        for (int i = 0; i < n; ++i) {
            if(IsValid(chessboard, row, i)) {
                chessboard[row][i] = 'Q';
                Backtracking(chessboard, n, row + 1);
                chessboard[row][i] = '.';
            }
        }
    }
};
````

