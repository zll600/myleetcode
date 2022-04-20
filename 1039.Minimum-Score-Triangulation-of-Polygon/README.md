# [1039. Minimum Score Triangulation of Polygon](https://leetcode-cn.com/problems/minimum-score-triangulation-of-polygon/)

## 题目

You have a convex `n`-sided polygon where each vertex has an integer value. You are given an integer array `values` where `values[i]` is the value of the `ith` vertex (i.e., **clockwise order**).

You will **triangulate** the polygon into `n - 2` triangles. For each triangle, the value of that triangle is the product of the values of its vertices, and the total score of the triangulation is the sum of these values over all `n - 2` triangles in the triangulation.

Return *the smallest possible total score that you can achieve with some triangulation of the polygon*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/25/shape1.jpg)

```
Input: values = [1,2,3]
Output: 6
Explanation: The polygon is already triangulated, and the score of the only triangle is 6.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/02/25/shape2.jpg)

```
Input: values = [3,7,4,5]
Output: 144
Explanation: There are two triangulations, with possible scores: 3*7*5 + 4*5*7 = 245, or 3*4*5 + 3*4*7 = 144.
The minimum score is 144.
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/02/25/shape3.jpg)

```
Input: values = [1,3,1,4,1,5]
Output: 13
Explanation: The minimum score triangulation has score 1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13.
```

 

**Constraints:**

- `n == values.length`
- `3 <= n <= 50`
- `1 <= values[i] <= 100`

## 题目大意

你有一个凸的 `n` 边形，其每个顶点都有一个整数值。给定一个整数数组 `values` ，其中 `values[i]` 是第 `i` 个顶点的值（即 顺时针顺序 ）。

假设将多边形 剖分 为 `n - 2` 个三角形。对于每个三角形，该三角形的值是顶点标记的乘积，三角剖分的分数是进行三角剖分后所有 `n - 2` 个三角形的值之和。

返回 多边形进行三角剖分后可以得到的最低分

## 解题思路

这是一道区间 dp 的题目

### Solution 1:

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/minimum-score-triangulation-of-polygon/solution/qu-jian-dong-tai-gui-hua-4ms-by-njyang-yang-yang/)

因为这里 j 始终大于 i，所以这里只需要填充一半的数组

````c++
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        const int n = values.size();
        // dp[i][j] 表示第 i 个到 第 j 个点形成多边形的分数
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // 状态转移
        for (int i = n - 3; i >= 0; --i) {
            for (int j = i + 2; j < n; ++j) {
                for (int m = i + 1; m < j; ++m) {
                    if (dp[i][j] == 0) {
                        dp[i][j] = 1L * values[i] * values[j] * values[m] + dp[i][m] + dp[m][j];
                    } else {
                        dp[i][j] =
                            min(dp[i][j], values[i] * values[j] * values[m] + dp[i][m] + dp[m][j]);
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};
````
