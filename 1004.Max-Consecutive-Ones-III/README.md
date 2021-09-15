# [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)

## 题目

Given a binary array `nums` and an integer `k`, return *the maximum number of consecutive* `1`*'s in the array if you can flip at most* `k` `0`'s.

 

**Example 1:**

```
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
```

**Example 2:**

```
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `nums[i]` is either `0` or `1`.
- `0 <= k <= nums.length`

## 题目大意

给定一个二元数组和一个整数 k，返回在你可以翻转最多 k 个0 的条件下，最长连续1 的子数组，

## 解题思路

* 这道题目可以用滑动窗口来解决（留待以后实现）
* 这道题目可以转化为 `[left, right]`区间中，出现的0 的个数不大于 k，也就是 presum[right]  - presum[left - 1] = total，len - tol <= k；
* 这里在查找左边界时，使用了二分查抄来加速，
* 这道题目还没有做完，留待以后实现

## 代码

### 使用前缀和

````java
class Solution {
    public int longestOnes(int[] nums, int k) {
        int n = nums.length;
        int ans = 0;
        int[] sum = new int[n + 1];
        for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + nums[i - 1];
        for (int i = 0; i < n; i++) {
            int l = 0, r = i;
            while (l < r) {
                int mid = l + r >> 1;
                if (check(sum, mid, i, k)) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            if (check(sum, r, i, k)) ans = Math.max(ans, i - r + 1);
        }
        return ans;
    }
    boolean check(int[] sum, int l, int r, int k) {
        int tol = sum[r + 1] - sum[l], len = r - l + 1;
        return len - tol <= k;
    }
}
````



