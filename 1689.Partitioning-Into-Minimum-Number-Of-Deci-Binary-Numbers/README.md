# [1689. Partitioning Into Minimum Number Of Deci-Binary Numbers](https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/)

## 题目

A decimal number is called **deci-binary** if each of its digits is either `0` or `1` without any leading zeros. For example, `101` and `1100` are **deci-binary**, while `112` and `3001` are not.

Given a string `n` that represents a positive decimal integer, return *the **minimum** number of positive **deci-binary** numbers needed so that they sum up to* `n`*.*

 

**Example 1:**

```
Input: n = "32"
Output: 3
Explanation: 10 + 11 + 11 = 32
```

**Example 2:**

```
Input: n = "82734"
Output: 8
```

**Example 3:**

```
Input: n = "27346209830709182346"
Output: 9
```

 

**Constraints:**

- `1 <= n.length <= 105`
- `n` consists of only digits.
- `n` does not contain any leading zeros and represents a positive integer.

## 题目大意

如果一个十进制数字不含任何前导零，且每一位上的数字不是 0 就是 1 ，那么该数字就是一个 十-二进制数 。例如，101 和 1100 都是  十-二进制数，而 112 和 3001 不是

给你一个表示十进制整数的字符串 `n` ，返回和为 `n` 的 十-二进制数 的最少数目

## 解题思路

通过观察题目给出的几个例子，不难发现，对于给定的字符串，对于最大的数每次对应的位放 1 才能消耗掉这个最高位，所以只要消耗光这个最高位即可

### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1600~1699/1689.Partitioning-Into-Minimum-Number-Of-Deci-Binary-Numbers/)

````c++
class Solution {
public:
    int minPartitions(string n) {
        return *max_element(n.begin(), n.end()) - '0';
    }
};
````
