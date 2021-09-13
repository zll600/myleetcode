# [523. Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/)

## 题目

Given an integer array `nums` and an integer `k`, return `true` *if* `nums` *has a continuous subarray of size **at least two** whose elements sum up to a multiple of* `k`*, or* `false` *otherwise*.

An integer `x` is a multiple of `k` if there exists an integer `n` such that `x = n * k`. `0` is **always** a multiple of `k`.

 

**Example 1:**

```
Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
```

**Example 2:**

```
Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
```

**Example 3:**

```
Input: nums = [23,2,6,4,7], k = 13
Output: false
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `0 <= nums[i] <= 109`
- `0 <= sum(nums[i]) <= 231 - 1`
- `1 <= k <= 231 - 1`

## 题目大意

给定一个数组和一个整数 k，如果连续至少两个元素的和为 k 的倍数，返回 true，否则返回 false，

## 解题思路

* 当子数组 [i, j]元素之和为 k 的倍数时，pre_sum[i] 和 pre_sum[j] 对 k 的模数相同
* 这道题可以参考这篇题解 ：https://leetcode-cn.com/problems/continuous-subarray-sum/solution/gong-shui-san-xie-tuo-zhan-wei-qiu-fang-1juse/

## 代码

````c++
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int len = nums.size();
        
        vector<int> pre_sum(len + 1, 0);
        for (int i = 1; i <= len; ++i) {
            pre_sum[i] = pre_sum[i - 1] + nums[i - 1];
        }
        
        unordered_set<int> cache;
        for (int i = 2; i <= len; ++i) {
            cache.insert(pre_sum[i - 2] % k);
            if (cache.find(pre_sum[i] % k) != cache.end()) {
                return true;
            }
        }
        
        return false;
    }
};
````

