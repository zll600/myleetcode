# [1046. Last Stone Weight](https://leetcode-cn.com/problems/last-stone-weight/)

## 题意

You are given an array of integers `stones` where `stones[i]` is the weight of the `ith` stone.

We are playing a game with the stones. On each turn, we choose the **heaviest two stones** and smash them together. Suppose the heaviest two stones have weights `x` and `y` with `x <= y`. The result of this smash is:

- If `x == y`, both stones are destroyed, and
- If `x != y`, the stone of weight `x` is destroyed, and the stone of weight `y` has new weight `y - x`.

At the end of the game, there is **at most one** stone left.

Return *the smallest possible weight of the left stone*. If there are no stones left, return `0`.

 

**Example 1:**

```
Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation: 
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of the last stone.
```

**Example 2:**

```
Input: stones = [1]
Output: 1
```

 

**Constraints:**

- `1 <= stones.length <= 30`
- `1 <= stones[i] <= 1000`

给定一个整数数组 `stone`，其中 `stones[i]` 表示第 `i` 个石头

使用石头来玩游戏，每一回合，我们选择最终的两个石头然后将他们一起粉碎，假设这连个最终的石头重量分别为 `x` 和 `y`，并且 `x <= y`，粉碎的结果如下：

- 如果 `x == y`，两个石头都被摧毁
- 如果 `x != y`，重量为 `x` 的石头被摧毁，而重量为 `y`的石头获得 `y - x` 的新质量，

在游戏的最后，最多只有一个石头留下

返回最后剩下的石头的的重量，如果没有石头存在，反应会 `0`;

## 解题思路

这道题目比较简单，直接根据题目条件模拟一下就可以了

### Solution 1: Priority_queue

这里使用大顶堆来避免每次操作之后都需要重新排队的问题

````c++
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        // 使用大顶堆来保证每次获取的都是最大值
        priority_queue<int> que(stones.begin(), stones.end());

        while (!que.empty()) {
            if (que.size() < 2) {
                break;
            }

            int y = que.top();
            que.pop();
            int x = que.top();
            que.pop();

            if (x < y) {
                que.push(y - x);
            }
        }

        return que.empty() ? 0 : que.top();
    }
};
````
