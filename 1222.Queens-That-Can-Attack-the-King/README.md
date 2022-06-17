#### [1222. Queens That Can Attack the King](https://leetcode.cn/problems/queens-that-can-attack-the-king/)

## 题目

On an **8x8** chessboard, there can be multiple Black Queens and one White King.

Given an array of integer coordinates `queens` that represents the positions of the Black Queens, and a pair of coordinates `king` that represent the position of the White King, return the coordinates  of all the queens (in any order) that can attack the King.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/10/01/untitled-diagram.jpg)

```
Input: queens = [[0,1],[1,0],[4,0],[0,4],[3,3],[2,4]], king = [0,0]
Output: [[0,1],[1,0],[3,3]]
Explanation:  
The queen at [0,1] can attack the king cause they're in the same row. 
The queen at [1,0] can attack the king cause they're in the same column. 
The queen at [3,3] can attack the king cause they're in the same diagnal. 
The queen at [0,4] can't attack the king cause it's blocked by the queen at [0,1]. 
The queen at [4,0] can't attack the king cause it's blocked by the queen at [1,0]. 
The queen at [2,4] can't attack the king cause it's not in the same row/column/diagnal as the king.
```

**Example 2:**

**![img](https://assets.leetcode.com/uploads/2019/10/01/untitled-diagram-1.jpg)**

```
Input: queens = [[0,0],[1,1],[2,2],[3,4],[3,5],[4,4],[4,5]], king = [3,3]
Output: [[2,2],[3,4],[4,4]]
```

**Example 3:**

**![img](https://assets.leetcode.com/uploads/2019/10/01/untitled-diagram-2.jpg)**

```
Input: queens = [[5,6],[7,7],[2,1],[0,7],[1,6],[5,1],[3,7],[0,3],[4,0],[1,2],[6,3],[5,0],[0,4],[2,2],[1,1],[6,4],[5,4],[0,0],[2,6],[4,5],[5,2],[1,4],[7,5],[2,3],[0,5],[4,2],[1,0],[2,7],[0,1],[4,6],[6,1],[0,6],[4,3],[1,7]], king = [3,4]
Output: [[2,3],[1,4],[1,6],[3,7],[4,3],[5,4],[4,5]]
```

 

**Constraints:**

- `1 <= queens.length <= 63`
- `queens[i].length == 2`
- `0 <= queens[i][j] < 8`
- `king.length == 2`
- `0 <= king[0], king[1] < 8`
- At most one piece is allowed in a cell.

## 题目大意

在一个 8x8 的棋盘上，放置着若干「黑皇后」和一个「白国王」。

给定一个由整数坐标组成的数组 queens ，表示黑皇后的位置；以及一对坐标 king ，表示白国王的位置，返回所有可以攻击国王的皇后的坐标(任意顺序)。

## 解题思路

八个方向，简单模拟就可以了

### Solution 1:

````c++
class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        vector<vector<int>> board(8, vector<int>(8));
        for (const auto& queen : queens) {
            board[queen[0]][queen[1]] = 1;
        }
        
        int m = king[0], n = king[1];
        // left
        vector<vector<int>> res;
        for (int i = n; i >= 0; --i) {
            if (board[m][i] == 1) {
                res.push_back({m, i});
                break;
            }
        }
        // right
        for (int i = n; i < 8; ++i) {
            if (board[m][i] == 1) {
                res.push_back({m, i});
                break;
            }
        }
        
        // up
        for (int i = m; i >= 0; --i) {
            if (board[i][n] == 1) {
                res.push_back({i, n});
                break;
            }
        }
        // down
        for (int i = m; i < 8; ++i) {
            if (board[i][n] == 1) {
                res.push_back({i, n});
                break;
            }
        }
        
        // left up
        for (int i = m - 1, j = n - 1; i >= 0 && j >= 0; --i, --j) {
            if (board[i][j] == 1) {
                res.push_back({i, j});
                break;
            }
        }
        // rigth bottom
        for (int i = m + 1, j = n + 1; i < 8 && j < 8; ++i, ++j) {
            if (board[i][j] == 1) {
                res.push_back({i, j});
                break;
            }
        }
        // right up
        for (int i = m - 1, j = n + 1; i >= 0 && j < 8; --i, ++j) {
            if (board[i][j] == 1) {
                res.push_back({i, j});
                break;
            }
        }
        // left bottom
        for (int i = m + 1, j = n - 1; i < 8 && j >= 0; ++i, --j) {
            if (board[i][j] == 1) {
                res.push_back({i, j});
                break;
            }
        }
        
        return res;
    }
};
````

