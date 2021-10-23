# [675. Cut Off Trees for Golf Event](https://leetcode-cn.com/problems/cut-off-trees-for-golf-event/)

## 题目

You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an `m x n` matrix. In this matrix:

- `0` means the cell cannot be walked through.
- `1` represents an empty cell that can be walked through.
- A number greater than `1` represents a tree in a cell that can be walked through, and this number is the tree's height.

In one step, you can walk in any of the four directions: north, east, south, and west. If you are standing in a cell with a tree, you can choose whether to cut it off.

You must cut off the trees in order from shortest to tallest. When you cut off a tree, the value at its cell becomes `1` (an empty cell).

Starting from the point `(0, 0)`, return *the minimum steps you need to walk to cut off all the trees*. If you cannot cut off all the trees, return `-1`.

You are guaranteed that no two trees have the same height, and there is at least one tree needs to be cut off.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/26/trees1.jpg)

```
Input: forest = [[1,2,3],[0,0,4],[7,6,5]]
Output: 6
Explanation: Following the path above allows you to cut off the trees from shortest to tallest in 6 steps.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/11/26/trees2.jpg)

```
Input: forest = [[1,2,3],[0,0,0],[7,6,5]]
Output: -1
Explanation: The trees in the bottom row cannot be accessed as the middle row is blocked.
```

**Example 3:**

```
Input: forest = [[2,3,4],[0,0,5],[8,7,6]]
Output: 6
Explanation: You can follow the same path as Example 1 to cut off all the trees.
Note that you can cut off the first tree at (0, 0) before making any steps.
```

 

**Constraints:**

- `m == forest.length`
- `n == forest[i].length`
- `1 <= m, n <= 50`
- `0 <= forest[i][j] <= 109`

## 题目大意

你被请来给一个要举办高尔夫比赛的树林砍树。树林由一个 m x n 的矩阵表示， 在这个矩阵中：

* 0 表示障碍，无法触碰
* 1 表示地面，可以行走
* 比 1 大的数 表示有树的单元格，可以行走，数值表示树的高度

每一步，你都可以向上、下、左、右四个方向之一移动一个单位，如果你站的地方有一棵树，那么你可以决定是否要砍倒它。

你需要按照树的高度从低向高砍掉所有的树，每砍过一颗树，该单元格的值变为 1（即变为地面）。

你将从 (0, 0) 点开始工作，返回你砍完所有树需要走的最小步数。 如果你无法砍完所有的树，返回 -1 。

可以保证的是，没有两棵树的高度是相同的，并且你至少需要砍倒一棵树。



## 解题思路

###  Solution 1:

这道题目参考花花的题解：https://zxi.mytechroad.com/blog/searching/leetcode-675-cut-off-trees-for-golf-event/

另外有一篇关于优化的题解，我觉得可以看看：https://leetcode-cn.com/problems/cut-off-trees-for-golf-event/solution/c-160ms-ti-jie-xi-shuo-chang-shu-you-hua-na-xie-sh/

核心思路就是，将所有的树收集然后进行排序，我们只能从低到高来砍，每次砍一棵树时，都要用 bfs 来更新路径

````c++
class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {    
        m_ = forest.size();
        n_ = forest[0].size();
        
        // {height, x, y}
        vector<tuple<int,int,int>> trees;
        for (int y = 0; y < m_; ++y)
            for (int x = 0; x < n_; ++x)
                if (forest[y][x] > 1)
                    trees.emplace_back(forest[y][x], x, y);
        
        // sort trees by height
        sort(trees.begin(), trees.end());
        
        // 起始位置
        int sx = 0;
        int sy = 0;
        
        // 累计的步数
        int total_steps = 0;
        
        // Move from current position to next tree to cut
        for (int i = 0; i < trees.size(); ++i) {
            int tx = get<1>(trees[i]);
            int ty = get<2>(trees[i]);
            
            int steps = BFS(forest, sx, sy, tx, ty);
            if (steps == INT_MAX) return -1;
            
            // Cut the tree, not necessary
            forest[ty][tx] = 1;
            
            // 更新结果
            total_steps += steps;
            
            // 更新起点
            sx = tx;
            sy = ty;
        }
        
        return total_steps;
        
    }    
private:
    // min steps to go from (sx,sy) to (tx,ty) based on current map
    // INT_MAX means not reachable
    int BFS(const vector<vector<int>>& forest, 
              int sx, int sy, 
              int tx, int ty) {
        
        // 方向数组
        static int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // 记录数组
        auto visited = vector<vector<int>>(m_, vector<int>(n_, 0));
        
        // {x, y}
        queue<pair<int,int>> q;
        q.emplace(sx, sy);
        
        int steps = 0;
        while (!q.empty()) {
            // 一次遍历一层
            int new_nodes = q.size();
            while (new_nodes--) {
                auto node = q.front();
                q.pop();
                // 当前位置
                const int cx = node.first;
                const int cy = node.second;
                
                // Found the shortest path
                if (cx == tx && cy == ty) 
                    return steps;
                
                for (int i = 0; i < 4; ++i) {
                    const int x = cx + dirs[i][0];
                    const int y = cy + dirs[i][1];
                    
                    // Out of bound or unwalkable
                    if (x < 0 || x == n_ 
                     || y < 0 || y == m_
                     || !forest[y][x]
                     || visited[y][x]) continue;
                    
                    // Mark x, y as visited
                    visited[y][x] = 1;                    
                    q.emplace(x, y);                
                }
            }
            ++steps;
        }
        
        // Impossible to reach
        return INT_MAX;
    }
    
    int m_;
    int n_;
};
````

