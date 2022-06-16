# [1191. K-Concatenation Maximum Sum](https://leetcode.cn/problems/k-concatenation-maximum-sum/)

## 题目

Given an integer array `arr` and an integer `k`, modify the array by repeating it `k` times.

For example, if `arr = [1, 2]` and `k = 3 `then the modified array will be `[1, 2, 1, 2, 1, 2]`.

Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be `0` and its sum in that case is `0`.

As the answer can be very large, return the answer **modulo** `109 + 7`.

 

**Example 1:**

```
Input: arr = [1,2], k = 3
Output: 9
```

**Example 2:**

```
Input: arr = [1,-2,1], k = 5
Output: 2
```

**Example 3:**

```
Input: arr = [-1,-2], k = 7
Output: 0
```

 

**Constraints:**

- `1 <= arr.length <= 105`
- `1 <= k <= 105`
- `-104 <= arr[i] <= 104`

## 题目大意

给定一个整数数组 `arr` 和一个整数 `k` ，通过重复 `k` 次来修改数组

例如，如果 `arr = [1, 2]` ， `k = 3` ，那么修改后的数组将是 `[1, 2, 1, 2, 1, 2]`

返回修改后的数组中的最大的子数组之和。注意，子数组长度可以是 `0`，在这种情况下它的总和也是 `0`

由于 结果可能会很大，需要返回的 `109 + 7` 的 *模*

## 解题思路



### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/k-concatenation-maximum-sum/solution/java-kadanesuan-fa-yu-jie-ti-si-lu-by-zdxiq125/)

这篇题解将的很详细，

首先可以利用至多两次循环知道一个最大的连续子数组的和 `max_so_far`，这里注意重复 k 次，可以产生 k 个数组而不是 k + 1 个，

所以在求出 `max_so_far` 之后，如果整个数组的累加和大于 0，那么说明可以继续扩展，但此时肯定有一个数组可能没有完全被充分累加

`````c++
class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        const int len = arr.size();
        long long max_of_end = arr[0] > 0 ? arr[0] : 0;
        long long max_so_far = max_of_end;
        long long total = arr[0];
        // at most two loops for max_so_far
        for (int i = 1; i < min(k, 2) * len; ++i) {
            max_of_end = max(max_of_end + arr[i % len], 1LL * arr[i % len]);
            max_so_far = max(max_of_end, max_so_far);
            if (i < len) {
                total += arr[i];
            }
        }
        // cout << max_so_far << " --  " << total << endl;

        while (total > 0 && --k >= 2) {
            max_so_far = (max_so_far + total) % mod_;
        }
        return max_so_far % mod_;
    }

 private:
    const int mod_ = 1000000007;
};
````
