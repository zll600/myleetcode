# [258. Add Digits](https://leetcode.com/problems/add-digits/)

## 题目

Given an integer `num`, repeatedly add all its digits until the result has only one digit, and return it.

 

**Example 1:**

```
Input: num = 38
Output: 2
Explanation: The process is
38 --> 3 + 8 --> 11
11 --> 1 + 1 --> 2 
Since 2 has only one digit, return it.
```

**Example 2:**

```
Input: num = 0
Output: 0
```

 

**Constraints:**

- `0 <= num <= 231 - 1`

 

**Follow up:** Could you do it without any loop/recursion in `O(1)` runtime?

## 题目大意

给定一个整数，重复地将它的各位相加直到结果只有一位数字，

## 解题思路

这道题要做出来，其实不难，可以用递归也可以用循环

这道题可以参考这篇题解：https://leetcode-cn.com/problems/add-digits/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-5-7/，其实是一道数学的题目，不过用 循环和 递归也是可以解决的。

### Solution 1: Ioop

````c++
class Solution {
public:
    int addDigits(int num) {
        if (num < 10) {
            return num;
        }
        
        while (num >= 10) {
            int cur = num;
            int ans = 0;
            // 累加每一位数
            while (cur) {
                ans += cur % 10;
                cur /= 10;
            }
            num = ans;
        }
        
        return num;
    }
};
````

### Solution 2: Recursion

````c++
class Solution {
public:
    int addDigits(int num) {
        if (num < 10) {
            return num;
        }
        
        int next = 0;
        while (num) {
            next += num % 10;
            num /= 10;
        }
        
        return addDigits(next);
    }
};
````



