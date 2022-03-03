# [935. Knight Dialer](https://leetcode-cn.com/problems/knight-dialer/)

## 题目

The chess knight has a **unique movement**, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an **L**). The possible movements of chess knight are shown in this diagaram:

A chess knight can move as indicated in the chess diagram below:

![img](https://assets.leetcode.com/uploads/2020/08/18/chess.jpg)

We have a chess knight and a phone pad as shown below, the knight **can only stand on a numeric cell** (i.e. blue cell).

![img](https://assets.leetcode.com/uploads/2020/08/18/phone.jpg)

Given an integer `n`, return how many distinct phone numbers of length `n` we can dial.

You are allowed to place the knight **on any numeric cell** initially and then you should perform `n - 1` jumps to dial a number of length `n`. All jumps should be **valid** knight jumps.

As the answer may be very large, **return the answer modulo** `109 + 7`.

 

**Example 1:**

```
Input: n = 1
Output: 10
Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
```

**Example 2:**

```
Input: n = 2
Output: 20
Explanation: All the valid number we can dial are [04, 06, 16, 18, 27, 29, 34, 38, 40, 43, 49, 60, 61, 67, 72, 76, 81, 83, 92, 94]
```

**Example 3:**

```
Input: n = 3131
Output: 136006598
Explanation: Please take care of the mod.
```

 

**Constraints:**

- `1 <= n <= 5000`

## 题目大意

象棋骑士有一个独特的移动方式，它可以垂直移动两个方格，水平移动一个方格，或者水平移动两个方格，垂直移动一个方格(两者都形成一个 L 的形状)。

我们有一个象棋骑士和一个电话垫，如下所示，骑士只能站在一个数字单元格上(即蓝色单元格)。

给定一个整数 n，返回我们可以拨多少个长度为 n 的不同电话号码。

你可以将骑士放置在任何数字单元格上，然后你应该执行 n - 1 次移动来获得长度为 n 的号码。所有的跳跃应该是有效的骑士跳跃。

因为答案可能很大，所以输出答案模 109 + 7.


## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/knight-dialer/solution/dpji-yi-hua-di-gui-by-8bun/)

这道题目的状态变量就是跳第 几次，到达哪个位置，

### Solution 1: DP


````c++
class Solution {
public:
    int knightDialer(int n) {
        // dp[i][j] 表示跳第 i 步的时候，到达 j 位置的时候可以欧多少种可能的组合
        vector<vector<int>> dp(n, vector<int>(10, 0));
        // 初始化
        for (int i = 0; i < 10; ++i) {
            dp[0][i] = 1;
        }
        
        // 递推，每个位置都可以由它本身可达的所有点到达
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 10; ++j) {
                for (int path : paths_[j]) {
                    dp[i][j] =(dp[i][j] + dp[i - 1][path]) % mod_;
                }
            }
        }
        
        int res = 0;
        for (int i = 0; i < 10; ++i) {
            res = (res + dp[n - 1][i]) % mod_;
        }
        
        return res % mod_;
    }
    
 private:
    // 这里提前写好琮每个位置开始可达的点
    const vector<vector<int>> paths_ = {
        {4, 6},
        {6, 8},
        {7, 9},
        {4, 8},
        {3, 9, 0},
        {},
        {1, 7, 0},
        {2, 6},
        {1, 3},
        {4, 2}
    };
    // 主意过程中的结果
    const int mod_ = 1000000007;
};
````



