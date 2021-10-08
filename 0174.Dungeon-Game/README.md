# [174. Dungeon Game](https://leetcode.com/problems/dungeon-game/)

The demons had captured the princess and imprisoned her in **the bottom-right corner** of a `dungeon`. The `dungeon` consists of `m x n` rooms laid out in a 2D grid. Our valiant knight was initially positioned in **the top-left room** and must fight his way through `dungeon` to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to `0` or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers), so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic orbs that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible, the knight decides to move only **rightward** or **downward** in each step.

Return *the knight's minimum initial health so that he can rescue the princess*.

**Note** that any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/13/dungeon-grid-1.jpg)

```
Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
Output: 7
Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.
```

**Example 2:**

```
Input: dungeon = [[0]]
Output: 1
```

 

**Constraints:**

- `m == dungeon.length`
- `n == dungeon[i].length`
- `1 <= m, n <= 200`
- `-1000 <= dungeon[i][j] <= 1000`

## 题目大意

一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。

骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。

有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。

为了尽快到达公主，骑士决定每次只向右或向下移动一步。

 

编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。

## 解题思路

这道题目左程云那本书中有答案，注意这里骑士的健康点数最小为 1，

### 解法1（动态规划）

* 状态定义：`dp[i][j]`表示骑士从 位置`[i][j]` ,到达右下角需要的最低健康点数，所以这道题木需要反向来求解，从右下角出发
* 状态转移：题目已经告诉我们，骑士在前往右下角的时候，每一步可以向右，也可以向下，那么如果**反向**来求解，骑士每一步可以向左，也可以向上，如果可以到达的话，就有`dp[i][j] + dungeon[i][j] = dp[i + 1][j]`、`dp[i][j] + dungeon[i][j] = dp[i][j - 1]`
* 初始化，这里的状态转移方程有两个地方不能使用，分别是最后一行，和最后一列，所以初始化这两个部分，就可以使得整个递推可以继续进行下去，

`````c++
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int rows = dungeon.size();
        int cols = dungeon[0].size();
        
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        int row = rows - 1;
        int col = cols - 1;
        // 骑士不能死亡，所以健康值至少为 1，
        // 如果房间的数值为正，则取 1 即可，
        // 如果房间的数值为负，则取房间数值的相反数 + 1，
        dp[row][col] = dungeon[row][col] > 0 ? 1 : -dungeon[row][col] + 1;
        
        // 初始化最后一行，只能由右边转移过来
        for (int j = col - 1; j >= 0; j--) {
            dp[row][j] = max(dp[row][j + 1] - dungeon[row][j], 1);
        }
        
        for (int i = row - 1; i >= 0; i--) {
            // 初始化最后一列，只能由下边转移过来
            dp[i][col] = max(dp[i + 1][col] - dungeon[i][col], 1);
            for (int j = col - 1; j >= 0; j--) {
                // 状态转移
                // 可以从右边
                int right = max(dp[i][j + 1] - dungeon[i][j], 1);
                // 也可以从下边
                int down = max(dp[i + 1][j] - dungeon[i][j], 1);
                
                dp[i][j] = min(right, down);
            }
        }
        
        return dp[0][0];
    }
};
`````

