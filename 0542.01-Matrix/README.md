# [542. 01 Matrix](https://leetcode.com/problems/01-matrix/)

## 题目

Given an `m x n` binary matrix `mat`, return *the distance of the nearest* `0` *for each cell*.

The distance between two adjacent cells is `1`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/24/01-1-grid.jpg)

```
Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/04/24/01-2-grid.jpg)

```
Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]
```

 

**Constraints:**

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n <= 104`
- `1 <= m * n <= 104`
- `mat[i][j]` is either `0` or `1`.
- There is at least one `0` in `mat`.

## 题目大意

给定一个 m x n的二进制矩阵，返回每个格子中，到最近0 的距离，两个相邻格子之间的距离为 1，

## 解题思路

这道题可以参考霜神的解法：

https://books.halfrost.com/leetcode/ChapterFour/0500~0599/0542.01-Matrix/

### Solution 1: BFS

具体的做法是：

* 生成一个新的矩阵（用来存储结果）和一个队列（进行广搜），遍历整个矩阵，将值为 0 的位置标记为 -1，同时加入到队列中
* 广度优先搜索，取出每一个值为 -1 （原值为0） 的位置，然后向四个方向进行状态转移，改变值为0 的地方，之后的遍历之前改变过的位置，不会再改变
* 将所有的 -1 恢复为 0

````c++
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        rows_ = mat.size();
        cols_ = mat[0].size();
        
        // 结果集
        vector<vector<int>> res(rows_, vector<int>(cols_, 0));
        // BFS 队列
        queue<pair<int, int>> que;
        // 预处理，将矩阵为 0 的元素置为 -1，
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (mat[i][j] == 0) {
                    res[i][j] = -1;
                    que.push(make_pair(i, j));
                }
            }
        }
        
        int level = 1;  // 距最近的 0 的位置
        while(!que.empty()) {
            const int size = que.size();  // 遍历上一次所有元素
            for (int i = 0; i < size; ++i) {
                // 取出一个进行状态转移
                pair<int, int> item = que.front();
                que.pop();
                int x = item.first;
                int y = item.second;
                
                for (const auto& dir : dirs_) {
                    int nx = x + dir[0];
                    int ny = y + dir[1];
                    
                    // 跳过的情况：
                    // 1. 下标不合法的
                    // 2. 值为 -1（原值为 0）
                    // 3. 值大于 1（已经赋过值了），对于要求的位置，我们只保留第一次的值，也就最小的一次
                    if (!IsInMatrix(nx, ny) || res[nx][ny] < 0 || res[nx][ny] > 0) {
                        continue;
                    }
                    
                    res[nx][ny] = level;
                    que.push(make_pair(nx, ny));
                }
            }
            ++level;
        }
        
        // 恢复
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j  < cols_; ++j) {
                if (res[i][j] == -1) {
                    res[i][j] = 0;
                }
            }
        }
        
        return res;
    }
    
 private:
    vector<vector<int>> dirs_ = {
        {1, 0},
        {-1, 0},
        {0, -1},
        {0, 1}
    };
    
    int rows_;
    int cols_;
    
    bool IsInMatrix(int x, int y) {
        return x >= 0 && x < rows_ && y >= 0 && y < cols_;
    }
};
````

