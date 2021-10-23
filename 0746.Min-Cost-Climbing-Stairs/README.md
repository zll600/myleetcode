# [746. Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)

## 题目

You are given an integer array `cost` where `cost[i]` is the cost of `ith` step on a staircase. Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index `0`, or the step with index `1`.

Return *the minimum cost to reach the top of the floor*.

 

**Example 1:**

```
Input: cost = [10,15,20]
Output: 15
Explanation: You will start at index 1.
- Pay 15 and climb two steps to reach the top.
The total cost is 15.
```

**Example 2:**

```
Input: cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6
Explanation: You will start at index 0.
- Pay 1 and climb two steps to reach index 2.
- Pay 1 and climb two steps to reach index 4.
- Pay 1 and climb two steps to reach index 6.
- Pay 1 and climb one step to reach index 7.
- Pay 1 and climb two steps to reach index 9.
- Pay 1 and climb one step to reach the top.
The total cost is 6.
```

 

**Constraints:**

- `2 <= cost.length <= 1000`
- `0 <= cost[i] <= 999`

## 题目大意

给定一个数组 cost 其中 cost[i] 表示台阶上的第 i 步，一旦你支付了花费，你就爬上一级或者两级台阶，你可以选择从 0 开始，或者从 1 开始，返回爬上楼梯顶部的最小花费

## 解题思路

这道题目和第 70 题很像，可以参考

### Solution 1: DP

注意这里求的是台阶的顶部，所以最终可以从 size - 1和 size - 2 两个位置到达，

* 状态定义：爬上第 i 阶台阶，所需要的最小花费，
* 状态转移：

````
dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
````

* 初始化：这里需要初始化 dp[i - 1] 和 dp[i - 2] 使整个地推可以进行下去
* 结果，选则 size - 1 和 size - 2 两个位置中最小的一个

````c++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        const int size = cost.size();
        vector<int> dp(size, 0);
        // 初始化
        dp[0] = cost[0];
        dp[1] = cost[1];
        
        for (int i = 2; i < size; ++i) {
            // 状态转移
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        }
        
        return min(dp[size - 1], dp[size - 2]);
    }
};
````

### Solution 2: 空间优化 dp

使用有限的变量来代替 dp 数组

````c++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        const int size = cost.size();
        int first = cost[0];
        int second = cost[1];
        
        for (int i = 2; i < size; ++i) {
            int cur = min(first, second) + cost[i];
            first = second;
            second = cur;
        }
        
        return min(first, second);
    }
};
````



