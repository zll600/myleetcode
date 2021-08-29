# [154. Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/)

## 题目

Suppose an array of length `n` sorted in ascending order is **rotated** between `1` and `n` times. For example, the array `nums = [0,1,4,4,5,6,7]` might become:

- `[4,5,6,7,0,1,4]` if it was rotated `4` times.
- `[0,1,4,4,5,6,7]` if it was rotated `7` times.

Notice that **rotating** an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` that may contain **duplicates**, return *the minimum element of this array*.

You must decrease the overall operation steps as much as possible.

 

**Example 1:**

```
Input: nums = [1,3,5]
Output: 1
```

**Example 2:**

```
Input: nums = [2,2,2,0,1]
Output: 0
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 5000`
- `-5000 <= nums[i] <= 5000`
- `nums` is sorted and rotated between `1` and `n` times.

 

**Follow up:** This problem is similar to [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/), but `nums` may contain **duplicates**. Would this affect the runtime complexity? How and why?

## 题目大意

给定一个已排序（可能含有重复元素的）的数组，数组在某个未知的位置上经过旋转，返回这个数组的最小元素。

## 解题思路

* 这道题目和第153道题类似，可以用“二分搜索”来解决，不过含有重复元素，

## 代码

````c++
class Solution {
public:
    // 解法一：Brute force
    int findMin(vector<int>& nums) {
        int res = INT_MAX;
        
        for (int i : nums) {
            if (i < res) {
                res = i;
            }
        }
        return res;
    }
    
    // 解法二：二分法：
    /*
    int findMin(vector<int>& nums) {
        int lo = 0;
        int hi = nums.size() - 1;
        
        while (lo < hi) {
            if (nums[lo] < nums[hi]) {
                return nums[lo];
            }
            
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] > nums[lo]) {
                lo = mid + 1;
            } else if (nums[mid] == nums[lo]) {
                ++lo;
            } else {
                hi = mid;
            }
        }
        return nums[lo];
    }
    */
};
````



