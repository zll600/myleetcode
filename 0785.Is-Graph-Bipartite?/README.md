# [785. Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/)

## 题目

There is an **undirected** graph with `n` nodes, where each node is numbered between `0` and `n - 1`. You are given a 2D array `graph`, where `graph[u]` is an array of nodes that node `u` is adjacent to. More formally, for each `v` in `graph[u]`, there is an undirected edge between node `u` and node `v`. The graph has the following properties:

- There are no self-edges (`graph[u]` does not contain `u`).
- There are no parallel edges (`graph[u]` does not contain duplicate values).
- If `v` is in `graph[u]`, then `u` is in `graph[v]` (the graph is undirected).
- The graph may not be connected, meaning there may be two nodes `u` and `v` such that there is no path between them.

A graph is **bipartite** if the nodes can be partitioned into two independent sets `A` and `B` such that **every** edge in the graph connects a node in set `A` and a node in set `B`.

Return `true` *if and only if it is **bipartite***.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/21/bi2.jpg)

```
Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
Output: false
Explanation: There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/10/21/bi1.jpg)

```
Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Output: true
Explanation: We can partition the nodes into two sets: {0, 2} and {1, 3}.
```

 

**Constraints:**

- `graph.length == n`
- `1 <= n <= 100`
- `0 <= graph[u].length < n`
- `0 <= graph[u][i] <= n - 1`
- `graph[u]` does not contain `u`.
- All the values of `graph[u]` are **unique**.
- If `graph[u]` contains `v`, then `graph[v]` contains `u`.

## 题目大意

给定一个 有 `n` 个节点的 *无向图*，其中每个节点标为 `[0, n - 1]` 之间，给定图的邻接表的表示形式 `graph`，
- 不存在自环（`graph[u]` 不包括 `u`）
- 不存在平行边（`graph[u]`不包括重复的值）
- 如果 `v` 在 `graph[u]` 中，则 `u` 也在 `graph[v]` 中，
- 这个图可能不是连通图，表示这里的两个节点 `u` 和 `v`，可能不存在两个节点之间的路径，

一个图如果是二分图，那么表示这个图的节点可以被分为两个集合 `A` 和 `B`，并且每条边有一个节点在 `A`，有一个节点在 `B`，当且仅当这个图是二分图的时候返回 `true`

## 解题思路



### Solution 1: DFS

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0785.Is-Graph-Bipartite/)

利用 DFS 在遍历的时候做一个记录，然后根据题目要做判断即可

````c++
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        const int len = graph.size();
        // -1 表示未遍历到
        // 0 表示 A， 1 表示 B
        vector<int> color(len, -1);

        // 遍历每个节点，任意一个地方出错，直接返回错误
        for (int i = 0; i < len; ++i) {
            if (!DFS(graph, color, i, -1)) {
                return false;
            }
        }

        return true;
    }

 private:
    bool DFS(const vector<vector<int>>& graph, vector<int>& color,
            int cur, int prev) {
        if (color[cur] == -1) {
            // 如果没有访问过

            // 设置为和上一个节点相反的状态
            if (prev == 1) {
                color[cur] = 0;
            } else {
                color[cur] = 1;
            }
        } else if (color[cur] == prev) {
            // 如果访问过，而且二者状态相同，那么直接返回错误
            return false;
        } else if (color[cur] != prev) {
            // 如果访问过，而且二者状态不同，那么直接返回正确即可
            return true;
        }

        // 遍历与这个点相连的其他点
        for (int node : graph[cur]) {
            if (!DFS(graph, color, node, color[cur])) {
                return false;
            }
        }

        return true;
    }
};
````

