# [1877. Minimize Maximum Pair Sum in Array](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/)

## 题目

The **pair sum** of a pair `(a,b)` is equal to `a + b`. The **maximum pair sum** is the largest **pair sum** in a list of pairs.

- For example, if we have pairs `(1,5)`, `(2,3)`, and `(4,4)`, the **maximum pair sum** would be `max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8`.

Given an array `nums` of **even** length `n`, pair up the elements of `nums` into `n / 2` pairs such that:

- Each element of `nums` is in **exactly one** pair, and
- The **maximum pair sum** is **minimized**.

Return *the minimized **maximum pair sum** after optimally pairing up the elements*.

 

**Example 1:**

```
Input: nums = [3,5,2,3]
Output: 7
Explanation: The elements can be paired up into pairs (3,3) and (5,2).
The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.
```

**Example 2:**

```
Input: nums = [3,5,4,2,4,6]
Output: 8
Explanation: The elements can be paired up into pairs (3,5), (4,4), and (6,2).
The maximum pair sum is max(3+5, 4+4, 6+2) = max(8, 8, 8) = 8.
```

 

**Constraints:**

- `n == nums.length`
- `2 <= n <= 105`
- `n` is **even**.
- `1 <= nums[i] <= 105`

## 题目大意

一个数对 pair(a, b)的数对和等于 a + b，最大数对和是一个数对数组中的最大数对和

- 比方说，如果我们有数对 (1,5) ，(2,3) 和 (4,4)，**最大数对和** 为 max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8 。

给定一个偶数长度 n 的数组，将数组中的数分为 n / 2个数对

- nums 中每个元素 **恰好** 在 一个 数对中，且
- **最大数对和** 的值 **最小** 

返回在优化后的数对划分后，最小化的最大数对和

## 解题思路

这道题可以用贪心算法来解，直观的感觉就是将原数组排序之后取数组中较小一边的一个值和数组中较大一边的值组成数对，可以使得最大数对和最小

这道题的具体证明见这篇题解：https://leetcode-cn.com/problems/minimize-maximum-pair-sum-in-array/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-ru29y/，我以后一定会把数学好好补上来的。

## 代码

````c++
class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0;
        
        int len = nums.size();
        for (int i = 0, j = len - 1; i < j; ++i, --j) {
            res = max(res, nums[i] + nums[j]);
        }
        
        return res;
    }
};
````

