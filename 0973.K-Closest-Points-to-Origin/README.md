# [973. K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/)

## 题目

Given an array of `points` where `points[i] = [xi, yi]` represents a point on the **X-Y** plane and an integer `k`, return the `k` closest points to the origin `(0, 0)`.

The distance between two points on the **X-Y** plane is the Euclidean distance (i.e., `√(x1 - x2)2 + (y1 - y2)2`).

You may return the answer in **any order**. The answer is **guaranteed** to be **unique** (except for the order that it is in).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/03/closestplane1.jpg)

```
Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
```

**Example 2:**

```
Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
Explanation: The answer [[-2,4],[3,3]] would also be accepted.
```

 

**Constraints:**

- `1 <= k <= points.length <= 104`
- `-104 < xi, yi < 104`

## 题目大意

给定一个数组 `points` ，其中 `points[i] = [xi, yi]` 表示 `X-Y` 平面上的一个点，并且是一个整数 `k` ，返回离原点 `(0,0)` 最近的 `k` 个点。

这里，平面上两点之间的距离是 欧几里德距离 `（ √(x1 - x2)2 + (y1 - y2)2 ）`

你可以按 任何顺序 返回答案。除了点坐标的顺序之外，答案 确保 是 唯一 的。

## 解题思路


### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0973.K-Closest-Points-to-Origin/)

按照升序排序，然后返回前 k 个即可

````c++
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        //  按照距离原点的距离排序
        sort(points.begin(), points.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[0] * lhs[0] + lhs[1] * lhs[1] < rhs[0] * rhs[0] + rhs[1] * rhs[1];
        });

        // 选取前 k 个即可
        vector<vector<int>> res;
        for (int i = 0; i < k; ++i) {
            res.push_back(points[i]);
        }

        return res;
    }
};
````
