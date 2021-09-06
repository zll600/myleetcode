# [77. Combinations](https://leetcode.com/problems/combinations/)

## 题目

Given two integers `n` and `k`, return *all possible combinations of* `k` *numbers out of the range* `[1, n]`.

You may return the answer in **any order**.

 

**Example 1:**

```
Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

**Example 2:**

```
Input: n = 1, k = 1
Output: [[1]]
```

 

**Constraints:**

- `1 <= n <= 20`
- `1 <= k <= n`

## 题目大意

给定两个整数 n 和 k，返回 [1,n]区间中 k 个数的所有组合，

## 解题思路

* 这是一道组合题，可以使用回溯算法来解决，并且可以进行剪枝优化

## 代码

```c++
class Solution {
public:
    
    vector<vector<int>> combine(int n, int k) {
        Backtracking(n, k, 1);
        return res;
    }
    
 private:
    vector<vector<int>> res;
    vector<int> path;
    
    void Backtracking(int n, int k, int idx) {
        if (path.size() == k) {
            res.push_back(path);
            return;
        }
        
        //for (int i = idx; i <= n; ++i) {
        for (int i = idx; i <= n - (k - path.size()) + 1; ++i) { // 剪枝优化
            path.push_back(i);
            Backtracking(n, k, i + 1);
            path.pop_back();
        }
    }
};
```

