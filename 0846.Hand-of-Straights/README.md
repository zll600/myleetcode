# [846. Hand of Straights](https://leetcode.com/problems/hand-of-straights/)

## 题目

Alice has some number of cards and she wants to rearrange the cards into groups so that each group is of size `groupSize`, and consists of `groupSize` consecutive cards.

Given an integer array `hand` where `hand[i]` is the value written on the `ith` card and an integer `groupSize`, return `true` if she can rearrange the cards, or `false` otherwise.

 

**Example 1:**

```
Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]
```

**Example 2:**

```
Input: hand = [1,2,3,4,5], groupSize = 4
Output: false
Explanation: Alice's hand can not be rearranged into groups of 4.
```

 

**Constraints:**

- `1 <= hand.length <= 104`
- `0 <= hand[i] <= 109`
- `1 <= groupSize <= hand.length`

 

**Note:** This question is the same as 1296: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/

## 题目大意

`Alice` 手中有一把牌，她想要重新排列这些牌，分成若干组，使每一组的牌数都是 `groupSize` ，并且由 `groupSize` 张连续的牌组成。

给你一个整数数组 `hand` 其中 `hand[i]` 是写在第 `i` 张牌，和一个整数 `groupSize` 。如果她可能重新排列这些牌，返回 `true` ；否则，返回 `false` 。

## 解题思路

我们先将数组排序，排序后，开始一组一组构建，如果任意一组构建失败，直接返回 false

### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0846.Hand-of-Straights/)

````c++
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int group_size) {
        const int len = hand.size();
        if (len % group_size != 0) {
            return false;
        }

        // 排序
        sort(hand.begin(), hand.end());
        // 统计频数
        unordered_map<int, int> freq;
        for (int num : hand) {
            ++freq[num];
        }

        // 每次看能否造出一组连续的集合，如果不满足直接返回 false
        for (int num : hand) {
            if (freq[num] == 0) {
                continue;
            }

            for (int diff = 0; diff < group_size; ++diff) {
                if (freq[num + diff] == 0) {
                    return false;
                }
                --freq[num + diff];
            }
        }

        return true;
    }
};
````
