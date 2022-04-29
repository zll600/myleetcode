# [959. Regions Cut By Slashes](https://leetcode.com/problems/regions-cut-by-slashes/)

## 题目

An `n x n` grid is composed of `1 x 1` squares where each `1 x 1` square consists of a `'/'`, `'\'`, or blank space `' '`. These characters divide the square into contiguous regions.

Given the grid `grid` represented as a string array, return *the number of regions*.

Note that backslash characters are escaped, so a `'\'` is represented as `'\\'`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/12/15/1.png)

```
Input: grid = [" /","/ "]
Output: 2
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2018/12/15/2.png)

```
Input: grid = [" /","  "]
Output: 1
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2018/12/15/4.png)

```
Input: grid = ["/\\","\\/"]
Output: 5
Explanation: Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.
```

 

**Constraints:**

- `n == grid.length == grid[i].length`
- `1 <= n <= 30`
- `grid[i][j]` is either `'/'`, `'\'`, or `' '`.

## 题目大意

在由 `1 x 1` 方格组成的 `N x N` 网格 `grid` 中，每个 `1 x 1` 方块由 `/`、`\` 或空格构成。这些字符会将方块划分为一些共边的区域。(请注意，反斜杠字符是转义的，因此 `\` 用 `“\” ` 表示)返回区域的数目

## 解题思路


### Solution 1:


这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0959.Regions-Cut-By-Slashes/)

这里借助并查集的思想，来解决这个问题，最终的结果就是无法在进行合并，那么剩下的元素


````c++
class UF {
 public:
    UF(int len) : data_(vector<int>(len)), cnt_(len) {
        for (int i = 0; i < len; ++i) {
            data_[i] = i;
        }
    }

    int Find(int x) {
        while (data_[x] != x) {
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
        data_[root_x] = data_[root_y];
    }

    int Cnt() const {
        return cnt_;
    }

 private:
    vector<int> data_;
    int cnt_;
};

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        const int len = grid.size();
        UF uf(4 * len * len);

        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                switch (grid[i][j]) {
                    case '\\':
                        uf.Union(GetFaceIdx(len, i, j, 0), GetFaceIdx(len, i, j, 1));
                        uf.Union(GetFaceIdx(len, i, j, 2), GetFaceIdx(len, i, j, 3));
                        break;
                    case '/':
                        uf.Union(GetFaceIdx(len, i, j, 0), GetFaceIdx(len, i, j, 3));
                        uf.Union(GetFaceIdx(len, i, j, 2), GetFaceIdx(len, i, j, 1));
                        break;
                    case ' ':
                        uf.Union(GetFaceIdx(len, i, j, 0), GetFaceIdx(len, i, j, 1));
                        uf.Union(GetFaceIdx(len, i, j, 2), GetFaceIdx(len, i, j, 1));
                        uf.Union(GetFaceIdx(len, i, j, 2), GetFaceIdx(len, i, j, 3));
                }

                if (i < len - 1) {
                    uf.Union(GetFaceIdx(len, i, j, 2), GetFaceIdx(len, i + 1, j, 0));
                }

                if (j < len - 1) {
                    uf.Union(GetFaceIdx(len, i, j, 1), GetFaceIdx(len, i, j + 1, 3));
                }
            }
        }

        // 这里本质就是求，并查集中最终剩下多少个元素
        int res = 0;
        for (int i = 0; i < 4 * len * len; ++i) {
            if (uf.Find(i) == i) {
                ++res;
            }
        }
        // 这里表明上面的猜想是正确的
        // cout << uf.Cnt() << endl;

        return res;
    }

 private:
    int GetFaceIdx(int len, int i, int j, int k) {
        return 4 * (i * len + j) + k;
    }
};
````
