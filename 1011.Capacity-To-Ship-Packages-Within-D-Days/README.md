# [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

## 题目

A conveyor belt has packages that must be shipped from one port to another within `days` days.

The `ith` package on the conveyor belt has a weight of `weights[i]`. Each day, we load the ship with packages on the conveyor belt (in the order given by `weights`). We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within `days` days.

 

**Example 1:**

```
Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10

Note that the cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.
```

**Example 2:**

```
Input: weights = [3,2,2,4,1,4], days = 3
Output: 6
Explanation: A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2
2nd day: 2, 4
3rd day: 1, 4
```

**Example 3:**

```
Input: weights = [1,2,3,1,1], days = 4
Output: 3
Explanation:
1st day: 1
2nd day: 2
3rd day: 3
4th day: 1, 1
```

 

**Constraints:**

- `1 <= days <= weights.length <= 5 * 104`
- `1 <= weights[i] <= 500`

## 题目大意

传送带上的包裹必须在 days 天内，从一个港口送到另一个港口，第 i 个包裹的重量是 weight[i]，每天我们都会按照给出重量的顺序，向传送带上装货物，我们装载的重量不会超过船的最大载重量，

返回在 days 天内能将传送代上的物品运送到船的最低运载能力，

## 解题思路

* 这道题目可以用“二分搜索”来解决，和第410 题很像，我直接抄了第 410 题的代码，

## 代码

````c++
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int lo = 0;
        int hi = 0;
        for (int it : weights) {
            hi += it;
            if (it > lo) {
                lo = it;
            }
        }
        
        if (D == 1) {
            return hi;
        }
        
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (Check(weights, mid, D)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        
        return lo;
    }
    
private:
    
    bool Check(const vector<int>& weights, int mid, int D) {
        int sum = 0;
        int count = 1;
        
        for (int it : weights) {
            sum += it;
            
            if (sum > mid) {
                sum = it;
                ++count;
                if (count > D) {
                    return false;
                }
            }
        }
        return true;
    }
};
````



