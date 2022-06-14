# [1139. Largest 1-Bordered Square](https://leetcode.cn/problems/largest-1-bordered-square/)

## 题目

Given a 2D `grid` of `0`s and `1`s, return the number of elements in the largest **square** subgrid that has all `1`s on its **border**, or `0` if such a subgrid doesn't exist in the `grid`.

 

**Example 1:**

```
Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
Output: 9
```

**Example 2:**

```
Input: grid = [[1,1,0,0]]
Output: 1
```

 

**Constraints:**

- `1 <= grid.length <= 100`
- `1 <= grid[0].length <= 100`
- `grid[i][j]` is `0` or `1`

## 题目大意

给你一个由若干 `0` 和 `1` 组成的二维网格 `grid`，请你找出边界全部由 `1` 组成的最大 **正方形** 子网格，并返回该子网格中的元素数量。如果不存在，则返回 `0`

## 解题思路

这道题目的暴力解法就是以每一个为 1 的位置作为右下角，然后找到最大的正方形面积，这样就找到了子问题

找到了每个正方形的右下角还需要确定这个正方向的边长才可以最终确定正方形的面积，

这里的解决办法是预处理每个位置左边（包括自身）连续的 1 的数目和右边（包括自身）连续的 1 的数目

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/largest-1-bordered-square/solution/java-dong-tai-gui-hua-by-resolmi/)

### Solution 1:

````c++
class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();

        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(2, 0)));
        dp[0][0][0] = grid[0][0] == 1 ? 1 : 0;
        dp[0][0][1] = grid[0][0] == 1 ? 1 : 0;
        for (int j = 1; j < n; ++j) {
            if (grid[0][j] == 0) {
                continue;
            }
            dp[0][j][0] = dp[0][j - 1][0] + 1;
            dp[0][j][1] = 1;
        }
        for (int i = 1; i < m; ++i) {
            if (grid[i][0] == 0) {
                continue;
            }
            dp[i][0][1] = dp[i - 1][0][1] + 1;
            dp[i][0][0] = 1;
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (grid[i][j] == 0) {
                    continue;
                }

                dp[i][j][0] = dp[i][j - 1][0] + 1;
                dp[i][j][1] = dp[i - 1][j][1] + 1;
            }
        }

        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // cout << dp[i][j][0] << " -- " << dp[i][j][1] << endl;
                for (int side = min(dp[i][j][0], dp[i][j][1]); side >= 1; --side) {
                    if (j - side + 1 >= 0 && dp[i][j - side + 1][1] >= side
                        && i - side + 1 >= 0 && dp[i - side + 1][j][0] >= side) {
                        res = max(res, side);
                        break;
                    }
                }
            }
        }
        return res * res;
    }
};
````
