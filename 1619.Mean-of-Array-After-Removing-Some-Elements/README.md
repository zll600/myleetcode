# [1619. Mean of Array After Removing Some Elements](https://leetcode.com/problems/mean-of-array-after-removing-some-elements/)

## 题目

Given an integer array `arr`, return *the mean of the remaining integers after removing the smallest `5%` and the largest `5%` of the elements.*

Answers within `10-5` of the **actual answer** will be considered accepted.

 

**Example 1:**

```
Input: arr = [1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3]
Output: 2.00000
Explanation: After erasing the minimum and the maximum values of this array, all elements are equal to 2, so the mean is 2.
```

**Example 2:**

```
Input: arr = [6,2,7,5,1,2,0,3,10,2,5,0,5,5,0,8,7,6,8,0]
Output: 4.00000
```

**Example 3:**

```
Input: arr = [6,0,7,0,7,5,7,8,3,4,0,7,8,1,6,8,1,1,2,4,8,1,9,5,4,3,8,5,10,8,6,6,1,0,6,10,8,2,3,4]
Output: 4.77778
```

 

**Constraints:**

- `20 <= arr.length <= 1000`
- `arr.length` **is a multiple** of `20`.
- `0 <= arr[i] <= 105`

## 题目大意

给你一个整数数组 `arr` ，请你删除最小 `5%` 的数字和最大 `5%` 的数字后，剩余数字的平均值。与 **标准答案** 误差在 `10-5` 的结果都被视为正确结果。

## 解题思路


### Solution 1:

直接排序，然后除去前面 5% 和 后面 5%，计算总和，然后球平均值即可

````c++
class Solution {
public:
    double trimMean(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        const int arr_len = arr.size();
        int sum = 0;
        for (int i = arr_len / 20; i < arr_len - arr_len / 20; ++i) {
            sum += arr[i];
        }
        return 1.0 * sum / (arr_len - arr_len / 10);
    }
};
````
