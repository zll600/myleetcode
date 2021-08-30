# [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)

## 题目

There is an integer array `nums` sorted in ascending order (with **distinct** values).

Prior to being passed to your function, `nums` is **rotated** at an unknown pivot index `k` (`0 <= k < nums.length`) such that the resulting array is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]` (**0-indexed**). For example, `[0,1,2,4,5,6,7]` might be rotated at pivot index `3` and become `[4,5,6,7,0,1,2]`.

Given the array `nums` **after** the rotation and an integer `target`, return *the index of* `target` *if it is in* `nums`*, or* `-1` *if it is not in* `nums`.

You must write an algorithm with `O(log n)` runtime complexity.

 

**Example 1:**

```
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
```

**Example 2:**

```
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

**Example 3:**

```
Input: nums = [1], target = 0
Output: -1
```

 

**Constraints:**

- `1 <= nums.length <= 5000`
- `-104 <= nums[i] <= 104`
- All values of `nums` are **unique**.
- `nums` is guaranteed to be rotated at some pivot.
- `-104 <= target <= 104`

## 题目大意

给定一个升序且没右重复数字的数组 nums，nums 在某个位置进行来翻转，给定一个整数，如果这个整数在 nums 中，就返回它的下标，若不在就返回 -1，

你的算法时间复杂度必须在 O(logn) 级别

## 解题思路

* 看到有序序列中查找某个数字，可以想到 **二分查找**，即使经过旋转后数组变成来局部有序，也可以使用二分
* 因为这里是局部有序序列，经旋转之后，这里形成来前后有序的两个序列，具体如何划分参考代码

````c++
class Solution {
public:
    // 解法一：Brute force 时间复杂度O(n)
    /*
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        int idx = -1;
        
        for (int i = 0; i < size; ++i) {
            if (nums[i] == target) {
                idx = i;
                break;
            }
        }
        return idx;
    }
    */
    
    // 解法二： 先分割为两个有序数组，然后进行二分查找，时间复杂度O(n)
    /*
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        int pivot = -1;
        for (int i = 0; i < size - 1; ++i) {
            if (nums[i] > nums[i + 1]) {
                pivot = i;
                break;
            }
        }
        
        int res = BinarySearch(nums, 0, pivot, target);
        if (res == -1) {
            res = BinarySearch(nums, pivot + 1, size - 1, target);
        }
        
        return res;
    }
    */
    
    // 解法三：二分法，先缩小至一个有序的区间，然后继续二分
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        if (size == 1) {
            return nums[0] == target ? 0 : -1;
        }
        
        int lo = 0;
        int hi = size - 1;
        while (lo <= hi) {		// 这里取等号，通常是为了在循环中返回 mid，不取等号，一般返回跳出返回 lo 的值。
            int mid = lo + (hi - lo) / 2;		// 另一种理解，这道题是判断数是否存在在数组中，用等号，不在返回 -1
            
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > nums[lo]) {  // 落到前面较大的一段
                if (nums[lo] <= target && target < nums[mid]) {
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            } else if (nums[mid] < nums[hi]) {  // 落到后面较大的一段
                if (nums[mid] < target && target <= nums[hi]) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            } else {    // 对于边界，单独处理即可
                if (nums[lo] == nums[mid]) {
                    ++lo;
                }
                if (nums[mid] == nums[hi]) {
                    --hi;
                }
            }
        }
        
        return -1;
    }
    
 private:
    int BinarySearch(const vector<int>& nums, int lo, int hi, int target) {
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] > target) {
                hi = mid - 1;
            } else if (nums[mid] < target) {
                lo = mid + 1;
            } else {
                return mid;
            }
        }
        
        return -1;
    }
};
````



