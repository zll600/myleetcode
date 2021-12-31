# [486. Predict the Winner](https://leetcode-cn.com/problems/predict-the-winner/)

## 题目

You are given an integer array `nums`. Two players are playing a game with this array: player 1 and player 2.

Player 1 and player 2 take turns, with player 1 starting first. Both players start the game with a score of `0`. At each turn, the player takes one of the numbers from either end of the array (i.e., `nums[0]` or `nums[nums.length - 1]`) which reduces the size of the array by `1`. The player adds the chosen number to their score. The game ends when there are no more elements in the array.

Return `true` if Player 1 can win the game. If the scores of both players are equal, then player 1 is still the winner, and you should also return `true`. You may assume that both players are playing optimally.

 

**Example 1:**

```
Input: nums = [1,5,2]
Output: false
Explanation: Initially, player 1 can choose between 1 and 2. 
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2). 
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5. 
Hence, player 1 will never be the winner and you need to return false.
```

**Example 2:**

```
Input: nums = [1,5,233,7]
Output: true
Explanation: Player 1 first chooses 1. Then player 2 has to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
```

 

**Constraints:**

- `1 <= nums.length <= 20`
- `0 <= nums[i] <= 107`

## 题目大意

给定一个整数数组 nums，有两名玩家在进行游戏：player1 和 player2 

player 1 和player 2 轮流进行。player1 先开始，两个玩家的初始分值都是 0 。每一回合，玩家从数组的任意一端取一个数字（即，nums[0] 或 nums[nums.length - 1]），取到的数字将会从数组中移除（数组长度减 1 ）。玩家选中的数字将会加到他的得分上。当数组中没有剩余数字可取时，游戏结束。

如果玩家 1 能成为赢家，返回 true 。如果两个玩家得分相等，同样认为玩家 1 是游戏的赢家，也返回 true 。你可以假设每个玩家的玩法都会使他的分数最大化。

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/predict-the-winner/solution/ji-yi-hua-di-gui-dong-tai-gui-hua-java-by-liweiwei/

这道题目也属于区间dp，解法可以参考第 877 题

注意这道题目的范围是在

### Solution 1: 记忆化递归

```c++
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        const int len = nums.size();
        vector<vector<int>> cache(len, vector<int>(len, INT_MIN));
        for (int i = 0; i < len; ++i) {
            cache[i][i] = nums[i];
        }
        return PredictTheWinner(nums, 0, len - 1, cache) >= 0;
    }
    
 private:
    int PredictTheWinner(const vector<int>& nums, int left, int right,
                        vector<vector<int>>& cache) {
        if (left == right) {
            // 递归终止条件，只有一个可选的
            return nums[left];
        }
        
        if (cache[left][right] != INT_MIN) {
            // 先查缓存
            return cache[left][right];
        }
        
        // 先手选左端
        int left_result = nums[left] - PredictTheWinner(nums, left + 1, right, cache);
        // 先手选右端
        int right_result = nums[right] - PredictTheWinner(nums, left, right - 1, cache);
        // 取最大值
        int res = max(left_result, right_result);
        cache[left][right] = res;
        return res;
    }
};
```

### Solution 2: DP

如果可以写出记忆化递归，则可以根据记忆化递归来写 dp

* 状态定义：`dp[i][j]`表示先手在`[i...j]`中做选择的道的相对分数
* 状态转移方程：`dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1])`
* 初始化：要使整个递推可以进行下去，初始化只有一个可选的时候

````c++
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        const int len = nums.size();
        vector<vector<int>> dp(len, vector<int>(len, INT_MIN));
        for (int i = 0; i < len; ++i) {
            dp[i][i] = nums[i];
        }
        
        for (int j = 1; j < len; ++j) {
            for (int i = j - 1; i >= 0; --i) {
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }
        return dp[0][len - 1] >= 0;
    }
  
};
````

