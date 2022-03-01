# [335. Self Crossing](https://leetcode-cn.com/problems/self-crossing/)

## 题目

You are given an array of integers `distance`.

You start at point `(0,0)` on an **X-Y** plane and you move `distance[0]` meters to the north, then `distance[1]` meters to the west, `distance[2]` meters to the south, `distance[3]` meters to the east, and so on. In other words, after each move, your direction changes counter-clockwise.

Return `true` if your path crosses itself, and `false` if it does not.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/14/selfcross1-plane.jpg)

```
Input: distance = [2,1,1,2]
Output: true
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/03/14/selfcross2-plane.jpg)

```
Input: distance = [1,2,3,4]
Output: false
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/03/14/selfcross3-plane.jpg)

```
Input: distance = [1,1,1,1]
Output: true
```

 

**Constraints:**

- `1 <= distance.length <= 105`
- `1 <= distance[i] <= 105`

## 题目大意

给定一个整数数组 distance，从 X-Y 平面上的点 (0,0) 开始，先向北移动 distance[0] 米，然后向西移动 distance[1] 米，向南移动 distance[2] 米，向东移动 distance[3] 米，持续移动。也就是说，每次移动后你的方位会发生逆时针变化。

如果发生路径交叉，返回 true，如果未发生，返回 false。

## 解题思路

这道题目的话，最初的思路，我想的是交叉就代表路径中出现的点再次出现了，所以想用判重去做，但是这样做内存消耗是很大的，就没有继续做下去，

这道题建议参考这篇题解：https://leetcode-cn.com/problems/self-crossing/solution/gong-shui-san-xie-fen-qing-kuang-tao-lun-zdrb/

这里的难点，在于思考出现交叉的所有可能的情况，然后写出判断条件

### Solution 1:

````c++
class Solution {
public:
    bool isSelfCrossing(vector<int>& distance) {
        const int len = distance.size();
        if (len < 4) {
            // 处理边界情况
            return false;
        }
        
        for (int i = 3; i < len; ++i) {
            if (distance[i] >= distance[i - 2] && distance[i - 1] <= distance[i - 3]) {
                // 相隔 2 条线
                return true;
            }
            if (i >= 4 && distance[i - 1] == distance[i - 3]
                && distance[i] + distance[i - 4] >= distance[i - 2]) {
                // 相隔 3 条线
                return true;
            }
            if (i >= 5 && distance[i - 1] <= distance[i - 3]
                && distance[i - 2] > distance[i - 4]
                && distance[i] + distance[i - 4] >= distance[i - 2]
                && distance[i - 1] + distance[i - 5] >= distance[i - 3]) {
                // 相隔 4 条线
                return true;
            }
        }
        return false;
    }
};
````

