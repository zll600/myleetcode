# [976. Largest Perimeter Triangle](https://leetcode-cn.com/problems/largest-perimeter-triangle/)

Given an integer array `nums`, return *the largest perimeter of a triangle with a non-zero area, formed from three of these lengths*. If it is impossible to form any triangle of a non-zero area, return `0`.

 

**Example 1:**

```
Input: nums = [2,1,2]
Output: 5
```

**Example 2:**

```
Input: nums = [1,2,1]
Output: 0
```

 

**Constraints:**

- `3 <= nums.length <= 104`
- `1 <= nums[i] <= 106`

## 题目大意

给定由一些正数（代表长度）组成的数组 nums ，返回 由其中三个长度组成的、面积 **不为零** 的三角形的最大周长 。如果不能形成任何面积 **不为零** 的三角形，返回 0

## 解题思路


### Solution 1:



````c++
class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        // 先排序优先取最大的
        sort(nums.begin(), nums.end());

        const int len = nums.size();
        int res = 0;
        for (int i = len - 3; i >= 0; --i) {
            if (nums[i] + nums[i + 1] > nums[i + 2]) {
                // 如果可以构成一个三角形
                res = max(res, nums[i] + nums[i + 1] + nums[i + 2]);
            }
        }

        return res;
    }
};
````
