# [1129. Shortest Path with Alternating Colors](https://leetcode.cn/problems/shortest-path-with-alternating-colors/)

## 题目

You are given an integer `n`, the number of nodes in a directed graph where the nodes are labeled from `0` to `n - 1`. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.

You are given two arrays `redEdges` and `blueEdges` where:

- `redEdges[i] = [ai, bi]` indicates that there is a directed red edge from node `ai` to node `bi` in the graph, and
- `blueEdges[j] = [uj, vj]` indicates that there is a directed blue edge from node `uj` to node `vj` in the graph.

Return an array `answer` of length `n`, where each `answer[x]` is the length of the shortest path from node `0` to node `x` such that the edge colors alternate along the path, or `-1` if such a path does not exist.

 

**Example 1:**

```
Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
Output: [0,1,-1]
```

**Example 2:**

```
Input: n = 3, redEdges = [[0,1]], blueEdges = [[2,1]]
Output: [0,1,-1]
```

 

**Constraints:**

- `1 <= n <= 100`
- `0 <= redEdges.length, blueEdges.length <= 400`
- `redEdges[i].length == blueEdges[j].length == 2`
- `0 <= ai, bi, uj, vj < n`

## 题目大意

在一个有向图中，节点分别标记为 `0, 1, ..., n-1`。图中每条边为 *红色* 或者 *蓝色* ，且存在 *自环* 或 *平行边*

`red_edges` 中的每一个 `[i, j]` 对表示从节点 `i` 到节点 `j` 的红色有向边。类似地，`blue_edges` 中的每一个 `[i, j]` 对表示从节点 `i` 到节点 `j` 的蓝色有向边

返回长度为 `n` 的数组 `answer`，其中 `answer[X]` 是从节点 `0` 到节点 `X` 的红色边和蓝色边 *交替* 出现的最短路径的长度。如果不存在这样的路径，那么 answer[x] = -1

## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/shortest-path-with-alternating-colors/solution/by-bai-mu-ying-li-dra-eniac-jehj/)

这里需要注意的有，这里的边都是有向边，同时每条边都有对应的颜色，所以在进行 BFS 的时候除了维护位置之外，还需要维护到达这个位置的边的颜色，

另外这道题目要求每个位置的 distance，所以在遍历的过程中需要维护每个位置的 distance，这里同样注意，每个点可以有两种不同颜色的边可以到达，所以每个位置的 dist 值要选择可以到达中的最小的那个

````c++
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        // create directed graph
        vector<vector<pair<int, int>>> graph(n);
        for (auto& edge : redEdges) {
            int from = edge[0], to = edge[1];
            graph[from].emplace_back(to, 0);
        }
        for (auto& edge : blueEdges) {
            int from = edge[0], to = edge[1];
            graph[from].emplace_back(to, 1);
        }

        // BFS

        // Every can be reached by two different colored edges
        vector<vector<int>> visited(n, vector<int>(2, 0));
        queue<tuple<int, int, int>> que;
        que.emplace(0, 0, 0);
        que.emplace(0, 0, 1);

        vector<int> dist(n, INT_MAX);
        dist[0] = 0;
        while (!que.empty()) {
            auto [from, distance, color] = que.front();
            que.pop();

            // cout << from << " -- ";
            for (auto& [to, col] : graph[from]) {
                // different colors
                // this node has not been reached by this color
                if (col != color && !visited[to][col]) {
                    // cout << to << " -- ";
                    dist[to] = min(dist[to], distance + 1);
                    que.emplace(to, distance + 1, col);
                    // 这个点已经通过 col 颜色的边遍历过一遍了
                    visited[to][col] = 1;
                }
            }
            // cout << endl;
        }
        for_each(dist.begin(), dist.end(), [](int& elem) {
            if (elem == INT_MAX) {
                elem = -1;
            }
        });

        return dist;
    }
};
`````
