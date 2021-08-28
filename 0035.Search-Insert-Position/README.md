# [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/)

## 题目

Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You must write an algorithm with `O(log n)` runtime complexity.

 

**Example 1:**

```
Input: nums = [1,3,5,6], target = 5
Output: 2
```

**Example 2:**

```
Input: nums = [1,3,5,6], target = 2
Output: 1
```

**Example 3:**

```
Input: nums = [1,3,5,6], target = 7
Output: 4
```

**Example 4:**

```
Input: nums = [1,3,5,6], target = 0
Output: 0
```

**Example 5:**

```
Input: nums = [1], target = 0
Output: 0
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-104 <= nums[i] <= 104`
- `nums` contains **distinct** values sorted in **ascending** order.
- `-104 <= target <= 104`

## 题目大意

给定一个**已排序且没有重复**的数组和个一个给定值，如果存在在数组中，返回这个值所在位置的下标，如果不存在，返回这个值将被插入的位置的下标。

## 解题思路

* 参考第三十四题中提到的二分搜索的题型总结，这道题，可以理解为求**大于等于 target 的第一个元素**或者**小于等于target的最后一个值**

````c++
class Solution {
public:
    // 解法一：
    /*
    int searchInsert(vector<int>& nums, int target) {
        int size = nums.size();
        
        if (nums[size - 1] < target) { // 特殊判断
            return size;
        }
        
        int left = 0;
        int right = size;
        while (left < right) {  // left == right [left,left] 区间只有一个元素
            int mid = left + (right - left) / 2;
            
            if (nums[mid] < target) {
                left = mid + 1;
            } else  {
                right = mid;    // 这里要找出第一个大于等于target 的元素
            }
        }
        
        return left;
    }*/
    
    // 解法二：
    int searchInsert(vector<int>& nums, int target) {
        int size = nums.size();
        int left = 0;
        int right = size - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] >= target) {
                right = mid - 1;
            } else {
                if (mid == size - 1 || nums[mid + 1] >= target) {
                    return mid + 1;
                }
                left = mid + 1;
            }
        }
        
        return 0;
    }
};
````

