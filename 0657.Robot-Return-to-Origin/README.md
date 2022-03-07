# [657. Robot Return to Origin](https://leetcode-cn.com/problems/robot-return-to-origin/)

## 题目

There is a robot starting at the position `(0, 0)`, the origin, on a 2D plane. Given a sequence of its moves, judge if this robot **ends up at** `(0, 0)` after it completes its moves.

You are given a string `moves` that represents the move sequence of the robot where `moves[i]` represents its `ith` move. Valid moves are `'R'` (right), `'L'` (left), `'U'` (up), and `'D'` (down).

Return `true` *if the robot returns to the origin after it finishes all of its moves, or* `false` *otherwise*.

**Note**: The way that the robot is "facing" is irrelevant. `'R'` will always make the robot move to the right once, `'L'` will always make it move left, etc. Also, assume that the magnitude of the robot's movement is the same for each move.

 

**Example 1:**

```
Input: moves = "UD"
Output: true
Explanation: The robot moves up once, and then down once. All moves have the same magnitude, so it ended up at the origin where it started. Therefore, we return true.
```

**Example 2:**

```
Input: moves = "LL"
Output: false
Explanation: The robot moves left twice. It ends up two "moves" to the left of the origin. We return false because it is not at the origin at the end of its moves.
```

 

**Constraints:**

- `1 <= moves.length <= 2 * 104`
- `moves` only contains the characters `'U'`, `'D'`, `'L'` and `'R'`.

## 题目大意

在二维平面上，有一个机器人从原点 `(0, 0)` 开始。给出它的移动顺序，判断这个机器人在完成移动后是否在 `(0, 0)` 处结束

移动顺序由字符串 `moves` 表示。字符 `move[i]` 表示其第 `i` 次移动。机器人的有效动作有 `R（右），L（左），U（上）和 D（下）`

如果机器人在完成所有动作后返回原点，则返回 `true`。否则，返回 `false`。

注意：机器人“面朝”的方向无关紧要。 `“R”` 将始终使机器人向右移动一次，`“L”` 将始终向左移动等。此外，假设每次移动机器人的移动幅度相同。

## 解题思路


### Solution 1:


````c++
class Solution {
public:
    bool judgeCircle(string moves) {
        // x 表示水平方向上的位移，y 表示垂直方向上的位移
        int x = 0, y = 0;

        for (char c : moves) {
            if (c == 'R') {
                ++x;
            } else if (c == 'L') {
                --x;
            } else if (c == 'U') {
                ++y;
            } else {
                --y;
            }
        }

        // 二者均为 0，即可表示回到起点
        return x == 0 && y == 0;
    }
};
````

