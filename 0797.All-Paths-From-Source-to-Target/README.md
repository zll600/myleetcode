# [797. All Paths From Source to Target](https://leetcode.cn/problems/all-paths-from-source-to-target/)

## 题目

Given a directed acyclic graph (**DAG**) of `n` nodes labeled from `0` to `n - 1`, find all possible paths from node `0` to node `n - 1` and return them in **any order**.

The graph is given as follows: `graph[i]` is a list of all nodes you can visit from node `i` (i.e., there is a directed edge from node `i` to node `graph[i][j]`).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/28/all_1.jpg)

```
Input: graph = [[1,2],[3],[3],[]]
Output: [[0,1,3],[0,2,3]]
Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/09/28/all_2.jpg)

```
Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
```

 

**Constraints:**

- `n == graph.length`
- `2 <= n <= 15`
- `0 <= graph[i][j] < n`
- `graph[i][j] != i` (i.e., there will be no self-loops).
- All the elements of `graph[i]` are **unique**.
- The input graph is **guaranteed** to be a **DAG**.



## 题目大意

给你一个有 `n` 个节点的 **有向无环图（DAG）**，请你找出所有从节点 `0` 到节点 `n-1` 的路径并输出（**不要求按特定顺序**）

 `graph[i]` 是一个从节点 `i` 可以访问的所有节点的列表（即从节点 `i` 到节点 `graph[i][j]`存在一条有向边）。

 
## 解题思路

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/all-paths-from-source-to-target/solution/gong-shui-san-xie-yun-yong-dfs-bao-sou-s-xlz9/)

这道题目的思路还是比较明确，就是有向图的遍历问题，这里特殊的是，有向图的遍历，不会遍历到出发的地方，所以这里其实也可以不用 visit 数组


### Solution 1: DFS

````c++
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> ans;
        vector<int> path;
        path.push_back(0);
        DFS(graph, 0, ans, path);
        return ans;
    }

 private:
    void DFS(const vector<vector<int>>& graph, int cur,
            vector<vector<int>>& ans, vector<int>& path) {
        if (cur == graph.size() - 1) {
            ans.push_back(path);
            return;
        }

        for (int next : graph[cur]) {
            path.push_back(next);
            DFS(graph, next, ans, path);
            path.pop_back();
        }
    }
};
````
