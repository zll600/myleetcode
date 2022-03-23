# [593. Valid Square](https://leetcode-cn.com/problems/valid-square/)

## 题目

Given the coordinates of four points in 2D space `p1`, `p2`, `p3` and `p4`, return `true` *if the four points construct a square*.

The coordinate of a point `pi` is represented as `[xi, yi]`. The input is **not** given in any order.

A **valid square** has four equal sides with positive length and four equal angles (90-degree angles).

 

**Example 1:**

```
Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: true
```

**Example 2:**

```
Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,12]
Output: false
```

**Example 3:**

```
Input: p1 = [1,0], p2 = [-1,0], p3 = [0,1], p4 = [0,-1]
Output: true
```

 

**Constraints:**

- `p1.length == p2.length == p3.length == p4.length == 2`
- `-104 <= xi, yi <= 104`

## 题目大意

给定2D空间中四个点的坐标 `p1, p2, p3 和 p4`，如果这四个点构成一个正方形，则返回 `true` 

点的坐标 `pi` 表示为 `[xi, yi]` 。输入 不是 按任何顺序给出的。

一个 **有效的正方形** 有四条等边和四个等角(90度角

## 解题思路

这道题目的关键在于如何判断一个正方形，这里采用的方式是，

- 正方形的四条边相等，
- 而且正方形的两条对角线相等

### Solution 1:

这里有一个需要注意的地方在于，每条边使用那两个点，如果不是很清晰的话，可以自己画个图，否则容易在计算边和对角线时，使用错误的点，

这里的排序的作用就是让我们更容易分配点去计算边，

````c++
class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<vector<int>> points = { p1, p2, p3, p4 };
        // 先按 x 排序再按照 y 排序
        sort(points.begin(), points.end(), [](const vector<int>& point1, const vector<int>& point2) {
            return point1[0] != point2[0] ? point1[0] < point2[0] : point1[1] < point2[1];
        });

        // 先计算 4 条边
        long d01 = CalcEdge(points[0], points[2]);
        if (d01 == 0) {
            return false;
        }
        long d13 = CalcEdge(points[1], points[3]);
        if (d01 != d13) {
            return false;
        }
        long d32 = CalcEdge(points[3], points[2]);
        if (d13 != d32) {
            return false;
        }
        long d20 = CalcEdge(points[2], points[0]);
        if (d32 != d20) {
            return false;
        }

        // 还有对角线
        long d03 = CalcEdge(points[0], points[3]);
        long d12 = CalcEdge(points[1], points[2]);

        return d03 == d12;
    }

 private:
    // 这里直接返回平方和即可
    long CalcEdge(const vector<int>& point1, const vector<int>& point2) {
        return 1L * (point2[1] - point1[1]) * (point2[1] - point1[1])
            + (point2[0] - point1[0]) * (point2[0] - point1[0]);
    }
};
````
