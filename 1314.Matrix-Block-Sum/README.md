#### [1314. Matrix Block Sum](https://leetcode.cn/problems/matrix-block-sum/)

Given a `m x n` matrix `mat` and an integer `k`, return *a matrix* `answer` *where each* `answer[i][j]` *is the sum of all elements* `mat[r][c]` *for*:

- `i - k <= r <= i + k,`
- `j - k <= c <= j + k`, and
- `(r, c)` is a valid position in the matrix.

 

**Example 1:**

```
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[12,21,16],[27,45,33],[24,39,28]]
```

**Example 2:**

```
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 2
Output: [[45,45,45],[45,45,45],[45,45,45]]
```

 

**Constraints:**

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n, k <= 100`
- `1 <= mat[i][j] <= 100`



### 题目大意

给你一个 m x n 的矩阵 mat 和一个整数 k ，请你返回一个矩阵 answer ，其中每个 answer[i][j] 是所有满足下述条件的元素 mat[r][c] 的和： 

    i - k <= r <= i + k,
    j - k <= c <= j + k 且
    (r, c) 在矩阵内。



### 解题思路



### Solution 1: Prefix sum

这道题目可以想到区间求和使用 前缀和来做，这里可以想到使用 二维前缀和来做，之前也做过一道类似的题目



`````c++
class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        const int m = mat.size();
        const int n = mat[0].size();
        vector<vector<int>> prefix_sum(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                prefix_sum[i][j] = mat[i - 1][j - 1] + prefix_sum[i - 1][j] + prefix_sum[i][j - 1]
                                    - prefix_sum[i - 1][j - 1];
                // cout << prefix_sum[i][j] << endl;
            }
        }
        
        vector<vector<int>> ans(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int left_row = max(i - k, 0), left_col = max(j - k, 0);
                int right_row = min(i + k, m - 1), right_col = min(j + k, n - 1);
                
                ans[i][j] = prefix_sum[right_row + 1][right_col + 1]
                            - prefix_sum[left_row][right_col + 1]
                            - prefix_sum[right_row + 1][left_col]
                            + prefix_sum[left_row][left_col];
                // cout << ans[i][j] << endl;
            }
        }
        return ans;
    }
};
`````

