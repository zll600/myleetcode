# [948. Bag of Tokens](https://leetcode.cn/problems/bag-of-tokens/)

## 题目

You have an initial **power** of `power`, an initial **score** of `0`, and a bag of `tokens` where `tokens[i]` is the value of the `ith` token (0-indexed).

Your goal is to maximize your total **score** by potentially playing each token in one of two ways:

- If your current **power** is at least `tokens[i]`, you may play the `ith` token face up, losing `tokens[i]` **power** and gaining `1` **score**.
- If your current **score** is at least `1`, you may play the `ith` token face down, gaining `tokens[i]` **power** and losing `1` **score**.

Each token may be played **at most** once and **in any order**. You do **not** have to play all the tokens.

Return *the largest possible **score** you can achieve after playing any number of tokens*.

 

**Example 1:**

```
Input: tokens = [100], power = 50
Output: 0
Explanation: Playing the only token in the bag is impossible because you either have too little power or too little score.
```

**Example 2:**

```
Input: tokens = [100,200], power = 150
Output: 1
Explanation: Play the 0th token (100) face up, your power becomes 50 and score becomes 1.
There is no need to play the 1st token since you cannot play it face up to add to your score.
```

**Example 3:**

```
Input: tokens = [100,200,300,400], power = 200
Output: 2
Explanation: Play the tokens in this order to get a score of 2:
1. Play the 0th token (100) face up, your power becomes 100 and score becomes 1.
2. Play the 3rd token (400) face down, your power becomes 500 and score becomes 0.
3. Play the 1st token (200) face up, your power becomes 300 and score becomes 1.
4. Play the 2nd token (300) face up, your power becomes 0 and score becomes 2.
```

 

**Constraints:**

- `0 <= tokens.length <= 1000`
- `0 <= tokens[i], power < 104`

## 题目大意

你的初始 能量 为 `P`，初始 分数 为 `0`，只有一包令牌 `tokens` 。其中 `tokens[i]` 是第 `i` 个令牌的值（下标从 `0` 开始）

令牌可能的两种使用方法如下：

-   如果你至少有 token[i] 点 能量 ，可以将令牌 i 置为正面朝上，失去 token[i] 点 能量 ，并得到 1 分 
-   如果我们至少有 1 分 ，可以将令牌 i 置为反面朝上，获得 token[i] 点 能量 ，并失去 1 分 

每个令牌 最多 只能使用一次，使用 顺序不限 ，不需 使用所有令牌

在使用任意数量的令牌后，返回我们可以得到的最大 分数

## 解题思路

### Solution 1: Two Pointers

先排序，利用较小值来增加分数，利用较大值增加 能量，

这里需要注意的一个地方有，如果 right - left <= 1 时，说明 二者已经相邻了，此时如果继续操作，最多损失一分以获得能量，然后再随时能量获得一分，这种情况其实就不用在随时分数了


````c++
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());

        int scores = 0;
        int left = 0, right = tokens.size() - 1;
        while (left <= right) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                ++scores;
                ++left;
            } else {
                if (scores > 0 && right - left > 1) {
                    --scores;
                    power += tokens[right];
                    --right;
                } else {
                    break;
                }
            }
            // cout << power << endl;
        }
        return scores;
    }
};
````
