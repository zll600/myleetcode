# [950. Reveal Cards In Increasing Order](https://leetcode.cn/problems/reveal-cards-in-increasing-order/)

## 题目

You are given an integer array `deck`. There is a deck of cards where every card has a unique integer. The integer on the `ith` card is `deck[i]`.

You can order the deck in any order you want. Initially, all the cards start face down (unrevealed) in one deck.

You will do the following steps repeatedly until all cards are revealed:

1. Take the top card of the deck, reveal it, and take it out of the deck.
2. If there are still cards in the deck then put the next top card of the deck at the bottom of the deck.
3. If there are still unrevealed cards, go back to step 1. Otherwise, stop.

Return *an ordering of the deck that would reveal the cards in increasing order*.

**Note** that the first entry in the answer is considered to be the top of the deck.

 

**Example 1:**

```
Input: deck = [17,13,11,2,3,5,7]
Output: [2,13,3,11,5,17,7]
Explanation: 
We get the deck in the order [17,13,11,2,3,5,7] (this order does not matter), and reorder it.
After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
We reveal 13, and move 17 to the bottom.  The deck is now [17].
We reveal 17.
Since all the cards revealed are in increasing order, the answer is correct.
```

**Example 2:**

```
Input: deck = [1,1000]
Output: [1,1000]
```

 

**Constraints:**

- `1 <= deck.length <= 1000`
- `1 <= deck[i] <= 106`
- All the values of `deck` are **unique**.

## 题目大意

牌组中的每张卡牌都对应有一个唯一的整数。你可以按你想要的顺序对这套卡片进行排序

最初，这些卡牌在牌组里是正面朝下的（即，未显示状态）

现在，重复执行以下步骤，直到显示所有卡牌为止：

-   从牌组顶部抽一张牌，显示它，然后将其从牌组中移出
-   如果牌组中仍有牌，则将下一张处于牌组顶部的牌放在牌组的底部
-   如果仍有未显示的牌，那么返回步骤 1。否则，停止行动

返回能以递增顺序显示卡牌的牌组顺序。

答案中的第一张牌被认为处于牌堆顶部

## 解题思路

### Solution 1:

先将真个数组升序排序，然后按照逆序遍历整个数组，将之前的规则反转，将新的数放在第一位

如果不好理解，可以自己在纸上画一画

````c+
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(), deck.end());

        deque<int> que;
        que.push_back(deck.back());
        deck.pop_back();

        while (!deck.empty()) {
            int cur = deck.back();
            deck.pop_back();

            // 取出最后一个位置的值
            int tmp = que.back();
            que.pop_back();
            // 放在第一个位置上
            que.push_front(tmp);
            // 将新的数加入
            que.push_front(cur);
        }

        return vector<int>(que.begin(), que.end());
    }
};
+
````

