# [310. Minimum Height Trees](https://leetcode-cn.com/problems/minimum-height-trees/)

## 题目

A tree is an undirected graph in which any two vertices are connected by *exactly* one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of `n` nodes labelled from `0` to `n - 1`, and an array of `n - 1` `edges` where `edges[i] = [ai, bi]` indicates that there is an undirected edge between the two nodes `ai` and `bi` in the tree, you can choose any node of the tree as the root. When you select a node `x` as the root, the result tree has height `h`. Among all possible rooted trees, those with minimum height (i.e. `min(h)`) are called **minimum height trees** (MHTs).

Return *a list of all **MHTs'** root labels*. You can return the answer in **any order**.

The **height** of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/01/e1.jpg)

```
Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]
Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/09/01/e2.jpg)

```
Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]
```

**Example 3:**

```
Input: n = 1, edges = []
Output: [0]
```

**Example 4:**

```
Input: n = 2, edges = [[0,1]]
Output: [0,1]
```

 

**Constraints:**

- `1 <= n <= 2 * 104`
- `edges.length == n - 1`
- `0 <= ai, bi < n`
- `ai != bi`
- All the pairs `(ai, bi)` are distinct.
- The given input is **guaranteed** to be a tree and there will be **no repeated** edges.

## 题目大意

树是一个无向图，其中任何两个顶点只通过一条路径连接。 换句话说，一个任何没有简单环路的连通图都是一棵树。

给你一棵包含 n 个节点的树，标记为 0 到 n - 1 。给定数字 n 和一个有 n - 1 条无向边的 edges 列表（每一个边都是一对标签），其中 edges[i] = [ai, bi] 表示树中节点 ai 和 bi 之间存在一条无向边。

可选择树中任何一个节点作为根。当选择节点 x 作为根节点时，设结果树的高度为 h 。在所有可能的树中，具有最小高度的树（即，min(h)）被称为 最小高度树 。

请你找到所有的 最小高度树 并按 任意顺序 返回它们的根节点标签列表。

树的 高度 是指根节点和叶子节点之间最长向下路径上边的数量

## 解题思路

可以想到这道题目会与求最短路径有关，所以可以向BFS 方向思考，如何去解决。

### Solution 1: BFS（TLE）

可以使用BFS 来求最短路径，但是问题在于，当数据规模较大时，就会出现超时

````c++
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 建图，使用邻接列表
        vector<vector<int>> adj_list(n);
        for (const auto& edge : edges) {
            int point1 = edge.front();
            int point2 = edge.back();
            adj_list[point1].push_back(point2);
            adj_list[point2].push_back(point1);
        }
        
        vector<int> ans; // 答案的集合
        int min_depth = 10000; // 最小深度
        for (int i = 0; i < n; ++i) {
            // 从每一个点开始 BFS
            int depth = BFS(adj_list, i);
            // 更新结果集合
            if (depth > min_depth) {
                continue;
            } else if (depth == min_depth) {
                ans.push_back(i);
            } else {
                ans.clear();
                ans.push_back(i);
                min_depth = depth;
            }
        }
        
        return ans;
    }
    
 private:
    int BFS(const vector<vector<int>>& graph, int start) {
        // 判断是否越界
        const int size = graph.size();
        if (start >= size) {
            return -1;
        }
        
        vector<bool> visited(size, false); // 做记录
        queue<int> que;
        que.push(start);
        visited[start] = true; // 这里入队就做记录
        int depth = 0;
        
        while (!que.empty()) {
            ++depth;
            
            // 每次遍历一层
            const int len = que.size();
            for (int i = 0; i < len; ++i) {
                int cur = que.front();
                que.pop();
                
                for (int point : graph[cur]) {
                    if (visited[point]) {
                        continue;
                    }
                    visited[point] = true;
                    que.push(point);
                    
                }
            }
        }
        return depth;
    }
};
````

