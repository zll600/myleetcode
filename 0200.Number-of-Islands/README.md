# [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)

Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return *the number of islands*.

An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

**Example 1:**

```
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
```

**Example 2:**

```
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 300`
- `grid[i][j]` is `'0'` or `'1'`.

## 题目大意

给定一个由“1（陆地）”，“0（水）”组成的二维网格，返回岛屿的数目，一个岛被水包围，由垂直或者水平链接的岛屿构成，你可以认为岛屿的四周都是水，

## 解题思路

* 这道题可以类比第 733题使用DFS 来解决，同样不需要撤销对状态的改变，
* 这道题目也可以使用 BFS 来求解
* 这道题目还可以使用 并查集来解决（留待以后更新）

## 代码

````c++
class Solution {
 public:
    int numIslands(vector<vector<char>>& grid) {
        rows = grid.size();
        cols = grid[0].size();
        
        vector<vector<bool>> visit(rows, vector<bool>(cols, false));
        int res = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!visit[i][j] && grid[i][j] == '1') {    // 剪枝条件
                    //Search(grid, visit, i, j);
                    BFS(grid, visit, i, j);
                    ++res;
                }
            }
        }
        
        return res;
    }
 private:
    int rows;
    int cols;
    
    vector<vector<int>> dirs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    bool IsValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
    
    // DFS
    void Search(const vector<vector<char>>& grid, vector<vector<bool>>& visit,
               int x, int y) {
        if (grid[x][y] == '0') {
            return;
        }
        
        visit[x][y] = true;
        for (const vector<int>& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            
            if (IsValid(nx, ny) && !visit[nx][ny]) {
                Search(grid, visit, nx, ny);
            }
        }
    }
    
    // BFS
    void BFS(const vector<vector<char>>& grid, vector<vector<bool>>& visit,
            int x, int y) {
        queue<pair<int, int>> que;
        que.push(make_pair(x, y));
        visit[x][y] = true;
        
        while (!que.empty()) {
            pair<int, int> item = que.front();
            que.pop();
            
            for(const vector<int>& dir : dirs) {
                int nx = item.first + dir[0];
                int ny = item.second + dir[1];
                
                if (IsValid(nx, ny) && !visit[nx][ny]
                   && grid[nx][ny] == '1') {
                    que.push(make_pair(nx, ny));
                    visit[nx][ny] = true;   // 这里需要注意，在放入队列时，就标记为访问过，否则会出现重复入队的情况
                }
            }
        }
    }
};
````

## 解题思路

* 这道题可以看作是求连通分量的个数，因此可以用并查集来解决，
* 这道题目由两个部分，我们计算所有的连通分量的数目，并将所有的 0 连通，形成一个连通分量，在创建 并查集的时候，额外创建了一个节点，如果可以使用这个节点来将所有的 0，连通，
* 这里先借用以下别人的代码，以后会再次修改

## 代码

````c++
public class Solution {

    public int numIslands(char[][] grid) {
        int rows = grid.length;
        if (rows == 0) {
            return 0;
        }
        int cols = grid[0].length;
        if (cols == 0) {
            return 0;
        }

        int[][] directions = new int[][]{{0, 1}, {1, 0}};
        int size = rows * cols;
        // 多开一个结点，把 '0' 都与最后这个结点连在一起
        UnionFind unionFind = new UnionFind(size + 1);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    for (int[] direction : directions) {
                        int newX = i + direction[0];
                        int newY = j + direction[1];
                        if (inArea(newX, newY, rows, cols) && grid[newX][newY] == '1') {
                            unionFind.union(getIndex(i, j, cols), getIndex(newX, newY, cols));
                        }
                    }
                } else {
                    unionFind.union(getIndex(i, j, cols), size);
                }
            }
        }
        return unionFind.getCount() - 1;
    }


    private class UnionFind {

        private int[] parent;
        /**
         * 连通分量个数
         */
        private int count;

        public UnionFind(int n) {
            count = n;
            parent = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        public int find(int x) {
            while (x != parent[x]) {
                // 只实现了路径压缩，并且是隔代压缩
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        }

        public void union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) {
                return;
            }
            parent[rootX] = rootY;
            count--;
        }

        public int getCount() {
            return count;
        }
    }

    private boolean inArea(int x, int y, int rows, int cols) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }

    private int getIndex(int x, int y, int cols) {
        return x * cols + y;
    }
}
````

