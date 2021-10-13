# [152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)

## 题目

Given an integer array `nums`, find a contiguous non-empty subarray within the array that has the largest product, and return *the product*.

It is **guaranteed** that the answer will fit in a **32-bit** integer.

A **subarray** is a contiguous subsequence of the array.

 

**Example 1:**

```
Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
```

**Example 2:**

```
Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
```

 

**Constraints:**

- `1 <= nums.length <= 2 * 104`
- `-10 <= nums[i] <= 10`
- The product of any prefix or suffix of `nums` is **guaranteed** to fit in a **32-bit** integer.

## 题目大意

给定一个整数数组，找到元素乘积最大的连续的非空子数组，返回乘积

## 解体思路

先分析题目，求最大值，猜想可以使用动态规划，然后找状态转移方程，以当前元素结尾的子数组的最大乘积，要么是与前一个元素结尾的子数组的最大乘积有关，要么就从当前元素重新开始一个新的子数组（这里先不要考虑正负数和0 的问题），然后这道题目显然是满足无后效性的，所以可以使用动态规划

### 解法1（DP）

这道题在维护状态时，因为乘积的结果受正负号的影响，所以需要维护一个最大值和一个最小值，因为如果当前数为负，且前一个状态的最小值为负，则二者的乘积可能是新的最大值

状态定义：最大值是 `Max(f(n)) = Max( Max(f(n-1)) * n, Min(f(n-1)) * n)`；最小值是 `Min(f(n)) = Min( Max(f(n-1)) * n, Min(f(n-1)) * n)`。只要动态维护这两个值，如果最后一个数是负数，最大值就在负数 * 最小值中产生，如果最后一个数是正数，最大值就在正数 * 最大值中产生。

这里注意的是，如果当前数为负数，那么需要交换最大值和最小值

`````c++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        const int size = nums.size();
        int max_val = nums[0];
        int min_val = nums[0];
        int res = nums[0];
        
        for (int i = 1; i < size; ++i) {
            if (nums[i] < 0) {  // 如果当前数为负数，则交换最大值和最小值
                swap(max_val, min_val);
            }
            
            max_val = max(max_val * nums[i], nums[i]);
            min_val = min(min_val * nums[i], nums[i]);
            
            res = max(res, max_val);
        }
        
        return res;
    }
};
`````

