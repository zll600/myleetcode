# [605. Can Place Flowers](https://leetcode.com/problems/can-place-flowers/)

## 题目

You have a long flowerbed in which some of the plots are planted, and some are not. However, flowers cannot be planted in **adjacent** plots.

Given an integer array `flowerbed` containing `0`'s and `1`'s, where `0` means empty and `1` means not empty, and an integer `n`, return *if* `n` new flowers can be planted in the `flowerbed` without violating the no-adjacent-flowers rule.

 

**Example 1:**

```
Input: flowerbed = [1,0,0,0,1], n = 1
Output: true
```

**Example 2:**

```
Input: flowerbed = [1,0,0,0,1], n = 2
Output: false
```

 

**Constraints:**

- `1 <= flowerbed.length <= 2 * 104`
- `flowerbed[i]` is `0` or `1`.
- There are no two adjacent flowers in `flowerbed`.
- `0 <= n <= flowerbed.length`

## 题目大意

你有一个很长的花坛，里面一些地块被种植，一些没有，然而，这些花不能被种在相邻的地方，

给定一个种有花的整数数组包括 0 和 1，其中 0 意味着空，1 意味中不空，

再 给定一个整数 n，返回这 n 朵花是否可以不用违反规则全被种进花坛

## 解题思路

这道题目是一道贪心的题目，如果当前位置可以种植一朵花就种一朵，



## 代码

