# [930. Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/)

Given a binary array `nums` and an integer `goal`, return *the number of non-empty **subarrays** with a sum* `goal`.

A **subarray** is a contiguous part of the array.

 

**Example 1:**

```
Input: nums = [1,0,1,0,1], goal = 2
Output: 4
Explanation: The 4 subarrays are bolded and underlined below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
```

**Example 2:**

```
Input: nums = [0,0,0,0,0], goal = 0
Output: 15
```

 

**Constraints:**

- `1 <= nums.length <= 3 * 104`
- `nums[i]` is either `0` or `1`.
- `0 <= goal <= nums.length`

## 题目大意

给定一个二元数组和一个整数 goal，返回数组和为 goal 的子数组的数目

## 解题思路

* 这道题目可以转化为一个区间求和的问题，可以利用前缀和来求解
* 对于区间`[0, right]`，主要找到一个左边界 left 满足`[0, left - 1]`，存在pre_sum[right] - pre_sum[left - 1] = goal，我们只需要在确定右边界的前提下，用哈希表缓存之前出现过的前缀和的次数，

## 代码

````c++
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int size = nums.size();
        vector<int> pre_sum(size + 1, 0);
        for (int i = 1; i <= size; ++i) {
            pre_sum[i] = pre_sum[i - 1] + nums[i - 1];
        }
        
        
        int res = 0;
        unordered_map<int, int> cache;
        cache.insert(make_pair(0, 1));
        
        for (int i = 1; i <= size; ++i) {
            int right = pre_sum[i];
            int left = right - goal;
            
            if (cache.find(left) != cache.end()) {
                res += cache.at(left);
            }
            ++cache[right];
        }
        
        return res;
    }
};
````



