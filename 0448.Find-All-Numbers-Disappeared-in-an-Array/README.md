# [448. Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)

## 题目

Given an array `nums` of `n` integers where `nums[i]` is in the range `[1, n]`, return *an array of all the integers in the range* `[1, n]` *that do not appear in* `nums`.

 

**Example 1:**

```
Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]
```

**Example 2:**

```
Input: nums = [1,1]
Output: [2]
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 105`
- `1 <= nums[i] <= n`

 

**Follow up:** Could you do it without extra space and in `O(n)` runtime? You may assume the returned list does not count as extra space.

## 题目大意

给定一个含有 n 个数的数组，其中元素的范围在 [1, n] 之间，返回在[1, n]中，没有出现在数组中的数

### 解题思路

### 解法1（原地哈希）

这种解法类似于41 题，因为数组的元素的取值范围和数组索引有明显的关联关系，

我们遍历一次数组，将符合 nums[i] 放在nums[i] - 1，然后再查找一次数组，找出不存在的元素

```c++
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            // 这里必须要使用一个循环，直到这个位置目前不能交换，才可以到下一个位置
            while (nums[i] != nums[nums[i] - 1]) {	// 当前元素没有出现在它理应出现的地方，则直接交换
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) {
                res.push_back(i + 1);
            }
        }
        
        return res;
    }
};
```

 