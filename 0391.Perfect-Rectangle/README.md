# [391. Perfect Rectangle](https://leetcode.com/problems/perfect-rectangle/)

## 题目

Given an array `rectangles` where `rectangles[i] = [xi, yi, ai, bi]` represents an axis-aligned rectangle. The bottom-left point of the rectangle is `(xi, yi)` and the top-right point of it is `(ai, bi)`.

Return `true` *if all the rectangles together form an exact cover of a rectangular region*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/27/perectrec1-plane.jpg)

```
Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
Output: true
Explanation: All 5 rectangles together form an exact cover of a rectangular region.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/03/27/perfectrec2-plane.jpg)

```
Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
Output: false
Explanation: Because there is a gap between the two rectangular regions.
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/03/27/perfecrrec4-plane.jpg)

```
Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
Output: false
Explanation: Because two of the rectangles overlap with each other.
```

 

**Constraints:**

- `1 <= rectangles.length <= 2 * 104`
- `rectangles[i].length == 4`
- `-105 <= xi, yi, ai, bi <= 105`

## 题目大意

给你一个数组 rectangles ，其中 `rectangles[i] = [xi, yi, ai, bi]` 表示一个坐标轴平行的矩形。这个矩形的左下顶点是 `(xi, yi)` ，右上顶点是 `(ai, bi)` 。

如果所有矩形一起精确覆盖了某个矩形区域，则返回 `true` ；否则，返回 `false`



## 解题思路

一开始的想法那是找到所有顶点中的左下和右上，然后计算这个面积和所有面积之和是否相等，但是这个有部分 case 过不了，这里详情见花花的题解： https://www.youtube.com/watch?v=8JM_dyOu_JY



### Solution 1:

这种解法最终要满足如下条件：

* 只有 4 个只使用了一次的顶点
* 各个矩形的面积之和等于大矩形面积之和

````c++
class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        // 这里需要利用 set 有序的特性
        set<pair<int, int>> corners;
        long area = 0; // 面积
        for (const auto& rect : rectangles) {
            // 枚举每个矩形的四个顶点，找出只出现过奇数次的点
            pair<int, int> p1{rect[0], rect[1]};
            pair<int, int> p2{rect[2], rect[1]};
            pair<int, int> p3{rect[2], rect[3]};
            pair<int, int> p4{rect[0], rect[3]};
            
            for (const auto& p : {p1, p2, p3, p4}) {
                const auto& ret = corners.insert(p);
                if (!ret.second) {
                    // 如果已经存在就删除
                    corners.erase(ret.first);
                }
            }
            // 累加面积
            area += 1L * (p3.first - p1.first) * (p3.second - p1.second);
        }
        
        if (corners.size() != 4) {
            return false;
        }
        
        const auto& p1 = *begin(corners); // 左下角
        const auto& p3 = *rbegin(corners); // 右上角
        return area == 1L * (p3.first - p1.first) * (p3.second - p1.second);
    }
};
````

