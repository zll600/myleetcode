# [565. Array Nesting](https://leetcode.com/problems/array-nesting/)

## 题目

You are given an integer array `nums` of length `n` where `nums` is a permutation of the numbers in the range `[0, n - 1]`.

You should build a set `s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... }` subjected to the following rule:

- The first element in `s[k]` starts with the selection of the element `nums[k]` of `index = k`.
- The next element in `s[k]` should be `nums[nums[k]]`, and then `nums[nums[nums[k]]]`, and so on.
- We stop adding right before a duplicate element occurs in `s[k]`.

Return *the longest length of a set* `s[k]`.

 

**Example 1:**

```
Input: nums = [5,4,0,3,1,6,2]
Output: 4
Explanation: 
nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
One of the longest sets s[k]:
s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}
```

**Example 2:**

```
Input: nums = [0,1,2]
Output: 1
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `0 <= nums[i] < nums.length`
- All the values of `nums` are **unique**.

## 题目大意


## 解题思路

这道题目如果不小心，很容易超时，

这道题目的思路可以参考 [这种解法](https://leetcode-cn.com/problems/array-nesting/solution/tu-jie-2chong-jie-ti-si-lu-di-2chong-jie-7ksf/)

这里的核心思想即为，

- 如果当前下标未访问，则按照规则去访问每个可以访问到的元素，直到出现循环

- 如果当前下标已经访问过了，那么当前下标开始的所有元素都已经访问过了

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/array-nesting/solution/ji-yi-hua-jie-fa-chang-liang-kong-jian-j-7crw/)

这里有一个很重要的思想，就是如果如果我们在求解一个大的问题的时候，计算了一个小问题，那么我们可以不用去考虑小问题

````c++
```
