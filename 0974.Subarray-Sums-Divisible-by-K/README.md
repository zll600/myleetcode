# [974. Subarray Sums Divisible by K](https://leetcode.cn/problems/subarray-sums-divisible-by-k/)

## 题目

Given an integer array `nums` and an integer `k`, return *the number of non-empty **subarrays** that have a sum divisible by* `k`.

A **subarray** is a **contiguous** part of an array.

 

**Example 1:**

```
Input: nums = [4,5,0,-2,-3,1], k = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by k = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
```

**Example 2:**

```
Input: nums = [5], k = 9
Output: 0
```

 

**Constraints:**

- `1 <= nums.length <= 3 * 104`
- `-104 <= nums[i] <= 104`
- `2 <= k <= 104`

## 题目大意

给定一个整数数组 `nums` 和一个整数 `k` ，返回其中元素之和可被 `k` 整除的（连续、非空） 子数组 的数目

子数组 是数组的 *连续* 部分

## 解题思路

这道题目是求数组的区间和，还是比较容易想到使用 前缀和来计算的

### Solution 1: Brute Force

暴力解法，会 TLE

````c++
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int ans = 0;

        const int len = nums.size();
        for (int i = 0; i < len; ++i) {
            int total = 0;
            for (int j = i; j < len; ++j) {
                total += nums[j];
                if (total % k == 0) {
                    ++ans;
                }
            }
        }

        return ans;
    }
};
````
 
### Solution 2: PrefixSum

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/subarray-sums-divisible-by-k/solution/you-jian-qian-zhui-he-na-jiu-zai-ci-dai-ni-da-tong/)

想到前缀和后，有 `nums[i] + ... + nums[j] == prefix_sum[j] - prefix_sum[i - 1]`，

所以题目就转换为 `(prefix_sum[j] - prefix_sum[i - 1]) % k == 0`，转化一下得到 `prefix_sum[j] % k == prefix_sum[i - 1] % k`，然后根据排列组合的知识，不难想到 得到 `prefix_sum[j]` 时，只要查找这个值已经出现了多少次即可

这道题目还有坑在于，nums[i] 可正可负，所以要对负数做特殊处理、这里还需要注意，编程语言中的取模可能和实际上不同

`````c++
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        const int len = nums.size();
        unordered_map<int, int> records;
        records.emplace(0, 1);
        
        int ans = 0;
        int prefix_sum_mod_k = 0;
        for (int i = 0; i < len; ++i) {
            prefix_sum_mod_k = (prefix_sum_mod_k + nums[i]) % k;
            if (prefix_sum_mod_k < 0) {
                prefix_sum_mod_k += k;
            }
            
            auto it = records.find(prefix_sum_mod_k);
            if (it != records.end()) {
                ans += it->second;
                ++it->second;
            } else {
                records.emplace(prefix_sum_mod_k, 1);
            }
        }
        
        return ans;
    }
};
`````
