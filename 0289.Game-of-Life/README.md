# [289. Game of Life](https://leetcode-cn.com/problems/game-of-life/)

## 题目

According to [Wikipedia's article](https://en.wikipedia.org/wiki/Conway's_Game_of_Life): "The **Game of Life**, also known simply as **Life**, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

The board is made up of an `m x n` grid of cells, where each cell has an initial state: **live** (represented by a `1`) or **dead** (represented by a `0`). Each cell interacts with its [eight neighbors](https://en.wikipedia.org/wiki/Moore_neighborhood) (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

1. Any live cell with fewer than two live neighbors dies as if caused by under-population.
2. Any live cell with two or three live neighbors lives on to the next generation.
3. Any live cell with more than three live neighbors dies, as if by over-population.
4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously. Given the current state of the `m x n` grid `board`, return *the next state*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/12/26/grid1.jpg)

```
Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/12/26/grid2.jpg)

```
Input: board = [[1,1],[1,0]]
Output: [[1,1],[1,1]]
```

 

**Constraints:**

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 25`
- `board[i][j]` is `0` or `1`.

 

**Follow up:**

- Could you solve it in-place? Remember that the board needs to be updated simultaneously: You cannot update some cells first and then use their updated values to update other cells.
- In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches upon the border of the array (i.e., live cells reach the border). How would you address these problems?

## 题目大意

根据 百度百科 ，生命游戏，简称为生命，是英国数学家约翰·何顿·康威在 1970 年发明的细胞自动机。

给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞都具有一个初始状态：1 即为活细胞（live），或 0 即为死细胞（dead）。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：

* 如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
* 如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
* 如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
* 如果死细胞周围正好有三个活细胞，则该位置死细胞复活；

下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。给你 m x n 网格面板 board 的当前状态，返回下一个状态。

## 解题思路

这道题目用到了矩阵中状态转移类题目常见的两种技巧，可以参考这篇题解：https://leetcode-cn.com/problems/game-of-life/solution/ju-zhen-wen-ti-tong-yong-jie-fa-by-freshrookie/

一个是用原有状态之外的量来做标记，另一个就是方向数组，

### Solution 1:

````c++
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        // 初始化行数和列数
        rows_ = board.size();
        cols_ = board[0].size();
        
        GameOfLife(board);
    }
    
 private:
    // 方向数组，可以设置为 static
    vector<vector<int>> dirs_ = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };
    
    int rows_;
    int cols_;
    
    // 判断坐标是否合法
    bool IsValid(int x, int y) {
        return x >= 0 && x < rows_ && y >= 0 && y < cols_;
    }
    
    void GameOfLife(vector<vector<int>>& board) {
        // 遍历每一个位置，并进行判断
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                int live = 0;
                // 遍历八个方向进行判断
                for (auto dir : dirs_) {
                    int nx = i + dir[0];
                    int ny = j + dir[1];
                    
                    if (!IsValid(nx, ny)) {
                        continue;
                    }
                    
                    // 如果存活或者即将由存活道死亡
                    if (board[nx][ny] == 1 || board[nx][ny] == 3) {
                        ++live;
                    }
                }
                
                // 做标记
                // 如果原来死亡
                if (board[i][j] == 0) {
                    if (live == 3) {
                        board[i][j] = 2;
                    }
                } else {
                    // 如果原来存活
                    if (live < 2 || live > 3) {
                        board[i][j] = 3;
                    }
                }
            }
        }
        
        // 改变原来的数组
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (board[i][j] == 2) {
                    board[i][j] = 1;
                } else if (board[i][j] == 3) {
                    board[i][j] = 0;
                }
            }
        }
    }
};
````

