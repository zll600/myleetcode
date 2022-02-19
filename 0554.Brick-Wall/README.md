# [554. Brick Wall](https://leetcode.com/problems/brick-wall/)

## 题目

There is a rectangular brick wall in front of you with `n` rows of bricks. The `ith` row has some number of bricks each of the same height (i.e., one unit) but they can be of different widths. The total width of each row is the same.

Draw a vertical line from the top to the bottom and cross the least bricks. If your line goes through the edge of a brick, then the brick is not considered as crossed. You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.

Given the 2D array `wall` that contains the information about the wall, return *the minimum number of crossed bricks after drawing such a vertical line*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/24/cutwall-grid.jpg)

```
Input: wall = [[1,2,2,1],[3,1,2],[1,3,2],[2,4],[3,1,2],[1,3,1,1]]
Output: 2
```

**Example 2:**

```
Input: wall = [[1],[1],[1]]
Output: 3
```

 

**Constraints:**

- `n == wall.length`
- `1 <= n <= 104`
- `1 <= wall[i].length <= 104`
- `1 <= sum(wall[i].length) <= 2 * 104`
- `sum(wall[i])` is the same for each row `i`.
- `1 <= wall[i][j] <= 231 - 1`

## 题目大意

有一个由 `n` 行砖组成的矩形，第 `ith` 由一些一样高度的砖，但是有不同的宽度，每一行的总计宽度都相同，从顶到底画一条垂直的先经过最少的砖块，如果你的线经过了砖的边缘，被认为是没有经过，你不能画一条线从墙的边缘经过，这种情况是为没有经过任何砖块，

给定一个 2D 数组 `wall` 包含了墙的所有信息，返回 画一条直线所经过的最小的砖块的数目，

## 解题思路

这道题目正向求解的话不是很容易,因为我们要求解空隙最多的位置,反向来求解的话,我们求出重复部分最多的位置,也就是经过的砖块睡最少的部门,


### Solution 1: HashTable

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/brick-wall/solution/gong-shui-san-xie-zheng-nan-ze-fan-shi-y-gsri/)

主要就是因为如果我们从正面来考虑所有可能的结果的时候,实现可能会比较复杂,所以这里从逆向来考虑

````c++
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        // 统计每个缝隙出现的频数,我们选择频数最大的位置,说明经过的砖块少
        unordered_map<int, int> freq;
        
        // 统计频数
        for (const vector<int>& nums : wall) {
            int tmp = 0;
            for (const int num : nums) {
                tmp += num;
                ++freq[tmp];
            }
            // 不能沿着墙的两条垂直边缘来画直线
            freq.erase(tmp);
        }
        
        // 寻找频数最小的那个
        const int len = wall.size();
        int res = len;
        for (const auto& item : freq) {
            res = min(res, len - item.second);
        }
        
        return res;
    }
};
````




