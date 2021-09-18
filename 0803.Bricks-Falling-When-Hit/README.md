# [803. Bricks Falling When Hit](https://leetcode.com/problems/bricks-falling-when-hit/)

## 题目

You are given an `m x n` binary `grid`, where each `1` represents a brick and `0` represents an empty space. A brick is **stable** if:

- It is directly connected to the top of the grid, or
- At least one other brick in its four adjacent cells is **stable**.

You are also given an array `hits`, which is a sequence of erasures we want to apply. Each time we want to erase the brick at the location `hits[i] = (rowi, coli)`. The brick on that location (if it exists) will disappear. Some other bricks may no longer be stable because of that erasure and will **fall**. Once a brick falls, it is **immediately** erased from the `grid` (i.e., it does not land on other stable bricks).

Return *an array* `result`*, where each* `result[i]` *is the number of bricks that will **fall** after the* `ith` *erasure is applied.*

**Note** that an erasure may refer to a location with no brick, and if it does, no bricks drop.

 

**Example 1:**

```
Input: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
Output: [2]
Explanation: Starting with the grid:
[[1,0,0,0],
 [1,1,1,0]]
We erase the underlined brick at (1,0), resulting in the grid:
[[1,0,0,0],
 [0,1,1,0]]
The two underlined bricks are no longer stable as they are no longer connected to the top nor adjacent to another stable brick, so they will fall. The resulting grid is:
[[1,0,0,0],
 [0,0,0,0]]
Hence the result is [2].
```

**Example 2:**

```
Input: grid = [[1,0,0,0],[1,1,0,0]], hits = [[1,1],[1,0]]
Output: [0,0]
Explanation: Starting with the grid:
[[1,0,0,0],
 [1,1,0,0]]
We erase the underlined brick at (1,1), resulting in the grid:
[[1,0,0,0],
 [1,0,0,0]]
All remaining bricks are still stable, so no bricks fall. The grid remains the same:
[[1,0,0,0],
 [1,0,0,0]]
Next, we erase the underlined brick at (1,0), resulting in the grid:
[[1,0,0,0],
 [0,0,0,0]]
Once again, all remaining bricks are still stable, so no bricks fall.
Hence the result is [0,0].
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 200`
- `grid[i][j]` is `0` or `1`.
- `1 <= hits.length <= 4 * 104`
- `hits[i].length == 2`
- `0 <= xi <= m - 1`
- `0 <= yi <= n - 1`
- All `(xi, yi)` are unique.

## 题目大意

给定一个 m x n 的二进制网格，1 代表砖块，0代表空白，一块砖如果满足下列条件就是稳定的：

* 直接和网格的顶端相连
* 四周至少有一块砖是稳定的，

给定一个数组 hits，代表我们想擦除的序列，每次我们我们想擦除位置 [row,col]，这个位置的砖块（如果存在）会消失，一些其他砖块因为不再稳定，也会掉下，每次擦出一块砖，会里掉掉落（不会掉落到其他空白位置），

返回一个结果数组，代表每次擦出掉落的砖块的数目，

注意：如果擦除的位置没有砖块，没有砖块落下

## 解题思路

* 这道题目也是图的联通性问题，不过这道题是要拆分连通分量，而不是合并，所以要逆向使用并查集
* 我们可以把**拆分连通分量**理解为**从擦除之后重建连通分量**，

## 代码

`````c++
class UF {
 public:
    UF(int n)
        : parent_(vector<int>(n)),
        size_(vector<int>(n)),
        rank_(vector<int>(n)) {
        
        for (int i = 0; i < n; ++i) {
            parent_[i] = i;
            size_[i] = 1;
        }
    }
    
    int Find(int p) {
        if (p != parent_[p]) {
            parent_[p] = Find(parent_[p]);
        }
        return parent_[p];
    }
    
    void Union(int p, int q) {
        int proot = Find(p);
        int qroot = Find(q);
        
        if (proot != qroot) {   // 这里也需要秩优化
            if (rank_[proot] < rank_[qroot]) {
                swap(proot, qroot);
            }
            parent_[qroot] = proot;
            size_[proot] += size_[qroot];
            if (rank_[proot] == rank_[qroot]) {
                ++rank_[proot];
            }
        }
    }
    
    int GetSize(int p) {
        int root = Find(p);
        return size_[root];
    }
    
 private:
    vector<int> parent_;
    vector<int> size_;
    vector<int> rank_;
};

class Solution {
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int rows = grid.size();
        int cols = grid[0].size();
        int len = hits.size();
        vector<int> res(len);
        
        // 区分是因为打碎之后该位置为0，还是本来就是0
        vector<vector<int>> copy_grid(grid);
        // 想将需要打碎的砖在 copy_grid 中置为0
        for (auto& v : hits) {
            copy_grid[v[0]][v[1]] = 0;
        }
        
        // 网格的顶部永远不会掉落
        // 将第一行中的砖块与额外的一块连通
        // 满足稳定的第一个条件
        UF uf(rows * cols + 1);
        for (int j = 0; j < cols; ++j) {
            if (copy_grid[0][j] == 0) {
                continue;
            }
            uf.Union(rows * cols, j);
        }
        
        // 初始化并查集
        // 先将所有稳定的连通在一起
        for (int i = 1; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (copy_grid[i][j] == 0) {
                    continue;
                }
                if (copy_grid[i - 1][j] == 1) {
                    uf.Union(i * cols + j, (i - 1) * cols + j);
                }
                if (j > 0 && copy_grid[i][j - 1] == 1) {
                    uf.Union(i * cols + j, i * cols + j - 1);
                }
            }
        }
        
        // 逆序补砖
        for (int k = len - 1; k >= 0; --k) {
            int i = hits[k][0];
            int j = hits[k][1];
            
            if (grid[i][j] == 0) {
                continue;
            }
            
            // 补上之前
            int origin = uf.GetSize(rows * cols);
            
            if (i == 0) {
                uf.Union(rows * cols, i * cols + j);
            }
            
            // 每添加一块砖都要更新它周围的四块
            for (auto& dir : dirs) {
                int row = i + dir[0];
                int col = j + dir[1];
                
                if (row < 0 || row >= rows || col < 0 || col >= cols || copy_grid[row][col] == 0) {
                    continue;
                }
                uf.Union(i * cols + j, row * cols + col);
            }
            // 补上之后
            int cur = uf.GetSize(rows * cols);
            res[k] = max(0, cur - origin - 1);  // 这里还需要打碎的那块不计算在内
            copy_grid[i][j] = 1;    // 补上砖
        }
        
        return res;
    }
    
 private:
    vector<vector<int>> dirs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
};
`````

