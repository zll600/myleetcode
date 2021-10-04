# [766. Toeplitz Matrix](https://leetcode.com/problems/toeplitz-matrix/)

## 题目

Given an `m x n` `matrix`, return *`true` if the matrix is Toeplitz. Otherwise, return `false`.*

A matrix is **Toeplitz** if every diagonal from top-left to bottom-right has the same elements.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/04/ex1.jpg)

```
Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
Output: true
Explanation:
In the above grid, the diagonals are:
"[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
In each diagonal all elements are the same, so the answer is True.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/11/04/ex2.jpg)

```
Input: matrix = [[1,2],[2,2]]
Output: false
Explanation:
The diagonal "[1, 2]" has different elements.
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 20`
- `0 <= matrix[i][j] <= 99`

 

**Follow up:**

- What if the `matrix` is stored on disk, and the memory is limited such that you can only load at most one row of the matrix into the memory at once?
- What if the `matrix` is so large that you can only load up a partial row into the memory at once?

## 题目大意

给定一个 m x n 的矩阵，

如果这个矩阵是托普利茨矩阵，返回 `true` ；否则，返回 `false` *。*

如果矩阵上每一条由左上到右下的对角线上的元素都相同，那么这个矩阵是 **托普利茨矩阵** 。



进阶要求：

- 如果矩阵存储在磁盘上，并且内存有限，以至于一次最多只能将矩阵的一行加载到内存中，该怎么办？
- 如果矩阵太大，以至于一次只能将不完整的一行加载到内存中，该怎么办？

 ## 解题思路

这道题目如果转化以下，可以这样思考，要求对角线上的元素相等也就是在遍历的过程中，当前元素和其左上角的元素必须是相等（如果存在的话），

## 解法1

这道题目如果是轮流判断每一条对角线的华，确实是比较难的，而且这种逐行遍历的方式也满足进阶要求

`````c++
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[0].size(); j++) {
                if (matrix[i - 1][j - 1] != matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
};
`````

