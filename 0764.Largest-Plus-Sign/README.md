# [764. Largest Plus Sign](https://leetcode-cn.com/problems/largest-plus-sign/)

## 题目

You are given an integer `n`. You have an `n x n` binary grid `grid` with all values initially `1`'s except for some indices given in the array `mines`. The `ith` element of the array `mines` is defined as `mines[i] = [xi, yi]` where `grid[xi][yi] == 0`.

Return *the order of the largest **axis-aligned** plus sign of* 1*'s contained in* `grid`. If there is none, return `0`.

An **axis-aligned plus sign** of `1`'s of order `k` has some center `grid[r][c] == 1` along with four arms of length `k - 1` going up, down, left, and right, and made of `1`'s. Note that there could be `0`'s or `1`'s beyond the arms of the plus sign, only the relevant area of the plus sign is checked for `1`'s.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/06/13/plus1-grid.jpg)

```
Input: n = 5, mines = [[4,2]]
Output: 2
Explanation: In the above grid, the largest plus sign can only be of order 2. One of them is shown.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/06/13/plus2-grid.jpg)

```
Input: n = 1, mines = [[0,0]]
Output: 0
Explanation: There is no plus sign, so return 0.
```

 

**Constraints:**

- `1 <= n <= 500`
- `1 <= mines.length <= 5000`
- `0 <= xi, yi < n`
- All the pairs `(xi, yi)` are **unique**.

## 题目大意

在一个 `n x n` 的矩阵 `grid` 中，除了在数组 `mines` 中给出的元素为 `0`，其他每个元素都为 `1`。`mines[i] = [xi, yi]` 表示 `grid[xi][yi] == 0`

返回  `grid` 中包含 `1` 的最大的 *轴对齐* 加号标志的阶数。如果未找到加号标志，则返回 `0`

一个 `k` 阶由 `1` 组成的 “轴对称”加号标志 具有中心网格 `grid[r][c] == 1` ，以及4个从中心向上、向下、向左、向右延伸，长度为 `k-1`，由 `1` 组成的臂。注意，只有加号标志的所有网格要求为 `1` ，别的网格可能为 0 也可能为 1
 
## 解题思路

这道题目直接的办法，就是遍历每一个位置，然后求出当前位置 的 臂长即可，但是这样还是容易超时，再考虑一下，还是可以看出这道题目是有重复的子结构的，可以使用 dp 来做

这道题目需要维护的状态有 遍历的坐标 [i, j]，四个方向上的臂长，这里地拿起 `dp[i][j][k]` 为位置 [i,j]  在 k 方向上的臂长(实际上这里是臂长 + 1)，k 的范围数 [0, 3]，分别表示 左，上，右，下

另外这道题的结果必定不再 grid 的四条边上，所以初始化就是这些位置初始化为 0，然后开始递推

再记一下，核心， dp 常用语解决无后效性的子问题，dp 相比 dfs 快的地方在于有些路径被剪枝了

### Solution 1: DP

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/largest-plus-sign/solution/javadong-tai-gui-hua-jian-dan-yi-dong-by-dan-huang/)

这里用 C++ 最终会超时


````c++
class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(4, 1)));
        for (const auto& mine : mines) {
            for (int i = 0; i < 4; ++i) {
                dp[mine[0]][mine[1]][i] = 0;
            }
        }
        
        // update from left and up
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                if (dp[i][j][0] == 0) {
                    continue;
                }
                dp[i][j][0] = dp[i][j - 1][0] + 1;
                dp[i][j][1] = dp[i - 1][j][1] + 1;
            }
        }
        
        // update from right and bottom
        for (int i = n - 2; i >= 0; --i) {
            for (int j = n - 2; j >= 0; --j) {
                if (dp[i][j][2] == 0) {
                    continue;
                }
                dp[i][j][2] = dp[i][j + 1][2] + 1;
                dp[i][j][3] = dp[i + 1][j][3] + 1;
            }
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int val = min(dp[i][j][0], dp[i][j][1]);
                val = min(val, dp[i][j][2]);
                val = min(val, dp[i][j][3]);
                // cout << i << "--" << j << "==" << val << endl;
                ans = max(ans, val);
            }
        }
        return ans;
    }
};
````
