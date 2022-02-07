# [540. Single Element in a Sorted Array](https://leetcode-cn.com/problems/single-element-in-a-sorted-array/)

## 题目

You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.

Return *the single element that appears only once*.

Your solution must run in `O(log n)` time and `O(1)` space.

 

**Example 1:**

```
Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
```

**Example 2:**

```
Input: nums = [3,3,7,7,10,11,11]
Output: 10
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `0 <= nums[i] <= 105`

## 题目大意

给定一个已经排序的数组，其中只有一个数字出现了一次，剩下的数字出现了两次，找到这个只出现一次的数字，

时间复杂度是 `O(logn)`，空间复杂度是 `O(1)`

## 解题思路

这道题目可以参考 [这篇题解](https://www.bilibili.com/video/BV1gW411y7N3?spm_id_from=333.999.0.0)

### Solution 1: 暴力解法

这种解法是可以通过的，但是不符合题目条件


````c++
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        const int len = nums.size();
        for (int i = 0;i < len; i += 2) {
            if (i == len - 1 || nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }
        return -1;
    }
};
````

### Solution 2: Binary Search

这中解法的大致思路是这样：

如果不考虑那个只出现一次的数：
- 索引为奇数的，则前一个位置应该与之相同，
- 索引为偶数的，则后一个位置应该与之相同，

这里我们判断出正确的，那么剩下的就是错误的了


````c++
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        const int len = nums.size();
        int low = 0, high = len;
        
        while (low < high) {
            const int mid = low + (high - low) / 2;
            // 如果是奇数，求 mid - 1，如果是 偶数，mid + 1
            const int n = mid % 2 != 0 ? mid - 1 : mid + 1;
            // const int n = mid ^ 1;
            
            if (nums[mid] == nums[n]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return nums[low];
    }
};
````
