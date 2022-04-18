# [871. Minimum Number of Refueling Stops](https://leetcode-cn.com/problems/minimum-number-of-refueling-stops/)

A car travels from a starting position to a destination which is target miles east of the starting position.

There are gas stations along the way. The gas stations are represented as an array stations where stations[i] = [positioni, fueli] indicates that the ith gas station is positioni miles east of the starting position and has fueli liters of gas.

The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it. It uses one liter of gas per one mile that it drives. When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.

Return the minimum number of refueling stops the car must make in order to reach its destination. If it cannot reach the destination, return -1.

Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there. If the car reaches the destination with 0 fuel left, it is still considered to have arrived.

 

Example 1:

Input: target = 1, startFuel = 1, stations = []
Output: 0
Explanation: We can reach the target without refueling.

Example 2:

Input: target = 100, startFuel = 1, stations = [[10,100]]
Output: -1
Explanation: We can not reach the target (or even the first gas station).

Example 3:

Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
Output: 2
Explanation: We start with 10 liters of fuel.
We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the target.
We made 2 refueling stops along the way, so we return 2.

 

Constraints:

    1 <= target, startFuel <= 109
    0 <= stations.length <= 500
    0 <= positioni <= positioni+1 < target
    1 <= fueli < 109

## 题目大意

汽车从起点出发驶向目的地，该目的地位于出发位置东面 `target` 英里处。

沿途有加油站，每个 `station[i]` 代表一个加油站，它位于出发位置东面 `station[i][0]` 英里处，并且有 `station[i][1]` 升汽油。

假设汽车油箱的容量是无限的，其中最初有 `startFuel` 升燃料。它每行驶 `1` 英里就会用掉 `1` 升汽油。

当汽车到达加油站时，它可能停下来加油，将所有汽油从加油站转移到汽车中。

为了到达目的地，汽车所必要的 *最低加油次数* 是多少？如果无法到达目的地，则返回 -1 。

注意：如果汽车到达加油站时剩余燃料为 `0`，它仍然可以在那里加油。如果汽车到达目的地时剩余燃料为 `0`，仍然认为它已经到达目的地。

## 解题思路

### Solution 1: DFS(TLE)

这里状态转移就是可以到达的距离，遍历的 stations 数组的位置和当前加油的次数

````c++
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        DFS(target, stations, 0, 0, startFuel);

        return res_;
    }

 private:
    int res_ = -1;
    bool DFS(int target, const vector<vector<int>>& stations, int idx, int cnt, int dis) {
        // 递归终止条件
        if (dis >= target) {
            if (res_ == -1) {
                res_ = cnt;
            } else {
                res_ = min(res_, cnt);
            }
            return true;
        }

        // 递归终止条件
        if (idx >= stations.size()) {
            return false;
        }

        // 不加油
        bool res = DFS(target, stations, idx + 1, cnt, dis);
        // 可以加油，并且加油
        if (dis >= stations[idx][0]) {
            res |= DFS(target, stations, idx + 1, cnt + 1, dis + stations[idx][1]);
        }
        return res;
    }
};
````



