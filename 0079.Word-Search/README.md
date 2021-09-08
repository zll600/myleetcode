# [79. Word Search](https://leetcode.com/problems/word-search/)

## 题目

Given an `m x n` grid of characters `board` and a string `word`, return `true` *if* `word` *exists in the grid*.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/04/word2.jpg)

```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/11/04/word-1.jpg)

```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2020/10/15/word3.jpg)

```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
```

 

**Constraints:**

- `m == board.length`
- `n = board[i].length`
- `1 <= m, n <= 6`
- `1 <= word.length <= 15`
- `board` and `word` consists of only lowercase and uppercase English letters.

**Follow up:** Could you use search pruning to make your solution faster with a larger `board`?

## 题目大意

给定一个包含字符的二位网格和一个字符串，如果这个单词存在于网格中，就返回 true，否则返回 false。

单词必须的按照字母出现的顺序，通过网格中相邻的字母构成，相邻的字母是指网格中水平相邻或者垂直相邻。同一个单元格中的字母不允许被使用多次。

## 解题思路

* 这道题目可以使用回溯法，穷举每一种可能，

## 代码

`````c++
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size();
        cols = board[0].size();
        vector<vector<bool>> visit(rows, vector<bool>(cols, false));
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] != word[0]) {   // 如果与第一个字符都不相同，则直接跳过，
                    continue;
                }
                
                if (Backtracking(board, word, visit, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    
 private:
    int rows;
    int cols;
    // 偏移量数组，在二维搜索中经常会遇到，
    vector<vector<int>> dirs = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
    };
    
    // 检验下标是否越界
    bool IsValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
    
    /*
    bool Backtracking(const vector<vector<char>>& board, const string& word,
                      vector<vector<bool>>& visit, int x, int y, int idx) {
        if (!IsValid(x, y)) {
            return false;
        }
        
        if (visit[x][y] == true || board[x][y] != word[idx]) {
            return false;
        }
        
        if (idx == word.size() - 1) {
            return board[x][y] == word.back();
        }
        

        visit[x][y] = true;
        if (Backtracking(board, word, visit, x + 1, y, idx + 1)
            || Backtracking(board, word, visit, x - 1, y, idx + 1)
            || Backtracking(board, word, visit, x, y - 1, idx +1)
            || Backtracking(board, word, visit, x, y + 1, idx + 1)) {
            return true;
        }
        visit[x][y] = false;
        return false;
    }
    */
    
    bool Backtracking(const vector<vector<char>>& board, const string& word,
                     vector<vector<bool>>& visit, int x, int y, int idx) {
        if (idx == word.size() - 1) {
            return board[x][y] == word[idx];
        }
        
        if (board[x][y] == word[idx]) {
            visit[x][y] = true;
            for (const vector<int>& dir : dirs) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                if (IsValid(nx, ny) && !visit[nx][ny]
                    && Backtracking(board, word, visit, nx, ny, idx + 1)) {
                    return true;
                }
            }
            
            visit[x][y] = false;
        }
        return false;
    }
};
`````

