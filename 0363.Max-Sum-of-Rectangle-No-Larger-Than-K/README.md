# [363. Max Sum of Rectangle No Larger Than K](https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/)

## 题目

Given an `m x n` matrix `matrix` and an integer `k`, return *the max sum of a rectangle in the matrix such that its sum is no larger than* `k`.

It is **guaranteed** that there will be a rectangle with a sum no larger than `k`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/18/sum-grid.jpg)

```
Input: matrix = [[1,0,1],[0,-2,3]], k = 2
Output: 2
Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
```

**Example 2:**

```
Input: matrix = [[2,2,-1]], k = 3
Output: 3
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 100`
- `-100 <= matrix[i][j] <= 100`
- `-105 <= k <= 105`

 

**Follow up:** What if the number of rows is much larger than the number of columns?

## 题目大意

给定一个m x n 的矩阵和一个整数 k，返回矩阵内部区域不大于 k 的最大和

## 解题思路

* 这道题得思路可以参考这篇题解：https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/submissions/
* 直接使用朴素前缀和加穷举的方式，但是容易超时
* 使用前缀和加二分的思想，可以减少一重循环，累死于四数之和问题，不过这里是在 set 中进行二分查找，因为原矩阵不一定有序

## 代码

`````c++
class Solution {
public:
    // 朴素解法，会超时
    int maxSumSubmatrix1(vector<vector<int>>& matrix, int k) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        vector<vector<int>> sum;
        
        sum.resize(rows + 1, vector<int>(cols + 1, 0));
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                sum[i][j] = sum[i -1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
        
        int res = INT_MIN;
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                for (int p = i; p <= rows; ++p) {
                    for (int q = j; q <= cols; ++q) {
                        int cur = sum[p][q] - sum[i - 1][q] - sum[p][j - 1] + sum[i - 1][j - 1];
                        if (cur <= k) {
                            res = max(res, cur);
                        }
                    }
                }
            }
        }
        
        return res;
    }
    
    // 前缀和 + 二分法
    int maxSumSubmatrix2(vector<vector<int>>& matrix, int k) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        vector<vector<int>> pre_sum(rows + 1, vector<int>(cols + 1, 0));
        // 前缀和加0，是为了避免分类讨论，使得计算的形式更加统一
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                pre_sum[i][j] = pre_sum[i - 1][j] + pre_sum[i][j - 1] - pre_sum[i - 1][j - 1] + matrix[i - 1][j - 1]; 
            }
        }
        
        int res = INT_MIN;
        
        for (int top = 1; top <= rows; ++top) {
            for (int bot = top; bot <= rows; ++bot) {
                set<int> cache;
                cache.insert(0);    // set 中加 0，是为了算【子矩阵的右边界】和【原矩阵得左边界形成得矩阵】，
                // 这里也对对应了上面计算前缀和空了一行，使得后面即使只有单独得一列也可以计算，eg[2, 2, -1], 3
                for (int r = 1; r <= cols; ++r) {
                    int right = pre_sum[bot][r] - pre_sum[top - 1][r];
                    auto left = cache.lower_bound(right - k);
                    if (left != cache.end()) {
                        int cur = right - *left;
                        res = max(res, cur);
                    }
                    cache.insert(right);
                }
            }
        }
        return res;
    }
    
    // 最大化二分效益
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        vector<vector<int>> pre_sum(rows + 1, vector<int>(cols + 1));
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                pre_sum[i][j] = pre_sum[i - 1][j] + pre_sum[i][j - 1] - pre_sum[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
        
        bool is_right = cols > rows;
        int res = INT_MIN;
        for (int i = 1; i <= (is_right ? rows : cols); ++i) {
            for (int j = i; j <= (is_right ? rows : cols); ++j) {
                set<int> cache;
                cache.insert(0);
                for (int fixed = 1; fixed <= (is_right ? cols : rows); ++fixed) {
                    int a = is_right
                        ? pre_sum[j][fixed] - pre_sum[i - 1][fixed] : pre_sum[fixed][j] - pre_sum[fixed][i - 1];
                    auto b = cache.lower_bound(a - k);
                    if (b != cache.end()) {
                        int cur = a - *b;
                        res = max(res, cur);
                    }
                    cache.insert(a);
                }
            }
        }
        return res;
    }
};
`````

