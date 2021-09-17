# [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/)

In this problem, a tree is an **undirected graph** that is connected and has no cycles.

You are given a graph that started as a tree with `n` nodes labeled from `1` to `n`, with one additional edge added. The added edge has two **different** vertices chosen from `1` to `n`, and was not an edge that already existed. The graph is represented as an array `edges` of length `n` where `edges[i] = [ai, bi]` indicates that there is an edge between nodes `ai` and `bi` in the graph.

Return *an edge that can be removed so that the resulting graph is a tree of* `n` *nodes*. If there are multiple answers, return the answer that occurs last in the input.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/05/02/reduntant1-1-graph.jpg)

```
Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/05/02/reduntant1-2-graph.jpg)

```
Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]
```

 

**Constraints:**

- `n == edges.length`
- `3 <= n <= 1000`
- `edges[i].length == 2`
- `1 <= ai < bi <= edges.length`
- `ai != bi`
- There are no repeated edges.
- The given graph is connected.

## 题目大意

在这个题目中，树是一个连通的无向无环图。

给定一个有n个节点的树，这棵树也有一条额外的边，这条边的两个定点包含在 1 到n 中间，且这条边不属于树中已经存在的边，图的信息存储于一个二维数组中

，edges[i] = [ai, bi]，代表 ai 和bi 之间有一条边，

返回一条可以删去的边，删去之后，可是的剩余的部分是一个有n 个节点的树，如果有多个答案，返回edges 中最后出现的边，

## 解题思路

* 这道题目可以这样想，在遍历边的数组时，更新 uf，如果之前两个节点已经连通，则此时再次连通，一定是出现环

## 代码

``````c++
class UF {
 public:
    UF(int num) {
        parent_.resize(num);
        for (int i = 0; i < num; ++i) {
            parent_[i] = i;
        }
    }

    bool Connected(int p, int q) {
        return Find(p) == Find(q);
    }

    int Find(int p) {
        while (p != parent_[p]) {
            parent_[p] = parent_[parent_[p]];
            p = parent_[p];
        }
        return p;
    }

    void Union(int p, int q) {
        int proot = Find(p);
        int qroot = Find(q);

        if (proot == qroot) {
            return;
        }
        parent_[proot] = qroot;
    }

 private:
    vector<int> parent_;
};

class Solution {
 public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        // 这里注意树中节点取 1 到 n，这里加一个空格，来避免偏移
        UF uf(n + 1);

        for (int i = 0; i < n; ++i) {
            if (uf.Connected(edges[i][0], edges[i][1])) {
                return edges[i];
            }
            uf.Union(edges[i][0], edges[i][1]);
        }

        return vector<int>();
    }
};
``````

