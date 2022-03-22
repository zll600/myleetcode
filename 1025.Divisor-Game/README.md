# [1025. Divisor Game](https://leetcode.com/problems/divisor-game/)

## 题目

Alice and Bob take turns playing a game, with Alice starting first.

Initially, there is a number `n` on the chalkboard. On each player's turn, that player makes a move consisting of:

- Choosing any `x` with `0 < x < n` and `n % x == 0`.
- Replacing the number `n` on the chalkboard with `n - x`.

Also, if a player cannot make a move, they lose the game.

Return `true` *if and only if Alice wins the game, assuming both players play optimally*.

 

**Example 1:**

```
Input: n = 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.
```

**Example 2:**

```
Input: n = 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.
```

 

**Constraints:**

- `1 <= n <= 1000`

## 题目大意

Alice 和 Bob 轮流做游戏，Alice 先开始，开始时，黑板上有一个数字 `n`，每一个玩家的回合，需要执行以下操作：

- 选择 `x` 在 `0 < x < n` 和 `n % x == 0`
- 用黑板上的 `n - x` 替换 `n`

如果玩家不能执行任何一种操作，他输掉游戏,

当 Alice 获胜的时候，返回 true,假设两玩家都选择最优

## 解题思路

这道题目我们可以参考 [这篇题解](https://leetcode-cn.com/problems/divisor-game/solution/python3gui-na-fa-by-pandawakaka/)


### Solution 1:

举几个例子可以发现，最终谁拿到 2 的话，就会输，而拿到 1 的话就会赢，

- 是奇数，那么只能选择奇数，奇数 - 奇数是偶数
- 如果是偶数，那么会选择偶数或者奇数，或者 1，那么选择 1,

````c++
class Solution {
public:
    bool divisorGame(int n) {
        return n % 2 == 0;
    }
};
````
