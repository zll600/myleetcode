# [754. Reach a Number](https://leetcode-cn.com/problems/reach-a-number/)

## 题目

You are standing at position `0` on an infinite number line. There is a destination at position `target`.

You can make some number of moves `numMoves` so that:

- On each move, you can either go left or right.
- During the `ith` move (starting from `i == 1` to `i == numMoves`), you take `i` steps in the chosen direction.

Given the integer `target`, return *the **minimum** number of moves required (i.e., the minimum* `numMoves`*) to reach the destination*.

 

**Example 1:**

```
Input: target = 2
Output: 3
Explanation:
On the 1st move, we step from 0 to 1 (1 step).
On the 2nd move, we step from 1 to -1 (2 steps).
On the 3rd move, we step from -1 to 2 (3 steps).
```

**Example 2:**

```
Input: target = 3
Output: 2
Explanation:
On the 1st move, we step from 0 to 1 (1 step).
On the 2nd move, we step from 1 to 3 (2 steps).
```

 

**Constraints:**

- `-109 <= target <= 109`
- `target != 0`

## 题目大意

在一根无限长的数轴上，你站在 `0` 的位置。终点在 `target` 的位置。

你可以做一些数量的移动 `numMoves` :

- 每次你可以选择 *向左* 或 *向右* 移动。
- 第 `i` 次移动（从  `i == 1` 开始，到 `i == numMoves` ），在选择的方向上走 `i` 步。

给定整数 `target` ，返回 到达目标所需的 *最小* 移动次数(即 `最小numMoves` ) 。

## 解题思路

这道题目比较难，我们要从题目的已知条件中找到可以 等价关系然后找到结果

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/reach-a-number/solution/deng-jie-yu-shu-zu-tian-jia-zheng-fu-hao-wen-ti-by/)


````c++
class Solution {
public:
    int reachNumber(int target) {
        if (target < 0) {
            // 如果是负数，我们处理为正数
            target = -target;
        }
        
        int i = 1;
        while (true) {
            // 这里利用等差数列的前 n 項和
            int total = (i * i + i) / 2;
            if (total >= target && (total - target) % 2 == 0) {
                // 找到最小的满足条件的 i
                return i;
            }
            ++i;
        }
        
        return -1;
    }
};
`````


