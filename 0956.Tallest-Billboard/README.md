# [956. Tallest Billboard](https://leetcode-cn.com/problems/tallest-billboard/)

## 题目

You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.

You are given a collection of `rods` that can be welded together. For example, if you have rods of lengths `1`, `2`, and `3`, you can weld them together to make a support of length `6`.

Return *the largest possible height of your billboard installation*. If you cannot support the billboard, return `0`.

 

**Example 1:**

```
Input: rods = [1,2,3,6]
Output: 6
Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
```

**Example 2:**

```
Input: rods = [1,2,3,4,5,6]
Output: 10
Explanation: We have two disjoint subsets {2,3,5} and {4,6}, which have the same sum = 10.
```

**Example 3:**

```
Input: rods = [1,2]
Output: 0
Explanation: The billboard cannot be supported, so we return 0.
```

 

**Constraints:**

- `1 <= rods.length <= 20`
- `1 <= rods[i] <= 1000`
- `sum(rods[i]) <= 5000`

## 题目大意

你正在安装一个广告牌，并希望它高度最大。这块广告牌将有两个钢制支架，两边各一个。每个钢支架的高度必须相等。

你有一堆可以焊接在一起的钢筋 rods。举个例子，如果钢筋的长度为 1、2 和 3，则可以将它们焊接在一起形成长度为 6 的支架。

返回 广告牌的最大可能安装高度 。如果没法安装广告牌，请返回 0 

## 解题思路

其实读完题目有点感觉像 `分割等和子集`，不过这里还需要最大化

有以下约束：


- 分割出两个子集
- 两个子集的和相等，
- 两个子集的和都是最大的

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/tallest-billboard/solution/dong-tai-gui-hua-ke-yi-kan-cheng-01bei-bao-de-bian/)

````c++
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        const int len = rods.size();
        if (len < 2) {
            return 0;
        }

        const int sum = std::accumulate(rods.begin(), rods.end(), 0);

        // dp[i][j] 表示用前 i 个数，两者之差为 j 的组合形成的 和
        vector<vector<int>> dp(len, vector<int>(sum + 1, 0));
        // 初始化，只使用第 1 个
        dp[0][rods[0]] = rods[0];

        int prefix_sum = rods[0];
        for (int i = 1; i < len; ++i) {
            for (int j = 0; j <=prefix_sum; ++j) {
                // 两个子集的差为 j,则两个子集的和肯定大于 j
                if (dp[i - 1][j] < j) {
                    continue;
                }

                // 不是用第 i 个
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);

                // 用第 i 个扩大差距
                int diff = j + rods[i];
                dp[i][diff] = max(dp[i][diff], dp[i - 1][j] + rods[i]);

                // 用第 i 个缩小差距
                diff = abs(j - rods[i]);
                dp[i][diff] = max(dp[i][diff], dp[i - 1][j] + rods[i]);
            }
            // 累加差值的上限
            prefix_sum += rods[i];
        }

        return dp[len - 1][0] / 2;
    }
};
````


