# [1018. Binary Prefix Divisible By 5](https://leetcode.com/problems/binary-prefix-divisible-by-5/)

## 题目

You are given a binary array `nums` (**0-indexed**).

We define `xi` as the number whose binary representation is the subarray `nums[0..i]` (from most-significant-bit to least-significant-bit).

- For example, if `nums = [1,0,1]`, then `x0 = 1`, `x1 = 2`, and `x2 = 5`.

Return *an array of booleans* `answer` *where* `answer[i]` *is* `true` *if* `xi` *is divisible by* `5`.

 

**Example 1:**

```
Input: nums = [0,1,1]
Output: [true,false,false]
Explanation: The input numbers in binary are 0, 01, 011; which are 0, 1, and 3 in base-10.
Only the first number is divisible by 5, so answer[0] is true.
```

**Example 2:**

```
Input: nums = [1,1,1]
Output: [false,false,false]
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `nums[i]` is either `0` or `1`.

## 题目大意

给定 二进制 的数组 nums。我们定义 `xi`：从 `nums[0]` 到 `nums[i]` 的第 `i` 个子数组被解释为一个二进制数（从最高有效位到最低有效位）

返回布尔值列表 `answer`，只有当 `xi` 可以被 `5` 整除时，答案 `answer[i]` 为 `true`，否则为 `false`

## 解题思路

这道题目的主要就是考察位运算，这里简单的运用 移位运算和 或运算即可

### Solution 1:

````c++
class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        vector<bool> res(nums.size());

        // 计算  xi 然后进行判断
        int cur = 0;
        for (int i = 0; i < nums.size(); ++i) {
            cur = (cur << 1 | nums[i]) % 5;
            res[i] = cur == 0;
        }

        return res;
    }
};
````
