# [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/)

题目

A city's **skyline** is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return *the **skyline** formed by these buildings collectively*.

The geometric information of each building is given in the array `buildings` where `buildings[i] = [lefti, righti, heighti]`:

- `lefti` is the x coordinate of the left edge of the `ith` building.
- `righti` is the x coordinate of the right edge of the `ith` building.
- `heighti` is the height of the `ith` building.

You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height `0`.

The **skyline** should be represented as a list of "key points" **sorted by their x-coordinate** in the form `[[x1,y1],[x2,y2],...]`. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate `0` and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.

**Note:** There must be no consecutive horizontal lines of equal height in the output skyline. For instance, `[...,[2 3],[4 5],[7 5],[11 5],[12 7],...]` is not acceptable; the three lines of height 5 should be merged into one in the final output as such: `[...,[2 3],[4 5],[12 7],...]`

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/12/01/merged.jpg)

```
Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
Explanation:
Figure A shows the buildings of the input.
Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.
```

**Example 2:**

```
Input: buildings = [[0,2,3],[2,5,3]]
Output: [[0,3],[5,0]]
```

 

**Constraints:**

- `1 <= buildings.length <= 104`
- `0 <= lefti < righti <= 231 - 1`
- `1 <= heighti <= 231 - 1`
- `buildings` is sorted by `lefti` in non-decreasing order.

## 题目大意

城市的天际线是从远处看城市的所有建筑物形成的轮廓的外部轮廓，给你所有建筑物的位置和高度，请返回由这些建筑物构成的天际线

建筑物的几何信息由 buildings 数组提供，其中 `buildings[i] = [lefti, righti, heighti]`:

* left 是建筑物在 x 轴上的左边缘的坐标
* right 是建筑物在 y 轴上的右边缘的坐标
* Height 是建筑物的高度

你可以认为所有的建筑物都在高度为 0 的平坦地面上，

天际线应该由这种形式的 `[[x1,y1],[x2,y2],...]`.的关键点组成，并按照 x 坐标进行排序，每个关键点的是一段水平距离的左端点，只有最右边的是右端点，其 y 坐标为 0，标示城市的结束，最左边和最右边的建筑物之间的所有地面都被视为城市天际线的一部分，



注意：在输出的天际线中不能存在连续的高度相同的节点，例如 `[...[2 3], [4 5], [7 5], [11 5], [12 7]...]` 是不正确的答案；三条高度为 5 的线应该在最终输出中合并为一个：`[...[2 3], [4 5], [12 7], ...]`

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/the-skyline-problem/solution/you-xian-dui-lie-java-by-liweiwei1419-jdb5/

这道题目难在理解题意方面，不是很好想

### Solution 1:



````c++
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // 将所有的点转化为 「横坐标，纵坐标」的形式
        vector<pair<int, int>> building_points;
        for (const vector<int>& building : buildings) {
            building_points.push_back(make_pair(building[0], -1 * building[2])); // 这里为了区分从下到上，将左断点的高度设为负数
            building_points.push_back(make_pair(building[1], building[2]));
        }
        
        sort(building_points.begin(), building_points.end(), [](const pair<int, int> a, const pair<int, int> b) {
            if (a.first != b.first) {
                return a.first < b.first; // 按照横坐标排序
            } else {
                return a.second < b.second; // 横坐标相同的，高度大的在前
            }
        });
        
        priority_queue<int, vector<int>, greater<int>> heap; // 这里使用一个小顶堆
        unordered_map<int, int> delayed; // 收集需要延迟删除的坐标
        heap.push(0); // 最开始的时候，需要产生高度差
        int last_height = 0; // 上一次的高度
        vector<vector<int>> res; // 结果集
        for (const pair<int, int>& building_point : building_points) {
            if (building_point.first < 0) {
                // 说明此时是从下到上，纵坐标选择最大的
                heap.push(-1 * building_point.second);
            } else {
                // 延迟删除
                ++delayed[building_point.second];
            }
            
            // 这里做删除动作
            while (!heap.empty()) {
                int cur_height = heap.top();
                if (delayed.find(cur_height) != delayed.end()) {
                    --delayed[cur_height];
                    if (delayed.at(cur_height) == 0) {
                        delayed.erase(cur_height);
                    }
                    heap.pop();
                } else {
                    break;
                }
            }
            
            int cur_height = heap.top();
            if (cur_height != last_height) {
                // 只有存在高度差的时候，才会更新结果集
                res.push_back(vector<int>{building_point.first, cur_height});
                last_height = cur_height;
            }
            
        }
        
        return res;
    }
};
````

