# [743. Network Delay Time](https://leetcode-cn.com/problems/network-delay-time/)

## 题目

You are given a network of `n` nodes, labeled from `1` to `n`. You are also given `times`, a list of travel times as directed edges `times[i] = (ui, vi, wi)`, where `ui` is the source node, `vi` is the target node, and `wi` is the time it takes for a signal to travel from source to target.

We will send a signal from a given node `k`. Return the time it takes for all the `n` nodes to receive the signal. If it is impossible for all the `n` nodes to receive the signal, return `-1`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/05/23/931_example_1.png)

```
Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
```

**Example 2:**

```
Input: times = [[1,2,1]], n = 2, k = 1
Output: 1
```

**Example 3:**

```
Input: times = [[1,2,1]], n = 2, k = 2
Output: -1
```

 

**Constraints:**

- `1 <= k <= n <= 100`
- `1 <= times.length <= 6000`
- `times[i].length == 3`
- `1 <= ui, vi <= n`
- `ui != vi`
- `0 <= wi <= 100`
- All the pairs `(ui, vi)` are **unique**. (i.e., no multiple edges.)

## 题目大意

给定一个 `n` 个节点的网络，标记为 `1` 到 `n`，给定一个 `times` ，给你一个列表 `times`，表示信号经过有向边传递的时间，有向边 `time[i] = (ui, vi, wi)`，其中 `ui` 是原节点，`vi` 是目标节点，`wi` 是用原节点到目标节点话费的时间

我们将从一个给定节点 `k` 发出信号，返回它到达所有节点的时间，如果不可能到达所有节点，返回 `-1`

## 解题思路

这道题有图的遍历有关
- 如何建图
- 如何遍历
- 在遍历的过程中如何累计时间


### Solution 1: BFS

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/network-delay-time/solution/c-bfs-by-qiank-rv2f/)

这使用一个数组来记录到达每个节点的最小时间，然后返回的时候取整个数组中的最大值，

````c++
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 建图
        unordered_map<int, unordered_map<int, int>> adj_lists;
        for (const auto& time : times) {
            int src = time[0];
            int dst = time[1];
            int weight = time[2];
            
            adj_lists[src][dst] = weight;
        }
        
        // 节点是从 1 到 n
        vector<int> memo(n + 1, INT_MAX);
        memo[k] = 0;
        
        // BFS
        queue<int> que;
        unordered_set<int> visited;
        que.push(k);
        visited.insert(k);
        
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            
            visited.insert(cur);
            
            for (auto& [dst, weight] : adj_lists[cur]) {
                // 这里计算累计时间
                int time = weight + memo[cur];
                
                if (memo[dst] > time) {
                    // 只记录到达次节点的最小时间
                    memo[dst] = time;
                    que.push(dst);
                }
            }
        }
        return visited.size() == n ? *max_element(memo.begin() + 1, memo.end()) : -1;
    }
};
````
