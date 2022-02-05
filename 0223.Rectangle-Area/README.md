# [223. Rectangle Area](https://leetcode.com/problems/rectangle-area/)

## 题目

Given the coordinates of two **rectilinear** rectangles in a 2D plane, return *the total area covered by the two rectangles*.

The first rectangle is defined by its **bottom-left** corner `(ax1, ay1)` and its **top-right** corner `(ax2, ay2)`.

The second rectangle is defined by its **bottom-left** corner `(bx1, by1)` and its **top-right** corner `(bx2, by2)`.

 

**Example 1:**

![Rectangle Area](https://assets.leetcode.com/uploads/2021/05/08/rectangle-plane.png)

```
Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
Output: 45
```

**Example 2:**

```
Input: ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2, bx1 = -2, by1 = -2, bx2 = 2, by2 = 2
Output: 16
```

 

**Constraints:**

- `-104 <= ax1, ay1, ax2, ay2, bx1, by1, bx2, by2 <= 104`

## 题目大意

在二维平面上计算出两个由直线构成的矩形重叠后形成的总面积。每个矩形由其左下顶点和右上顶点坐标表示，如图所示。说明: 假设矩形面积不会超出 int 的范围。

## 解题思路

这道题目可以说是一道几何的题目，难点主要在于在坐标轴上，确定重叠矩形的左下角和右下角的坐标

### Solution 1:

这种解法可以参考霜神的解法：https://books.halfrost.com/leetcode/ChapterFour/0200~0299/0223.Rectangle-Area/

代码中为了解释清楚，我将得到坐标的语句分开写，这个其实都可以的

````c++
class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int cx1 = max(ax1, bx1); // 左下角的 x 轴取二者中较大的
        int cy1 = max(ay1, by1); // 左下角的 y 轴中取二者中较大的
        int cx2 = min(ax2, bx2); // 右上角的 x 轴取二者中较小的一个
        int cy2 = min(ay2, by2); // 右上角的 y 轴取二者中小的一个
        
        return Area(ax1, ay1, ax2, ay2) + Area(bx1, by1, bx2, by2) - Area(cx1, cy1, cx2, cy2);
    }
    
 private:
    int Area(int x1, int y1, int x2, int y2) {
        int l = x2 - x1; // 右边总大于左边
        int h = y2 - y1; // 上边总大于下边
        
        if (l <= 0 || h <= 0) { // 特殊情况
            return 0;
        }
        
        return l * h;
    }
};
````

