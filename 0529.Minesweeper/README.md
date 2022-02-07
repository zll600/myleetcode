# [529. Minesweeper](https://leetcode.com/problems/minesweeper/)

## 题目

Let's play the minesweeper game ([Wikipedia](https://en.wikipedia.org/wiki/Minesweeper_(video_game)), [online game](http://minesweeperonline.com/))!

You are given an `m x n` char matrix `board` representing the game board where:

- `'M'` represents an unrevealed mine,
- `'E'` represents an unrevealed empty square,
- `'B'` represents a revealed blank square that has no adjacent mines (i.e., above, below, left, right, and all 4 diagonals),
- digit (`'1'` to `'8'`) represents how many mines are adjacent to this revealed square, and
- `'X'` represents a revealed mine.

You are also given an integer array `click` where `click = [clickr, clickc]` represents the next click position among all the unrevealed squares (`'M'` or `'E'`).

Return *the board after revealing this position according to the following rules*:

1. If a mine `'M'` is revealed, then the game is over. You should change it to `'X'`.
2. If an empty square `'E'` with no adjacent mines is revealed, then change it to a revealed blank `'B'` and all of its adjacent unrevealed squares should be revealed recursively.
3. If an empty square `'E'` with at least one adjacent mine is revealed, then change it to a digit (`'1'` to `'8'`) representing the number of adjacent mines.
4. Return the board when no more squares will be revealed.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/10/12/minesweeper_example_1.png)

```
Input: board = [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]], click = [3,0]
Output: [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2018/10/12/minesweeper_example_2.png)

```
Input: board = [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]], click = [1,2]
Output: [["B","1","E","1","B"],["B","1","X","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
```

 

**Constraints:**

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 50`
- `board[i][j]` is either `'M'`, `'E'`, `'B'`, or a digit from `'1'` to `'8'`.
- `click.length == 2`
- `0 <= clickr < m`
- `0 <= clickc < n`
- `board[clickr][clickc]` is either `'M'` or `'E'`.

## 题目大意

让我们一起来玩扫雷游戏！

给你一个大小为 `m x n` 二维字符矩阵 `board` ，表示扫雷游戏的盘面，其中：

- 'M' 代表一个 未挖出的 地雷，
- 'E' 代表一个 未挖出的 空方块，
- 'B' 代表没有相邻（上，下，左，右，和所有4个对角线）地雷的 已挖出的 空白方块，
- 数字（'1' 到 '8'）表示有多少地雷与这块 已挖出的 方块相邻，
- 'X' 则表示一个 已挖出的 地雷。

给你一个整数数组 `click` ，其中 `click = [clickr, clickc]` 表示在所有 未挖出的 方块（'M' 或者 'E'）中的下一个点击位置（clickr 是行下标，clickc 是列下标）。

根据以下规则，返回相应位置被点击后对应的盘面：

1. 如果一个地雷`（'M'`）被挖出，游戏就结束了- 把它改为 `'X'` 。
2. 如果一个 没有相邻地雷 的空方块 `（'E'）` 被挖出，修改它为 `（'B'）`，并且所有和其相邻的 未挖出 方块都应该被递归地揭露。
3. 如果一个 至少与一个地雷相邻 的空方块 `（'E'）` 被挖出，修改它为数字`（'1' 到 '8' ）`，表示相邻地雷的数量。
4. 如果在此次点击中，若无更多方块可被揭露，则返回盘面。


## 解题思路

分情况：
- 如果是 地雷，改变之后直接返回
- 否则进行递归

### Solution 1: DFS

这里的递归终止条件比较难写，可以参考 [这篇题解](https://leetcode-cn.com/problems/minesweeper/solution/cong-qi-dian-kai-shi-dfs-bfs-bian-li-yi-bian-ji-ke/)


````c++
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        m_ = board.size();
        n_ = board[0].size();
        x_ = click[0], y_ = click[1];

        if (board[x_][y_] == 'M') {
            board[x_][y_] = 'X';
        } else {
            DFS(board, x_, y_);
        }

        return board;
    }

 private:
    int x_;
    int y_;
    int m_;
    int n_;
    vector<int> dx_ = {-1, 1, 0, 0, -1, 1, 1, -1};
    vector<int> dy_ = {0, 0, -1, 1, 1, -1, 1, -1};

    void DFS(vector<vector<char>>& board, int x, int y) {
        // 递归终止条件：周围有至少一个地雷
        int cnt = 0;
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx_[i];
            int ny = y + dy_[i];

            if (nx < 0 || nx >= m_ || ny < 0 || ny >= n_) {
                continue;
            }

            if (board[nx][ny] == 'M') {
                ++cnt;
            }
        }
        if (cnt > 0) {
            board[x][y] = cnt + '0';
            return;
        }

        board[x][y] = 'B'; // 标记为 'B'，可以避免重复访问
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx_[i];
            int ny = y + dy_[i];

            if (nx < 0 || nx >= m_ || ny < 0 || ny >= n_
                || board[nx][ny] != 'E') {
                // 这里避免了重复访问
                continue;
            }

            // 继续递归
            DFS(board, nx, ny);
        }
    }
};
````


