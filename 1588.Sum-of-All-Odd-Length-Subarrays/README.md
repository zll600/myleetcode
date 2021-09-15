# [1588. Sum of All Odd Length Subarrays](https://leetcode.com/problems/sum-of-all-odd-length-subarrays/)

## 题目

Given an array of positive integers `arr`, calculate the sum of all possible odd-length subarrays.

A subarray is a contiguous subsequence of the array.

Return *the sum of all odd-length subarrays of* `arr`.

 

**Example 1:**

```
Input: arr = [1,4,2,5,3]
Output: 58
Explanation: The odd-length subarrays of arr and their sums are:
[1] = 1
[4] = 4
[2] = 2
[5] = 5
[3] = 3
[1,4,2] = 7
[4,2,5] = 11
[2,5,3] = 10
[1,4,2,5,3] = 15
If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58
```

**Example 2:**

```
Input: arr = [1,2]
Output: 3
Explanation: There are only 2 subarrays of odd length, [1] and [2]. Their sum is 3.
```

**Example 3:**

```
Input: arr = [10,11,12]
Output: 66
```

 

**Constraints:**

- `1 <= arr.length <= 100`
- `1 <= arr[i] <= 1000`

## 题目大意

给定一个正整数数组 arr，计算所有奇数长度的数组子数组的和，返回所有奇数长度子数组和之和

## 解题思路

* 最直接的方法是枚举所有的奇数子数组，有两个变量可以决定一个子数组，一个是子数组的长度，一个子数组的起点，然后计算每个的和
* 看到区间求和问题，我们可以考虑利用前缀和来做预处理，减少一层循环

## 代码

`````c++
class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        vector<int> sum;
        sum.push_back(0);   // 为了避免分类讨论，这里插入一个空值
        partial_sum(arr.begin(), arr.end(), back_inserter(sum));
        
        int size = arr.size();
        int res = 0;
        for (int len = 1; len <= size; len += 2) {
            for (int start = 0; start + len - 1 < size; ++start) {
                int last = start + len - 1;
                res += sum[last + 1] - sum[start];
            }
        }
        
        return res;
    }
};
`````

