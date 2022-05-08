# [887. Super Egg Drop](https://leetcode.com/problems/super-egg-drop/)

## 题目

You are given `k` identical eggs and you have access to a building with `n` floors labeled from `1` to `n`.

You know that there exists a floor `f` where `0 <= f <= n` such that any egg dropped at a floor **higher** than `f` will **break**, and any egg dropped **at or below** floor `f` will **not break**.

Each move, you may take an unbroken egg and drop it from any floor `x` (where `1 <= x <= n`). If the egg breaks, you can no longer use it. However, if the egg does not break, you may **reuse** it in future moves.

Return *the **minimum number of moves** that you need to determine **with certainty** what the value of* `f` is.

 

**Example 1:**

```
Input: k = 1, n = 2
Output: 2
Explanation: 
Drop the egg from floor 1. If it breaks, we know that f = 0.
Otherwise, drop the egg from floor 2. If it breaks, we know that f = 1.
If it does not break, then we know f = 2.
Hence, we need at minimum 2 moves to determine with certainty what the value of f is.
```

**Example 2:**

```
Input: k = 2, n = 6
Output: 3
```

**Example 3:**

```
Input: k = 3, n = 14
Output: 4
```

 

**Constraints:**

- `1 <= k <= 100`
- `1 <= n <= 104`

## 题目大意

你将获得 `k` 个鸡蛋，并可以使用一栋从 `1` 到 `n`  共有 `n` 层楼的建筑。

每个蛋的功能都是一样的，如果一个蛋碎了，你就不能再把它掉下去。你知道存在楼层 `f` ，满足 `0 <= F <= N` 任何从高于 `F` 的楼层落下的鸡蛋都会碎，从 `f` 楼层或比它低的楼层落下的鸡蛋都不会破

每次移动，你可以取一个鸡蛋（如果你有完整的鸡蛋）并把它从任一楼层 `x` 扔下（满足 `1 <= x <= x`）

你的目标是确切地知道 f 的值是多少。无论 f 的初始值如何，你确定 f 的值的最小移动次数是多少？

## 解题思路

首先梳理一下 n 和 f 的关系

- n 表示有 1 到 n 层楼
- f 表示在 0 <= f <= n 中从比 f 高的楼层落下的蛋都会碎，从 f 层或者低于 f 层落下都不会碎

### Solution 1: DFS

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/super-egg-drop/solution/887-by-ikaruga/)

这种解法将题目：n 个楼层， k 个鸡蛋，在最少扔 t 次的前提下，测出 f 的值，转化为，k 个鸡蛋，t 次机会，求出可以确定的 f 的个数，直到等于 n 层楼为止

````
func superEggDrop(k int, n int) int {
    t := 1
    for dfs(k, t) < n + 1 {
        t++
    }
    return t
}

func dfs(k, t int) int {
    // Base case
    if k == 1 || t == 1 {
        return t + 1
    }
    // Step
    return dfs(k - 1, t - 1) + dfs(k, t - 1)
}
```
