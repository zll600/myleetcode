# [442. Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/)

## 题目

Given an integer array `nums` of length `n` where all the integers of `nums` are in the range `[1, n]` and each integer appears **once** or **twice**, return *an array of all the integers that appears **twice***.

You must write an algorithm that runs in `O(n) `time and uses only constant extra space.

 

**Example 1:**

```
Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]
```

**Example 2:**

```
Input: nums = [1,1,2]
Output: [1]
```

**Example 3:**

```
Input: nums = [1]
Output: []
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 105`
- `1 <= nums[i] <= n`
- Each element in `nums` appears **once** or **twice**.

## 题目大意

给定一个长度为 n 的证书数组，其中元素的范围在 [1, n] 中，每个元素只出现一次或者两次，返回数组中所有出现两次的数

你必须使用 O(n) 的算法，且只能使用常数的空间

## 解题思路

### 解法1（原地哈希）

`````c++
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != nums[nums[i] - 1]) {	// 如果元素没有出现在它理应出现的位置，则交换
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) {
                res.push_back(nums[i]);	// 如果元素没有出现在它理应出现的位置，说明出现了重复
            }
        }
        
        return res;
    }
};
`````

