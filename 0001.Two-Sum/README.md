# [1. Two Sum](https://leetcode.com/problems/two-sum/)

## 题目

Given an array of integers `nums` and an integer `target`, return *indices of the two numbers such that they add up to `target`*.

You may assume that each input would have ***exactly\* one solution**, and you may not use the *same* element twice.

You can return the answer in any order.

 

**Example 1:**

```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].
```

**Example 2:**

```
Input: nums = [3,2,4], target = 6
Output: [1,2]
```

**Example 3:**

```
Input: nums = [3,3], target = 6
Output: [0,1]
```

 

**Constraints:**

- `2 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`
- **Only one valid answer exists.**

 

**Follow-up:** Can you come up with an algorithm that is less than `O(n2) `time complexity?

## 题目大意

给定一个数组和一个整数值，返回数组中两个相加等于给定值的数组的下标，

你可以认为题目值哟一个解，你不会使用同一个数多次，你可以以任意顺序返回答案

## 解题思路

使用一个 map 记录已经出现过的数的下标，每次查看 target - nums[i] 是否存在于 map 中，

## 代码

````c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int size = nums.size();
        unordered_map<int, int> cache;
        
        for (int i = 0; i < size; ++i) {
            if (cache.count(target - nums[i]) > 0) {
                return vector<int>{cache[target - nums[i]], i};
            }
            cache[nums[i]] = i;
        }
        
        return vector<int>();
    }
};
````



