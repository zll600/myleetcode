# [1037. Valid Boomerang](https://leetcode.com/problems/valid-boomerang/)

## 题目

Given an array `points` where `points[i] = [xi, yi]` represents a point on the **X-Y** plane, return `true` *if these points are a **boomerang***.

A **boomerang** is a set of three points that are **all distinct** and **not in a straight line**.

 

**Example 1:**

```
Input: points = [[1,1],[2,3],[3,2]]
Output: true
```

**Example 2:**

```
Input: points = [[1,1],[2,2],[3,3]]
Output: false
```

 

**Constraints:**

- `points.length == 3`
- `points[i].length == 2`
- `0 <= xi, yi <= 100`

## 题目大意

回旋镖定义为一组三个点，这些点各不相同且不在一条直线上。

给出平面上三个点组成的列表，判断这些点是否可以构成回旋镖。

## 解题思路

三个点可以构成两条直线，且这两条直线有一个公共点，所以实际上只需要判断这两条直线的斜率是否相同，如果不同，就可以满足题意

这里还有一个数学技巧：由于斜率的计算是除法，还可能遇到分母为 0 的情况，那么可以转换成乘法，交叉相乘再判断是否相等，就可以省去判断分母为 0 的情况了

### Solution 1:

这道题目可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/1000~1099/1037.Valid-Boomerang/

```c++
class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points) {
        	return (points[0][0]-points[1][0])*(points[0][1]-points[2][1]) != (points[0][0]-points[2][0])*(points[0][1]-points[1][1]);
    }
};
```

