# [1423. Maximum Points You Can Obtain from Cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/)

## 题目

There are several cards **arranged in a row**, and each card has an associated number of points. The points are given in the integer array `cardPoints`.

In one step, you can take one card from the beginning or from the end of the row. You have to take exactly `k` cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array `cardPoints` and the integer `k`, return the *maximum score* you can obtain.

 

**Example 1:**

```
Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.
```

**Example 2:**

```
Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.
```

**Example 3:**

```
Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards.
```

 

**Constraints:**

- `1 <= cardPoints.length <= 105`
- `1 <= cardPoints[i] <= 104`
- `1 <= k <= cardPoints.length`

## 题目大意

几张卡牌 排成一行，每张卡牌都有一个对应的点数。点数由整数数组 `cardPoints` 给出

每次行动，你可以从行的开头或者末尾拿一张卡牌，最终你必须正好拿 `k` 张卡牌

你的点数就是你拿到手中的所有卡牌的点数之和。给你一个整数数组 `cardPoints` 和整数 `k`，请你返回可以获得的最大点数

## 解题思路

这道题目可以参考 [这篇题解]()

### Solution 1: DFS

当这道题目没有什么头绪的时候，很可能会想到使用 dfs 来暴力枚举所有可能，然后选择最优解，

- base case：k == 0，只能返回 0
- transition k != 0 max(选左边卡牌，从剩余卡牌中选择 k - 1张，选右边卡牌，从剩余卡牌中选择 k - 1 张)

虽然这种解法使用了记忆化，但是还是会超时

````python3
class Solution:
    def maxScore(self, card_points: List[int], k: int) -> int:
        n = len(card_points)
        self.memo = {}
        return self.dfs(card_points, 0, n - 1, k)

    def dfs(self, card_points, i, j, k):
        # base case
        if k == 0:
            return 0
        if (i, j) in self.memo:
            return self.memo[(i, j)]

        # transition
        left = card_points[i] + self.dfs(card_points, i + 1, j, k - 1)
        right = card_points[j] + self.dfs(card_points, i, j - 1, k - 1)
        res = max(left, right)
        self.memo[(i, j)] = res
        return res
````
