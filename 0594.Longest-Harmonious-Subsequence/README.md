# [594. Longest Harmonious Subsequence](https://leetcode.com/problems/longest-harmonious-subsequence/)

## 题目

We define a harmonious array as an array where the difference between its maximum value and its minimum value is **exactly** `1`.

Given an integer array `nums`, return *the length of its longest harmonious subsequence among all its possible subsequences*.

A **subsequence** of array is a sequence that can be  derived from the array by deleting some or no elements without changing  the order of the remaining elements.

 

**Example 1:**

```
Input: nums = [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
```

**Example 2:**

```
Input: nums = [1,2,3,4]
Output: 2
```

**Example 3:**

```
Input: nums = [1,1,1,1]
Output: 0
```

 

**Constraints:**

- `1 <= nums.length <= 2 * 104`
- `-109 <= nums[i] <= 109`

## 题目大意

我们定义一个汉明数组，其中最大值和最小值的差值就是 `1`

给定一个整数数组 `nums`，返回所有可能的子序列中最长汉明子序列的长度

子序列是可以从原数组中删除一些元素，但不改变其顺序得到，

## 解题思路

这里的一个关键问题就是如何确定一个汉明数组，

### Solution 1:

这种做法就是使用一个哈希表来统计出各个数字出现的频数，然后找到差值为 `1` 的两个值组成一个子序列，用二者长度的和来更新最终的结果，

````c++
class Solution {
public:
    int findLHS(vector<int>& nums) {
        // 统计频数
        unordered_map<int, int> freq;
        for (int num : nums) {
            ++freq[num];
        }
        
        int res = 0;
        // 找到相邻两个值的最大长度
        for (const auto& item : freq) {
            auto it = freq.find(item.first + 1);
            if (it == freq.end()) {
                continue;
            }
            res = max(res, item.second + it->second);
        }
        
        return res;
    }
};
````
