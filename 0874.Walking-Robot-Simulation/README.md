# [874. Walking Robot Simulation](https://leetcode.com/problems/walking-robot-simulation/)

## 题目

A robot on an infinite XY-plane starts at point `(0, 0)` facing north. The robot can receive a sequence of these three possible types of `commands`:

- `-2`: Turn left `90` degrees.
- `-1`: Turn right `90` degrees.
- `1 <= k <= 9`: Move forward `k` units, one unit at a time.

Some of the grid squares are `obstacles`. The `ith` obstacle is at grid point `obstacles[i] = (xi, yi)`. If the robot runs into an obstacle, then it will instead stay in its current location and move on to the next command.

Return *the **maximum Euclidean distance** that the robot ever gets from the origin **squared** (i.e. if the distance is* `5`*, return* `25`*)*.

**Note:**

- North means +Y direction.
- East means +X direction.
- South means -Y direction.
- West means -X direction.

 

**Example 1:**

```
Input: commands = [4,-1,3], obstacles = []
Output: 25
Explanation: The robot starts at (0, 0):
1. Move north 4 units to (0, 4).
2. Turn right.
3. Move east 3 units to (3, 4).
The furthest point the robot ever gets from the origin is (3, 4), which squared is 32 + 42 = 25 units away.
```

**Example 2:**

```
Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
Output: 65
Explanation: The robot starts at (0, 0):
1. Move north 4 units to (0, 4).
2. Turn right.
3. Move east 1 unit and get blocked by the obstacle at (2, 4), robot is at (1, 4).
4. Turn left.
5. Move north 4 units to (1, 8).
The furthest point the robot ever gets from the origin is (1, 8), which squared is 12 + 82 = 65 units away.
```

**Example 3:**

```
Input: commands = [6,-1,-1,6], obstacles = []
Output: 36
Explanation: The robot starts at (0, 0):
1. Move north 6 units to (0, 6).
2. Turn right.
3. Turn right.
4. Move south 6 units to (0, 0).
The furthest point the robot ever gets from the origin is (0, 6), which squared is 62 = 36 units away.
```

 

**Constraints:**

- `1 <= commands.length <= 104`
- `commands[i]` is either `-2`, `-1`, or an integer in the range `[1, 9]`.
- `0 <= obstacles.length <= 104`
- `-3 * 104 <= xi, yi <= 3 * 104`
- The answer is guaranteed to be less than `231`.

## 题目大意

机器人在一个无限大小的 `XY` 网格平面上行走，从点 `(0, 0)` 处开始出发，面向北方。该机器人可以接收以下三种类型的命令 `commands` ：

- 2 ：向左转 90 度
- -1 ：向右转 90 度
- 1 <= x <= 9 ：向前移动 x 个单位长度

在网格上有一些格子被视为障碍物 `obstacles` 。第 `i` 个障碍物位于网格点 `obstacles[i] = (xi, yi)` 。

机器人无法走到障碍物上，它将会停留在障碍物的前一个网格方块上，但仍然可以继续尝试进行该路线的其余部分。

返回从原点到机器人所有经过的路径点（坐标为整数）的最大欧式距离的平方。（即，如果距离为 5 ，则返回 25 ）

注意：

- 北表示 +Y 方向。
- 东表示 +X 方向。
- 南表示 -Y 方向。
- 西表示 -X 方向。

## 解题思路

这里的难点在于如何表示机器人的状态，主要可以表示出机器人的状态，然后根据命令进行相应的状态转移就可以得到结果

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0874.Walking-Robot-Simulation/)

这里可以这样表示机器人的状态

````c++

cur_x, cur_y 表示当前位置
direction 表示方向 0,1,2,3 分别表示 北，东，南，西

direction_x = {0, 1, 0, -1} 表示每一次的步进
direction_y = {1, 0, -1, 0} 表示每一次的步进

```


````c++
struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const pair<T1, T2>& item) const {
        auto p1 = std::hash<T1>{}(item.first);
        auto p2 = std::hash<T2>{}(item.second);

        return p1 ^ p2;
    }
};

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // 加速查找
        unordered_set<pair<int, int>, PairHash> obstacles_set;
        for (const auto& obstacle : obstacles) {
            if (!obstacle.empty()) {
                obstacles_set.emplace(obstacle[0], obstacle[1]);
            }
        }

        int res = 0;
        // 当前机器人的位置
        int cur_x = 0, cur_y = 0;
        // 表示方向 0,1,2,3 对应 北，东，南，西
        int direction = 0;
        // 执行命令
        for (int command : commands) {
            if (command == -2) {
                direction = (direction + 3) % 4;
                continue;
            }
            if (command == -1) {
                direction = (direction + 1) % 4;
                continue;
            }

            while (command > 0) {
                int nx = cur_x + direct_x[direction];
                int ny = cur_y + direct_y[direction];

                auto key = make_pair(nx, ny);
                // 如果下一个位置不可达，结束这条命令的执行
                if (obstacles_set.find(key) != obstacles_set.end()) {
                    break;
                }

                res = max(res, nx * nx + ny * ny);
                cur_x = nx;
                cur_y = ny;

                --command;
            }
        }
        return res;
    }

 private:
    // 偏移数组
    const vector<int> direct_x = {0, 1, 0, -1};
    const vector<int> direct_y = {1, 0, -1, 0};

};
````
