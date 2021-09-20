# [231. Power of Two](https://leetcode.com/problems/power-of-two/)

## 题目

Given an integer `n`, return *`true` if it is a power of two. Otherwise, return `false`*.

An integer `n` is a power of two, if there exists an integer `x` such that `n == 2x`.

 

**Example 1:**

```
Input: n = 1
Output: true
Explanation: 20 = 1
```

**Example 2:**

```
Input: n = 16
Output: true
Explanation: 24 = 16
```

**Example 3:**

```
Input: n = 3
Output: false
```

**Example 4:**

```
Input: n = 4
Output: true
```

**Example 5:**

```
Input: n = 5
Output: false
```

 

**Constraints:**

- `-231 <= n <= 231 - 1`

 

**Follow up:** Could you solve it without loops/recursion?

## 题目大意

给定一个数，如果它是 2 的幂返回 true ，否则返回 false，

## 解题思路

* 若 n 满足条件，则
  * 恒有 n & (n - 1) == 0，这是因为：
    * n 二进制最高位为1，其余所有位为0
    * n - 1 二进制最高位为 0，其余所有位为0，
  * 一定满足 n > 0

## 代码

````c++
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
};
````

