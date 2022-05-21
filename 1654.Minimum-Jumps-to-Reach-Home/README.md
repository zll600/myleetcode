# [1654. Minimum Jumps to Reach Home](https://leetcode.com/problems/minimum-jumps-to-reach-home/)

## 题目

A certain bug's home is on the x-axis at position `x`. Help them get there from position `0`.

The bug jumps according to the following rules:

- It can jump exactly `a` positions **forward** (to the right).
- It can jump exactly `b` positions **backward** (to the left).
- It cannot jump backward twice in a row.
- It cannot jump to any `forbidden` positions.

The bug may jump forward **beyond** its home, but it **cannot jump** to positions numbered with **negative** integers.

Given an array of integers `forbidden`, where `forbidden[i]` means that the bug cannot jump to the position `forbidden[i]`, and integers `a`, `b`, and `x`, return *the minimum number of jumps needed for the bug to reach its home*. If there is no possible sequence of jumps that lands the bug on position `x`, return `-1.`

 

**Example 1:**

```
Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
Output: 3
Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
```

**Example 2:**

```
Input: forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
Output: -1
```

**Example 3:**

```
Input: forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
Output: 2
Explanation: One jump forward (0 -> 16) then one jump backward (16 -> 7) will get the bug home.
```

 

**Constraints:**

- `1 <= forbidden.length <= 1000`
- `1 <= a, b, forbidden[i] <= 2000`
- `0 <= x <= 2000`
- All the elements in `forbidden` are distinct.
- Position `x` is not forbidden.

## 题目大意

有一只跳蚤的家在数轴上的位置 `x` 处。请你帮助它从位置 `0` 出发，到达它的家。

跳蚤跳跃的规则如下：

- 它可以 `往前` 跳恰好 `a` 个位置（即往右跳）。
- 它可以 `往后` 跳恰好 `b` 个位置（即往左跳）。
- 它不能 `连续` 往后跳 `2` 次。
- 它不能跳到任何 `forbidden` 数组中的位置。

跳蚤可以往前跳 超过 它的家的位置，但是它  不能跳到负整数 的位置。

给你一个整数数组 `forbidden` ，其中 `forbidden[i]` 是跳蚤不能跳到的位置，同时给你整数 `a`， `b` 和 `x` ，请你返回跳蚤到家的最少跳跃次数。如果没有恰好到达 `x` 的可行方案，请你返回 `-1` 

## 解题思路

这道题目，跳骚的状态有 当前的位置，连续向后跳的次数，

这里是求到家的最少跳跃次数，可以理解为最短路径

### Solution 1: BFS

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1600~1699/1654.Minimum-Jumps-to-Reach-Home/)

这种解法利用 bfs 来球最少的次数，这里特别巧妙的一点是，将所有 forbidden 的点，全部在 bfs 之前标记为已经访问过了，这里在遍历过程中就不需要再次判断了，这里只需要维护好这个状态即可

````c++
class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        vector<int> visited(6000, 0);
        for (int pos : forbidden) {
            visited[pos] = 1;
        }

        int res = -1;
        queue<pair<int, int>> que;
        que.push({0, 0});

        while (!que.empty()) {
            const int len = que.size();
            ++res;

            for (int i = 0; i < len; ++i) {
                pair<int,int> item = que.front();
                que.pop();

                int cur = item.first;
                int back = item.second;

                // 如果已经到达
                if (cur == x) {
                    return res;
                }
                // 向后
                if (back == 0 && cur - b >= 0 && !visited[cur - b]) {
                    visited[cur - b] = 1;
                    que.push({cur - b, 1});
                }
                // 向前
                if (cur + a < visited.size() && !visited[cur + a]) {
                    visited[cur + a] = 1;
                    que.push({cur + a, 0});
                }
            }
        }
        return -1;
    }
};
````

