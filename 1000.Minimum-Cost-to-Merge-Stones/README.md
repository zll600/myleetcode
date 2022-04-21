# [1000. Minimum Cost to Merge Stones](https://leetcode-cn.com/problems/minimum-cost-to-merge-stones/)

## 题目

There are `n` piles of `stones` arranged in a row. The `ith` pile has `stones[i]` stones.

A move consists of merging exactly `k` consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these `k` piles.

Return *the minimum cost to merge all piles of stones into one pile*. If it is impossible, return `-1`.

 

**Example 1:**

```
Input: stones = [3,2,4,1], k = 2
Output: 20
Explanation: We start with [3, 2, 4, 1].
We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
We merge [4, 1] for a cost of 5, and we are left with [5, 5].
We merge [5, 5] for a cost of 10, and we are left with [10].
The total cost was 20, and this is the minimum possible.
```

**Example 2:**

```
Input: stones = [3,2,4,1], k = 3
Output: -1
Explanation: After any merge operation, there are 2 piles left, and we can't merge anymore.  So the task is impossible.
```

**Example 3:**

```
Input: stones = [3,5,1,2,6], k = 3
Output: 25
Explanation: We start with [3, 5, 1, 2, 6].
We merge [5, 1, 2] for a cost of 8, and we are left with [3, 8, 6].
We merge [3, 8, 6] for a cost of 17, and we are left with [17].
The total cost was 25, and this is the minimum possible.
```

 

**Constraints:**

- `n == stones.length`
- `1 <= n <= 30`
- `1 <= stones[i] <= 100`
- `2 <= k <= 30`

## 题目大意

有 N 堆石头排成一排，第 i 堆中有 stones[i] 块石头。

每次移动（move）需要将连续的 K 堆石头合并为一堆，而这个移动的成本为这 K 堆石头的总数。

找出把所有石头合并成一堆的最低成本。如果不可能，返回 -1 。

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/minimum-cost-to-merge-stones/solution/yi-dong-you-yi-dao-nan-yi-bu-bu-shuo-ming-si-lu-he/)

这道题目也是一道前缀和的题目

### Solution 1: dp



````c++
class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
        const int n = stones.size();

        // 肯定不能每次 k 个合并成一堆
        if ((n - 1) % (k - 1) != 0) {
            return -1;
        }

        vector<vector<vector<int>>> dp(
            n + 1, vector<vector<int>>(n + 1, vector<int>(k + 1, 0)));
        // 利用前缀和加速
        vector<int> sum(n + 1);
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + stones[i - 1];
        }

        // 初始化
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                for (int m = 2; m <= k; ++m) {
                    dp[i][j][m] = 100000;
                }
            }
            dp[i][i][1] = 0;
        }

        // 状态转移
        for (int len = 2; len <= n; ++len) {
            for (int i = 1; i + len  - 1 <= n; ++i) {
                int j = i + len - 1;
                for (int m = 2; m <= k; ++m) {
                    for (int p = i; p < j; p += k - 1) {
                        dp[i][j][m] = min(dp[i][j][m], dp[i][p][1] +
                                          dp[p + 1][j][m - 1]);
                    }
                }
                dp[i][j][1] = dp[i][j][k] + sum[j] - sum[i - 1];
            }
        }

        return dp[1][n][1];
    }
};
````
