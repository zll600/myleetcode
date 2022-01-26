# [ 795. Number of Subarrays with Bounded Maximum](https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/)

## 题目

Given an integer array `nums` and two integers `left` and `right`, return *the number of contiguous non-empty **subarrays** such that the value of the maximum array element in that subarray is in the range* `[left, right]`.

The test cases are generated so that the answer will fit in a **32-bit** integer.

 

**Example 1:**

```
Input: nums = [2,1,4,3], left = 2, right = 3
Output: 3
Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
```

**Example 2:**

```
Input: nums = [2,9,2,5,6], left = 2, right = 8
Output: 7
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `0 <= nums[i] <= 109`
- `0 <= left <= right <= 109`

## 题目大意

给定一个元素都是正整数的数组`nums`，正整数 `left` 以及 `right` `(left <= right)`。求连续、非空且其中最大元素满足大于等于`left` 小于等于`right`的子数组个数。

## 解题思路

这道题可以这样来思考

* 分别求出 小于等于 right，和小于等于 left - 1 的子数组的个数 `cnt[right] 和 cnt[left - 1]`
* 大于等于 left 且小于等于 right 的 等于 `cnt[right] - cnt[left - 1]`

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/unique-substrings-in-wraparound-string/solution/xi-fa-dai-ni-xue-suan-fa-yi-ci-gao-ding-qian-zhui-/

### Solution 1: Sliding Window

这里使用的辅助函数，用来小于等于某个边界值的子数组的个数，其实也可以理解为 滑动窗口，不过这里没有明显的窗口左边界和右边界的移动

```c++
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        // 题目要求的范围是 [left, right] 这里是包含等于的
        return GetMostK(nums, right) - GetMostK(nums, left - 1);
    }
 private:
    int GetMostK(const vector<int>& nums, int bound) {
        int res = 0;
        int pre = 0;
        for (int num : nums) {
            // 这里统计以当前位置结尾的 元素的子数组的个数
            if (num <= bound) {
                ++pre;
            } else {
                pre = 0;
            }
            res += pre;
        }
        return res;
    }
};
```

