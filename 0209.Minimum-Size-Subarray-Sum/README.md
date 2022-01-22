# [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)

## 题目

Given an array of positive integers `nums` and a positive integer `target`, return the minimal length of a **contiguous subarray** `[numsl, numsl+1, ..., numsr-1, numsr]` of which the sum is greater than or equal to `target`. If there is no such subarray, return `0` instead.

 

**Example 1:**

```
Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
```

**Example 2:**

```
Input: target = 4, nums = [1,4,4]
Output: 1
```

**Example 3:**

```
Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
```

 

**Constraints:**

- `1 <= target <= 109`
- `1 <= nums.length <= 105`
- `1 <= nums[i] <= 105`

## 题目大意

给定一个正整数的数组和一个正整数，找出数组中满足和大于等于`target`的子数组的最小长度，如果没有就返回0

## 解题思路

利用滑动窗口，右窗口一直向右扩，如果`sum`大于等于`target`,就一直缩小左边界，直到窗口的累加和不满条件，每次更新左边界的时候，都要更新最终的结果

这道题目还可以联系第 862 题，很像

### Solution 1： Sliding Window

````c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = 0;  // 子数组的和
        int left = 0;  // 右边界
        int right = 0;   // 左边界

        int res = INT_MAX;  // 取最小值，初始化最大值
        const int size = nums.size();
        // 循环不变量：[left, right) 
        while (right < size) {
            sum += nums[right];  // 扩大窗口
            ++right;

            while (sum >= target) {  // 缩小窗口
                res = min(res, right - left);  // 更新值
                sum -= nums[left];
                ++left;
            }
        }

        return res == INT_MAX ? 0 : res;
    }
};
````



````c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        /*
        int length = INT32_MAX;
        for (int i = 0; i < nums.size(); i++) {
            int sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                
                if (sum >= target) {
                    length = (length > (j - i + 1)) ? (j - i + 1) : length;
                    break;
                }
            }
        }
        
        return length < INT32_MAX ? length : 0;*/
        
        int size = nums.size();
        int len = size + 1;	// 因为结果要取最小，所以这里设置为最大，不影响最终的结果
        
        int left = 0;
        int right = 0;
        
        int sum = 0;
        for (; right < size; ++right) {
            sum += nums[right];
            
            while (sum >= target) {
                len = min(len, right - left + 1);
                sum -= nums[left];
                ++left;
            }
        }
        
        return len == size + 1 ? 0 : len;
    }
};
````

