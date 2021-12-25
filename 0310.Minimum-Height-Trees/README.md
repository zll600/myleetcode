

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

可以想到这道题目会与求最短路径有关，所以可以向BFS 方向思考，如何去解决。这道题可以参考这篇题解：https://leetcode-cn.com/problems/minimum-height-trees/solution/c-xun-xu-jian-jin-de-si-lu-bfsdfstuo-bu-hmk2y/

### Solution 1: BFS（TLE）

可以使用BFS 来求最短路径，但是问题在于，当数据规模较大时，就会出现超时

````c++
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 建图
        vector<vector<int>> adj_list(n);
        for (const auto& edge : edges) {
            int point1 = edge[0];
            int point2 = edge[1];
            adj_list[point1].push_back(point2);
            adj_list[point2].push_back(point1);
        }
        
        vector<int> res;
        int min_depth = 10000; // 极端情况，退化为链表
        for (int i = 0; i < n; ++i) {
            int depth = BFS(adj_list, i);
            
            if (depth > min_depth) {
                continue;
            } else if (depth == min_depth) {
                res.push_back(i);
            } else {
                res.clear();
                min_depth = depth;
                res.push_back(i);
            }
        }
        return res;
    }
    
 private:
    int BFS(const vector<vector<int>> graph, int start) {
        const int size = graph.size();
        if (start >= size) {
            return -1;
        }
        
        vector<bool> visited(size, false); // 标记数组
        queue<int> que; // 队列
        que.push(start);
        visited[start] = true;
        
        int depth = 0;
        while (!que.empty()) {
            ++depth;
            const int len = que.size();
            // 遍历一层
            for (int i = 0; i < len; ++i) {
                int cur = que.front();
                que.pop();
                for (int point : graph[cur]) {
                    if (!visited[point]) {
                        // 入队就做标记
                        que.push(point);
                        visited[point] = true;
                    }
                }
            }
        }
        
        return depth;
    }
};
````

### Solution 2: DFS + cache(TLE)

这种解法利用 DFS  + 缓存，但是依旧会超时

```c++
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 建图
        vector<vector<int>> adj_list(n);
        for (const auto& edge : edges) {
            int point1 = edge[0];
            int point2 = edge[1];
            adj_list[point1].push_back(point2);
            adj_list[point2].push_back(point1);
        }
        
        vector<int> res;
        int min_depth = 10000; // 极端情况，退化为链表
        for (int i = 0; i < n; ++i) {
            int depth = DFS(adj_list, i, -1);
            
            if (depth > min_depth) {
                continue;
            } else if (depth == min_depth) {
                res.push_back(i);
            } else {
                res.clear();
                min_depth = depth;
                res.push_back(i);
            }
        }
        return res;
    }
    
 private:
    // cache
    // key start * 1e5 + root
    // value max_deptha
    unordered_map<int, int> cache_;
    
    int DFS(const vector<vector<int>>& graph, int start, int root) {
        int key = start * 1e5 + root;
        if (cache_.find(key) != cache_.end()) {
            return cache_.at(key);
        }
        
        int ret = 0;
        for (int point : graph[start]) {
            if (point == root) {
                continue;
            }
            ret = max(ret, DFS(graph, point, start));
        }
        cache_[key] = ret + 1;
        return ret + 1;
    }
};
```

### Solution 3:

这种解法也可以在看下这篇题解：https://leetcode-cn.com/problems/minimum-height-trees/solution/bfs-liang-duan-shao-xiang-qiu-zhong-dian-5mol/

关键就是出度越大，以此为根结点的数组的高度越小，越能留到后面

````c++
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            // 边界情况
            return vector<int>({0});
        }
        
        // 构建邻接表和入度数组
        vector<vector<int>> adj_lists(n);
        vector<int> degrees(n, 0);
        for (const auto& edge : edges) {
            int point1 = edge[0];
            int point2 = edge[1];
            adj_lists[point1].push_back(point2);
            adj_lists[point2].push_back(point1);
            
            ++degrees[point1];
            ++degrees[point2];
        }
        
        queue<int> que;
        for (int i = 0; i < n; ++i) {
            if (degrees[i] == 1) {
                que.push(i);
            }
        }
        
        while (!que.empty()) {
            const int size = que.size();
            if (size == n) {
                break;
            }
            n -= size;
            
            for (int i = 0; i < size; ++i) {
                int cur = que.front();
                que.pop();
                
                int adj;
                for (int point : adj_lists[cur]) {
                    adj = point;
                    if (degrees[adj] > 1) {
                        break;
                    }
                }
                --degrees[adj];
                
                if (degrees[adj] == 1) {
                    que.push(adj);
                }
            }
        }
        
        vector<int> res;
        while (!que.empty()) {
            res.push_back(que.front());
            que.pop();
        }
        
        return res;
    }
};
````

