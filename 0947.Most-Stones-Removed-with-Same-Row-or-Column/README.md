# [947. Most Stones Removed with Same Row or Column](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/)

## 题目

On a 2D plane, we place `n` stones at some integer coordinate points. Each coordinate point may have at most one stone.

A stone can be removed if it shares either **the same row or the same column** as another stone that has not been removed.

Given an array `stones` of length `n` where `stones[i] = [xi, yi]` represents the location of the `ith` stone, return *the largest possible number of stones that can be removed*.

 

**Example 1:**

```
Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation: One way to remove 5 stones is as follows:
1. Remove stone [2,2] because it shares the same row as [2,1].
2. Remove stone [2,1] because it shares the same column as [0,1].
3. Remove stone [1,2] because it shares the same row as [1,0].
4. Remove stone [1,0] because it shares the same column as [0,0].
5. Remove stone [0,1] because it shares the same row as [0,0].
Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.
```

**Example 2:**

```
Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Explanation: One way to make 3 moves is as follows:
1. Remove stone [2,2] because it shares the same row as [2,0].
2. Remove stone [2,0] because it shares the same column as [0,0].
3. Remove stone [0,2] because it shares the same row as [0,0].
Stones [0,0] and [1,1] cannot be removed since they do not share a row/column with another stone still on the plane.
```

**Example 3:**

```
Input: stones = [[0,0]]
Output: 0
Explanation: [0,0] is the only stone on the plane, so you cannot remove it.
```

 

**Constraints:**

- `1 <= stones.length <= 1000`
- `0 <= xi, yi <= 104`
- No two stones are at the same coordinate point.

## 题目大意

在二维平面上，我们将石头放置在一些整数坐标点上。每个坐标点上最多只能有一块石头

现在，remove 操作将会移除与网格上的某一块石头共享一列或一行的一块石头

我们最多能执行多少次 remove 操作

## 解题思路

### Solution 1: Union Find

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0947.Most-Stones-Removed-with-Same-Row-or-Column/)

这里将存在共享同一行和同一列的石头连接起来，然后看最后剩下多少个节点，再进行计算即可


````c++
class UF {
 public:
    UF(int len) : data_(vector<int>(len)), count_(len) {
        for (int i = 0; i < len; ++i) {
            data_[i] = i;
        }
    }

    // 隔代压缩
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

        data_[root_x] = root_y;
        --count_;
    }

    int TotalCount() const {
        return count_;
    }

 private:
    vector<int> data_;
    int count_;
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        const int len = stones.size();
        if (len <= 1) {
            return 0;
        }

        UF uf(len);
        unordered_map<int, int> row_map, col_map;
        for (int i = 0; i < len; ++i) {\
            // 同一行
            auto it = row_map.find(stones[i][0]);
            if (it != row_map.end()) {
                uf.Union(it->second, i);
            } else {
                row_map[stones[i][0]] = i;
            }

            // 同一列
            it = col_map.find(stones[i][1]);
            if (it != col_map.end()) {
                uf.Union(it->second, i);
            } else {
                col_map[stones[i][1]] = i;
            }
        }
        cout << uf.TotalCount() << endl;

        return len - uf.TotalCount();
    }
};
````
