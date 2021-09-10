# [120. Triangle](https://leetcode.com/problems/triangle/) 

## 题目

Given a `triangle` array, return *the minimum path sum from top to bottom*.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index `i` on the current row, you may move to either index `i` or index `i + 1` on the next row.

 

**Example 1:**

```
Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
```

**Example 2:**

```
Input: triangle = [[-10]]
Output: -10
```

 

**Constraints:**

- `1 <= triangle.length <= 200`
- `triangle[0].length == 1`
- `triangle[i].length == triangle[i - 1].length + 1`
- `-104 <= triangle[i][j] <= 104`

 

**Follow up:** Could you do this using only `O(n)` extra space, where `n` is the total number of rows in the triangle?

## 题目大意

给定一个三角形数组，从上到下计算最小的路径和，每一步只能移动到下一行的相邻节点，

如果你在当前行的 i 位置，你可以移动到下一行的 i 和 i + 1 位置，

## 解题思路

* 这道题目可以利用 DP 来解决，递推公式题目中已经给出，
* 这道题目还可以利用滚动数组降低空间复杂度，空间复杂度O(n)
* 这道题还可以原地更改，空间复杂度O(1)

## 代码

`````c++
class Solution {
public:
    /*
    int minimumTotal(vector<vector<int>>& triangle) {
        int rows = triangle.size();
        
        int ans = INT_MAX;
        vector<vector<int>> dp(rows, vector<int>(rows, INT_MAX));
        dp[0][0] = triangle[0][0];
        
        for (int i = 1; i < rows; ++i) {
            for (int j = 0; j < i + 1; ++j) {
                if (j != 0) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + triangle[i][j]);
                }
                if (j != i) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + triangle[i][j]);
                }
            }
        }
        for (int i = 0; i < rows; ++i) {    // 从最后一行中求结果
            ans = min(ans, dp[rows - 1][i]);
        }
        
        return ans;
    }*/
    
    // 利用滚动数组进行优化
    int minimumTotal(vector<vector<int>>& triangle) {
        int rows = triangle.size();
        
        vector<vector<int>> dp(2, vector<int>(rows, INT_MAX));
        dp[0][0] = triangle[0][0];
        for (int i = 1; i < rows; ++i) {
            for (int j = 0; j < i + 1; ++j) {
                dp[i & 1][j] = INT_MAX;
                if (j != 0) {
                    dp[i & 1][j] = min(dp[i & 1][j], dp[(i - 1) & 1][j - 1] + triangle[i][j]); 
                }
                if (j != i) {
                    dp[i & 1][j] = min(dp[i & 1][j], dp[(i - 1) & 1][j] + triangle[i][j]);
                }
            }
        }
        int ans = INT_MAX;
        for (int i = 0; i < rows; ++i) {
            ans = min(ans, dp[(rows - 1) & 1][i]);
        }
        return ans;
    }
};
`````

