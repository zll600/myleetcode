# [2170. Minimum Operations to Make the Array Alternating](https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/)

## 题目

You are given a **0-indexed** array `nums` consisting of `n` positive integers.

The array `nums` is called **alternating** if:

- `nums[i - 2] == nums[i]`, where `2 <= i <= n - 1`.
- `nums[i - 1] != nums[i]`, where `1 <= i <= n - 1`.

In one **operation**, you can choose an index `i` and **change** `nums[i]` into **any** positive integer.

Return *the **minimum number of operations** required to make the array alternating*.

 

**Example 1:**

```
Input: nums = [3,1,3,2,4,3]
Output: 3
Explanation:
One way to make the array alternating is by converting it to [3,1,3,1,3,1].
The number of operations required in this case is 3.
It can be proven that it is not possible to make the array alternating in less than 3 operations. 
```

**Example 2:**

```
Input: nums = [1,2,2,2,2]
Output: 2
Explanation:
One way to make the array alternating is by converting it to [1,2,1,2,1].
The number of operations required in this case is 2.
Note that the array cannot be converted to [2,2,2,2,2] because in this case nums[0] == nums[1] which violates the conditions of an alternating array.
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `1 <= nums[i] <= 105`

## 题目大意

给你一个下标从 `0` 开始的数组 `nums` ，该数组由 `n` 个正整数组成

如果满足下述条件，则数组 `nums` 是一个 交替数组 ：

- `nums[i - 2] == nums[i]` ，其中 `2 <= i <= n - 1`
- `nums[i - 1] != nums[i]` ，其中 `1 <= i <= n - 1`

在一步 操作 中，你可以选择下标 `i` 并将 `nums[i]` 更改 为 任一 正整数。返回使数组变成交替数组的 最少操作数

## 解题思路

这道题目不难想到，最终只可能有两个数，要使得操作次数最少，就需要尽可能将不符合条件的值改为出现次数最大的值

另外根据题目中的条件，可以发现，奇数位置上的值最终一定是相同的，偶数位置上的值最终也一定是相同的

所以可以考虑，将数组分为奇偶两组，将两组的值，分别设置为两组出现频数最大的数，

但是同时还需要考虑，两组的最大值相等的情况，所以在求每最大值的的时候，可以求出出现频数靠前的前两个数，并选择使得改动次数最小的哪一个

### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/minimum-operations-to-make-the-array-alternating/solution/tan-xin-fen-lei-tao-lun-by-endlesscheng-qj15/)

如果题解中的代码看不太懂，可以看看评论区

`````c++
class Solution {
public:
    int minimumOperations(vector<int>& nums) {

        unordered_map<int, int> odd_freq, even_freq;
        for (int i = 0; i < nums.size(); ++i) {
            if (i & 1) {
                ++odd_freq[nums[i]];
            } else {
                ++even_freq[nums[i]];
            }
        }

        vector<pair<int, int>> odd_max = GetFreq(odd_freq);
        vector<pair<int, int>> even_max = GetFreq(even_freq);
        // 如果奇数位置和偶数位置不用使用最大频数的值不同，直接计算即可
        if (odd_max[0].first != even_max[0].first) {
            return nums.size() - odd_max[0].second - even_max[0].second;
        }

        // 如果最大频数的数相同，还需要考虑第二大的值，并且选取一个操作次数最少的结果
        return nums.size() - max(odd_max[0].second + even_max[1].second,
                                 odd_max[1].second + even_max[0].second);
    }

 private:
    vector<pair<int, int>> GetFreq(const unordered_map<int, int> freqs) {
        vector<pair<int, int>> res(freqs.begin(), freqs.end());
        sort(res.begin(), res.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.second > rhs.second;
        });
        // 返回前两个最大的值
        res.resize(2);
        return res;
    }
};
`````

