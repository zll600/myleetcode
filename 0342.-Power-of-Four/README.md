# [342. Power of Four](https://leetcode.com/problems/power-of-four/)

## 题目

Given an integer `n`, return *`true` if it is a power of four. Otherwise, return `false`*.

An integer `n` is a power of four, if there exists an integer `x` such that `n == 4x`.

 

**Example 1:**

```
Input: n = 16
Output: true
```

**Example 2:**

```
Input: n = 5
Output: false
```

**Example 3:**

```
Input: n = 1
Output: true
```

 

**Constraints:**

- `-231 <= n <= 231 - 1`

 

**Follow up:** Could you solve it without loops/recursion?

## 题目大意

给定一个数，如果其是  4 的幂，返回true，否则返回 false，

## 解题思路

* 如果使用循环的话，这道题目可以使用将十进制转化为 4 进制来做，然后右移，判断最后n == 1即可
* 如果不能使用循环和递归，这里需要一些数论的知识（留待以后实现）

## 代码

``````c++
class Solution {
public:
    // 这里将这个数转化为四进制，然后右移，如果最后剩下一位 1，就表示是 4 的幂
    bool isPowerOfFour(int n) {
        if (n < 1) {
            return false;
        }
        
        while (n > 1) {
            if (n % 4 != 0) {   // 转化为 4 进制
                return false;
            }
            n /= 4; // 右移
        }
        
        return n == 1;  // 剩下的一位是 1，
    }
};
``````

