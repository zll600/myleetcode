# [836. Rectangle Overlap](https://leetcode.com/problems/rectangle-overlap/)

## 题目

An axis-aligned rectangle is represented as a list `[x1, y1, x2, y2]`, where `(x1, y1)` is the coordinate of its bottom-left corner, and `(x2, y2)` is the coordinate of its top-right corner. Its top and bottom edges are parallel to the X-axis, and its left and right edges are parallel to the Y-axis.

Two rectangles overlap if the area of their intersection is **positive**. To be clear, two rectangles that only touch at the corner or edges do not overlap.

Given two axis-aligned rectangles `rec1` and `rec2`, return `true` *if they overlap, otherwise return* `false`.

 

**Example 1:**

```
Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
Output: true
```

**Example 2:**

```
Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
Output: false
```

**Example 3:**

```
Input: rec1 = [0,0,1,1], rec2 = [2,2,3,3]
Output: false
```

 

**Constraints:**

- `rect1.length == 4`
- `rect2.length == 4`
- `-109 <= rec1[i], rec2[i] <= 109`
- `rec1` and `rec2` represent a valid rectangle with a non-zero area.

## 题目大意

矩形以列表 [x1, y1, x2, y2] 的形式表示，其中 (x1, y1) 为左下角的坐标，(x2, y2) 是右上角的坐标。

如果相交的面积为正，则称两矩形重叠。需要明确的是，只在角或边接触的两个矩形不构成重叠。

给出两个矩形，判断它们是否重叠并返回结果。

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/rectangle-overlap/solution/tu-jie-jiang-ju-xing-zhong-die-wen-ti-zhuan-hua-we/

这种题目的主要想法就是将二维转化为一维，将面积上的相交，用坐标来判断，通常转化为区间相交的问题

### Solution 1:

这里求重叠的情况比较多，所以这里通过求不重叠再取反来求，

```c++
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // x 轴方向
        bool x_overlap = !(rec1[2] <= rec2[0] || rec2[2] <= rec1[0]);
        // y 轴方向
        bool y_overlap = !(rec1[3] <= rec2[1] || rec2[3] <= rec1[1]);
        
        return x_overlap && y_overlap;
    }
};
```

