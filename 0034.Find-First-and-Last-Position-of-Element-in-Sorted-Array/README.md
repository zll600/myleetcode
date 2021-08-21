# [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

## 题目

Given an array of integers `nums` sorted in ascending order, find the starting and ending position of a given `target` value.

Your algorithm’s runtime complexity must be in the order of *O*(log *n*).

If the target is not found in the array, return `[-1, -1]`.



Example1:

```
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
```

Example2:

````
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
````

## 题目大意

给定一个已按照升序排序的整数数组，找出一个给定值的开始和结束位置的索引，你的算法时间复杂度必须是 O(logn),如果目标值不在数组中，返回 [-1, -1].

## 解题思路

* 给定一个有序数组 `nums`和`target`,找出数组中第一个和最后一个出现的和这个数相等的元素的下标，
* 二分搜索的四大基础变种题型：
  1. 查找第一个值等于给定值的元素
  2. 查找最后一个值等于给定值的元素
  3. 查找第一个值大于等于给定值的元素
  4. 查找最后一个值小于等于给定值的元素

## 代码

````c++
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {        
        if (nums.empty()) {
            return vector<int>(2, -1);
        }
        
        return vector<int>{FindFirstEqualElement(nums, target),
                          FindLastEqualElement(nums, target)};
    }
    
 private:
    // 查找第一个值等于给定值的元素，时间复杂度 O(logn)
    int FindFirstEqualElement(const vector<int>& nums, int target) {
        int size = nums.size();
        
        int low = 0;
        int high = size - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (nums[mid] > target) {
                high = mid - 1;
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                if (mid == 0 || nums[mid - 1] != target) {	// 找第一个等于给定值的元素
                    return mid;
                }
                high = mid - 1;
            }
        }
        return -1;
    }
    
    // 查找最后一个值等于给定值的元素，时间复杂度O(logn)
    int FindLastEqualElement(const vector<int>& nums, int target) {
        int size = nums.size();
        
        int low = 0;
        int high = size - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (nums[mid] > target) {
                high = mid - 1;
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                if (mid == size - 1 || nums[mid + 1] != target) {	// 找最后一个等于给定值的元素
                    return mid;
                }
                low = mid + 1;
            }
        }
        return -1;
    }
    
    // 查找第一个大于等于给定值的元素，时间复杂度O(logn)
    int FindFirstGreaterElement(const vector<int>& nums, int target) {
        int size = nums.size();
        
        int low = 0;
        int high = size - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (nums[mid] >=target) {
                if (mid == 0 || nums[mid - 1] < target) {	// 找第一个大于等于给定值的元素
                    return mid;
                }
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }
    
    int FindLastLessElement(const vector<int>& nums, int target) {
        int size = nums.size();
        
        int low = 0;
        int high = size - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (nums[mid] <= target) {
                if (mid == size || nums[mid + 1] > target) {	// 找最后一个小于等于给定值的元素
                    return mid;
                }
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
};
````

