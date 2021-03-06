# [1304. Find N Unique Integers Sum up to Zero](https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/)

## 题目

Given an integer `n`, return **any** array containing `n` **unique** integers such that they add up to `0`.

 

**Example 1:**

```
Input: n = 5
Output: [-7,-1,1,3,4]
Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].
```

**Example 2:**

```
Input: n = 3
Output: [-1,0,1]
```

**Example 3:**

```
Input: n = 1
Output: [0]
```

 

**Constraints:**

- `1 <= n <= 1000`

## 题目大意

给你一个整数 `n`，请你返回 任意 一个由 `n` 个 各不相同 的整数组成的数组，并且这 `n` 个数相加和为 `0`

## 解题思路

这道题目要求数组中不能出现重复的数字，这是这道题目比较难的地方

### Solution 1:

这道题还是比较简单的，这里对称的赋值就可以了

````c++
class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> arr(n, 0);
        int left = 0, right = n - 1;
        int start = 1;

        while (left < right) {
            arr[left] = start;
            ++left;
            arr[right] = -start;
            --right;
            ++start;
        }
        return arr;
    }
};
````
