# [918. Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/)

## 题目

Given a **circular integer array** `nums` of length `n`, return *the maximum possible sum of a non-empty **subarray** of* `nums`.

A **circular array** means the end of the array connects to the beginning of the array. Formally, the next element of `nums[i]` is `nums[(i + 1) % n]` and the previous element of `nums[i]` is `nums[(i - 1 + n) % n]`.

A **subarray** may only include each element of the fixed buffer `nums` at most once. Formally, for a subarray `nums[i], nums[i + 1], ..., nums[j]`, there does not exist `i <= k1`, `k2 <= j` with `k1 % n == k2 % n`.

 

**Example 1:**

```
Input: nums = [1,-2,3,-2]
Output: 3
Explanation: Subarray [3] has maximum sum 3.
```

**Example 2:**

```
Input: nums = [5,-3,5]
Output: 10
Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.
```

**Example 3:**

```
Input: nums = [-3,-2,-3]
Output: -2
Explanation: Subarray [-2] has maximum sum -2.
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 3 * 104`
- `-3 * 104 <= nums[i] <= 3 * 104`

## 题目大意

给定一个由整数环形数组 `nums`，求 `nums` 的非空子数组的最大可能和。

在此处，环形数组意味着数组的末端将会与开头相连呈环状( `nums[i]` 的下一个元素是 `nums[(i + 1) % n` 并且前一个元素是 `nums[i]` 是 `nums[(i - 1 + n)%n]`)

子数组 最多只能包含固定缓冲区 nums 中的每个元素一次。形式上，对于子数组 nums[i], nums[i + 1], ..., nums[j] ，不存在 i <= k1, k2 <= j 其中 k1 % n == k2 % n 

## 解题思路


### Solution  1: DP

这道题目可以参考 [这篇题解](https://leetcode.com/submissions/detail/686442778/)

这道题可以联系第 53 题来做

这里分为两种情况，

- 不存在循环，则和 第 53 题一样
- 存在循环，那么直接去最大和比较困难，这里反向思考，求出最小和，那么 总和 - 最小和就是最大和

还有很多需要注意的点，已经写在代码的注释中了

````c++
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        // case no circulation
        int max1 = INT_MIN;
        int sum = 0;
        for (int num : nums) {
            sum += num;
            if (sum > max1) {
                max1 = sum;
            }
            if (sum < 1) {
                // 如果当前位置的数已经不能使得 累加和为正，则取消
                sum = 0;
            }
        }

        // case: circular
        int arr_sum = accumulate(nums.begin(), nums.end(), 0);
        int min_sum = 0;

        sum = 0;
        const int len = nums.size();

        // 如果存在 circle，那么首位肯定不再最小和中
        for (int i = 1; i < len - 1; ++i) {
            sum += nums[i];
            if (sum >= 0) {
                // 如果当前位置已经不能使得 累加和为 负，则取消
                sum = 0;
            }
            if (sum < min_sum) {
                min_sum = sum;
            }
        }

        int max2 = arr_sum - min_sum;

        return max(max1, max2);
    }
};
````
