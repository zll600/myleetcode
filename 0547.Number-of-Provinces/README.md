# [547. Number of Provinces](https://leetcode.com/problems/number-of-provinces/)

## 题目

There are `n` cities. Some of them are connected, while some are not. If city `a` is connected directly with city `b`, and city `b` is connected directly with city `c`, then city `a` is connected indirectly with city `c`.

A **province** is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an `n x n` matrix `isConnected` where `isConnected[i][j] = 1` if the `ith` city and the `jth` city are directly connected, and `isConnected[i][j] = 0` otherwise.

Return *the total number of **provinces***.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/12/24/graph1.jpg)

```
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/12/24/graph2.jpg)

```
Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
```

 

**Constraints:**

- `1 <= n <= 200`
- `n == isConnected.length`
- `n == isConnected[i].length`
- `isConnected[i][j]` is `1` or `0`.
- `isConnected[i][i] == 1`
- `isConnected[i][j] == isConnected[j][i]`

## 题目大意

有 n 个城市，其中一些是链接的，另一些是没有连接的，如果城市 a直接与城市 b 相连，城市b 与城市 c 直接相连，则城市 a 和城市 c 直接相连，省份包括直接和间接相连的城市，

给定一个城市矩阵 matirx，其中 `matrix[i][j]` == 1 代表城市i 和城市 j 相连接，反之不连接，

返回矩阵中省份的数目

## 解题思路

* 这道题目可以说是一道并查集的模板题，
* 如果两个单字母变量满足等于的关系，则两两个单字母变量连通，如果后面这两个单字母变量再次出现不等关系，则会出现矛盾，直接返回 false。

## 代码

`````c++
class UF {
 public:
    UF(int size) : count_(size) {
        id_.resize(size);
        for (int i = 0; i < size; ++i) {
            id_[i] = i;
        }
    }

    bool Connected(int p, int q) {
        return Find(p) == Find(q);
    }

    int Find(int p) {
        while (p != id_[p]) {
            id_[p] = id_[id_[p]];
            p = id_[p];
        }
        return p;
    }

    void Union(int p, int q) {
        int proot = Find(p);
        int qroot = Find(q);

        if (proot == qroot) {
            return;
        }

        id_[proot] = qroot;
        --count_;
    }

    int Count() const {
        return count_;
    }

 private:
    vector<int> id_;
    int count_;  
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        UF uf(n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 1) {
                    uf.Union(i, j);
                }
            }
        }
        return uf.Count();
    }
};
`````

