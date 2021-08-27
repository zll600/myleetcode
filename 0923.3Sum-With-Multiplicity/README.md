# [923. 3Sum With Multiplicity](https://leetcode.com/problems/3sum-with-multiplicity/)

## 题目

Given an integer array `arr`, and an integer `target`, return the number of tuples `i, j, k` such that `i < j < k` and `arr[i] + arr[j] + arr[k] == target`.

As the answer can be very large, return it **modulo** `109 + 7`.

 

**Example 1:**

```
Input: arr = [1,1,2,2,3,3,4,4,5,5], target = 8
Output: 20
Explanation: 
Enumerating by the values (arr[i], arr[j], arr[k]):
(1, 2, 5) occurs 8 times;
(1, 3, 4) occurs 8 times;
(2, 2, 4) occurs 2 times;
(2, 3, 3) occurs 2 times.
```

**Example 2:**

```
Input: arr = [1,1,2,2,2,2], target = 5
Output: 12
Explanation: 
arr[i] = 1, arr[j] = arr[k] = 2 occurs 12 times:
We choose one 1 from [1,1] in 2 ways,
and two 2s from [2,2,2,2] in 6 ways.
```

 

**Constraints:**

- `3 <= arr.length <= 3000`
- `0 <= arr[i] <= 100`
- `0 <= target <= 300`

## 题目大意

给定一个数组和一个目标值，返回 3 个数相加的和的解，相同数值，不同下标算不同解

## 解题思路

这道题解法和 15 题一样，也是利用双指针，不过这次需要用一些排列组合的知识来降低时间复杂度，注意对溢出情况的特殊处理

* 利用双指针
* 利用 map 做缓存

## 代码

````c++
// Two pointers
/*
class Solution {
public:
    int threeSumMulti(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int size = nums.size();
        int mod = 1000000007;
        int res = 0;
        int last = 0;
        
        for (int i = 0; i < size - 2; ++i) {
            int j = i + 1;
            int k = size - 1;
            
            while (j < k) {
                long sum = 1L * nums[i] + nums[j] + nums[k];
                
                if (sum > target) {
                    while (j < k && nums[k] == nums[--k]);
                } else if (sum < target) {
                    while (j < k && nums[j] == nums[++j]);
                } else if (sum == target && nums[j] != nums[k]){
                    int left = 1;
                    int right = 1;
                    
                    while (j < k && nums[k] == nums[k - 1]) {
                        --k;
                        ++right;
                    }
                    while (j < k && nums[j] == nums[j + 1]) {
                        ++j;
                        ++left;
                    }
                    ++j;
                    --k;
                    
                    res += left * right;
                    res %= mod;
                } else {
                    int len = k - j + 1;
                    res += len * (len - 1) / 2;
                    res %= mod;
                    break;
                }
            }
        }
        return res % mod;
    }
};
*/

// 利用缓存 空间换时间
class Solution {
public:
    int threeSumMulti(vector<int>& nums, int target) {
        int mod = 1000000007;
        unordered_map<int, int> freq;
        for (int i : nums) {
            ++freq[i];
        }
        
        vector<int> uniq_num;
        for (pair<const int, int> it : freq) {
            uniq_num.push_back(it.first);
        }
        sort(uniq_num.begin(), uniq_num.end());
        
        int size = uniq_num.size();
        long res = 0;
        
        for (int i = 0; i < size; ++i) {
            int num_i = freq[uniq_num[i]];
            if (uniq_num[i] * 3 == target && num_i >= 3) {
                res += 1L * num_i * (num_i - 1) * (num_i - 2) / 6;
            }
            
            for (int j = i + 1; j < size; ++j) {
                int num_j = freq[uniq_num[j]];
                
                if (uniq_num[i] * 2 + uniq_num[j] == target && num_i > 1) {
                    res += 1L * num_i * (num_i - 1) / 2 * num_j;
                }
                
                if (uniq_num[i] + uniq_num[j] * 2 == target && num_j > 0) {
                    res += 1L * num_j * (num_j - 1) / 2 * num_i;
                }
                
                int k = target - uniq_num[i] - uniq_num[j];
                if (k > uniq_num[j] && freq[k] > 0) {
                    res += 1L * num_i * num_j * freq[k];
                }
            }
        }
        return res % mod;
    }
};

````

