# [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)

## 题目

Write an efficient algorithm that searches for a value in an `m x n` matrix. This matrix has the following properties:

- Integers in each row are sorted from left to right.
- The first integer of each row is greater than the last integer of the previous row.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/05/mat.jpg)

```
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/10/05/mat2.jpg)

```
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 100`
- `-104 <= matrix[i][j], target <= 104`

## 题目大意

编写一个算法在一个 m x n 的矩阵中搜索给定的值，

矩阵满足下列条件：

* 矩阵的行从左到右排序，
* 矩阵的每行第一个元素，比上一行的最后一个元素大。

## 解题思路

* 使用“二分搜索”，对全局矩阵进行二分搜索，因为矩阵的有序性，这里可以将其看作一个一维矩阵，需要进行一定的坐标转换。
* 从右上角开始搜索，如果比目标值大，就将对应的列左移，如果比目标值小，就将对应的行下移，这道题目也可以从左下角开始搜索，但是左上角和右下角不行，原因在于，只有右上角，和左下角才可以起到缩小查找区间的作用

## 代码

````c++
class Solution {
public:
    // 解法一：二分法。需要将矩阵坐标进行转化
    /*
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int lo = 0;
        int hi = matrix.size() * matrix[0].size() - 1;
        int mod = matrix[0].size();
        
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (matrix[mid / mod][mid % mod] == target) {
                return true;
            } else if (matrix[mid / mod][mid % mod] > target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        
        return false;
    }
    */
    
    // 解法二：坐标轴法
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        int row = 0;
        int col = cols - 1;
        while (col >= 0 && row < rows) {
            if (matrix[row][col] > target) {
                --col;
            } else if (matrix[row][col] < target) {
                ++row;
            } else {
                return true;
            }
        }
        
        return false;
    }
};
````



