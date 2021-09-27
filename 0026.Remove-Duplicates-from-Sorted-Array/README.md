# [26. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)

## 题目

Given an integer array `nums` sorted in **non-decreasing order**, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that each unique element appears only **once**. The **relative order** of the elements should be kept the **same**.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the **first part** of the array `nums`. More formally, if there are `k` elements after removing the duplicates, then the first `k` elements of `nums` should hold the final result. It does not matter what you leave beyond the first `k` elements.

Return `k` *after placing the final result in the first* `k` *slots of* `nums`.

Do **not** allocate extra space for another array. You must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with O(1) extra memory.

**Custom Judge:**

The judge will test your solution with the following code:

```
int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
```

If all assertions pass, then your solution will be **accepted**.

 

**Example 1:**

```
Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
```

**Example 2:**

```
Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
```

 

**Constraints:**

- `0 <= nums.length <= 3 * 104`
- `-100 <= nums[i] <= 100`
- `nums` is sorted in **non-decreasing** order.

## 题目大意

给定一个按照非降序排序的数组，原地删除数组中的重复元素，是每个元素只出现一次，并且保持原数组中的相对顺序

## 解题思路

这道题比较简单，利用双指针解法即可，可以减少一层循环

用一个指针遍历数组，用另一个指针来做删除

## 代码

``````c++
class Solution {
public:
    int removeDuplicates1(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        
        // 循环不变量
        // all in [0, idx] 是符合条件的部分
        // 初始为 0，区间只有一个元素
        int idx = 0;    //这里的idx表示上一个已经添加的位置
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[idx]) {
                idx++;
                nums[idx] = nums[i];
            }
        }
        
        return idx + 1; // 注意我们设 idx 是下标，题目要求返回的是长度
    }
    
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        
        return Process(nums, 1);
    }
    
 private:
    int Process(vector<int>& nums,int k) {
        int idx = 0;
        for (int num : nums) {
            if (idx < k || nums[idx - k] != num) {
                nums[idx] = num;
                idx++;
            }
        }
        return idx; // 这里的 idx 是下一个可以添加的位置
    }
};
``````

