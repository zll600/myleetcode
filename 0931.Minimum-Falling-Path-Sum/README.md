# [931. Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/)

## 题目

Given an `n x n` array of integers `matrix`, return *the **minimum sum** of any **falling path** through* `matrix`.

A **falling path** starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position `(row, col)` will be `(row + 1, col - 1)`, `(row + 1, col)`, or `(row + 1, col + 1)`.

 

**Example 1:**

```
Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: There are two falling paths with a minimum sum underlined below:
[[2,1,3],      [[2,1,3],
 [6,5,4],       [6,5,4],
 [7,8,9]]       [7,8,9]]
```

**Example 2:**

```
Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: The falling path with a minimum sum is underlined below:
[[-19,57],
 [-40,-5]]
```

**Example 3:**

```
Input: matrix = [[-48]]
Output: -48
```

 

**Constraints:**

- `n == matrix.length`
- `n == matrix[i].length`
- `1 <= n <= 100`
- `-100 <= matrix[i][j] <= 100`

## 题目大意

给定一个n x n 的矩阵，找出并返回通过矩阵的最小下降路径和，

下降路径开始在第一行的任意一个元素，并从下一行选一个元素，可以是同一列，也可以使相邻列，具体来说可以从(row, col) 到(row, col - 1), (row, col), (row, col + 1) 这三个位置，

## 解题思路

* 这是一道 DP 的题目
* 这道题目可以联系第120 题，递推公式，题目中已经给出了，

## 代码

````c++
class Solution {
public:    
    // 二维数组
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        dp[0][0] = matrix[0][0];
        for (int i = 1; i < n; ++i) {
            dp[0][i] = matrix[0][i];
        }
        
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dp[i - 1][j] != INT_MAX) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + matrix[i][j]);
                }
                
                if (j - 1 >= 0 && dp[i - 1][j - 1] != INT_MAX) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + matrix[i][j]);
                }
                
                if (j + 1 < m && dp[i - 1][j + 1] != INT_MAX) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j + 1] + matrix[i][j]);
                }
            }
        }
        
        int res = INT_MAX;
        for (int i = 0; i < n; ++i) {
            res = min(res, dp[m - 1][i]);
        }
        return res;
    }
};
````

