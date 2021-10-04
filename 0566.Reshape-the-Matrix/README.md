# [566. Reshape the Matrix](https://leetcode.com/problems/reshape-the-matrix/)

## 题目

In MATLAB, there is a handy function called `reshape` which can reshape an `m x n` matrix into a new one with a different size `r x c` keeping its original data.

You are given an `m x n` matrix `mat` and two integers `r` and `c` representing the number of rows and the number of columns of the wanted reshaped matrix.

The reshaped matrix should be filled with all the elements of the original matrix in the same row-traversing order as they were.

If the `reshape` operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/24/reshape1-grid.jpg)

```
Input: mat = [[1,2],[3,4]], r = 1, c = 4
Output: [[1,2,3,4]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/04/24/reshape2-grid.jpg)

```
Input: mat = [[1,2],[3,4]], r = 2, c = 4
Output: [[1,2],[3,4]]
```

 

**Constraints:**

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n <= 100`
- `-1000 <= mat[i][j] <= 1000`
- `1 <= r, c <= 300`

## 题目大意

在 MATLAB 中，有一个很方便的函数叫做 reshape，其可以将一个 m x n 的矩阵，转化为一个不同大小的 r x c 的矩阵，保持原来的数组，

给定一个 m x  n 的矩阵 mat，和两个整数 r ， c，代表期望的矩阵的行数和列数，

重构后的矩阵需要将原始矩阵的所有元素以相同的行遍历顺序填充。如果具有给定参数的reshape操作是可行且合理的，则输出新的重塑矩阵；否则，输出原始矩阵。

## 解题思路

这道题目首先应该判断是否可以转换，如果不能转换则直接返回原数组，

### 解法1

这道题目并不是很难，直接模拟即可

`````c++
class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        if (CanReshape(nums, r, c)) {
            return Reshape(nums, r, c);
        }
        
        return nums;
    }
    
 private:
    // 是否可以转化
    bool CanReshape(const vector<vector<int>>& nums, int r, int c) {
        return r * c == nums.size() * nums[0].size();
    }
    
    // 转化
    vector<vector<int>> Reshape(const vector<vector<int>>& matrix, int r, int c) {
        vector<vector<int>> output(r, vector<int>(c, 0));
        
        int row = 0;
        int col = 0;
        for (const vector<int>& nums : matrix) {
            for (int num : nums) {
                if (col == c) {  // 这里需要换行
                    row++;
                    col = 0;
                }
                output[row][col] = num;
                col++;
            }
        }
        return output;
    }
};
`````

