#### [1351. Count Negative Numbers in a Sorted Matrix](https://leetcode.cn/problems/count-negative-numbers-in-a-sorted-matrix/)

## 题目

Given a `m x n` matrix `grid` which is sorted in non-increasing order both row-wise and column-wise, return *the number of **negative** numbers in* `grid`.

 

**Example 1:**

```
Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
Output: 8
Explanation: There are 8 negatives number in the matrix.
```

**Example 2:**

```
Input: grid = [[3,2],[1,0]]
Output: 0
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 100`
- `-100 <= grid[i][j] <= 100`

 

**Follow up:** Could you find an `O(n + m)` solution?

## 题目大意

给你一个 `m * n` 的矩阵 `grid`，矩阵中的元素无论是按行还是按列，都以非递增顺序排列。 请你统计并返回 `grid` 中 **负数** 的数目。



### Solution 1: Binary Search

这道题目就是普通的二分查找，但是细节还是比较重要的，另外还可以利用每一行，每一列都是非递增的这一特点来进行优化

````c++
class Solution:
    def countNegatives(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        
        ans = 0
        for i in range(m):
            low, high = 0, n
            
            if grid[i][n - 1] >= 0:
                continue
            
            if grid[i][0] < 0:
                ans += n
                continue
            
            while low < high:
                mid = low + (high - low) // 2
                # print(f'{low} -> {mid} -> {high}')
                
                if grid[i][mid] >= 0:
                    low = mid + 1
                else:
                    high = mid
        
            if 0 <= high < n:
                ans += n - high
            else:
                ans += n
                
        return ans
    
'''
[[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
[[1,-1],[-1,-1]]
[[3,2],[1,0]]
'''
````

