# [790. Domino and Tromino Tiling](https://leetcode-cn.com/problems/domino-and-tromino-tiling/)

## 题目

You have two types of tiles: a `2 x 1` domino shape and a tromino shape. You may rotate these shapes.

![img](https://assets.leetcode.com/uploads/2021/07/15/lc-domino.jpg)

Given an integer n, return *the number of ways to tile an* `2 x n` *board*. Since the answer may be very large, return it **modulo** `109 + 7`.

In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/07/15/lc-domino1.jpg)

```
Input: n = 3
Output: 5
Explanation: The five different ways are show above.
```

**Example 2:**

```
Input: n = 1
Output: 1
```

 

**Constraints:**

- `1 <= n <= 1000`

## 题目大意

有两种形状的瓷砖：一种是 2 x 1 的多米诺形，另一种是形如 "L" 的托米诺形。两种形状都可以旋转。

给定整数 n ，返回可以平铺 2 x n 的面板的方法的数量。返回对 109 + 7 取模 的值。

平铺指的是每个正方形都必须有瓷砖覆盖。两个平铺不同，当且仅当面板上有四个方向上的相邻单元中的两个，使得恰好有一个平铺有一个瓷砖占据两个正方形。

## 解题思路

这道题目一开始自己想的话，觉得，递推公式也不是很难，然后看了下题解，直接放弃，真想不到，

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/domino-and-tromino-tiling/solution/zong-jie-yi-xia-da-lao-de-dpsi-lu-by-huan-shi-cai-/)

````c++
class Solution {
public:
    int numTilings(int n) {
        vector<int> dp(n + 3);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;
        
        for (int i = 4; i <= n; ++i) {
            dp[i] = (2*(dp[i-1] % mod_) % mod_ + dp[i-3] % mod_) % mod_;
        }
        
        return dp[n];
    }
    
 private:
    const int mod_ = 1000000007;
};
````
