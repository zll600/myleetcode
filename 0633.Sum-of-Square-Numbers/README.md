# [633. Sum of Square Numbers](https://leetcode.com/problems/sum-of-square-numbers/)

## 题目

Given a non-negative integer `c`, decide whether there're two integers `a` and `b` such that `a2 + b2 = c`.

 

**Example 1:**

```
Input: c = 5
Output: true
Explanation: 1 * 1 + 2 * 2 = 5
```

**Example 2:**

```
Input: c = 3
Output: false
```

 

**Constraints:**

- `0 <= c <= 231 - 1`

## 题目大意

给定一个 **非负整数** `c` ，你要判断是否存在两个整数 `a` 和 `b`，使得 `a^2 + b^2 = c`


## 解题思路

这里需要注意的是，整个搜索区间是有序的，这一点很重要

### Solution 1: Two Pointers

就是双指针左右夹逼，注意中间的乘积是有可能溢出的

````c++
class Solution {
public:
    bool judgeSquareSum(int c) {
        // 双指针左右夹逼
        int high = static_cast<int>(sqrt(c));
        int low = 0;
        
        while (low <= high) {
            const long long sum = 1LL * low * low + high * high;
            
            if (sum < c) {
                ++low;
            } else if (sum > c) {
                --high;
            } else {
                return true;
            }
        }
        return false;
    }
};
````
