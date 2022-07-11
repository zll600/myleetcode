#### [1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance](https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)

### 题目

There are `n` cities numbered from `0` to `n-1`. Given the array `edges` where `edges[i] = [fromi, toi, weighti]` represents a bidirectional and weighted edge between cities `fromi` and `toi`, and given the integer `distanceThreshold`.

Return the city with the smallest number of cities that are reachable through some path and whose distance is **at most** `distanceThreshold`, If there are multiple such cities, return the city with the greatest number.

Notice that the distance of a path connecting cities ***i*** and ***j*** is equal to the sum of the edges' weights along that path.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/01/16/find_the_city_01.png)

```
Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
Output: 3
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2] 
City 1 -> [City 0, City 2, City 3] 
City 2 -> [City 0, City 1, City 3] 
City 3 -> [City 1, City 2] 
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/01/16/find_the_city_02.png)

```
Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
Output: 0
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1] 
City 1 -> [City 0, City 4] 
City 2 -> [City 3, City 4] 
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3] 
The city 0 has 1 neighboring city at a distanceThreshold = 2.
```

 

**Constraints:**

- `2 <= n <= 100`
- `1 <= edges.length <= n * (n - 1) / 2`
- `edges[i].length == 3`
- `0 <= fromi < toi < n`
- `1 <= weighti, distanceThreshold <= 10^4`
- All pairs `(fromi, toi)` are distinct.

## 题目大意

有 n 个城市，按从 0 到 n-1 编号。给你一个边数组 edges，其中 edges[i] = [fromi, toi, weighti] 代表 fromi 和 toi 两个城市之间的双向加权边，距离阈值是一个整数 distanceThreshold。

返回能通过某些路径到达其他城市数目最少、且路径距离 最大 为 distanceThreshold 的城市。如果有多个这样的城市，则返回编号最大的城市。

注意，连接城市 i 和 j 的路径的距离等于沿该路径的所有边的权重之和



## 解题思路

这道题目还是可以比较容易想到最短路径算法的，不过比起一般的 bfs,这里可以使用一些更优的算法

### Solution 1: Floyd 

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/solution/yu-zhi-ju-chi-nei-lin-ju-zui-shao-de-cheng-shi-flo/)和 [这篇题解](https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/solution/yu-zhi-ju-chi-nei-lin-ju-zui-shao-de-cheng-shi-flo/)

````c++
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> adj_vec(n, vector<int>(n, INT_MAX));
        for (const auto& edge : edges) {
            adj_vec[edge[0]][edge[1]] = edge[2];
            adj_vec[edge[1]][edge[0]] = edge[2];
        }
        
        // Floyd algorithm
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == j || adj_vec[i][k] == INT_MAX || adj_vec[k][j] == INT_MAX) {
                        continue;
                    }
                    adj_vec[i][j] = min(adj_vec[i][k] + adj_vec[k][j], adj_vec[i][j]);
                }
            }
        }
        
        int ans = INT_MAX;
        int idx = -1;
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                
                if (adj_vec[i][j] <= distanceThreshold) {
                    ++cnt;
                }
            }
            
            if (cnt <= ans) {
                ans = cnt;
                idx = i;
            }
        }
        return idx;
    }
};
````

