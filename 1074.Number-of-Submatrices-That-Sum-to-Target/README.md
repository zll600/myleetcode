# [1074. Number of Submatrices That Sum to Target](https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/)

## 题目

Given a `matrix` and a `target`, return the number of non-empty submatrices that sum to target.

A submatrix `x1, y1, x2, y2` is the set of all cells `matrix[x][y]` with `x1 <= x <= x2` and `y1 <= y <= y2`.

Two submatrices `(x1, y1, x2, y2)` and `(x1', y1', x2', y2')` are different if they have some coordinate that is different: for example, if `x1 != x1'`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/02/mate1.jpg)

```
Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.
```

**Example 2:**

```
Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.
```

**Example 3:**

```
Input: matrix = [[904]], target = 0
Output: 0
```

 

**Constraints:**

- `1 <= matrix.length <= 100`
- `1 <= matrix[0].length <= 100`
- `-1000 <= matrix[i] <= 1000`
- `-10^8 <= target <= 10^8`

## 题目大意

给定一个矩阵和值，返回元素之和等于目标值的非空矩阵的数目。

这道题目的解决方法可以参考第363题

## 解题思路

````c++
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> sum(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
        int ans = 0;
        for (int top = 1; top <= n; top++) {
            for (int bot = top; bot <= n; bot++) {
                int cur = 0;
                unordered_map<int, int> map;
                for (int r = 1; r <= m; r++) {
                    cur = sum[bot][r] - sum[top - 1][r];
                    if (cur == target) ans++;
                    if (map.count(cur - target)) ans += map[cur - target];
                    map[cur]++;
                }
            }
        }
        return ans;
    }
};
````





