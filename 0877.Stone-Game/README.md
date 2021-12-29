# [877. Stone Game](https://leetcode-cn.com/problems/stone-game/)

## 题目

Alice and Bob play a game with piles of stones. There are an **even** number of piles arranged in a row, and each pile has a **positive** integer number of stones `piles[i]`.

The objective of the game is to end with the most stones. The **total** number of stones across all the piles is **odd**, so there are no ties.

Alice and Bob take turns, with **Alice starting first**. Each turn, a player takes the entire pile of stones either from the **beginning** or from the **end** of the row. This continues until there are no more piles left, at which point the person with the **most stones wins**.

Assuming Alice and Bob play optimally, return `true` *if Alice wins the game, or* `false` *if Bob wins*.

 

**Example 1:**

```
Input: piles = [5,3,4,5]
Output: true
Explanation: 
Alice starts first, and can only take the first 5 or the last 5.
Say she takes the first 5, so that the row becomes [3, 4, 5].
If Bob takes 3, then the board is [4, 5], and Alice takes 5 to win with 10 points.
If Bob takes the last 5, then the board is [3, 4], and Alice takes 4 to win with 9 points.
This demonstrated that taking the first 5 was a winning move for Alice, so we return true.
```

**Example 2:**

```
Input: piles = [3,7,2,3]
Output: true
```

 

**Constraints:**

- `2 <= piles.length <= 500`
- `piles.length` is **even**.
- `1 <= piles[i] <= 500`
- `sum(piles[i])` is **odd**.

## 题目大意

Alice 和 Bob 用几堆石子在做游戏。一共有**偶数**堆石子，排成一行；每堆都有 正 整数颗石子，数目为 `piles[i]` 。

游戏以谁手中的石子最多来决出胜负。石子的 总数 是 **奇数** ，所以没有平局。

Alice 和 Bob 轮流进行，Alice 先开始 。 每回合，玩家从行的 开始 或 结束 处取走整堆石头。 这种情况一直持续到没有更多的石子堆为止，此时手中 石子最多 的玩家 获胜 。

假设 Alice 和 Bob 都发挥出最佳水平，当 Alice 赢得比赛时返回 true ，当 Bob 赢得比赛时返回 false 。

## 解题思路

这道题可以参考这篇题解：https://leetcode-cn.com/problems/stone-game/solution/ji-yi-hua-di-gui-dong-tai-gui-hua-shu-xue-jie-java/

这里引入一个相对分数的概念：「相对分数」的意思是，我作为先手，得分是正分，而对手得分与我而言是负分。动态规划在状态转移的过程中，每一步考虑「相对分数」最大，即综合了「正分」和「负分」的结果得出最佳选择。

### Solution 1: 记忆化递归

先自顶向下递归，在自底向上递归

````c++
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        const int len = piles.size();
        // 因为这里使用的是相对分数，并要选取最大值，所以这里需要设置最小的负值作为初始值，
        vector<vector<int>> cache(len, vector<int>(len, INT_MIN));
        for (int i = 0; i < len; ++i) {
            // 如果只有一个可以选的话，那么分数就是那一摞石头的数量
            cache[i][i] = piles[i];
        }
        return StoneGame(piles, 0, len - 1, cache);
    }
    
 private:
    int StoneGame(const vector<int>& piles, int left, int right, vector<vector<int>>& cache) {
        if (left == right) {
            // 终止条件
            return piles[left];
        }
        
        if (cache[left][right] != INT_MIN) {
            // 先查缓存
            return cache[left][right];
        }
        //。选左边
        int left_result = piles[left] - StoneGame(piles, left + 1, right, cache);
        // 选右边
        int right_result = piles[right] - StoneGame(piles, left, right - 1, cache);
        int res = max(left_result, right_result); // 取最大
        cache[left][right] = res;
        return res;
    }
};
````

### Solution 2: DP

这道题目是满足无后效性的

如果已经写出了 记忆化递归，可以根据记忆化递归来写 dp，

* 状态定义：`dp[i][j]`表示区间`[i...j]`内可以获得的相对分数
* 状态转移方程：`dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1])`
* 初始化：`dp[i][i]`表示只有一个可选的

```c++
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        const int len = piles.size();
        
        vector<vector<int>> dp(len, vector<int>(len, INT_MIN));
        for (int i = 0; i < len; ++i) {
            dp[i][i] = piles[i];
        }
        
        for (int j = 1; j < len; ++j) {
            for (int i = j - 1; i >= 0; --i) {
                dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
            }
        }
        return dp[0][len - 1];
    }
};
```

