# [53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)

## 题目

Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return *its sum*.

A **subarray** is a **contiguous** part of an array.

 

**Example 1:**

```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
```

**Example 2:**

```
Input: nums = [1]
Output: 1
```

**Example 3:**

```
Input: nums = [5,4,-1,7,8]
Output: 23
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-104 <= nums[i] <= 104`

 

**Follow up:** If you have figured out the `O(n)` solution, try coding another solution using the **divide and conquer** approach, which is more subtle.

## 题目大意

给定一个整数数组 nums，找到和最大的连续子数组，并返回这个最大和

## 解题思路

先说以下这道题目很适合用动态规划来解决，但是也有其他的解法

### 解法1(动态规划)

状态的定义：`dp[i]`表示以 i 位置结尾的和最大的连续子数组，

状态转移：以 i  结尾的连续子数组的状态可以由 i - 1 结尾的子数组推断出来，求和我们一般是采用直接加的形式，但是这道题中元素有正有负，所以要重新考虑

* 如果 `dp[i - 1]` 的结果小于等于0，那末说明前面的当前位置的最大连续子数组不能由 i - 1 位置扩充而来，前面对当前位置求 最大和没有帮助
* 如果 `dp[i - 1]` 的结果大于等于0，那么加上当前位置，以当前位置结尾的子数组和就会比只有当前位置要大，

初始化：dp[0] 表示以 0 位置结尾的最长子数组，所以 `dp[0] = nums[0]`

利用上述方法，我们求的是以各位置结尾的子数组的最大和，但是题目要求的所有最大和中最大的，我采用的方法是在求 dp[i] 的时候就更新最大值，这里依然需要注意最大值的初值，与开始遍历的位置有关系

````c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums[0];
        }
        
        int res = nums[0];  // 因为下面的动态转移直接是从 1 开始的，所以这里初值为 nums[0]
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            res = max(res, dp[i]);
        }
        
        return res;
    }
};
````

#### 优化

因为i 位置只与 i - 1 位置有关系，所以可以使用滚动变量来更新数组

`````c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums[0];
        }
        
        int res = nums[0];  // 因为下面的动态转移直接是从 1 开始的，所以这里初值为 nums[0]
        int prev = nums[0];
        int cur = 0;
        
        for (int i = 1; i < nums.size(); i++) {
            cur = max(prev + nums[i], nums[i]);
            res = max(res, cur);
            prev = cur;
        }
        
        return res;
    }
};
`````

### 解法2（分治）

这里放上一篇题解：https://leetcode-cn.com/problems/maximum-subarray/solution/dong-tai-gui-hua-fen-zhi-fa-python-dai-ma-java-dai/

简单来说，就是分段去求：

* [left, mid] 段
* [mid + 1, right] 段
* [mid, mid + 1] 段，这一段从中间开始向两边扩，

从这三段中选出最大的即可

`````c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums[0];
        }
        
        return MaxSubArraySum(nums, 0, nums.size() - 1);
    }
    
 private:
    int MaxCrossingSum(const vector<int>& nums, int left, int mid, int right) {
        // 一定会包含 nums[mid] 这个元素
        int sum = 0;
        int left_sum = INT_MIN;
        // 左半边包含 nums[mid] 元素，最多可以到什么地方
        // 以 nums[mid] 结尾的子数组的最大和
        for (int i = mid; i >= left; i--) {
            sum += nums[i];
            if (sum > left_sum) {
                left_sum = sum;
            }
        }
        
        // 右半边不包含 nums[mid] 元素，最多可以到什么地方
        // 以 mid + 1 开始的子数组的最大和
        sum = 0;
        int right_sum = INT_MIN;
        for (int i = mid + 1; i <= right; i++) {
            sum += nums[i];
            if (sum > right_sum) {
                right_sum = sum;
            }
        }
        
        return left_sum + right_sum;
    }
    
    int MaxSubArraySum(const vector<int>& nums, int left, int right) {
        if (left == right) {  // 终止条件
            return nums[left];
        }
        
        int mid = left + (right - left) / 2;
        return max(max(MaxSubArraySum(nums, left, mid), MaxSubArraySum(nums, mid + 1, right)),
                  MaxCrossingSum(nums, left, mid, right));
    }
};
`````

