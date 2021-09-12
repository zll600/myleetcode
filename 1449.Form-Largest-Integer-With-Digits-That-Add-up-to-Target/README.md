# [1449. Form Largest Integer With Digits That Add up to Target](https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/)

## 题目

Given an array of integers `cost` and an integer `target`. Return the **maximum** integer you can paint under the following rules:

- The cost of painting a digit (i+1) is given by `cost[i]` (0 indexed).
- The total cost used must be equal to `target`.
- Integer does not have digits 0.

Since the answer may be too large, return it as string.

If there is no way to paint any integer given the condition, return "0".

 

**Example 1:**

```
Input: cost = [4,3,2,5,6,7,2,5,5], target = 9
Output: "7772"
Explanation:  The cost to paint the digit '7' is 2, and the digit '2' is 3. Then cost("7772") = 2*3+ 3*1 = 9. You could also paint "977", but "7772" is the largest number.
Digit    cost
  1  ->   4
  2  ->   3
  3  ->   2
  4  ->   5
  5  ->   6
  6  ->   7
  7  ->   2
  8  ->   5
  9  ->   5
```

**Example 2:**

```
Input: cost = [7,6,5,5,5,6,8,7,8], target = 12
Output: "85"
Explanation: The cost to paint the digit '8' is 7, and the digit '5' is 5. Then cost("85") = 7 + 5 = 12.
```

**Example 3:**

```
Input: cost = [2,4,6,2,4,6,4,4,4], target = 5
Output: "0"
Explanation: It's not possible to paint any integer with total cost equal to target.
```

**Example 4:**

```
Input: cost = [6,10,15,40,40,40,40,40,40], target = 47
Output: "32211"
```

 

**Constraints:**

- `cost.length == 9`
- `1 <= cost[i] <= 5000`
- `1 <= target <= 5000`

## 题目大意

给定一个整数数组 cost 和一个整数 target，返回你能得到的满足下面规则最大值：

* 当前数位添加一个数位(i + 1)的成本是 cast[i],（下标从0 开始）
* 总成本必须等于 target
* 整数不包含 0，

将结果按照字符串返回

如果按照上述条件无法得到结果，返回 “0”，

## 解题思路

