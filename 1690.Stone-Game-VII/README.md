# [1690. Stone Game VII](https://leetcode.com/problems/stone-game-vii/)

## 题目

Alice and Bob take turns playing a game, with **Alice starting first**.

There are `n` stones arranged in a row. On each player's turn, they can **remove** either the leftmost stone or the rightmost stone from the row and receive points equal to the **sum** of the remaining stones' values in the row. The winner is the one with  the higher score when there are no stones left to remove.

Bob found that he will always lose this game (poor Bob, he always loses), so he decided to **minimize the score's difference**. Alice's goal is to **maximize the difference** in the score.

Given an array of integers `stones` where `stones[i]` represents the value of the `ith` stone **from the left**, return *the **difference** in Alice and Bob's score if they both play **optimally**.*

 

**Example 1:**

```
Input: stones = [5,3,1,4,2]
Output: 6
Explanation: 
- Alice removes 2 and gets 5 + 3 + 1 + 4 = 13 points. Alice = 13, Bob = 0, stones = [5,3,1,4].
- Bob removes 5 and gets 3 + 1 + 4 = 8 points. Alice = 13, Bob = 8, stones = [3,1,4].
- Alice removes 3 and gets 1 + 4 = 5 points. Alice = 18, Bob = 8, stones = [1,4].
- Bob removes 1 and gets 4 points. Alice = 18, Bob = 12, stones = [4].
- Alice removes 4 and gets 0 points. Alice = 18, Bob = 12, stones = [].
The score difference is 18 - 12 = 6.
```

**Example 2:**

```
Input: stones = [7,90,5,1,100,10,10,2]
Output: 122
```

 

**Constraints:**

- `n == stones.length`
- `2 <= n <= 1000`
- `1 <= stones[i] <= 1000`

## 题目大意

石子游戏中，爱丽丝和鲍勃轮流进行自己的回合，爱丽丝先开始。有 `n` 块石子排成一排

每个玩家的回合中，可以从行中 移除  最左边的石头或最右边的石头，并获得与该行中剩余石头值之 和  相等的得分。当没有石头可移除时，得分较高者获胜

鲍勃发现他总是输掉游戏（可怜的鲍勃，他总是输），所以他决定尽力 减小得分的差值  。爱丽丝的目标是最大限度地 扩大得分的差值

给你一个整数数组 stones ，其中 stones[i] 表示 从左边开始 的第 i 个石头的值，如果爱丽丝和鲍勃都 发挥出最佳水平 ，请返回他们 得分的差值

## 解题思路

这道题目是比较典型的区间 dp 的题目

### Solution 1: dp

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/stone-game-vii/solution/javadp-yi-yu-li-jie-dpshu-zu-jin-jin-kao-uufn/)

````c++
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        const int len = stones.size();
        // dp[i][j] 表示 在区间 [i, j]上 alice 作为先手，产生的最大差值
        vector<vector<int>> dp(len, vector<int>(len));
        for (int i = len - 2; i >= 0; --i) {
            for (int j = i + 1; j < len; ++j) {
                if (i + 1 == j) {
                    // 如果只有两个元素了
                    dp[i][j] = max(stones[i], stones[j]);
                } else {
                    // alice 选择 i
                    // bob 可以选择 i + 1，或者 j
                    int left = min(stones[i + 1] + dp[i + 2][j], stones[j] + dp[i + 1][j - 1]);
                    // alice 选择 j
                    // bob 可以选择 i 或者 j - 1
                    int right = min(stones[i] + dp[i + 1][j - 1], stones[j - 1] + dp[i][j - 2]);
                    // 维护这个最大值
                    dp[i][j] = max(left, right);
                }
            }
        }
        return dp[0][len - 1];
    }
};
````
