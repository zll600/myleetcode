# [598. Range Addition II](https://leetcode.com/problems/range-addition-ii/)

## 题目

You are given an `m x n` matrix `M` initialized with all `0`'s and an array of operations `ops`, where `ops[i] = [ai, bi]` means `M[x][y]` should be incremented by one for all `0 <= x < ai` and `0 <= y < bi`.

Count and return *the number of maximum integers in the matrix after performing all the operations*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/02/ex1.jpg)

```
Input: m = 3, n = 3, ops = [[2,2],[3,3]]
Output: 4
Explanation: The maximum integer in M is 2, and there are four of it in M. So return 4.
```

**Example 2:**

```
Input: m = 3, n = 3, ops = [[2,2],[3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3]]
Output: 4
```

**Example 3:**

```
Input: m = 3, n = 3, ops = []
Output: 9
```

 

**Constraints:**

- `1 <= m, n <= 4 * 10^4`
- `0 <= ops.length <= 10^4`
- `ops[i].length == 2`
- `1 <= ai <= m`
- `1 <= bi <= n`

## 题目大意

给定一个 `m x n` 的初始化为 0 的矩阵 `M`，和一个操作数组 `ops`，其中 `ops[i] = [ai, bi]` 表示 `M[x][y]` 应该对于 `0 <= x < ai` 且 `0 <= y < bi` 的所有位置都增加 `1`，

在执行给定的一系列操作后，你需要返回矩阵中含有最大整数的元素个数

## 解题思路


### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0500~0599/0598.Range-Addition-II/)

这道题目只会改变一个矩形范围圈起来的值，而且无论如何画出来的矩形都以 `[0, 0]` 为左上角，所以我们只要求出最小的矩形的右下角即可，

这样就可以求出重复次数最多的值的数目


````c++
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int m_min = m, n_min = n;
        // 这里我们只需要动态维护 右下角的坐标即可
        for (const auto& op : ops) {
            m_min = min(m_min, op[0]);
            n_min = min(n_min, op[1]);
        }

        return m_min * n_min;
    }
};
````
