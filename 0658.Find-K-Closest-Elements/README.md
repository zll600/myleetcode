# [658. Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/)

## 题目

Given a **sorted** integer array `arr`, two integers `k` and `x`, return the `k` closest integers to `x` in the array. The result should also be sorted in ascending order.

An integer `a` is closer to `x` than an integer `b` if:

- `|a - x| < |b - x|`, or
- `|a - x| == |b - x|` and `a < b`

 

**Example 1:**

```
Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
```

**Example 2:**

```
Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]
```

 

**Constraints:**

- `1 <= k <= arr.length`
- `1 <= arr.length <= 104`
- `arr` is sorted in **ascending** order.
- `-104 <= arr[i], x <= 104`

## 题目大意

给定一个 *已经排序* 的整数数组 `arr`，和两个整数 `k` 和 `x`，返回数组中最接近 `x` 的 `k` 个数，结果依旧按照升序排序，

`a` 比 `b` 更接近 `x`，如果：

- `|a - x| < |b - x|`, or
- `|a - x| == |b - x|` 且 a < b`

## 解题思路

题目中的数组有按照升序排序的，要在有序的数据中找出一个给定的值，或者接近的值，我就想到了 二分查找，

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0658.Find-K-Closest-Elements/)

利用二分查找找出答案区间的起始地址，

````c++
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        const int len = arr.size();

        // 这里 二分查找 整个区间的起点
        int low = 0, high = len - k;
        while (low < high) {
            const int mid = low + (high - low) / 2;

            if (x - arr[mid] > arr[mid + k] - x) {
                // 我们要找的low 是符合条件的最大的
                // 说明原来的 low 是不符合条件的
                low = mid + 1;
            } else {
                // 原来的high 是符合 条件的
                high = mid;
            }
        }

        return vector<int>(arr.begin() + low, arr.begin() + low + k);
    }
};
````
