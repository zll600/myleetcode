# [812. Largest Triangle Area](https://leetcode.com/problems/largest-triangle-area/)

## 题目

Given an array of points on the **X-Y** plane `points` where `points[i] = [xi, yi]`, return *the area of the largest triangle that can be formed by any three different points*. Answers within `10-5` of the actual answer will be accepted.

 

**Example 1:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/04/04/1027.png)

```
Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
Output: 2.00000
Explanation: The five points are shown in the above figure. The red triangle is the largest.
```

**Example 2:**

```
Input: points = [[1,0],[0,0],[0,1]]
Output: 0.50000
```

 

**Constraints:**

- `3 <= points.length <= 50`
- `-50 <= xi, yi <= 50`
- All the given points are **unique**.

## 题目大意

给定一个表示 `X-Y` 平面的上的点的坐标数组 `points`，其中每个点都是 `points[i] = [xi, yi]`，返回从中找出3 个不同的点可以组成的最大的三角形的面积

## 解题思路


### Solution 1: 

这里枚举所有可能的组合，然后选出最大的即可


````c++
class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        double res = 0.0;

        const int len = points.size();
        for (int i = 0; i < len - 2; ++i) {
            for (int j = i + 1; j < len - 1; ++j) {
                for (int k = j + 1; k < len; ++k) {
                    // 保留最大值
                    res = max(res, Area(points[i], points[j], points[k]));
                }
            }
        }

        return res;
    }

 private:
    // 求面积
    double Area(const vector<int>& point1, const vector<int>& point2, const vector<int>& point3) {
        return abs(point1[0] * point2[1] + point2[0] * point3[1]
                   + point3[0] * point1[1] - point1[0] * point3[1]
                   - point2[0] * point1[1] - point3[0] * point2[1]) / 2.0;
    }
};
````
