# [1053. Previous Permutation With One Swap](https://leetcode.cn/problems/previous-permutation-with-one-swap/)

## 题目

Given an array of positive integers `arr` (not necessarily distinct), return *the lexicographically largest permutation that is smaller than* `arr`, that can be **made with exactly one swap** (A *swap* exchanges the positions of two numbers `arr[i]` and `arr[j]`). If it cannot be done, then return the same array.

 

**Example 1:**

```
Input: arr = [3,2,1]
Output: [3,1,2]
Explanation: Swapping 2 and 1.
```

**Example 2:**

```
Input: arr = [1,1,5]
Output: [1,1,5]
Explanation: This is already the smallest permutation.
```

**Example 3:**

```
Input: arr = [1,9,4,6,7]
Output: [1,7,4,6,9]
Explanation: Swapping 9 and 7.
```

 

**Constraints:**

- `1 <= arr.length <= 104`
- `1 <= arr[i] <= 104`

## 题目大意

给你一个正整数的数组 A（其中的元素不一定完全不同），请你返回可在 一次交换（交换两数字 A[i] 和 A[j] 的位置）后得到的、按字典序排列小于 A 的最大可能排列。

如果无法这么操作，就请返回原数组

## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/previous-permutation-with-one-swap/solution/han-xiang-xi-fen-xi-si-lu-jian-dan-ti-mu-you-qu-by/)

首先找到第一个降序的位置 i，即满足 `arr[i] > arr[i + 1]`

然后在 i 的左边查找小于 arr[i]，且最接近 arr[i] 的值

````c++
class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& arr) {
        const int len = arr.size();
        for (int i = len - 2; i >= 0; --i) {
            // 找到第一个降序的地方
            if (arr[i] > arr[i + 1]) {
                int index = -1;
                int value = -1;
                // 找到左边最接近的位置
                for (int j = i + 1; j < len; ++j) {
                    if (arr[i] > arr[j]) {
                        if (arr[j] > value) {
                            value = arr[j];
                            index = j;
                        }
                    }
                }
                if (index != -1) {
                    swap(arr[i], arr[index]);
                    break;
                }
            }
        }
        return arr;
    }
};
````
