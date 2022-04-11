# [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)

## 题目

There is a directed graph of `n` nodes with each node labeled from `0` to `n - 1`. The graph is represented by a **0-indexed** 2D integer array `graph` where `graph[i]` is an integer array of nodes adjacent to node `i`, meaning there is an edge from node `i` to each node in `graph[i]`.

A node is a **terminal node** if there are no outgoing edges. A node is a **safe node** if every possible path starting from that node leads to a **terminal node**.

Return *an array containing all the **safe nodes** of the graph*. The answer should be sorted in **ascending** order.

 

**Example 1:**

![Illustration of graph](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/03/17/picture1.png)

```
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.
```

**Example 2:**

```
Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation:
Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.
```

 

**Constraints:**

- `n == graph.length`
- `1 <= n <= 104`
- `0 <= graph[i].length <= n`
- `0 <= graph[i][j] <= n - 1`
- `graph[i]` is sorted in a strictly increasing order.
- The graph may contain self-loops.
- The number of edges in the graph will be in the range `[1, 4 * 104]`.

## 题目大意

有一个有 `n` 个节点的有向图，节点按 `0` 到 `n - 1` 编号。图由一个 索引从 `0` 开始 的 `2D` 整数数组 `graph` 表示， 

`graph[i]` 是与节点 `i` 相邻的节点的整数数组，这意味着从节点 `i` 到 `graph[i]` 中的每个节点都有一条边。

如果一个节点没有 *连出的有向边* ，则它是 *终端节点* 。如果没有出边，则节点为 *终端节点*。如果从该节点开始的所有可能路径都通向一个 *终端节点* ，则该节点为 *安全节点* 

返回一个由图中所有 *安全节点* 组成的数组作为答案。答案数组中的元素应当按 *升序* 排列

## 解题思路

这道题目需要判断图中是否存在环路，如果一个点在环路内，那么就不能成为一个 *安全节点*，

### Solution 1:

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/find-eventual-safe-states/solution/gtalgorithm-san-ju-hua-jiao-ni-wan-zhuan-xf5o/)

````c++
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        const int n = graph.size();
        // 拓扑排序需要根据入度来计算，所以需要将这里的图先反一下
        vector<vector<int>> adj_list(n);
        // 入度数组
        vector<int> in_degress(n);
        for (int i = 0; i < n;  ++i) {
            for (int x : graph[i]) {
                adj_list[x].push_back(i);
            }
            in_degress[i] = graph[i].size();
        }

        // 拓扑排序
        queue<int> que;
        for (int i = 0; i < n; ++i) {
            // 将入度为 0 的点入队
            if (!in_degress[i]) {
                que.push(i);
            }
        }

        while (!que.empty()) {
            // 取出一个节点
            int cur = que.front();
            que.pop();

            for (int x : adj_list[cur]) {
                // 跟新节点的入度
                --in_degress[x];

                if (!in_degress[x]) {
                    que.push(x);
                }
            }
        }

        // 入度为 0 的节点，最是我们要找的安全节点
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            if (!in_degress[i]) {
                res.push_back(i);
            }
        }

        return res;
    }
};
````

## 解题思路
