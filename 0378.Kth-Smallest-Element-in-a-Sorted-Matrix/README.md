# [378. Kth Smallest Element in a Sorted Matrix](https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/)

## 题目

Given an `n x n` `matrix` where each of the rows and columns is sorted in ascending order, return *the* `kth` *smallest element in the matrix*.

Note that it is the `kth` smallest element **in the sorted order**, not the `kth` **distinct** element.

You must find a solution with a memory complexity better than `O(n2)`.

 

**Example 1:**

```
Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
```

**Example 2:**

```
Input: matrix = [[-5]], k = 1
Output: -5
```

 

**Constraints:**

- `n == matrix.length == matrix[i].length`
- `1 <= n <= 300`
- `-109 <= matrix[i][j] <= 109`
- All the rows and columns of `matrix` are **guaranteed** to be sorted in **non-decreasing order**.
- `1 <= k <= n2`

 

**Follow up:**

- Could you solve the problem with a constant memory (i.e., `O(1)` memory complexity)?
- Could you solve the problem in `O(n)` time complexity? The solution may be too advanced for an interview but you may find reading [this paper](http://www.cse.yorku.ca/~andy/pubs/X+Y.pdf) fun.

## 题目大意

给定一个 n x n 的矩阵，其中每一行每一列都按照升序排序，返回矩阵中第 k 小的数，它是 **排序后** 的第 `k` 小元素，而不是第 `k` 个 **不同** 的元素。

## 解题思路

注意这里要找的是第 k 小的数，不是第 k 个不同的数，从例子中可以发现，是可以存在相同的数的，

### Solution 1: 大顶堆

这里使用一个大顶堆来维护第 k 小的数，时间复杂度是 O(n2)，这里显然没有利用到矩阵有序的特点，所以这道题目应该还有更优的解法

````c++
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int> heap; // 这里需要一个大顶堆
        const int n = matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (heap.size() == k && heap.top() > matrix[i][j]) {
                    // 如果堆满，则更新堆顶
                    heap.pop();
                    heap.push(matrix[i][j]);
                } else if (heap.size() < k) {
                    // 如果堆没有满，则直接入堆
                    heap.push(matrix[i][j]);
                }
            }
        }
        
        return heap.top(); // 返回堆顶
    }
};
````

### Solution 2: Binary Search

题目既然给了数据是有序的，那么就可考虑使用二分查找，但是这道题目是在二维数组上进行二分查找，所以有些不一样，

这种解法，可以参考霜神的解法：https://books.halfrost.com/leetcode/ChapterFour/0300~0399/0378.Kth-Smallest-Element-in-a-Sorted-Matrix/

```c++
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        const int n = matrix.size();
        int low = matrix[0][0];
        int high = matrix[n - 1][n - 1];
        while (low < high) {
            int mid = low + (high - low) / 2; // 折柳二分搜索的是值，不是下标
            
            if (CounterKthSmallest(matrix, n, mid) >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        return low;
    }
    
 private:
    // 计算比 mid 小的数的数目
    int CounterKthSmallest(const vector<vector<int>>& matrix, int n, int mid) {
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            int j = n - 1;
            while (j >= 0 && matrix[i][j] > mid) {
                --j;
            }
            cnt += j + 1;
        }
        
        return cnt;
    }
};
```

