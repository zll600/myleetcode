# [1094. Car Pooling](https://leetcode.cn/problems/car-pooling/)

## 题目

There is a car with `capacity` empty seats. The vehicle only drives east (i.e., it cannot turn around and drive west).

You are given the integer `capacity` and an array `trips` where `trips[i] = [numPassengersi, fromi, toi]` indicates that the `ith` trip has `numPassengersi` passengers and the locations to pick them up and drop them off are `fromi` and `toi` respectively. The locations are given as the number of kilometers due east from the car's initial location.

Return `true` *if it is possible to pick up and drop off all passengers for all the given trips, or* `false` *otherwise*.

 

**Example 1:**

```
Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false
```

**Example 2:**

```
Input: trips = [[2,1,5],[3,3,7]], capacity = 5
Output: true
```

 

**Constraints:**

- `1 <= trips.length <= 1000`
- `trips[i].length == 3`
- `1 <= numPassengersi <= 100`
- `0 <= fromi < toi <= 1000`
- `1 <= capacity <= 105`



车上最初有 capacity 个空座位。车 只能 向一个方向行驶（也就是说，不允许掉头或改变方向）

给定整数 capacity 和一个数组 trips ,  trip[i] = [numPassengersi, fromi, toi] 表示第 i 次旅行有 numPassengersi 乘客，接他们和放他们的位置分别是 fromi 和 toi 。这些位置是从汽车的初始位置向东的公里数。

当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false。

 

示例 1：

输入：trips = [[2,1,5],[3,3,7]], capacity = 4
输出：false

示例 2：

输入：trips = [[2,1,5],[3,3,7]], capacity = 5
输出：true

 

提示：

    1 <= trips.length <= 1000
    trips[i].length == 3
    1 <= numPassengersi <= 100
    0 <= fromi < toi <= 1000
    1 <= capacity <= 105

## 题目大意

车上最初有 `capacity` 个空座位。车 *只能* 向一个方向行驶（也就是说，不允许掉头或改变方向）

给定整数 `capacity` 和一个数组 `trips` ,  `trip[i] = [numPassengersi, fromi, toi]` 表示第 `i` 次旅行有 `numPassengersi` 乘客，接他们和放他们的位置分别是 `fromi` 和 `toi` 。这些位置是从汽车的初始位置向东的公里数

当且仅当你可以在所有给定的行程中接送所有乘客时，返回 `true`，否则请返回 `false`

## 解题思路

### Solution 1:

这里计算出每个位置的净上车人数（可正可负），只要经过的过程中不超过容量即可

````c++
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // 利用 locations 存储每个位置的净上车人数
        map<int, int> locations;
        for (const auto& trip : trips) {
            int passengers = trip[0];
            int from = trip[1], to = trip[2];
            locations[from] += passengers;
            locations[to] -= passengers;
        }

        int cur = 0;
        auto iter = locations.cbegin();
        while (iter != locations.end()) {
            // cout << iter->first << " : " << iter->second << endl;
            cur += iter->second;
            // 如果乘客上车和下车之后，当前乘客数超过容量，直接返回即可
            if (cur > capacity) {
                return false;
            }
            ++iter;
        }
        return true;
    }
};
````





