# [688. Knight Probability in Chessboard](https://leetcode.com/problems/knight-probability-in-chessboard/)

## 题目

On an `n x n` chessboard, a knight starts at the cell `(row, column)` and attempts to make exactly `k` moves. The rows and columns are **0-indexed**, so the top-left cell is `(0, 0)`, and the bottom-right cell is `(n - 1, n - 1)`.

A chess knight has eight possible moves it can make, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.

![img](https://assets.leetcode.com/uploads/2018/10/12/knight.png)

Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly `k` moves or has moved off the chessboard.

Return *the probability that the knight remains on the board after it has stopped moving*.

 

**Example 1:**

```
Input: n = 3, k = 2, row = 0, column = 0
Output: 0.06250
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.
```

**Example 2:**

```
Input: n = 1, k = 0, row = 0, column = 0
Output: 1.00000
```

 

**Constraints:**

- `1 <= n <= 25`
- `0 <= k <= 100`
- `0 <= row, column <= n`

## 题目

在一个 n x n 的棋盘上，一个骑士开始在 (row, column) 位置，想要去移动 k 次，左上角的坐标是(0, 0)，右下角的坐标是(n - 1, n - 1)

如下图所示，国际象棋的 “马” 每一步先沿水平或垂直方向移动 2 个格子，然后向与之相垂直的方向再移动 1 个格子，共有 8 个可选的位置。

现在 “马” 每一步都从可选的位置（包括棋盘外部的）中独立随机地选择一个进行移动，直到移动了 `K` 次或跳到了棋盘外面。

求移动结束后，“马” 仍留在棋盘上的概率。

## 解题思路

### 解法1（记忆化递归）

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/knight-probability-in-chessboard/solution/sha-huan-cun-zhi-jie-gao-ding-wo-bao-zhe-3lbs/

从每个位置向 八个方向移动，如果走完 k 步且在棋盘中，就返回 1，否则返回0，

所有的方案总数是 8 的 n 次方，最终递归得到的结果 / 8 的n 次方，就是答案

````c++
class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        double total = pow(8, k);
        
        // 缓存
        vector<vector<vector<double>>> cache(k + 1, vector<vector<double>>(n, vector<double>(n)));
        double res = DFS(n, row, column, k, cache);
        
        return res / total;
    }
    
 private:
    vector<vector<int>> dirs = {
        {2, 1},
        {2, -1},
        {-2, 1},
        {-2, -1},
        {1, 2},
        {1, -2},
        {-1, 2},
        {-1, -2}
    };
    
    bool IsValid(int n, int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < n;
    }
    
    double DFS(int n, int x, int y, int k,
            vector<vector<vector<double>>>& cache) {
        if (!IsValid(n, x, y)) {
            return 0;
        }
        
        if (k == 0) {
            return 1;
        }
        
        if (cache[k][x][y] != 0) {
            return cache[k][x][y];
        }
        
        // 向八个方向移动
        double res = 0;
        for (vector<int>& dir : dirs) {
            res += DFS(n, x + dir[0], y + dir[1], k - 1, cache);  // 这里如果用 int，可能发生溢出
        }
        cache[k][x][y] = res;
        return res;
    }
};
````

