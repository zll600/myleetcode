# [815. Bus Routes](https://leetcode.com/problems/bus-routes/)

## 题目

You are given an array `routes` representing bus routes where `routes[i]` is a bus route that the `ith` bus repeats forever.

- For example, if `routes[0] = [1, 5, 7]`, this means that the `0th` bus travels in the sequence `1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ...` forever.

You will start at the bus stop `source` (You are not on any bus initially), and you want to go to the bus stop `target`. You can travel between bus stops by buses only.

Return *the least number of buses you must take to travel from* `source` *to* `target`. Return `-1` if it is not possible.

 

**Example 1:**

```
Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
Output: 2
Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
```

**Example 2:**

```
Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
Output: -1
```

 

**Constraints:**

- `1 <= routes.length <= 500`.
- `1 <= routes[i].length <= 105`
- All the values of `routes[i]` are **unique**.
- `sum(routes[i].length) <= 105`
- `0 <= routes[i][j] < 106`
- `0 <= source, target < 106`

## 题目大意

我们有一系列公交路线。每一条路线 `routes[i]` 上都有一辆公交车在上面循环行驶。

例如，有一条路线 `routes[0] = [1, 5, 7]`，表示第一辆 (下标为0) 公交车会一直按照 `1->5->7->1->5->7->1->… ` 的车站路线行驶。

假设我们从 `S` 车站开始（初始时不在公交车上），要去往 `T` 站。 期间仅可乘坐公交车，求出最少乘坐的公交车数量。返回 `-1` 表示不可能到达终点车站。

## 解题思路 

这道题目求最少乘坐的公交车数量，有点 bfs 的感觉

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0815.Bus-Routes/)

这道题目就是图论求最短路径，所以这里建图 + BFS 一下就可以了，注意做好访问标记，防止循环入队

````c++
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) {
            return 0;
        }
        
        const int len = routes.size();
        
        // 建图
        unordered_map<int, vector<int>> adj_list;
        for (int i = 0; i < len; ++i) {
            for (int route : routes[i]) {
                adj_list[route].push_back(i);
            }
        }
        
        // bfs
        queue<int> que;
        que.push(source);
        
        unordered_set<int> visited;
        int res = 0;
        while (!que.empty()) {
            ++res;
            
            
            const int que_len = que.size();
            for (int i = 0; i < que_len; ++i) {
                int cur = que.front();
                que.pop();
                
                for (int bus : adj_list[cur]) {
                    if (visited.find(bus) != visited.end()) {
                        continue;
                    }
                    
                    // 这里做标记防止循环访问
                    visited.insert(bus);
                    for (int val : routes[bus]) {
                        if (val == target) {
                            return res;
                        }
                        
                        que.push(val);
                    }
                }
            }
        }
        
        return -1;
    }
};
````
