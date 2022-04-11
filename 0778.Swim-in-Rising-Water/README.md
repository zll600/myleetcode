# [778. Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/) 



You are given an `n x n` integer matrix `grid` where each value `grid[i][j]` represents the elevation at that point `(i, j)`.

The rain starts to fall. At time `t`, the depth of the water everywhere is `t`. You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most `t`. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.

Return *the least time until you can reach the bottom right square* `(n - 1, n - 1)` *if you start at the top left square* `(0, 0)`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/06/29/swim1-grid.jpg)

```
Input: grid = [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/06/29/swim2-grid-1.jpg)

```
Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation: The final route is shown.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
```

 

**Constraints:**

- `n == grid.length`
- `n == grid[i].length`
- `1 <= n <= 50`
- `0 <= grid[i][j] < n2`
- Each value `grid[i][j]` is **unique**.

## 题目大意

在一个 `n x n` 的整数矩阵 `grid` 中，每一个方格的值 `grid[i][j]` 表示位置 `(i, j)` 的平台高度。

当开始下雨时，在时间为 `t` 时，水池中的水位为 `t` 。

你可以从一个平台游向四周相邻的任意一个平台，但是前提是此时水位必须同时淹没这两个平台。假定你可以瞬间移动无限距离，也就是默认在方格内部游动是不耗时的。当然，在你游泳的时候你必须待在坐标方格里面。

你从坐标方格的左上平台 `(0，0)` 出发。返回 你到达坐标方格的右下平台 `(n-1, n-1)` 所需的最少时间 。

## 解题思路


### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0778.Swim-in-Rising-Water/) 

和 [这篇题解](https://leetcode-cn.com/problems/swim-in-rising-water/solution/kruskal-bing-cha-ji-by-yexiso-sue9/)

````c++
class UnionFind {
 public:
    UnionFind(int cnt) : data_(vector<int>(cnt, 0)) {
        for (int i = 0; i < cnt; ++i) {
            data_[i] = i;
        }
    }
    
    int Find(int val) {
        while (val != data_[val]) {
            data_[val] = data_[data_[val]];
            val = data_[val];
        }
        return val;
    }
    
    void Union(int x, int y) {
        int root_x = Find(x);
        int root_y = Find(y);
        data_[root_x] = root_y;
        // cout << root_x << "--> " << root_y << endl;
    }
    
    bool IsConnected(int x, int y) {
        return Find(x) == Find(y);
    }
 private:
    vector<int> data_;
};

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        const int len = grid.size();
        UnionFind un(len * len);
        int res = 0;
        
        // 直到两部分连通为止
        while (!un.IsConnected(0, len * len - 1)) {
            // 循环进行连通
            for (int i = 0; i < len; ++i) {
                for (int j = 0; j < len; ++j) {
                    if (grid[i][j] > res) {
                        continue;
                    }
                    
                    // 向下走
                    if (i < len - 1 && grid[i + 1][j] <= res) {
                        cout << i * len + j << "--" << (i + 1) * len + i << ":";
                        un.Union(i * len + j, (i + 1) * len + j);
                    }
                    // 向右走
                    if (j < len - 1 && grid[i][j + 1] <= res) {
                        // cout << i * len + j << "--" << i * len + j + 1 << ":";
                        un.Union(i * len + j, i * len + j + 1);
                    }
                }
                cout << endl;
            }
            ++res;
        }
        
        return res - 1;
    }
};
````


