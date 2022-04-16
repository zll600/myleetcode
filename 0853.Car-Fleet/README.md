# [853. Car Fleet](https://leetcode.com/problems/car-fleet/)

## 题目

There are `n` cars going to the same destination along a one-lane road. The destination is `target` miles away.

You are given two integer array `position` and `speed`, both of length `n`, where `position[i]` is the position of the `ith` car and `speed[i]` is the speed of the `ith` car (in miles per hour).

A car can never pass another car ahead of it, but it can catch up to it and drive bumper to bumper **at the same speed**. The faster car will **slow down** to match the slower car's speed. The distance between these two cars is ignored (i.e., they are assumed to have the same position).

A **car fleet** is some non-empty set of cars driving at the same position and same speed. Note that a single car is also a car fleet.

If a car catches up to a car fleet right at the destination point, it will still be considered as one car fleet.

Return *the **number of car fleets** that will arrive at the destination*.

 

**Example 1:**

```
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet, meeting each other at 12.
The car starting at 0 does not catch up to any other car, so it is a fleet by itself.
The cars starting at 5 (speed 1) and 3 (speed 3) become a fleet, meeting each other at 6. The fleet moves at speed 1 until it reaches target.
Note that no other cars meet these fleets before the destination, so the answer is 3.
```

**Example 2:**

```
Input: target = 10, position = [3], speed = [3]
Output: 1
Explanation: There is only one car, hence there is only one fleet.
```

**Example 3:**

```
Input: target = 100, position = [0,2,4], speed = [4,2,1]
Output: 1
Explanation:
The cars starting at 0 (speed 4) and 2 (speed 2) become a fleet, meeting each other at 4. The fleet moves at speed 2.
Then, the fleet (speed 2) and the car starting at 4 (speed 1) become one fleet, meeting each other at 6. The fleet moves at speed 1 until it reaches target.
```

 

**Constraints:**

- `n == position.length == speed.length`
- `1 <= n <= 105`
- `0 < target <= 106`
- `0 <= position[i] < target`
- All the values of `position` are **unique**.
- `0 < speed[i] <= 106`

## 题目大意

`N`  辆车沿着一条车道驶向位于 `target` 英里之外的共同目的地。每辆车 `i` 以恒定的速度 `speed[i] （英里/小时）`，从初始位置 `position[i] （英里）` 沿车道驶向目的地。

一辆车永远不会超过前面的另一辆车，但它可以追上去，并与前车以相同的速度紧接着行驶。此时，我们会忽略这两辆车之间的距离，也就是说，它们被假定处于相同的位置。

车队 是一些由行驶在相同位置、具有相同速度的车组成的非空集合。注意，一辆车也可以是一个车队。即便一辆车在目的地才赶上了一个车队，它们仍然会被视作是同一个车队。

问最后会有多少车队到达目的地?

## 解题思路


### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0853.Car-Fleet/)

这里将耗时和起点绑定，利用这两个变量来确定状态，进行比较

````c++
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        const int len = position.size();

        // 存储 耗时 和 距离
        vector<pair<double, int>> cars;
        for (int i = 0; i < len; ++i) {
            cars.emplace_back((1.0 * target - position[i]) / speed[i], position[i]);
        }

        // 按照其实位置排序
        sort(cars.begin(), cars.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.second > rhs.second;
        });

        int fleets = 0;
        double last_cost_time = 0.0;
        for (int i = 0; i < len; ++i) {
            cout << cars[i].first << " --- " << cars[i].second << endl;
            // 如果起始位置靠后，而且耗时比上一辆车大，那么就可以形成一个新的车队
            if (cars[i].first > last_cost_time) {
                ++fleets;
                last_cost_time = cars[i].first;
            }
        }

        return fleets;
    }
};
````

### Solution 2:

如果这道题目没有 target 限制，那么只要靠后的车速度大于前面的车，就可以形成一个车队
