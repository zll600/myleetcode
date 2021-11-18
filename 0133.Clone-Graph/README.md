# [133. Clone Graph](https://leetcode-cn.com/problems/clone-graph/)

## 题目

Given a reference of a node in a **[connected](https://en.wikipedia.org/wiki/Connectivity_(graph_theory)#Connected_graph)** undirected graph.

Return a [**deep copy**](https://en.wikipedia.org/wiki/Object_copying#Deep_copy) (clone) of the graph.

Each node in the graph contains a value (`int`) and a list (`List[Node]`) of its neighbors.

```
class Node {
    public int val;
    public List<Node> neighbors;
}
```

 

**Test case format:**

For simplicity, each node's value is the same as the node's index (1-indexed). For example, the first node with `val == 1`, the second node with `val == 2`, and so on. The graph is represented in the test case using an adjacency list.

**An adjacency list** is a collection of unordered **lists** used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.

The given node will always be the first node with `val = 1`. You must return the **copy of the given node** as a reference to the cloned graph.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/11/04/133_clone_graph_question.png)

```
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/01/07/graph.png)

```
Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.
```

**Example 3:**

```
Input: adjList = []
Output: []
Explanation: This an empty graph, it does not have any nodes.
```

**Example 4:**

![img](https://assets.leetcode.com/uploads/2020/01/07/graph-1.png)

```
Input: adjList = [[2],[1]]
Output: [[2],[1]]
```

 

**Constraints:**

- The number of nodes in the graph is in the range `[0, 100]`.
- `1 <= Node.val <= 100`
- `Node.val` is unique for each node.
- There are no repeated edges and no self-loops in the graph.
- The Graph is connected and all nodes can be visited starting from the given node.

## 题目大意

给定一个无向图中节点的拷贝，返回这个图的深拷贝，这张图采用的是邻接表的形式存储的

## 解题思路

个人觉得，这道题目需要逐个复制节点，重点就是图的遍历，所以主要考察的还是 dfs 和 bfs 这两种算法

### Solution 1: DFS

这种解法可以参考这两篇题解：https://leetcode-cn.com/problems/clone-graph/solution/dfs-he-bfs-by-powcai/

https://leetcode-cn.com/problems/clone-graph/solution/ke-long-tu-ha-xi-dfs-zui-qing-xi-yi-dong-3v6l/



这道题目关键就是在遍历的时候需要存储一个从源节点到克隆节点的映射，来记录已经访问过的源节点，并缓存结果，不能用 set 来记录，这里既需要记录已经访问过的节点，也需要记录已经构造过的克隆节点

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        // 为防止多次构造同一个节点
        // 记录从源节点到克隆节点的映射
        unordered_map<Node*, Node*> visited;
        return DFS(node, visited);
    }
    
 private:
    Node* DFS(Node *node, unordered_map<Node*, Node*>& visited) {
        if (!node) {
            return nullptr;
        }
        // 如果已经构建过了，直接返回
        if (visited.find(node) != visited.end()) {
            return visited.at(node);
        }
        
        Node *clone = new Node(node->val);  // 构建新节点
        visited.emplace(node, clone);  // 保存映射
        for (Node* neighbor : node->neighbors) {  // 遍历邻接列表
            clone->neighbors.push_back(DFS(neighbor, visited));
        }
        return clone;  // 返回新节点
    }
};
```



### Solution 2: BFS

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/clone-graph/solution/dfs-he-bfs-by-powcai/

````c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) {  // 处理边界情况
            return node;
        }
        
        // 存储从源节点到克隆节点的映射
        unordered_map<Node*, Node*> visited;
        queue<Node*> que;  // 队列
        
        Node *clone = new Node(node->val);  // 构建新节点
        visited.emplace(node, clone);  // 构造映射
        que.push(node);
        
        // BFS
        while (!que.empty()) {
            Node *cur = que.front();
            que.pop();
            
            // 访问邻接列表
            for (Node* neighbor : cur->neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    // 如果之前没有访问过，则说明需要构建新节点
                    visited.emplace(neighbor, new Node(neighbor->val));
                    que.push(neighbor);  // 入队，待遍历
                }
                // 更新克隆节点的邻接列表
                visited[cur]->neighbors.push_back(visited.at(neighbor));
            }
        }
        return clone;
    }
};
````

