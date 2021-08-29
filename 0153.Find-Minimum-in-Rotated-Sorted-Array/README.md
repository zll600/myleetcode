# [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

## 题目

Suppose an array of length `n` sorted in ascending order is **rotated** between `1` and `n` times. For example, the array `nums = [0,1,2,4,5,6,7]` might become:

- `[4,5,6,7,0,1,2]` if it was rotated `4` times.
- `[0,1,2,4,5,6,7]` if it was rotated `7` times.

Notice that **rotating** an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` of **unique** elements, return *the minimum element of this array*.

You must write an algorithm that runs in `O(log n) time.`

 

**Example 1:**

```
Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.
```

**Example 2:**

```
Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.
```

**Example 3:**

```
Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times. 
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 5000`
- `-5000 <= nums[i] <= 5000`
- All the integers of `nums` are **unique**.
- `nums` is sorted and rotated between `1` and `n` times.

## 题目大意

给定一个**按升序排序且没有重复元素**的数组，这个数组在某一点上进行来旋转，请找出其中的最小元素。

## 解题思路

* 暴力搜索，保存最小的值，不断更新
* 二分搜索，
  * 这道题目就相当与以某一个点为中心，将数组进行来分割并调换位置。
  * 找最小的元素其实就找到数组中第一个比前面元素小，也比后面元素小的元素，特殊情况是旋转之后，最小的元素在第一个位置或者在最后一个位置。
  * 这里还需要注意一个问题，就是在区间为左闭右开的情况下，循环退出的条件，
    * lo < hi ，如果在循环过程中不存在等价条件可以使程序直接退出的情况
    * lo <= hi，如果循环中存在等价条件，且退出循环后不符合条件（例如：返回 -1 的情况）

## 代码

````c++
class Solution {
public:
    
    // 解法一：最直接 Brute force
    /*
    int findMin(vector<int>& nums) {
        int size = nums.size();
        
        int res = nums[0];
        for (int i = 1; i < size; ++i) {
            if (res > nums[i]) {
                res = nums[i];
            }
        }
        
        return res;
    }*/
    
     // 解法二：二分搜索
    int findMin(vector<int>& nums) {
        int lo = 0;
        int hi = nums.size() - 1;   
        
        while (lo < hi) {   // 因为区间长度为 1 的时候退出，因为没有相等的条件可以判断出结果。
            if (nums[lo] < nums[hi]) { // 例如，[1,2,3,4]旋转后出现 [1, 2, 3, 4] 的特殊情况
                return nums[lo];
            }
            
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= nums[lo]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        
        return nums[lo];
    }
    
    // 解法三：二分法
    int findMin(vector<int>& nums) {
        int size = nums.size();
        if (size == 1) {
            return nums[0];
        }
        if (nums[size - 1] > nums[0]) {
            return nums[0];
        }
        
        int lo = 0;
        int hi = size - 1;
        while (lo <= hi) {
            if (nums[lo] < nums[hi]) {
                return nums[lo];
            }
            
            int mid = lo + (hi - lo) / 2;
            if ((mid == size - 1 && nums[mid - 1] > nums[mid])
               || mid < size && mid > 0 && nums[mid + 1] > nums[mid] && nums[mid - 1] > nums[mid]) {
                return nums[mid];
            }
            
            if (nums[mid] > nums[lo] && nums[lo] > nums[hi]) {  //  mid 在数值大的一边
                lo = mid + 1;
            } else if (nums[mid] < nums[lo] && nums[lo] > nums[hi]) {   // mid 在数值小的一边
                hi = mid - 1;
            } else {
                if (nums[mid] == nums[lo]) {
                    ++lo;
                }
                if (nums[hi] == nums[mid]) {
                    --hi;
                }
            }
        }
        
        return -1;
    }
};
````

