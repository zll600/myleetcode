# [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)

## 题目

You are climbing a staircase. It takes `n` steps to reach the top.

Each time you can either climb `1` or `2` steps. In how many distinct ways can you climb to the top?

 

**Example 1:**

```
Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
```

**Example 2:**

```
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
```

 

**Constraints:**

- `1 <= n <= 45`

## 题目大意

假设你正在爬楼梯。需要 *n* 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

## 解题思路

### Solution 1: DP

**状态定义**：`dp[i]` 表示爬上第 n 阶台阶的方法数，所以这里的数组要多分配一位

**转移方程**：第 n 阶台阶可以由n - 1 阶台阶跨一步，也可以由 n - 2 阶台阶跨 2 步

`````
dp[i] = dp[i - 1] + dp[i - 2]
`````

**初始化**：这里必须初始化 dp[1] 和 dp[2] ，才能使状态递推下去，dp[0] 没有实际意义，

结果：dp[n] 表示第 n 阶台阶的方法数

````c++
class Solution {
public:
    int climbStairs(int n) {
        if (n < 3) {  // 特殊情况，特殊处理
            return n;
        }

        vector<int> dp(n + 1, 0);
        // 这里不初始化0，因为 0 没有意义
        dp[1] = 1;  // 初始化
        dp[2] = 2;  // 初始化

        for (int i = 3; i < n + 1; ++i) {
            // 状态转移
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};
````

