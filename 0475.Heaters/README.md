# [475. Heaters](https://leetcode.com/problems/heaters/) 

## 题目

Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.

Every house can be warmed, as long as the house is within the heater's warm radius range. 

Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.

Notice that all the heaters follow your radius standard, and the warm radius will the same.

 

Example 1:

Input: houses = [1,2,3], heaters = [2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:

Input: houses = [1,2,3,4], heaters = [1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
Example 3:

Input: houses = [1,5], heaters = [2]
Output: 3
 

Constraints:

1 <= houses.length, heaters.length <= 3 * 104
1 <= houses[i], heaters[i] <= 109

## 题目大意

冬季已经来临。 你的任务是设计一个有固定加热半径的供暖器向所有房屋供暖。现在，给出位于一条水平线上的房屋和供暖器的位置，找到可以覆盖所有房屋的最小加热半径。所以，你的输入将会是房屋和供暖器的位置。你将输出供暖器的最小加热半径。

## 解题思路

有点像木桶效应，这里必须找出距离最近的供暖器最远的房屋之间的距离，

### Solution 1: 暴力解法

从每一个位置开始判断，每个位置找最近的供暖器，整体找最远的

````c++
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        // 先将两个集合排序
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        const int len = max(houses.back(), heaters.back());
        vector<bool> is_heaters(len + 1, false);
        
        for (int heater : heaters) {
            is_heaters[heater] = true;
        }
        
        int res = 0;
        const int size = houses.size();
        for (int i = 0; i < size; ++i) {
            // 对每间房屋找到最近的供暖器
            int left = houses[i];
            while (left > 0 && is_heaters[left] == false) {
                --left;
            }
            int left_len = left <= 0 ? INT_MAX : houses[i] - left;
            
            int right = houses[i];
            while (right <= len && is_heaters[right] == false) {
                ++right;
            }
            int right_len = right > len ? INT_MAX : right - houses[i];
            // cout << left << " --- " << left_len << "---" << right << "---" << right_len << endl;
            res = max(res, min(left_len, right_len));
        }
        
        return res;
    }
};

````

### Solution 2: BinarySearch

这种方法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0475.Heaters/)

通过 二分查找来降低时间复杂度

````c++
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(heaters.begin(), heaters.end());
        
        int res = 0;
        for (int house : houses) {
            int heater = FindClosestHeater(house, heaters);
            int radius = abs(heater - house);
            res = max(res, radius);
        }
        return res;
    }
    
 private:
    // 二分查找，可以降低时间复杂度
    int FindClosestHeater(int house, const vector<int>& heaters) {
        int low = 0, high = heaters.size() - 1;
        if (house < heaters[low]) {
            return heaters[low];
        }
        
        if (house > heaters[high]) {
            return heaters[high];
        }
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (house == heaters[mid]) {
                return heaters[mid];
            } else if (house < heaters[mid]) {
                high = mid - 1;
            } else if (house > heaters[mid]) {
                low = mid + 1;
            }
        }
        
        return house - heaters[high] < heaters[low] - house ? heaters[high] : heaters[low];
    }
};
````
