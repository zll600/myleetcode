# [488. Zuma Game](https://leetcode.com/problems/zuma-game/)

## 题目

You are playing a variation of the game Zuma.

In this variation of Zuma, there is a **single row** of colored balls on a board, where each ball can be colored red `'R'`, yellow `'Y'`, blue `'B'`, green `'G'`, or white `'W'`. You also have several colored balls in your hand.

Your goal is to **clear all** of the balls from the board. On each turn:

- Pick **any** ball from your hand and insert it in between two balls in the row or on either end of the row.

- If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.

  - If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.

- If there are no more balls on the board, then you win the game.

- Repeat this process until you either win or do not have any more balls in your hand.

Given a string `board`, representing the row of balls on the board, and a string `hand`, representing the balls in your hand, return *the **minimum** number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return* `-1`.

 

**Example 1:**

```
Input: board = "WRRBBW", hand = "RB"
Output: -1
Explanation: It is impossible to clear all the balls. The best you can do is:
- Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
- Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
There are still balls remaining on the board, and you are out of balls to insert.
```

**Example 2:**

```
Input: board = "WWRRBBWW", hand = "WRBRW"
Output: 2
Explanation: To make the board empty:
- Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
- Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
2 balls from your hand were needed to clear the board.
```

**Example 3:**

```
Input: board = "G", hand = "GGGGG"
Output: 2
Explanation: To make the board empty:
- Insert 'G' so the board becomes GG.
- Insert 'G' so the board becomes GGG. GGG -> empty.
2 balls from your hand were needed to clear the board.
```

 

**Constraints:**

- `1 <= board.length <= 16`
- `1 <= hand.length <= 5`
- `board` and `hand` consist of the characters `'R'`, `'Y'`, `'B'`, `'G'`, and `'W'`.
- The initial row of balls on the board will **not** have any groups of three or more consecutive balls of the same color.

## 题目大意

你正在参与祖玛游戏的一个变种。

在这个祖玛游戏变体中，桌面上有 一排 彩球，每个球的颜色可能是：红色 `'R'`、黄色 `'Y'`、蓝色 `'B'`、绿色 `'G'` 或白色 `'W'` 。你的手中也有一些彩球。

你的目标是 **清空** 桌面上所有的球。每一回合：

- 从你手上的彩球中选出 任意一颗 ，然后将其插入桌面上那一排球中：两球之间或这一排球的任一端。
- 接着，如果有出现 三个或者三个以上 且 颜色相同 的球相连的话，就把它们移除掉。
  - 如果这种移除操作同样导致出现三个或者三个以上且颜色相同的球相连，则可以继续移除这些球，直到不再满足移除条件。

- 如果桌面上所有球都被移除，则认为你赢得本场游戏。
  重复这个过程，直到你赢了游戏或者手中没有更多的球。

给你一个字符串 `board` ，表示桌面上最开始的那排球。另给你一个字符串 `hand` ，表示手里的彩球。请你按上述操作步骤移除掉桌上所有球，计算并返回所需的 最少 球数。如果不能移除桌上所有的球，返回 `-1` 

## 解题思路

这道题其实没有什么很好的思路,那就只能试试 回溯法了,所以难点在

- 定义回溯时变化的状态
- 当前状态可以用哪些变量来保持,
- 这几个变量是如何变化的

### Solution 1: DFS

这种解法可以参考 [这篇题解](https://leetcode.com/problems/zuma-game/submissions/)

````c++
class Solution {
    int ans, used;
    unordered_map<char, int> rem;
    stack<pair<char, int>> st;

    // inserted 表示在当前位置与前一个位置同色的情况下，两个位置之间是否插入过异色球
    void dfs(int pos, string &board, bool inserted) {
        if (used >= ans)
            return;

        if (pos == board.size()) {
            if (st.empty())
                ans = used;
            return;
        }

        // 将pos位置的小球加入
        if (!st.empty() && st.top().first == board[pos]) {
            st.top().second++;
        } else {
            st.emplace(board[pos], 1);
        }

        // 1. 不额外插入小球的情形
        // 1.1 当前颜色满三个，且后面没有相同颜色的球
        if (st.top().second >= 3 && (pos + 1 == board.size() || board[pos + 1] != board[pos])) {
            auto tmp = st.top();
            st.pop();
            dfs(pos + 1, board, false);
            st.push(tmp);
        }

        // 1.2. 当前颜色小球不满三个
        // 1.3. 当前颜色小球恰好三个，但当前小球和上一小球不同色，或者之前插入过非同色球，这说明初始情形为XX...X，之后中间的小球被消去，从而形成了XXX，这种情况是允许的。因为我们可改变消去的顺序。如果当前小球和上一小球同色，则说明初始情形为X...XX，此时假设右边还有X，则中间的XX要么结合左边的X，要么结合右边的X，不可能同时结合。如果当前小球数量已经达到四个，则不可能再积累更多同色球，因为最多只可能形成四连珠，五连珠在形成前至少有一边已经达到三个，是不可能形成的。
        if (st.top().second < 3 ||
            (st.top().second == 3 && (board[pos] != board[pos - 1] || inserted)))
            dfs(pos + 1, board, false);

        // 2. 插入与当前位置同色的小球
        if (rem[board[pos]] >= 1 &&
            (pos + 1 == board.size() || board[pos + 1] != board[pos])) {
            int lim = rem[board[pos]];
            for (int i = 1; i <= min(2, lim); ++i) { // 至多插入两个
                // 加入i个同色小球
                rem[board[pos]] -= i;
                used += i;
                st.top().second += i;
                if (st.top().second >= 3) { // 累积同色球达到三个
                    auto tmp = st.top();      // 维护现场
                    st.pop();                 // 消去同色球
                    dfs(pos + 1, board, false);
                    st.push(tmp); // 还原现场
                } else {
                    dfs(pos + 1, board, false);
                }

                // 还原现场
                st.top().second -= i;
                used -= i;
                rem[board[pos]] += i;
            }
        }

        // 3. 当后面有相同颜色的球时，尝试插入与当前位置不同色的小球
        if (pos + 1 < board.size() && board[pos + 1] == board[pos]) {
            auto tmp = st.top(); // 维护现场
            if (tmp.second >= 3) // 消去当前积累的同色小球
                st.pop();

            for (auto[ch, num]: rem) {
                if (ch == board[pos] || num == 0)
                    continue;
                int hi = (tmp.second >= 3) ? min(3, num) : 1; // 如果当前小球积累不足三个，则至多只插入一个分隔
                for (int j = 1; j <= min(3, num); ++j) {
                    rem[ch] -= j;
                    used += j;

                    // 加入j个小球
                    if (!st.empty() && st.top().first == ch) {
                        st.top().second += j;
                    } else {
                        st.emplace(ch, j);
                    }

                    if (st.top().second >= 3) { // 插入的异色球和之前的球累加达到了三个
                        auto tmp2 = st.top(); // 维护现场
                        st.pop();             // 消去同色球
                        dfs(pos + 1, board, true);
                        st.push(tmp2); // 还原现场
                    } else {
                        dfs(pos + 1, board, true);
                    }

                    // 还原现场
                    if (st.top().second > j) {
                        st.top().second -= j;
                    } else {
                        st.pop();
                    }
                    used -= j;
                    rem[ch] += j;
                }
            }

            if (tmp.second >= 3)
                st.push(tmp); // 还原现场
        }

        // 还原现场
        if (st.top().second == 1) {
            st.pop();
        } else {
            st.top().second--;
        }
    }

public:
    int findMinStep(string board, string hand) {
        for (char ch: hand)
            rem[ch]++;

        ans = 1e9;
        used = 0;
        dfs(0, board, false);
        return ans == 1e9 ? -1 : ans;
    }
};

作者：lucifer1004
链接：https://leetcode-cn.com/problems/zuma-game/solution/c-0ms-by-lucifer1004-ivwb/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
````
