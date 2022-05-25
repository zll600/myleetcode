# [1685. Sum of Absolute Differences in a Sorted Array](https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/)

## 题目

You are given an integer array `nums` sorted in **non-decreasing** order.

Build and return *an integer array* `result` *with the same length as* `nums` *such that* `result[i]` *is equal to the **summation of absolute differences** between* `nums[i]` *and all the other elements in the array.*

In other words, `result[i]` is equal to `sum(|nums[i]-nums[j]|)` where `0 <= j < nums.length` and `j != i` (**0-indexed**).

 

**Example 1:**

```
Input: nums = [2,3,5]
Output: [4,3,5]
Explanation: Assuming the arrays are 0-indexed, then
result[0] = |2-2| + |2-3| + |2-5| = 0 + 1 + 3 = 4,
result[1] = |3-2| + |3-3| + |3-5| = 1 + 0 + 2 = 3,
result[2] = |5-2| + |5-3| + |5-5| = 3 + 2 + 0 = 5.
```

**Example 2:**

```
Input: nums = [1,4,6,8,10]
Output: [24,15,13,15,21]
```

 

**Constraints:**

- `2 <= nums.length <= 105`
- `1 <= nums[i] <= nums[i + 1] <= 104`

## 题目大意

给你一个 *非递减* 有序整数数组 `nums` 。请你建立并返回一个整数数组 `result`，它跟 `nums` 长度相同，且`result[i]` 等于 `nums[i]` 与数组中所有其他元素差的绝对值之和

换句话说， `result[i]` 等于 `sum(|nums[i]-nums[j]|)` ，其中 `0 <= j < nums.length` 且 `j != i` (下标从 0 开始)

## 解题思路

这道题目还是比较容易想到 使用前缀和来做预处理来降低时间复杂度的，

这道题目的暴力解法就遍历每个位置，然后再次遍历整个数组，但是题目中的有序的特性就没有用上，

根据有序的特性，则第 ith 数左边的数均小于 i，右边的数均大于 i,

- 左边的数对结果的贡献就是 i - num,
- 右边的数对结果的贡献就是 num - i,
- i 对自身结果的贡献是 0，

所以问题就转移到了如果快速求出左边和右边的 贡献，因为左边的数都要被 i 减，右边的数都要减去 i,所以只要求出 [0, i - 1] 的和 和 [i + 1, len - 1] 的和即可，这里使用前缀和就很容易做了

这道题目也可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1600~1699/1685.Sum-of-Absolute-Differences-in-a-Sorted-Array/)

### Solution 1:



````c++
class Solution {
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        const int len = nums.size();
        vector<int> prefix_sum(len + 1);
        for (int i = 1; i <= len; ++i) {
            prefix_sum[i] = prefix_sum[i - 1] + nums[i - 1];
        }
        
        vector<int> ans(len);
        for (int i = 0; i < len; ++i) {
            int cur = nums[i];
            int left_sum = cur * i - prefix_sum[i];
            int right_sum = prefix_sum[len] - prefix_sum[i + 1] - (len - i - 1) * cur;
            ans[i] = left_sum + right_sum;
        }
        return ans;
    }
};
````
