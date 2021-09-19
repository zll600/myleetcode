# [268. Missing Number](https://leetcode.com/problems/missing-number/) 

## 题目

Given an array `nums` containing `n` distinct numbers in the range `[0, n]`, return *the only number in the range that is missing from the array.*

**Follow up:** Could you implement a solution using only `O(1)` extra space complexity and `O(n)` runtime complexity?

 

**Example 1:**

```
Input: nums = [3,0,1]
Output: 2
Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.
```

**Example 2:**

```
Input: nums = [0,1]
Output: 2
Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number in the range since it does not appear in nums.
```

**Example 3:**

```
Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number in the range since it does not appear in nums.
```

**Example 4:**

```
Input: nums = [0]
Output: 1
Explanation: n = 1 since there is 1 number, so all numbers are in the range [0,1]. 1 is the missing number in the range since it does not appear in nums.
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 104`
- `0 <= nums[i] <= n`
- All the numbers of `nums` are **unique**.

## 题目大意

给定一个在[0, n]范围内包含 n 个数的数组，返回这个数组中没有出现的那个数

你可以在线性时间和常数的空间中解决该问题吗

## 解体思路

* 这道题目就是利用异或的性质，x^ x = 0，我们可以利用这个这性质让数组下标和元素的值进行异或，数组下标是[0, n - 1]，所以循环结束后，还需要和 n 进行异或

## 代码

````c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int xors = 0, i = 0;
        for (; i < nums.size(); ++i) {
            xors = xors ^  i ^ nums[i];
        }
        
        return xors ^ i;
    }
};
````

