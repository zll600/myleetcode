# [221. Maximal Square](https://leetcode.com/problems/maximal-square/)

## 题目

Given an `m x n` binary `matrix` filled with `0`'s and `1`'s, *find the largest square containing only* `1`'s *and return its area*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/26/max1grid.jpg)

```
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 4
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/11/26/max2grid.jpg)

```
Input: matrix = [["0","1"],["1","0"]]
Output: 1
```

**Example 3:**

```
Input: matrix = [["0"]]
Output: 0
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 300`
- `matrix[i][j]` is `'0'` or `'1'`.

## 题目大意

给定一个 m x n 的矩阵，其中填满的 0 和 1，找到只包含 1 的最大正方形，返回最大面积

## 解题思路

### 解法1（动态规划）

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/maximal-square/solution/li-jie-san-zhe-qu-zui-xiao-1-by-lzhlyle/

**状态定义**：`dp[i + 1][j + 1]` 表示以 `matrix[i][j]`为右下角的的正方形的最大边长，这里加入一个哨兵值（避免分类讨论）

**状态转移**：每个位置的值可以由其左边，上边，左上三个位置转移而来，根据木桶理论，三者中取最小

````
if (matrix[i][j] == '1') {
	dp[i + 1][j + 1] = min(min(dp[i][j + 1], dp[i + 1][j]), dp[i][j]);
}
````

**初始化**：

这里需要将第一行和第一列初始化为0，使整个递推可以进行下去，

`````c++
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        
        // 这里将状态数组在最左侧添加了一列，在最上方添加了一行，避免了分类讨论
        vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0));
        int res = 0;
        
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (matrix[row][col] == '1') {
                    // 每个位置依赖于 左边、上边、左上的位置结尾的正方形的面积
                    dp[row + 1][col + 1] = min(min(dp[row][col + 1], dp[row + 1][col]), dp[row][col]) + 1;
                    res = max(res, dp[row + 1][col + 1]);
                }
            }
        }
        
        return res * res;
    }
};
`````

### 解法2（状态压缩）

因为当前行的状态只依赖于前一行，因此可以将状态数组压缩，不过这里有几点需要注意的问题：

* 每次遍历新的一行的时候，都需要设一个 0 值作为左上方，参与动态转移
* 对于矩阵中值为 0 的元素，状态数组要重新设为 0 值，

`````c++
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        
        // 因为当前行最多只依赖于前两行，所以可以二维转为 一维
        vector<int> dp(cols + 1);
        int res = 0;
        
        for (int i = 0; i < rows; ++i) {
            // 保留左上角的值
            int left_up = 0;
            for (int j = 0; j < cols; ++j) {
                // 更新之前先保存
                int tmp = dp[j + 1];
                if (matrix[i][j] == '1') {
                    dp[j + 1] = min(min(dp[j + 1], dp[j]), left_up) + 1;
                    res = max(res, dp[j + 1]);
                } else {
                    dp[j + 1] = 0;  // 这里要把是 0 的位置，恢复为 0
                }
                left_up = tmp;
            }
        }
        
        return res * res;
    }
};
`````

