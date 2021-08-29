# [81. Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)

## 题目

There is an integer array `nums` sorted in non-decreasing order (not necessarily with **distinct** values).

Before being passed to your function, `nums` is **rotated** at an unknown pivot index `k` (`0 <= k < nums.length`) such that the resulting array is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]` (**0-indexed**). For example, `[0,1,2,4,4,4,5,6,6,7]` might be rotated at pivot index `5` and become `[4,5,6,6,7,0,1,2,4,4]`.

Given the array `nums` **after** the rotation and an integer `target`, return `true` *if* `target` *is in* `nums`*, or* `false` *if it is not in* `nums`*.*

You must decrease the overall operation steps as much as possible.

 

**Example 1:**

```
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
```

**Example 2:**

```
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
```

 

**Constraints:**

- `1 <= nums.length <= 5000`
- `-104 <= nums[i] <= 104`
- `nums` is guaranteed to be rotated at some pivot.
- `-104 <= target <= 104`

 

**Follow up:** This problem is similar to [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/description/), but `nums` may contain **duplicates**. Would this affect the runtime complexity? How and why?

## 题目大意

给定一个按照非降序排列的数组（可能包含重复元素），数组经过旋转，给定一个特定的值，如果这个值在数组中，就返回对应的数组下标（下标从 0 开始），如果不存在返回 -1。

## 解题思路

* 与第33题形同这道题目也可以用“二分搜索”来做，不同的是，这道题目中数字是可以重复，这意味这，如果 pivot 的数不为一，那么旋转之后，我们就不能直接通过与左右边界的比较来得出结果，所以除了可以明确的判断之外，这道题的其他部分退化为了顺序遍历。

## 代码

````c++
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int lo = 0;
        int hi = nums.size() - 1;
        
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (nums[mid] == target) {
                return true;
            } else if (nums[mid] > nums[lo]) {      // 在数值较大的一边查找
                if (nums[lo] <= target && target < nums[mid]) {
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            } else if (nums[mid] < nums[hi]) {      // 在数值较小的一边查找
                if (nums[mid] < target && target <= nums[hi]) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            } else {           // 这里退化为顺序遍历
                if (nums[mid] == nums[lo]) {
                    ++lo;
                }
                if (nums[mid] == nums[hi]) {
                    --hi;
                }
            }
        }
        return false;
    }
};
````

