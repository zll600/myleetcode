# [1252. Cells with Odd Values in a Matrix](https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/)

There is an `m x n` matrix that is initialized to all `0`'s. There is also a 2D array `indices` where each `indices[i] = [ri, ci]` represents a **0-indexed location** to perform some increment operations on the matrix.

For each location `indices[i]`, do **both** of the following:

1. Increment **all** the cells on row `ri`.
2. Increment **all** the cells on column `ci`.

Given `m`, `n`, and `indices`, return *the **number of odd-valued cells** in the matrix after applying the increment to all locations in* `indices`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/10/30/e1.png)

```
Input: m = 2, n = 3, indices = [[0,1],[1,1]]
Output: 6
Explanation: Initial matrix = [[0,0,0],[0,0,0]].
After applying first increment it becomes [[1,2,1],[0,1,0]].
The final matrix is [[1,3,1],[1,3,1]], which contains 6 odd numbers.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/10/30/e2.png)

```
Input: m = 2, n = 2, indices = [[1,1],[0,0]]
Output: 0
Explanation: Final matrix = [[2,2],[2,2]]. There are no odd numbers in the final matrix.
```

 

**Constraints:**

- `1 <= m, n <= 50`
- `1 <= indices.length <= 100`
- `0 <= ri < m`
- `0 <= ci < n`

 

**Follow up:** Could you solve this in `O(n + m + indices.length)` time with only `O(n + m)` extra space?

## 题目大意

给你一个 `n x m` 的矩阵，最开始的时候，每个单元格中的值都是 `0`。另有一个索引数组 `indices`，`indices[i] = [ri, ci]` 中的 `ri` 和 `ci` 分别表示指定的行和列（从 0 开始编号）。

你需要将每对 `[ri, ci]` 指定的行和列上的所有单元格的值加 1。请你在执行完所有 indices 指定的增量操作后，返回矩阵中 「奇数值单元格」 的数目


## 解题思路

这道题目进行简单模拟就可以了，

### Solution 1：

这种解法可以参考 [这篇题解](https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/submissions/)

````c++
class Solution {
public:
    int oddCells(int m, int n, vector<vector<int>>& indices) {
        vector<vector<int>> matrix(m, vector<int>(n, 0));

        // 简单模拟一下
        for (const vector<int>& indice: indices) {
            for (int i = 0; i < m; ++i) {
                ++matrix[i][indice[1]];
            }
            for (int j = 0; j < n; ++j) {
                ++matrix[indice[0]][j];
            }
        }

        // 统计结果
        int res = 0;
        for (const vector<int>& nums : matrix) {
            for (int num : nums) {
                if (num & 1 == 1) {
                    ++res;
                }
            }
        }

        return res;
    }
};
````
