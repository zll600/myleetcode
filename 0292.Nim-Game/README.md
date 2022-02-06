# [292. Nim Game](https://leetcode-cn.com/problems/nim-game/)

## 题目

You are playing the following Nim Game with your friend:

- Initially, there is a heap of stones on the table.
- You and your friend will alternate taking turns, and **you go first**.
- On each turn, the person whose turn it is will remove 1 to 3 stones from the heap.
- The one who removes the last stone is the winner.

Given `n`, the number of stones in the heap, return `true` *if you can win the game assuming both you and your friend play optimally, otherwise return* `false`.

 

**Example 1:**

```
Input: n = 4
Output: false
Explanation: These are the possible outcomes:
1. You remove 1 stone. Your friend removes 3 stones, including the last stone. Your friend wins.
2. You remove 2 stones. Your friend removes 2 stones, including the last stone. Your friend wins.
3. You remove 3 stones. Your friend removes the last stone. Your friend wins.
In all outcomes, your friend wins.
```

**Example 2:**

```
Input: n = 1
Output: true
```

**Example 3:**

```
Input: n = 2
Output: true
```

 

**Constraints:**

- `1 <= n <= 231 - 1`

## 题目大意

你正在和你的朋友玩 nim 游戏：

* 开始时，桌子上有一堆石头，
* 你和你的朋友轮流做，你先开始，
* 每次，轮到某个人的话，当前这个人可以选择从堆中删除 1 到 3 个石头，
* 删除最后一个石头的人获得胜利

假设你们每一步都是最优解。请编写一个函数，来判断你是否可以在给定石头数量为 `n` 的情况下赢得游戏。如果可以赢，返回 `true`；否则，返回 `false` 。

## 解题思路

这道题不会：我直接放题解：https://leetcode-cn.com/problems/nim-game/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-wmz2t/

### Solution 1:

````c++
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4 != 0;
    }
};
````

