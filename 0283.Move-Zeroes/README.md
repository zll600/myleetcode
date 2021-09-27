# [283. Move Zeroes](https://leetcode.com/problems/move-zeroes/)

## 题目

Given an integer array `nums`, move all `0`'s to the end of it while maintaining the relative order of the non-zero elements.

**Note** that you must do this in-place without making a copy of the array.

 

**Example 1:**

```
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
```

**Example 2:**

```
Input: nums = [0]
Output: [0]
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-231 <= nums[i] <= 231 - 1`

 

**Follow up:** Could you minimize the total number of operations done?

## 题目大意

给低能过一个整数数组，在维护元素相对顺序的前提下，移动所有的0到末尾

不能使用额外空间

## 解题思路

这道题和第 27 题、26题都有点像，可以利用双指针来作，

* 方法一，将所有的非零元素放在数组的前面然后将剩余元素置为 1，
* 方法二，在遍历的时候不断的进行交换，将 0 往后移动

## 代码

````c++
class Solution {
public:
    // 遍历两次
    void moveZeroes1(vector<int>& nums) {
        int idx = 0;
        for (int num : nums) {
           if (num != 0) {
               nums[idx] = num;
               idx++;
           }
        }
        
        while (idx < nums.size()) {
            nums[idx] = 0;
            idx++;
        }
    }
    
    // 遍历一次
    void moveZeroes(vector<int>& nums) {
        for (int i = 0, j = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                if (i != j) {
                    swap(nums[j], nums[i]);
                }
                ++j;  // 如果 i == j 两个都要调整
            }
        }
    }
};
````

