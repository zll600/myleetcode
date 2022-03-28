# [649. Dota2 Senate](https://leetcode-cn.com/problems/dota2-senate/)

In the world of Dota2, there are two parties: the Radiant and the Dire.

The Dota2 senate consists of senators coming from two parties. Now  the Senate wants to decide on a change in the Dota2 game. The voting for this change is a round-based procedure. In each round, each senator can exercise **one** of the two rights:

- **Ban one senator's right:** A senator can make another senator lose all his rights in this and all the following rounds.
- **Announce the victory:** If this senator found the  senators who still have rights to vote are all from the same party, he  can announce the victory and decide on the change in the game.

Given a string `senate` representing each senator's party belonging. The character `'R'` and `'D'` represent the Radiant party and the Dire party. Then if there are `n` senators, the size of the given string will be `n`.

The round-based procedure starts from the first senator to the last  senator in the given order. This procedure will last until the end of  voting. All the senators who have lost their rights will be skipped  during the procedure.

Suppose every senator is smart enough and will play the best strategy for his own party. Predict which party will finally announce the  victory and change the Dota2 game. The output should be `"Radiant"` or `"Dire"`.

 

**Example 1:**

```
Input: senate = "RD"
Output: "Radiant"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And in round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.
```

**Example 2:**

```
Input: senate = "RDD"
Output: "Dire"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And the third senator comes from Dire and he can ban the first senator's right in round 1. 
And in round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.
```

 

**Constraints:**

- `n == senate.length`
- `1 <= n <= 104`
- `senate[i]` is either `'R'` or `'D'`.

`Dota2` 的世界里有两个阵营：`Radiant(天辉)`和 `Dire(夜魇)`

`Dota2` 参议院由来自两派的参议员组成。现在参议院希望对一个 `Dota2` 游戏里的改变作出决定。他们以一个基于轮回过程的投票进行。在每一轮中，每一位参议员都可以行使两项权利中的一项


- 禁止一名参议员的权利：

    参议员可以让另一位参议员在这一轮和随后的几轮中丧失所有的权利。

- 宣布胜利：

    如果参议员发现有权利投票的参议员都是同一个阵营的，他可以宣布胜利并决定在游戏中的有关变化。

给定一个字符串代表每个参议员的阵营。字母 `“R”` 和 `“D”` 分别代表了 `Radiant（天辉）` 和 `Dire（夜魇）` 。然后，如果有 `n` 个参议员，给定字符串的大小将是 `n`

以轮为基础的过程从给定顺序的第一个参议员开始到最后一个参议员结束。这一过程将持续到投票结束。所有 *失去权利* 的参议员将在过程中被跳过。

假设每一位参议员都足够聪明，会为自己的政党做出最好的策略，你需要预测哪一方最终会宣布胜利并在 `Dota2` 游戏中决定改变。输出应该是 `Radiant` 或 `Dire`。

## 解题思路



### Solution 1: 

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/dota2-senate/solution/java-649dota2can-yi-yuan-chao-9961-by-mu-0dqh/)

- 每个参议员都都只有两种状态，*持有权利* 或者 *失去权利*
- 先遍历到的参议员可以禁止对方政党的 *参议员的所有权利*


````c++
class Solution {
public:
    string predictPartyVictory(string senate) {
        int r_number = 0, d_number = 0;
        int r_cur_ban = 0, d_cur_ban = 0;
        int r_total_ban = 0, d_total_ban = 0;
        
        // 只有这个标志开启的时候，才会统计字符的总数
        bool flag = true;
        const int len = senate.size();
        while (true) {
            for (int i = 0; i < len; ++i) {
                if (senate[i] == 'R') {
                    if (flag) {
                        ++r_number;
                    }
                    if (r_cur_ban == 0) {
                        // 如果没有被禁止的 'R'，那么这个 'R'，就可以禁止一个 'D'
                        
                        ++d_cur_ban;
                        ++d_total_ban;
                        
                        // 如果所有的 'D'，都被禁止了，那么剩下的就是 'R'
                        if (d_total_ban == d_cur_ban && !flag) {
                            return "Radiant";
                        }
                    } else {
                        // 这个 'R'，被之前的 'D' 禁止了，所以什么也不能做
                        --r_cur_ban;
                        senate[i] = 'r';
                    }
                } else if (senate[i] == 'D') {
                    if (flag) {
                        ++d_number;      
                    }
                    if (d_cur_ban == 0) {
                        // 如果之前可以禁止 'D' 的 'R'，那么这个 'D'，就不能作用了
                        ++r_cur_ban;
                        ++r_total_ban;
                        
                        // 如果所有的 'R'，都被禁止了，那么 'D'，赢
                        if (r_total_ban == r_cur_ban && !flag) {
                            return "Dire";
                        }
                    } else {
                        // 如果这个 'D' 不能起作用
                        --d_cur_ban;
                        senate[i] = 'd';
                    }
                }
            }
            
            // 只有第一轮统计 'R' 和 'D' 的总数的时候，这个标志才处于开启状态
            flag = false;
            
            if (d_total_ban >= d_number) {
                return "Radiant";
            }
            if (r_total_ban >= r_number) {
                return "Dire";
            }
        }
        
        return "";
    }
};
````
