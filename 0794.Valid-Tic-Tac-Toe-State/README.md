# [794. Valid Tic-Tac-Toe State](https://leetcode.com/problems/valid-tic-tac-toe-state/)

## 题目

Given a Tic-Tac-Toe board as a string array `board`, return `true` if and only if it is possible to reach this board position during the course of a valid tic-tac-toe game.

The board is a `3 x 3` array that consists of characters `' '`, `'X'`, and `'O'`. The `' '` character represents an empty square.

Here are the rules of Tic-Tac-Toe:

- Players take turns placing characters into empty squares `' '`.
- The first player always places `'X'` characters, while the second player always places `'O'` characters.
- `'X'` and `'O'` characters are always placed into empty squares, never filled ones.
- The game ends when there are three of the same (non-empty) character filling any row, column, or diagonal.
- The game also ends if all squares are non-empty.
- No more moves can be played if the game is over.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/05/15/tictactoe1-grid.jpg)

```
Input: board = ["O  ","   ","   "]
Output: false
Explanation: The first player always plays "X".
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/05/15/tictactoe2-grid.jpg)

```
Input: board = ["XOX"," X ","   "]
Output: false
Explanation: Players take turns making moves.
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/05/15/tictactoe4-grid.jpg)

```
Input: board = ["XOX","O O","XOX"]
Output: true
```

 

**Constraints:**

- `board.length == 3`
- `board[i].length == 3`
- `board[i][j]` is either `'X'`, `'O'`, or `' '`.

## 题目大意 

给你一个字符串数组 `board` 表示井字游戏的棋盘。当且仅当在井字游戏过程中，棋盘有可能达到 `board` 所显示的状态时，才返回 `true` 。

井字游戏的棋盘是一个 `3 x 3` 数组，由字符 `' '`，`'X'` 和 `'O'` 组成。字符 `' '` 代表一个空位。

以下是井字游戏的规则：

- 玩家轮流将字符放入空位 `（' '）` 中。
- 玩家 1 总是放字符 `'X'` ，而玩家 `2` 总是放字符 `'O'` 。
- `'X'` 和 `'O'` 只允许放置在空位中，不允许对已放有字符的位置进行填充。
- 当有 `3` 个相同（且非空）的字符填充任何行、列或对角线时，游戏结束。
- 当所有位置非空时，也算为游戏结束。
- 如果游戏结束，玩家不允许再放置字符。

## 解题思路

我们可以总结出有下列几个特点：

- 任何时候，`X` 的数目要么与 `O` 相等，要么比 `O` 大一，
- `X` 和 `O` 的数量相等的时候，`X` 不存在任何行、列或者对角线，
- `X` 比 `O` 的数量大一的时候， `O` 不存在任何行、列或者对角线

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0794.Valid-Tic-Tac-Toe-State/)


````c++
class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        // 统计字符频数
        int cnt_x = 0, cnt_o = 0;
        for (const string& word : board) {
            for (char c : word) {
                if (c == 'X') {
                    ++cnt_x;
                } else if (c == 'O') {
                    ++cnt_o;
                }
            }
        }
        
        if (cnt_x < cnt_o || cnt_x > cnt_o + 1) {
            return false;
        }
        
        if (cnt_x == cnt_o) {
            return OneLine(board, 'X');
        }
        if (cnt_x == cnt_o + 1) {
            return OneLine(board, 'O');
        }
        return false;
    }
    
 private:
    bool OneLine(vector<string>& board, char c) {
        // 先判断 3个 行
        string row(3, c);
        for (const string word : board) {
            if (word == row) {
                return false;
            }
        }
        
        // 再判断 3个 列
        if ((board[0][0] == c && board[1][0] == c && board[2][0] == c)
            || (board[0][1] == c && board[1][1] == c && board[2][1] == c)
            || (board[0][2] == c && board[1][2] == c && board[2][2] == c)) {
            return false;
        }
        
        // 两条对角线
        if ((board[0][0] == c && board[1][1] == c && board[2][2] == c)
           || (board[0][2] == c && board[1][1] == c && board[2][0] == c)) {
            return false;
        }
        
        return true;
    }
};
````


