# [1248. Count Number of Nice Subarrays](https://leetcode-cn.com/problems/count-number-of-nice-subarrays/)

## 题目

Given an array of integers `nums` and an integer `k`. A continuous subarray is called **nice** if there are `k` odd numbers on it.

Return *the number of **nice** sub-arrays*.

 

**Example 1:**

```
Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
```

**Example 2:**

```
Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There is no odd numbers in the array.
```

**Example 3:**

```
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16
```

 

**Constraints:**

- `1 <= nums.length <= 50000`
- `1 <= nums[i] <= 10^5`
- `1 <= k <= nums.length`

## 题目大意

给定一个整数数组 nums 和一个整数 k，如果某个 **连续** 子数组中恰好有 `k` 个奇数数字，我们就认为这个子数组是「**优美子数组**」

返回优美子数组的数量

## 解题思路

滑动窗口的核心在于确定左右边界更新的条件。

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/count-number-of-nice-subarrays/solution/hua-dong-chuang-kou-qian-zhui-he-bi-xu-miao-dong-b/



### Solution 1: Sliding Window

这种解法使用滑动窗口来做，关键在于

* 确定窗口扩大和收缩的条件
* 计数时，根据窗口的含义，确定窗口两端的 偶数的个数来计算

时间复杂度 O(n) 空间复杂度 O(n)

```c++
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        const int len = nums.size();
        int left = 0, right = 0;
        int res = 0, cnt = 0;
        
        // 窗口 [left, right)
        while (right < len) {
            if ((nums[right] & 1) != 0) {
                // 如果是奇数增加记述
                ++cnt;
            }
            // 这里继续满足窗口的定义
            ++right;
            
            if (cnt == k) {
                int after = right;
                while (after < len && (nums[after] & 1) == 0) {
                    ++after;
                }
                
                int before_cnt = 0;
                while (left < right && (nums[left] & 1) == 0) {
                    ++before_cnt;
                    ++left;
                }
                
                // after - right + 1 是因为也可以一个偶数都不选
                res += (after - right + 1) * (before_cnt + 1);
                
                // 窗口向右移
                --cnt;
                ++left;
            }
        }
        
        return res;
    }
};
```

### Solution 2: PrefiixSum 

这种解法使用前缀和来做统计

````c++
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        const int len = nums.size();
        // 下标表示 有多少个奇数
        // 值表示这样的位置有多少个
        vector<int> prefix(len + 1);
        prefix[0] = 1;
        
        int res = 0, sum = 0;
        for (int num : nums) {
            sum += num & 1;
            ++prefix[sum];
            if (sum >= k) {
                // 这里值考虑添加过的部分
                res += prefix[sum - k];
            }
        }
        
        return res;
    }
};
````

