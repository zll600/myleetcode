# [497. Random Point in Non-overlapping Rectangles](https://leetcode.com/problems/random-point-in-non-overlapping-rectangles)

## 题目

You are given an array of non-overlapping axis-aligned rectangles `rects` where `rects[i] = [ai, bi, xi, yi]` indicates that `(ai, bi)` is the bottom-left corner point of the `ith` rectangle and `(xi, yi)` is the top-right corner point of the `ith` rectangle. Design an algorithm to pick a random integer point inside the space covered by one of the given rectangles. A point on the perimeter of a rectangle is included in the space covered by the rectangle.

Any integer point inside the space covered by one of the given rectangles should be equally likely to be returned.

**Note** that an integer point is a point that has integer coordinates.

Implement the `Solution` class:

- `Solution(int[][] rects)` Initializes the object with the given rectangles `rects`.
- `int[] pick()` Returns a random integer point `[u, v]` inside the space covered by one of the given rectangles.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/07/24/lc-pickrandomrec.jpg)

```
Input
["Solution", "pick", "pick", "pick", "pick", "pick"]
[[[[-2, -2, 1, 1], [2, 2, 4, 6]]], [], [], [], [], []]
Output
[null, [1, -2], [1, -1], [-1, -2], [-2, -2], [0, 0]]

Explanation
Solution solution = new Solution([[-2, -2, 1, 1], [2, 2, 4, 6]]);
solution.pick(); // return [1, -2]
solution.pick(); // return [1, -1]
solution.pick(); // return [-1, -2]
solution.pick(); // return [-2, -2]
solution.pick(); // return [0, 0]
```

 

**Constraints:**

- `1 <= rects.length <= 100`
- `rects[i].length == 4`
- `-109 <= ai < xi <= 109`
- `-109 <= bi < yi <= 109`
- `xi - ai <= 2000`
- `yi - bi <= 2000`
- All the rectangles do not overlap.
- At most `104` calls will be made to `pick`.

## 题目大意

给定一个由非重叠的轴对齐矩形的数组 `rects` ，其中 `rects[i] = [ai, bi, xi, yi]` 表示 `(ai, bi)` 是第 `i` 个矩形的左下角点，`(xi, yi)` 是第 `i` 个矩形的右上角角点。设计一个算法来挑选一个随机整数点内的空间所覆盖的一个给定的矩形。矩形周长上的一个点包含在矩形覆盖的空间中

在一个给定的矩形覆盖的空间内任何整数点都有可能被返回

请注意 ，整数点是具有整数坐标的点

实现 `Solution` 类:

- `Solution(int[][] rects)` 用给定的矩形数组 `rects` 初始化对象。
- `int[] pick()` 返回一个随机的整数点 `[u, v]` 在给定的矩形所覆盖的空间内。


## 解题思路

这还是一道在一定范围内进行随机选取的题目，不过这道题目是二维，所以我们要经历两次选取：

- 选出一个矩形
- 从选定的矩形中选出一个点

### Solution 1:

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/random-point-in-non-overlapping-rectangles/solution/xu-shui-chi-chou-yang-by-zhouzihong-hf5i/)

````c++
class Solution {
public:
    Solution(vector<vector<int>>& rects) : rects_(rects) {
    }
    
    vector<int> pick() {
        int total = 0;
        vector<int> select;
        for (const auto& rect : rects_) {
            int pointer_cnt = (rect[3] - rect[1] + 1) * (rect[2] - rect[0] + 1);
            total += pointer_cnt;
            if (rand() % total < pointer_cnt) {
                // 这里还是蓄水池抽样的原理，选出一个矩形
                select = rect;
            }
        }
        
        // 这里再使用一次蓄水池抽样算法，从矩形中选出一个点
        int x1 = select[0], y1 = select[1], x2 = select[2], y2 = select[3];
        int res_x = rand() % (x2 - x1 + 1) + x1;
        int res_y = rand() % (y2 - y1 + 1) + y1;
        return { res_x, res_y };
    }
    
 private:
    vector<vector<int>> rects_;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 *
````
