# [164. Maximum Gap](https://leetcode.com/problems/maximum-gap/)

## 题目

Given an integer array `nums`, return *the maximum difference between two successive elements in its sorted form*. If the array contains less than two elements, return `0`.

You must write an algorithm that runs in linear time and uses linear extra space.

 

**Example 1:**

```
Input: nums = [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
```

**Example 2:**

```
Input: nums = [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `0 <= nums[i] <= 109`

## 题目大意

给定一个未排序的整数数组，返回连续两个节点的最大差值，如果数组中的元素少于 2 个，返回 0

使用线性的算法和 线性的空间

## 解题思路

先对数组进行排序，排序之后求解

### Solution 1:

这种解法，先对数组进行排序，排序之后再求出差值，可以ac，但是不符合题目要求。

```c++
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        const int len = nums.size();
        if (len < 2) {
            return 0;
        }
        
        sort(nums.begin(), nums.end());
        
        int ans = 0;
        for (int i = 1; i< len; ++i) {
            ans = max(ans, nums[i] - nums[i - 1]);
        }
        
        return ans;
    }
};
```

### Solution 2:

这道题目可以参考这篇题解：https://books.halfrost.com/leetcode/ChapterFour/0100~0199/0164.Maximum-Gap/

利用基数排序，可以将算法的时间复杂度降低到线性，这里仔细注意 统计的频数和下标之间的转化

`````c++
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        const int len = nums.size();
        if (len < 2) { // 边界条件
            return 0;
        }
        
        auto max_iter = max_element(nums.begin(), nums.end());
        int max_val = *max_iter; // 获得最大值
        
        int exp = 1; // 指数
        int range = 10; // 范围，这个是根据题目得到的
        vector<int> aux(len); // 辅助数组
        
        while (max_val / exp) {
            vector<int> count(range); // 计数数组
            
            // 统计 某一位上数值相同的 元素 的数目，
            for (int num : nums) {
                ++count[(num / exp) % 10];
            }
            
            // 将频数转化为下标
            for (int i = 1; i < range; ++i) {
                count[i] += count[i - 1];
            }
            
            // 将排序后的结果写入辅助数组，
            for (int i = len - 1; i >= 0; --i) {
                int tmp = count[(nums[i]/exp)%10] - 1; // 这里将频统计后的频数转为下标的时候要 -1，不然会越界
                aux[tmp] = nums[i];
                count[(nums[i]/exp)%10] = tmp; // 更新该位置的频数
            }
            
            // 覆盖原始数组
            for (int i = 0; i < len; ++i) {
                nums[i] = aux[i];
            }
            
            exp *= 10; // 更新计数
        }
        
        int res = 0;
        for (int i = 1; i < len; ++i) {
            res = max(res, nums[i] - nums[i - 1]);
        }
        
        return res;
    }
};
`````

