# [1480. Running Sum of 1d Array](https://leetcode.com/problems/running-sum-of-1d-array/)

## 题目

Given an array `nums`. We define a running sum of an array as `runningSum[i] = sum(nums[0]…nums[i])`.

Return the running sum of `nums`.

 

**Example 1:**

```
Input: nums = [1,2,3,4]
Output: [1,3,6,10]
Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].
```

**Example 2:**

```
Input: nums = [1,1,1,1,1]
Output: [1,2,3,4,5]
Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].
```

**Example 3:**

```
Input: nums = [3,1,2,10,1]
Output: [3,4,6,16,17]
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `-10^6 <= nums[i] <= 10^6`

## 题目大意

给定一个数组，我们定义一个动态数组和的定义为`runningSum[i] = sum(nums[0]...nums[i])`

## 解题思路

* 这道题只是计算每个位置上的前缀和而已，没有什么特别的坑

## 代码

`````c++
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int size = nums.size();
        vector<int> running(size);
        running[0] = nums[0];
        
        for (int i = 1; i < size; ++i) {
            running[i] = running[i - 1] + nums[i];
        }
        
        return running;
    }
};
`````

