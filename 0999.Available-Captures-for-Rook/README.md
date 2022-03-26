# [999. Available Captures for Rook](https://leetcode.com/problems/available-captures-for-rook/)

## 题目

On an `8 x 8` chessboard, there is **exactly one** white rook `'R'` and some number of white bishops `'B'`, black pawns `'p'`, and empty squares `'.'`.

When the rook moves, it chooses one of four cardinal directions  (north, east, south, or west), then moves in that direction until it  chooses to stop, reaches the edge of the board, captures a black pawn,  or is blocked by a white bishop. A rook is considered **attacking** a pawn if the rook can capture the pawn on the rook's turn. The **number of available captures** for the white rook is the number of pawns that the rook is **attacking**.

Return *the **number of available captures** for the white rook*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/02/20/1253_example_1_improved.PNG)

```
Input: board = [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 3
Explanation: In this example, the rook is attacking all the pawns.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/02/19/1253_example_2_improved.PNG)

```
Input: board = [[".",".",".",".",".",".",".","."],[".","p","p","p","p","p",".","."],[".","p","p","B","p","p",".","."],[".","p","B","R","B","p",".","."],[".","p","p","B","p","p",".","."],[".","p","p","p","p","p",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 0
Explanation: The bishops are blocking the rook from attacking any of the pawns.
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2019/02/20/1253_example_3_improved.PNG)

```
Input: board = [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","p",".",".",".","."],["p","p",".","R",".","p","B","."],[".",".",".",".",".",".",".","."],[".",".",".","B",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 3
Explanation: The rook is attacking the pawns at positions b5, d6, and f5.
```

 

**Constraints:**

- `board.length == 8`
- `board[i].length == 8`
- `board[i][j]` is either `'R'`, `'.'`, `'B'`, or `'p'`
- There is exactly one cell with `board[i][j] == 'R'`

## 题目大意

在一个 `8 x 8` 的棋盘上，有一个 *白色的车（Rook）* ，用字符 `‘R’` 表示。棋盘上还可能存在空方块，*白色的象（Bishop）* 以及 *黑色的卒（pawn）* ，分别用字符 `‘.'，‘B’ 和 ‘p’` 表示。不难看出，车按国际象棋中的规则移动。*东，西，南，北* 四个基本方向任选其一，然后一直向选定的方向移动，直到满足下列四个条件之一：

- 棋手选择主动停下来。
- 棋子因到达棋盘的边缘而停下。
- 棋子移动到某一方格来捕获位于该方格上敌方（黑色）的卒，停在该方格内。
- 车不能进入/越过已经放有其他友方棋子（白色的象）的方格，停在友方棋子前。

你现在可以控制车移动一次，请你统计有多少敌方的卒处于你的捕获范围内（即，可以被一步捕获的棋子数）。

## 解题思路

这道题目的难点在于，要根据第一次选择的移动的方向，来确定之后的步进，

### Solution 1: 


````c++
class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        int sum = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                // 找个 ‘车’ 的位置，然后向四个方向尝试，分别给定不同的步进
                if (board[i][j] == 'R') {
                    sum += Capture(board, i + 1, j, 1, 0);
                    sum += Capture(board, i, j + 1, 0, 1);
                    sum += Capture(board, i - 1, j, -1, 0);
                    sum += Capture(board, i, j - 1, 0, -1);
                }
            }
        }

        return sum;
    }

 private:
    // 这里要根据之前移动的方向来定义这次的 步进
    int Capture(const vector<vector<char>>& board, int x, int y, int bx, int by) {
        // 这里只要满足题目中的几个要求即可
        while (x >= 0 && x < 8 && y >= 0 && y < 8 && board[x][y] != 'B') {
            if (board[x][y] == 'p') {
                return 1;
            }

            x += bx;
            y += by;
        }

        return 0;
    }
};
````
