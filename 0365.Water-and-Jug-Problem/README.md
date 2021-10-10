# [365. Water and Jug Problem](https://leetcode.com/problems/water-and-jug-problem/)

## 题目

You are given two jugs with capacities `jug1Capacity` and `jug2Capacity` liters. There is an infinite amount of water supply available. Determine whether it is possible to measure exactly `targetCapacity` liters using these two jugs.

If `targetCapacity` liters of water are measurable, you must have `targetCapacity` liters of water contained **within one or both buckets** by the end.

Operations allowed:

- Fill any of the jugs with water.
- Empty any of the jugs.
- Pour water from one jug into another till the other jug is completely full, or the first jug itself is empty.

 

**Example 1:**

```
Input: jug1Capacity = 3, jug2Capacity = 5, targetCapacity = 4
Output: true
Explanation: The famous Die Hard example 
```

**Example 2:**

```
Input: jug1Capacity = 2, jug2Capacity = 6, targetCapacity = 5
Output: false
```

**Example 3:**

```
Input: jug1Capacity = 1, jug2Capacity = 2, targetCapacity = 3
Output: true
```

 

**Constraints:**

- `1 <= jug1Capacity, jug2Capacity, targetCapacity <= 106`

## 题目大意

给定两个容量分别为 jug1Capacity 和 jug2Capacity 升的水壶，这里有无限多的水，决定能否通过这两个水壶得到准确的 targetCapacity 升水

如果可以，最后请用以上水壶中的一或两个来盛放取得的 *z升* 水。

下面时你允许的选项：

* 装满任意一个水壶
* 清空任意一个水壶
* 从一个水壶向另外一个水壶倒水，直到装满或者倒空

## 解题思路

