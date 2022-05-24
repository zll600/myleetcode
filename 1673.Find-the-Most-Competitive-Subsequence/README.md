# [1673. Find the Most Competitive Subsequence](https://leetcode.com/problems/find-the-most-competitive-subsequence/)

## 题目

Given an integer array `nums` and a positive integer `k`, return *the most **competitive** subsequence of* `nums` *of size* `k`.

An array's subsequence is a resulting sequence obtained by erasing some (possibly zero) elements from the array.

We define that a subsequence `a` is more **competitive** than a subsequence `b` (of the same length) if in the first position where `a` and `b` differ, subsequence `a` has a number **less** than the corresponding number in `b`. For example, `[1,3,4]` is more competitive than `[1,3,5]` because the first position they differ is at the final number, and `4` is less than `5`.

 

**Example 1:**

```
Input: nums = [3,5,2,6], k = 2
Output: [2,6]
Explanation: Among the set of every possible subsequence: {[3,5], [3,2], [3,6], [5,2], [5,6], [2,6]}, [2,6] is the most competitive.
```

**Example 2:**

```
Input: nums = [2,4,3,3,5,4,9,6], k = 4
Output: [2,3,3,4]
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `0 <= nums[i] <= 109`
- `1 <= k <= nums.length`

## 题目大意

给你一个整数数组 `nums` 和一个正整数 `k` ，返回长度为 `k` 且最具 竞争力 的 `nums` 子序列。数组的子序列是从数组中删除一些元素（可能不删除元素）得到的序列

在子序列 `a` 和子序列 `b` 第一个不相同的位置上，如果 `a` 中的数字小于 `b` 中对应的数字，那么我们称子序列 `a` 比子序列 `b`（相同长度下）更具 竞争力

例如，`[1,3,4]` 比 `[1,3,5]` 更具竞争力，在第一个不相同的位置，也就是最后一个位置上， `4` 小于 `5` 

## 解题思路

这道题目，跟着题目在纸上画一画，就不难发现，这里就是使用单调栈，接下来就是确定入站和出栈的条件了

这道题目除了利用单调栈，维护元素的有序性之外，还需要注意的是，题目最终的结果必须是 k 个元素，也就是说即使不满足单调有序的条件，也需要优先满足这个条件

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/find-the-most-competitive-subsequence/solution/zhan-java-by-liweiwei1419-rkac/)

````c++
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        const int len = nums.size();
        if (k == len) {
            return nums;
        }
        // 要删除元素的而个数
        int rm_cnt = len - k;
        stack<int> sta;
        for (int i = 0; i < len; ++i) {
            // 出栈条件
            while (rm_cnt > 0 && !sta.empty() && nums[i] < sta.top()) {
                sta.pop();
                --rm_cnt;
            }
            // 入栈条件
            sta.push(nums[i]);
        }
        
        // 如果栈内元素数目没有达到要求
        while (rm_cnt > 0) {
            sta.pop();
            --rm_cnt;
        }
        
        vector<int> res;
        while (!sta.empty()) {
            res.push_back(sta.top());
            sta.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
````

