# [1232. Check If It Is a Straight Line](https://leetcode.com/problems/check-if-it-is-a-straight-line/)

## 题目大意

You are given an array `coordinates`, `coordinates[i] = [x, y]`, where `[x, y]` represents the coordinate of a point. Check if these points make a straight line in the XY plane.

 

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/10/15/untitled-diagram-2.jpg)

```
Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
Output: true
```

**Example 2:**

**![img](https://assets.leetcode.com/uploads/2019/10/09/untitled-diagram-1.jpg)**

```
Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
Output: false
```

 

**Constraints:**

- `2 <= coordinates.length <= 1000`
- `coordinates[i].length == 2`
- `-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4`
- `coordinates` contains no duplicate point.

## 题目大意

在一个 XY 坐标系中有一些点，我们用数组 `coordinates` 来分别记录它们的坐标，其中 `coordinates[i] = [x, y]` 表示横坐标为 `x`、纵坐标为 `y` 的点。

请你来判断，这些点是否在该坐标系中属于同一条直线上，是则返回 `true`，否则请返回 `false`。

## 解题思路

这是一道 几何 的题目，具体来说就是两点确定一条直线，每条直线的斜率相同就可以说明，点在同一条直线上了，另外这里将除法改为了乘法

### Solution 1:

```c++
class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        const int len = coordinates.size();	
        // 最初两点之间的斜率
        int base_dx = coordinates[1][0] - coordinates[0][0];
        int base_dy = coordinates[1][1] - coordinates[0][1];
        
        for (int i = 1; i < len - 1; ++i) {
            int dx = coordinates[i + 1][0] - coordinates[i][0];
            int dy = coordinates[i + 1][1] - coordinates[i][1];
            
            if (1L * base_dx * dy != 1L * dx * base_dy) {
              // 一处不相等，直接返回
                return false;
            }
        }
        
        return true;
    }
};
```

