# [130. Surrounded Regions](https://leetcode.com/problems/surrounded-regions/)

Given an `m x n` matrix `board` containing `'X'` and `'O'`, *capture all regions that are 4-directionally surrounded by* `'X'`.

A region is **captured** by flipping all `'O'`s into `'X'`s in that surrounded region.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/xogrid.jpg)

```
Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
Explanation: Surrounded regions should not be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.
```

**Example 2:**

```
Input: board = [["X"]]
Output: [["X"]]
```

 

**Constraints:**

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 200`
- `board[i][j]` is `'X'` or `'O'`.

## 题目大意

给定一个二位矩阵只包含‘X’和‘O’，将所有四周都被 ‘X’包围的 ‘O’转化为‘X’，

例一中有解释，被保围的区域不会出席那在边界上，这就意味着边界上的 ‘O’，不会被转化，任何不再边界上，和不与边界上相连的’O‘，都会被转化为’X‘，水平或者垂直相邻的两个元素，被认为是相邻的。

## 解题思路

* 这道题目可以用DFS 和 BFS 来解决，转换之后的问题就是如果找到与边界相连的 'O'

* 这道题目也可以使用并查集来做（留待以后实现）

## 代码

`````c++
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        rows = board.size();
        cols = board[0].size();
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (IsEdge(i, j) && board[i][j] == 'O') {
                    //DFS(board, i, j);
                    BFS(board, i, j);
                }
            }
        }
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] == 'O') {   // 这两个替换的顺序很重要，一定要先换‘O’，再换‘#’，
                    board[i][j] = 'X';
                }
                if (board[i][j] == '#') {
                    board[i][j] = 'O';
                }
            }
        }
    }
    
 private:
    int rows;
    int cols;
    
    vector<vector<int>> dirs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    bool IsValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
    
    bool IsEdge(int x, int y) {
        return x == 0 || x == rows - 1 || y == 0 || y == cols - 1;
    }
    
    // 使用DFS 来解决
    void  DFS(vector<vector<char>>& board, int x, int y) {        
        board[x][y] = '#';
        // 向四周扩展
        for (const vector<int>& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            
            if (IsValid(nx, ny) && board[nx][ny] == 'O') {
                DFS(board, nx, ny);
            }
        }
    }
    
    void BFS(vector<vector<char>>& board, int x, int y) {
        queue<pair<int, int>> que;
        que.push(make_pair(x, y));
        board[x][y] = '#';
        
        while (!que.empty()) {
            pair<int, int> cur = que.front();
            que.pop();
            
            // 上
            if (cur.first - 1 >= 0 && board[cur.first - 1][cur.second] == 'O') {
                que.push(make_pair(cur.first - 1, cur.second));
                board[cur.first - 1][cur.second] = '#'; // 这里要做标记，不要等弹出时，防止重复入队
            }
            
            // 下
            if (cur.first + 1 < rows && board[cur.first + 1][cur.second] == 'O') {
                que.push(make_pair(cur.first + 1, cur.second));
                board[cur.first + 1][cur.second] = '#';
            }
            
            // 左
            if (cur.second - 1 >= 0 && board[cur.first][cur.second - 1] == 'O') {
                que.push(make_pair(cur.first, cur.second - 1));
                board[cur.first][cur.second - 1] = '#';
            }
            
            // 右
            if (cur.second + 1 < cols && board[cur.first][cur.second + 1] == 'O') {
                que.push(make_pair(cur.first, cur.second + 1));
                board[cur.first][cur.second + 1] = '#';
            }
        }
    }
};
`````

