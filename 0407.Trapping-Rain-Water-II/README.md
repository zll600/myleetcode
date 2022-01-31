# [407. Trapping Rain Water II](https://leetcode-cn.com/problems/trapping-rain-water-ii/)

## 题目

Given an `m x n` integer matrix `heightMap` representing the height of each unit cell in a 2D elevation map, return *the volume of water it can trap after raining*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/08/trap1-3d.jpg)

```
Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
Output: 4
Explanation: After the rain, water is trapped between the blocks.
We have two small ponds 1 and 3 units trapped.
The total volume of water trapped is 4.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/04/08/trap2-3d.jpg)

```
Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
Output: 10
```

 

**Constraints:**

- `m == heightMap.length`
- `n == heightMap[i].length`
- `1 <= m, n <= 200`
- `0 <= heightMap[i][j] <= 2 * 104`

## 题目大意

给你一个 `m x n` 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水。

 

## 解题思路

一般来讲会采用从当前块开始向其他块进行遍历，然后找到四周最小的一个，判断能否灌水，但是这样复杂度可能会比较高，那么换个方向，从四周到中间灌水，


### Solution 1:

下面这个是我的解法，但是还是有问题，留待以后修正吧，代码中加的注释有详细的解释

这种解法，可以参考 [这篇题解](https://leetcode-cn.com/problems/trapping-rain-water-ii/solution/you-xian-dui-lie-de-si-lu-jie-jue-jie-yu-shui-ii-b/)，可以好好看看评论中的理解

````c++
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        m_ = heightMap.size();
        n_ = heightMap[0].size();
        
        // 访问数组
        vector<vector<bool>> visited(m_, vector<bool>(n_));
        // 比较函数，这里使用元组的第三个数来
        auto cmp = [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
            return get<2>(a) > get<2>(b);
        };
        // 这里使用小顶堆 可以做大，只要遍历的块小于堆顶，那么一定小于堆中的其他元素，也就是小于当前块的周围
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp)> que(cmp);
        
        // 先将所有的最外围加入到集合中
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                if (i == 0 || i == m_ - 1 || j == 0 || j == n_ - 1) {
                    que.emplace(i, j, heightMap[i][j]);
                }
            }
        }
        
        int res = 0;
        while (!que.empty()) {
            // 拿出堆顶
            auto cur = que.top();
            que.pop();
            
            for (int i = 0; i < 4; ++i) {
                int nx = get<0>(cur) + dirs_[i];
                int ny = get<1>(cur) + dirs_[i + 1];
                
                if (nx >= 0 && nx < m_ && ny >= 0 && ny < n_ && !visited[nx][ny]) {
                    // 先判断更新后的位置是否有效，且没有访问过，才进行访问
                    if (get<2>(cur) > heightMap[nx][ny]) {
                        // 如果可以这个新位置可以接水
                        res += get<2>(cur) - heightMap[nx][ny];
                    }
                    // 这里高度取最大的
                    que.emplace(nx, ny, max(heightMap[nx][ny], get<2>(cur)));
                    visited[nx][ny] = true; // 记录已经访问过了
                }
            }
        }
        return res;
    }
    
 private:
    int m_;
    int n_;
    vector<int> dirs_ = {-1, 0, 1, 0, -1};
};
````
