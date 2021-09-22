# [452. Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)

## 题目

There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array `points` where `points[i] = [xstart, xend]` denotes a balloon whose **horizontal diameter** stretches between `xstart` and `xend`. You do not know the exact y-coordinates of the balloons.

Arrows can be shot up **directly vertically** (in the positive y-direction) from different points along the x-axis. A balloon with `xstart` and `xend` is **burst** by an arrow shot at `x` if `xstart <= x <= xend`. There is **no limit** to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.

Given the array `points`, return *the **minimum** number of arrows that must be shot to burst all balloons*.

 

**Example 1:**

```
Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].
```

**Example 2:**

```
Input: points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4
Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.
```

**Example 3:**

```
Input: points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
- Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].
```

 

**Constraints:**

- `1 <= points.length <= 105`
- `points[i].length == 2`
- `-231 <= xstart < xend <= 231 - 1`

## 题目大意

在一个二维平面上有一些球形的气球，这里用一个二维数组表示气球`points[i] = [xstart, xend]` ，这个气球在水平方向上的范围处于 xstart 到 xend 之间，你不知道气球在垂直方向上的坐标

一支弓箭可以沿着 x 轴从不同点完全垂直地射出。在坐标 `x` 处射出一支箭，若有一个气球的直径的开始和结束坐标为 `xstart`，`xend`， 且满足  `xstart ≤ x ≤ xend`，则该气球会被引爆。可以射出的弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前进。我们想找到使得所有气球全部被引爆，所需的弓箭的最小数量。

给你一个数组 points ，其中 points [i] = [xstart,xend] ，返回引爆所有气球所必须射出的最小弓箭数。

## 解题思路

这道题强烈建议画图，将气球表示为一个线段范围为[xstart, xend]，不同的选段可以有重合的部分，

这道题目可以利用贪心的思想来做，我们要做的就是尽可能让更多的区间重合，

这道题我才用的按照右边界来进行排序，保存当前的右边界，如果后面的的气球的左边界都在这个范围内，就表示只用一支箭就可以打爆所有气球，负责需要更多的箭。

## 代码

`````c++
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        // 先将所有的气球按照其右边界进行升序排序
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) -> bool {
            return a[1] < b[1];
        });
        
        int res = 0;
        int i = 0;
        while (i < points.size()) {
            int right_bound = points[i][1]; // 保存当前的右边界
            ++i;
            // 对于while 循环改变 i 一定要检查是否发生越界
            while (i < points.size() && points[i][0] <= right_bound) { // 计算后面有多少个左边界小于等于但前的右边界
                ++i;
            }
            ++res;  // 递增弓箭数（可能是下一个不重合了，也有可能时 i 越界了）
        }
        
        return res;
    }
};
`````



