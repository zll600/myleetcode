# [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)

## 题目

Given an integer array `nums`, return the length of the longest strictly increasing subsequence.

A **subsequence** is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, `[3,6,2,7]` is a subsequence of the array `[0,3,1,6,2,2,7]`.

 

**Example 1:**

```
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
```

**Example 2:**

```
Input: nums = [0,1,0,3,2,3]
Output: 4
```

**Example 3:**

```
Input: nums = [7,7,7,7,7,7,7]
Output: 1
```

 

**Constraints:**

- `1 <= nums.length <= 2500`
- `-104 <= nums[i] <= 104`

 

**Follow up:** Can you come up with an algorithm that runs in `O(n log(n))` time complexity?

## 题目大意

给定一个整数数组 nums，返回这个最长的严格递增的子序列的长度

**进阶要求* *：使用 O(nlogn) 的算法

## 解题思路

这是一道很经典的动态规划问题 LIS 问题

### Solution 1:

状态的定义：dp[i] 表示以 i 位置结尾的子序列的长度

状态转移：

````
dp[i] = max(dp[i], dp[j] + 1) (j < i && nums[i] > nums[j])
````

每次求 i 需要遍历 i 之前的所有位置，

初始化：每个位置初始化为 1，表示一个这个位置结尾的子序列长度至少为 1

````c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        
        const int size = nums.size();
        
        int res = 0;
        vector<int> dp(size, 1);
        
        for (int i = 1; i < size; ++i) {
            //  状态转移
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            
            // 维护结果
            res = max(res, dp[i]);
        }
        
        return res;
    }
};
````

### Solution 2:

这种解法利用一个数组，始终维持某个长度的子序列的最后一个元素，我们让这个最后一个元素尽量小，则最终的子序列就可以尽量的长

这道题的解法可以参考这篇题解：https://leetcode.com/problems/longest-increasing-subsequence/submissions/

````c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        
        const int size = nums.size();
        int res = 0;
        
        // tail 数组定义：tail[i] 表示长度为 i + 1 的子序列末尾元素的值
        vector<int> tail(size);
        // 遍历nums[0]，直接放在第一个位置
        tail[0] = nums[0];
        // end 表示有序数组 tail，最后一个已赋值元素的索引
        int end = 0;
        
        for (int i = 1; i < size; ++i) {
            if (nums[i] > tail[end]) {
                ++end;
                tail[end] = nums[i];
            } else {
                // 二分查找第一个大于等于 nums[i] 的对象，尝试让该位置上的值更小
                int left = 0;
                int right = end;
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    // 要找第一个大于等于的，所以应该将右边界左移
                    if (tail[mid] >= nums[i]) {
                        right = mid;
                    } else {
                        left = mid + 1;
                    }
                }
                tail[left] = nums[i];
            }
        }
        ++end;
        return end;
    }
};
````

