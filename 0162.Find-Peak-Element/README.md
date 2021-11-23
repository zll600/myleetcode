# [162. Find Peak Element](https://leetcode.com/problems/find-peak-element/)

## 题目

A peak element is an element that is strictly greater than its neighbors.

Given an integer array `nums`, find a peak element, and return its index. If the array contains multiple peaks, return the index to **any of the peaks**.

You may imagine that `nums[-1] = nums[n] = -∞`.

You must write an algorithm that runs in `O(log n)` time.

 

**Example 1:**

```
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
```

**Example 2:**

```
Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `-231 <= nums[i] <= 231 - 1`
- `nums[i] != nums[i + 1]` for all valid `i`.

## 题目大意

峰值元素是指其值严格大于左右相邻值的元素。

给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞ 。

你必须实现时间复杂度为 O(log n) 的算法来解决此问题。

## 解题思路

从这道题目的限制条件中，我们可以发现数组元素都是互异的，这道题目可以联系第 852 题，不过这道题要求返回任何一个，要求更低一点

### Solution 1:

这种解法可以参考一下这篇题解：https://leetcode-cn.com/problems/find-peak-element/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-qva7v/

````c++
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        const int len = nums.size();
        if (len == 1) {
            return 0;
        }
        
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            const int mid = left + (right - left) / 2;
            
            if (nums[mid] > nums[mid + 1]) {
                // 如果 mid > mid + 1 说明左边应该可能存在峰值，继续向左搜索
                right = mid;
            } else {
                // 向右搜索
                left = mid + 1;
            }
        }
        
        return left;
    }
};
````

### Solution 2:

这种解法可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0100~0199/0162.Find-Peak-Element/

`````c++
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        const int len = nums.size();
        if (len == 1) {
            return 0;
        }
        
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            
            if ((mid == len - 1 && nums[mid - 1] < nums[mid])
                || (mid == 0 && nums[mid] > nums[mid + 1])
                || (mid > 0 && nums[mid] > nums[mid - 1] && mid < len - 1 && nums[mid] > nums[mid + 1])) {
                // 如果 mid 位于左边界或者右边界，且满足条件
                // 或者 mid 位于中间，且满足条件
                return mid;
            } else if (mid > 0 && nums[mid] > nums[mid - 1]) {
                // 如果mid 大于左边，则说明右边可能有
                left = mid + 1;
            } else if (mid > 0 && nums[mid] < nums[mid - 1]) {
                // 如果mid 大于右边，则说明左边可能有
                right = mid - 1;
            } else if (mid == left) {
                ++left;
            } else if (mid == right) {
                --right;
            }
        }
        
        return -1;
    }
};
`````

