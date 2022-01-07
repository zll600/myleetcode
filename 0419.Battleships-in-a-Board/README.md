# [419. Battleships in a Board](https://leetcode-cn.com/problems/battleships-in-a-board/)

## 题目

Given an `m x n` matrix `board` where each cell is a battleship `'X'` or empty `'.'`, return *the number of the **battleships** on* `board`.

**Battleships** can only be placed horizontally or vertically on `board`. In other words, they can only be made of the shape `1 x k` (`1` row, `k` columns) or `k x 1` (`k` rows, `1` column), where `k` can be of any size. At least one horizontal or vertical cell separates between two battleships (i.e., there are no adjacent battleships).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/10/battelship-grid.jpg)

```
Input: board = [["X",".",".","X"],[".",".",".","X"],[".",".",".","X"]]
Output: 2
```

**Example 2:**

```
Input: board = [["."]]
Output: 0
```

 

**Constraints:**

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 200`
- `board[i][j]` is either `'.'` or `'X'`.

 

**Follow up:** Could you do it in one-pass, using only `O(1)` extra memory and without modifying the values `board`?

## 题目大意

给定一个 m x n 的矩阵中，每一格表示战舰 'X' 或者空'.'，返回矩阵中的战舰的数量，

战舰 只能水平或者垂直放置在 board 上。换句话说，战舰只能按 1 x k（1 行，k 列）或 k x 1（k 行，1 列）的形状建造，其中 k 可以是任意大小。两艘战舰之间至少有一个水平或垂直的空位分隔 （即没有相邻的战舰）



**进阶要求**：只使用一次遍历，使用O(1)的空间复杂度，不修改甲板的值，

## 解题思路

这道题属于 **连通集数量查询问题**，理论上可以使用 DFS，BFS 和 并查集 来解决， 



### Solution 1: DFS

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/battleships-in-a-board/solution/wei-rao-li-lun-dfsjie-jue-lian-tong-tu-c-zu9v/

虽然战舰只能水平或者竖直来延伸，沿着相邻位置扩展，但是这里依旧可以向四个方向递归

```c++
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        rows_ = board.size();
        cols_ = board[0].size();
        
        int res = 0;
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (board[i][j] == '.' || board[i][j] == 'Y') {
                    continue;
                }
                // 从每个可能的位置开始递归
                DFS(board, i, j);
                ++res;
            }
        }
        
        return res;
    }

 private:
    vector<int> dirs_ = {0, 1, 0, -1, 0}; // 方向数组
    int rows_;
    int cols_;
    
    // 判断坐标是否有效
    bool IsValid(int x, int y) {
        return x >= 0 && y >= 0 && x < rows_ && y < cols_;
    }
    
    void DFS(vector<vector<char>>& board, int x, int y) {
        board[x][y] = 'Y'; // 做标记
        
        for (int i = 0; i < 4; ++i) {
            // 虽然战舰只能水平或者竖直延伸，但是依旧可以继续向四个方向递归
            int nx = x + dirs_[i];
            int ny = y + dirs_[i + 1];
            
            if (!IsValid(nx, ny) || board[nx][ny] == '.' || board[nx][ny] == 'Y') {
                continue;
            }
            DFS(board, nx, ny);
        }
    }
};

```



### Solution 2: BFS

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/battleships-in-a-board/solution/gong-shui-san-xie-ji-chong-sao-miao-xian-trmc/



```c++
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();
        
        int res = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i > 0 && board[i - 1][j] == 'X') {
                    // 上方
                    continue;
                }
                if (j > 0 && board[i][j - 1] == 'X') {
                    // 下方
                    continue;
                }
                
                if (board[i][j] == 'X') {
                    // 如果是一个战舰的开头
                    ++res;
                }
            }
        }
        
        return res;
    }
};

```

