# [1319. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/)

There are `n` computers numbered from `0` to `n - 1` connected by ethernet cables `connections` forming a network where `connections[i] = [ai, bi]` represents a connection between computers `ai` and `bi`. Any computer can reach any other computer directly or indirectly through the network.

You are given an initial computer network `connections`.  You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them  directly connected.

Return *the minimum number of times you need to do this in order to make all the computers connected*. If it is not possible, return `-1`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/01/02/sample_1_1677.png)

```
Input: n = 4, connections = [[0,1],[0,2],[1,2]]
Output: 1
Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/01/02/sample_2_1677.png)

```
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
Output: 2
```

**Example 3:**

```
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
Output: -1
Explanation: There are not enough cables.
```

 

**Constraints:**

- `1 <= n <= 105`
- `1 <= connections.length <= min(n * (n - 1) / 2, 105)`
- `connections[i].length == 2`
- `0 <= ai, bi < n`
- `ai != bi`
- There are no repeated connections.
- No two computers are connected by more than one cable.

## 

用以太网线缆将 `n` 台计算机连接成一个网络，计算机的编号从 `0` 到 `n-1`。线缆用 `connections` 表示，其中 `connections[i] = [a, b]` 连接了计算机 `a` 和 `b`。

网络中的任何一台计算机都可以通过网络直接或者间接访问同一个网络中其他任意一台计算机。

给你这个计算机网络的初始布线 `connections`，你可以拔开任意两台直连计算机之间的线缆，并用它连接一对未直连的计算机

请你计算并返回使所有计算机都连通所需的最少操作次数。如果不可能，则返回 -1 。

## 解题思路

这道题目还是比较容易想到使用 并查集的，connections 数组中可能存在冗余链接，需要计算出冗余连接数和连通分量的个数来判断能否全部连通，

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1300~1399/1319.Number-of-Operations-to-Make-Network-Connected/)

根据 connections 数组更新连通分量，统计冗余链接，这里注意需要链接的操作数是 连通分量的总数 - 1，

````c++
class UnionFind {
 public:
    UnionFind(int n) : cnt_(n), data_(std::move(vector<int>(n))) {
        for (int i = 0; i < n; ++i) {
            data_[i] = i;
        }
    }
    
    int Find(int x) {
        while (x != data_[x]) {
            data_[x] = data_[data_[x]];
            x = data_[x];
        }
        return x;
    }
    
    void Union(int x, int y) {
        int root_x = Find(x);
        int root_y = Find(y);
        
        if (root_x == root_y) {
            return;
        }
        
        --cnt_;
        data_[root_x] = root_y;
    }
    
    int GetCnt() const {
        return cnt_;
    }
    
 private:
    int cnt_;
    vector<int> data_;
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        UnionFind uf(n);
        int redundance = 0;
        for (const auto& connection : connections) {
            if (uf.Find(connection[0]) == uf.Find(connection[1])) {
                redundance++;
            } else {
                uf.Union(connection[0], connection[1]);
            }
        }
        
        if (redundance < uf.GetCnt() - 1) {
            return -1;
        }
        
        return uf.GetCnt() - 1;
    }
};
````
