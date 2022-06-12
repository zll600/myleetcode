# [1033. Moving Stones Until Consecutive](https://leetcode.cn/problems/moving-stones-until-consecutive/)

## 题目

There are three stones in different positions on the X-axis. You are given three integers `a`, `b`, and `c`, the positions of the stones.

In one move, you pick up a stone at an endpoint (i.e., either the  lowest or highest position stone), and move it to an unoccupied position between those endpoints. Formally, let's say the stones are currently  at positions `x`, `y`, and `z` with `x < y < z`. You pick up the stone at either position `x` or position `z`, and move that stone to an integer position `k`, with `x < k < z` and `k != y`.

The game ends when you cannot make any more moves (i.e., the stones are in three consecutive positions).

Return *an integer array* `answer` *of length* `2` *where*:

- `answer[0]` *is the minimum number of moves you can play, and*
- `answer[1]` *is the maximum number of moves you can play*.

 

**Example 1:**

```
Input: a = 1, b = 2, c = 5
Output: [1,2]
Explanation: Move the stone from 5 to 3, or move the stone from 5 to 4 to 3.
```

**Example 2:**

```
Input: a = 4, b = 3, c = 2
Output: [0,0]
Explanation: We cannot make any moves.
```

**Example 3:**

```
Input: a = 3, b = 5, c = 1
Output: [1,2]
Explanation: Move the stone from 1 to 4; or move the stone from 1 to 2 to 4.
```

 

**Constraints:**

- `1 <= a, b, c <= 100`
- `a`, `b`, and `c` have different values.

## 题目大意

三枚石子放置在数轴上，位置分别为 `a`，`b`，`c`

每一回合，你可以从两端之一拿起一枚石子（位置最大或最小），并将其放入两端之间的任一空闲位置。形式上，假设这三枚石子当前分别位于位置 `x`, `y`, `z` 且 `x < y < z`。那么就可以从位置 `x` 或者是位置 `z` 拿起一枚石子，并将该石子移动到某一整数位置 `k` 处，其中 `x < k < z` 且 `k != y`

当你无法进行任何移动时，即，这些石子的位置连续时，游戏结束

要使游戏结束，你可以执行的最小和最大移动次数分别是多少？ 以长度为 `2` 的数组形式返回答案：`answer = [minimum_moves, maximum_moves]`

## 解题思路


### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/moving-stones-until-consecutive/solution/1033-cchao-100de-shu-xue-jie-fa-by-ffret-qsjy/)

这里先先将 a, b, c 排序，供后序分类讨论

移动最远：

- a 到 b - 1 距离 b - 1 - a
- c 到 b + 1 距离 c - b - 1

联立：c - a - 2

移动最近:

- 如果已经连续，不需要移动
- 如果a 和 b 空一个位置，或者 b 和 c 空一个位置，移动一步
- 其余情况，先转化为第二种情况，再次移动

````c++
class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        if (a > b) {
            swap(a, b);
        }
        if (a > c) {
            swap(a, c);
        }
        if (b > c) {
            swap(b, c);
        }
        // a < b < c
        
        // 如果三个相邻
        if (a == b - 1 && c == b + 1) {
            return {0, 0};
        }

        // 1) a, b 相邻， b, c 相邻
        // 2） a b 空一个位置，b， c 空一个位置
        if (b - a == 1 || c - b == 1 || b - a == 2 || c - b == 2) {
            return {1, c - a - 2};
        }
        // 其余情况需要多一步转化为上述两种情况之一
        return {2, c - a - 2};
    }
};
````


