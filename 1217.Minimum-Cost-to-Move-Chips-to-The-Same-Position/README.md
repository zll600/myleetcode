# [1217. Minimum Cost to Move Chips to The Same Position](https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/)

## 题目

We have `n` chips, where the position of the `ith` chip is `position[i]`.

We need to move all the chips to **the same position**. In one step, we can change the position of the `ith` chip from `position[i]` to:

- `position[i] + 2` or `position[i] - 2` with `cost = 0`.
- `position[i] + 1` or `position[i] - 1` with `cost = 1`.

Return *the minimum cost* needed to move all the chips to the same position.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/08/15/chips_e1.jpg)

```
Input: position = [1,2,3]
Output: 1
Explanation: First step: Move the chip at position 3 to position 1 with cost = 0.
Second step: Move the chip at position 2 to position 1 with cost = 1.
Total cost is 1.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/08/15/chip_e2.jpg)

```
Input: position = [2,2,2,3,3]
Output: 2
Explanation: We can move the two chips at position  3 to position 2. Each move has cost = 1. The total cost = 2.
```

**Example 3:**

```
Input: position = [1,1000000000]
Output: 1
```

 

**Constraints:**

- `1 <= position.length <= 100`
- `1 <= position[i] <= 10^9`

## 题目大意

数轴上放置了一些筹码，每个筹码的位置存在数组 `chips` 当中。你可以对 任何筹码 执行下面两种操作之一（不限操作次数，`0` 次也可以）：

- 将第 `i` 个筹码向左或者右移动 `2` 个单位，代价为 `0`
- 将第 `i` 个筹码向左或者右移动 `1` 个单位，代价为 `1`

最开始的时候，同一位置上也可能放着两个或者更多的筹码。返回将所有筹码移动到同一位置（任意位置）上所需要的最小代价

## 解题思路

这道题目其实还是比较难想的，根据题目中给出的条件：

- 偶数到偶数，奇数到奇数，cost 为 0
- 偶数到奇数，奇数到偶数，cost 为 1

这里一定要搞清楚数组中的每个值，是第 i 个筹码的位置，而不是数量，一定不要搞错

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/minimum-cost-to-move-chips-to-the-same-position/solution/xian-li-jie-ti-yi-zai-li-jie-dai-ma-si-lu-by-athen/)

`````c++
class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        int odd_cnt = 0, even_cnt = 0;
        for (int val : position) {
            if (val % 2 == 0) {
                ++even_cnt;
            } else {
                ++odd_cnt;
            }
        }
        
        return min(odd_cnt, even_cnt);
    }
};
````
