# [1301. Number of Paths with Max Score](https://leetcode.com/problems/number-of-paths-with-max-score/)

## 题目

You are given a square `board` of characters. You can move on the board starting at the bottom right square marked with the character `'S'`.

You need to reach the top left square marked with the character `'E'`. The rest of the squares are labeled either with a numeric character `1, 2, ..., 9` or with an obstacle `'X'`. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, **taken modulo `10^9 + 7`**.

In case there is no path, return `[0, 0]`.

 

**Example 1:**

```
Input: board = ["E23","2X2","12S"]
Output: [7,1]
```

**Example 2:**

```
Input: board = ["E12","1X1","21S"]
Output: [4,2]
```

**Example 3:**

```
Input: board = ["E11","XXX","11S"]
Output: [0,0]
```

 

**Constraints:**

- `2 <= board.length == board[i].length <= 100`

## 题目大意

给定一个字符窗正方形，你可以从正方形右下角 ‘S’处开始移动，你的目标是到达左上角的‘E’，数组的剩余部分是数组1，2，3....,或者是障碍的‘X’，在每一次移动中，你可以向左，向上，或者左是左上方，返回一个列表，第一个收集的最大总分数、第二个是收集最大分数的方案数，

如果没有任何路径返回[0, 0];

## 解题思路

* 这道题其实是两个路径 DP，求得最大分数，求得最大得分的方案数
* 求最大分数：
  * 状态定义 ：`dp[x][y]`表示到达位置(x, y)，的最大分数
  * 初始化：用 INT_MIN 标记无法访问的位置
  * 状态转移：`dp[x][y] = max(dp[x - 1][y], dp[x][y + 1], dp[x + 1][y + 1]) + board[x][y]`
* 求得的最大方案数：
  * 状态定义：`dp[x][y]` 表示到达位置(x, y)，得到最大分数的方案数
  * 初始化：
  * 状态转移：这里需要注意，最大值不一定使由一个位置得出，具体看代码，这里大概的做法是：如果转之后的结果和

## 代码

