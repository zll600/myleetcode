# [914. X of a Kind in a Deck of Cards](https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards/)

##   题目

In a deck of cards, each card has an integer written on it.

Return `true` if and only if you can choose `X >= 2` such that it is possible to split the entire deck into 1 or more groups of cards, where:

- Each group has exactly `X` cards.
- All the cards in each group have the same integer.

 

**Example 1:**

```
Input: deck = [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4].
```

**Example 2:**

```
Input: deck = [1,1,1,2,2,2,3,3]
Output: false
Explanation: No possible partition.
```

 

**Constraints:**

- `1 <= deck.length <= 104`
- `0 <= deck[i] < 104`

## 题目大意

给定一副牌，每张牌上都写着一个整数。此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成 1 组或更多组：

- 每组都有 X 张牌。
- 组内所有的牌上都写着相同的

当且仅当你可选的 `X >= 2` 时返回 `true`

## 解题思路

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0914.X-of-a-Kind-in-a-Deck-of-Cards/)

这里主要做的就是统计每个数字出现的频数，然后求所有频数的最大公约数即可

### Solution 1:


````c++
class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        const int len = deck.size();
        if (len < 2) {
            return false;
        }

        // 统计频数
        unordered_map<int, int> freq;
        for (int num : deck) {
            ++freq[num];
        }

        // 求全局的最大公约数
        int target = -1;
        for (const auto& item : freq) {
            if (target == -1) {
                target = item.second;
                continue;
            }
            target = GCD(target, item.second);
        }

        return target >= 2;
    }

 private:
    int GCD(int a, int b) {
        return !a ? b : GCD(b % a, a);
    }
};
````
