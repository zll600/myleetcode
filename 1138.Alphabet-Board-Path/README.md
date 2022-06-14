# [1138. Alphabet Board Path](https://leetcode.cn/problems/alphabet-board-path/)

## 题目大意

On an alphabet board, we start at position `(0, 0)`, corresponding to character `board[0][0]`.

Here, `board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"]`, as shown in the diagram below.

![img](https://assets.leetcode.com/uploads/2019/07/28/azboard.png)

We may make the following moves:

- `'U'` moves our position up one row, if the position exists on the board;
- `'D'` moves our position down one row, if the position exists on the board;
- `'L'` moves our position left one column, if the position exists on the board;
- `'R'` moves our position right one column, if the position exists on the board;
- `'!'` adds the character `board[r][c]` at our current position `(r, c)` to the answer.

(Here, the only positions that exist on the board are positions with letters on them.)

Return a sequence of moves that makes our answer equal to `target` in the minimum number of moves. You may return any path that does so.

## 解题思路

我们从一块字母板上的位置 `(0, 0)` 出发，该坐标对应的字符为 `board[0][0]`

在本题里，字母板为 `board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"]`，如下所示

我们可以按下面的指令规则行动：

-   如果方格存在，'U' 意味着将我们的位置上移一行；
-   如果方格存在，'D' 意味着将我们的位置下移一行；
-   如果方格存在，'L' 意味着将我们的位置左移一列；
-   如果方格存在，'R' 意味着将我们的位置右移一列；
-   '!' 会把在我们当前位置 (r, c) 的字符 board[r][c] 添加到答案中。

（注意，字母板上只存在有字母的位置。）

返回指令序列，用最小的行动次数让答案和目标 target 相同。你可以返回任何达成目标的路径。

## 解题思路

### Solution 1:

首先将每一个字符映射成为坐标，然后根据坐标来计算距离

遍历 target，对于每个字符映射到的位置，对于每个位置只需要做多两个方向上的移动就可以了，

这里需要特别注意的是，因为 z 的特殊性，（向 z 移动）L 方向应该在 D 方向之前移动，（从 z 出发）U 应该在 R 之前移动

这里提供两个测试用例帮助理解 'zb'，'zdc'


````c++
class Solution {
public:
    string alphabetBoardPath(string target) {
        string res;
        
        int x = 0, y = 0;
        for (char c : target) {
            int dx = (c - 'a') / 5;
            int dy = (c - 'a') % 5;
            
            if (y > dy) {
                res += string(y - dy, 'L');
            }
            
            if (x > dx) {
                res += string(x - dx, 'U');
            }
            
            if (y < dy) {
                res += string(dy - y, 'R');
            }
            
            if (x < dx) {
                res += string(dx - x, 'D');
            }
            
            res += '!';
            x = dx;
            y = dy;
        }
        return res;
    }
};
````


