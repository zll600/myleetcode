#### [1471. The k Strongest Values in an Array](https://leetcode.cn/problems/the-k-strongest-values-in-an-array/)

Given an array of integers `arr` and an integer `k`.

A value `arr[i]` is said to be stronger than a value `arr[j]` if `|arr[i] - m| > |arr[j] - m|` where `m` is the **median** of the array.
 If `|arr[i] - m| == |arr[j] - m|`, then `arr[i]` is said to be stronger than `arr[j]` if `arr[i] > arr[j]`.

Return *a list of the strongest `k`* values in the array. return the answer **in any arbitrary order**.

**Median** is the middle value in an ordered integer  list. More formally, if the length of the list is n, the median is the  element in position `((n - 1) / 2)` in the sorted list **(0-indexed)**.

- For `arr = [6, -3, 7, 2, 11]`, `n = 5` and the median is obtained by sorting the array `arr = [-3, 2, 6, 7, 11]` and the median is `arr[m]` where `m = ((5 - 1) / 2) = 2`. The median is `6`.
- For `arr = [-7, 22, 17, 3]`, `n = 4` and the median is obtained by sorting the array `arr = [-7, 3, 17, 22]` and the median is `arr[m]` where `m = ((4 - 1) / 2) = 1`. The median is `3`.

 

**Example 1:**

```
Input: arr = [1,2,3,4,5], k = 2
Output: [5,1]
Explanation: Median is 3, the elements of the array sorted by the strongest are [5,1,4,2,3]. The strongest 2 elements are [5, 1]. [1, 5] is also accepted answer.
Please note that although |5 - 3| == |1 - 3| but 5 is stronger than 1 because 5 > 1.
```

**Example 2:**

```
Input: arr = [1,1,3,5,5], k = 2
Output: [5,5]
Explanation: Median is 3, the elements of the array sorted by the strongest are [5,5,1,1,3]. The strongest 2 elements are [5, 5].
```

**Example 3:**

```
Input: arr = [6,7,11,7,6,8], k = 5
Output: [11,8,6,6,7]
Explanation: Median is 7, the elements of the array sorted by the strongest are [11,8,6,6,7,7].
Any permutation of [11,8,6,6,7] is accepted.
```

 

**Constraints:**

- `1 <= arr.length <= 105`
- `-105 <= arr[i] <= 105`
- `1 <= k <= arr.length`

## 题目大意

给你一个整数数组 `arr` 和一个整数 `k` 

设 `m` 为数组的中位数，只要满足下述两个前提之一，就可以判定 `arr[i]` 的值比 `arr[j]` 的值更强：

- `|arr[i] - m| > |arr[j] - m|`
- `|arr[i] - m| == |arr[j] - m|，且 arr[i] > arr[j]`

请返回由数组中最强的 `k` 个值组成的列表。答案可以以 *任意顺序* 返回

中位数 是一个有序整数列表中处于中间位置的值。形式上，如果列表的长度为 `n` ，那么中位数就是该有序列表（下标从 0 开始）中位于 `((n - 1) / 2)` 的元素

- 例如 `arr = [6, -3, 7, 2, 11]`，`n = 5`：数组排序后得到 `arr = [-3, 2, 6, 7, 11]` ，数组的中间位置为 `m = ((5 - 1) / 2) = 2` ，中位数 `arr[m]` 的值为 `6` 
- 例如 `arr = [-7, 22, 17, 3]`，`n = 4`：数组排序后得到 `arr = [-7, 3, 17, 22]` ，数组的中间位置为 `m = ((4 - 1) / 2) = 1` ，中位数 `arr[m]` 的值为 `3` 

## 解题思路 

### Solution 1: Sort

这种解法重写排序，规则，在求出中位数之后，重排整个数组

````c++
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        // 取中位数
        sort(arr.begin(), arr.end());
        int mid = arr[(arr.size() - 1) / 2];
        // 重新排序
        sort(arr.begin(), arr.end(), [&](int lhs, int rhs) {
            if (abs(lhs - mid) == abs(rhs - mid)) {
                return lhs > rhs;
            }
            return abs(lhs - mid) > abs(rhs - mid);
        });

        // 取前 k 个即可
        return vector<int>(arr.begin(), arr.begin() + k);
    }
};
````

