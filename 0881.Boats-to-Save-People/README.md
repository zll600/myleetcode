# [881. Boats to Save People](https://leetcode.com/problems/boats-to-save-people/)

## 题目

You are given an array `people` where `people[i]` is the weight of the `ith` person, and an **infinite number of boats** where each boat can carry a maximum weight of `limit`. Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most `limit`.

Return *the minimum number of boats to carry every given person*.

 

**Example 1:**

```
Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)
```

**Example 2:**

```
Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)
```

**Example 3:**

```
Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)
```

 

**Constraints:**

- `1 <= people.length <= 5 * 104`
- `1 <= people[i] <= limit <= 3 * 104`

## 题目大意

给定一个关于人的重量的数组和每条船的最大承载量，返回要装下这么多人最少需要多少船

## 解题思路

先对输入数组进行排序，然后双指针一左一右进行遍历，如果两个指针所指元素之和大于limit，则只将右指针左移，否则，将左指针右移，将右指针左移，

每次循环都要更新船的数量

## 代码

````c++
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        if (limit < 1) {
            return 0;
        }
        int size = people.size();
        sort(people.begin(), people.end());
        
        int res = 0;
        int left = 0;
        int right = size - 1;
        while (left <= right) {
            if (left == right) {	// 当只剩最后一个元素时，不能进行双指针相加的操作，
                ++res;
                return res;
            }
            
            if (people[left] + people[right] <= limit) {
                ++left;
                --right;
            } else {
                --right;
            }
            ++res;
        }
        
        return res;
    }
};
````

