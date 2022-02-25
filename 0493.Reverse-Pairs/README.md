# [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/)

## 题目

Given an integer array `nums`, return *the number of **reverse pairs** in the array*.

A reverse pair is a pair `(i, j)` where `0 <= i < j < nums.length` and `nums[i] > 2 * nums[j]`.

 

**Example 1:**

```
Input: nums = [1,3,2,3,1]
Output: 2
```

**Example 2:**

```
Input: nums = [2,4,3,5,1]
Output: 3
```

 

**Constraints:**

- `1 <= nums.length <= 5 * 104`
- `-231 <= nums[i] <= 231 - 1`

## 题目大意

给定一个整数数组 `nums`，返回数组中的 `翻转对` 的数目，

一个翻转对是一对 `(i, j)` 其中 `0 <= i < j < nums.length` 和 `nums[i] > 2 * nums[j]`


## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/reverse-pairs/solution/shou-hua-tu-jie-yi-bu-yi-bu-jie-xi-gui-bing-pai-xu/)

### Solution 1: 

这道题就是利用归并排序的特点，在和并两个有序部分的时候，计算多组符合条件的 `反转对`，


````c++
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        vector<int> tmp(nums.size());
        MergeSort(nums, 0, nums.size() - 1, tmp);
        
        // for_each(nums.begin(), nums.end(), [](int a) {
        //     cout << a << " ";
        // });
        // cout << endl;
        
        return ans_;
    }
    
 private:
    int ans_;
    
    void MergeTwoSortedArray(vector<int>& nums, int low, int mid,
                            int high, vector<int>& tmp) {
        copy(nums.begin() + low, nums.begin() + high + 1, tmp.begin() + low);
        
        int i = low, j = mid + 1;
        for (int k = low; k <= high; ++k) {
            // 先判断是否越界
            if (i == mid + 1) {
                nums[k] = tmp[j];
                ++j;
            } else if (j == high + 1) {
                nums[k] = tmp[i];
                ++i;
            } else if (tmp[i] <= tmp[j]) {
                nums[k] = tmp[i];
                ++i;
            } else {
                nums[k] = tmp[j];
                ++j;
            }
        }
    }
    
    void MergeSort(vector<int>& nums, int low, int high, vector<int>& tmp) {
        if (low >= high) {
            return;
        }
        
        // 先递归分解
        const int mid = low + (high - low) / 2;
        MergeSort(nums, low, mid, tmp);
        MergeSort(nums, mid + 1, high, tmp);
        
        int i = low, j = mid + 1;
        while (i <= mid && j <= high) {
            if (1L * nums[i] > 2L * nums[j]) {
                // 如果满足条件可以尝试向右扩
                ans_ += mid - i + 1;
                ++j;
            } else {
                ++i;
            }
        }
        
        // 合并两个有序的序列
        MergeTwoSortedArray(nums, low, mid, high, tmp);
    }
};
````
