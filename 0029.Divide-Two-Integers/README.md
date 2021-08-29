# [29. Divide Two Integers](https://leetcode.com/problems/divide-two-integers/)

## 题目

Given two integers `dividend` and `divisor`, divide two integers without using multiplication, division, and mod operator.

Return the quotient after dividing `dividend` by `divisor`.

The integer division should truncate toward zero, which means losing its fractional part. For example, `truncate(8.345) = 8` and `truncate(-2.7335) = -2`.

**Note:** Assume we are dealing with an environment that could only store integers within the **32-bit** signed integer range: `[−231, 231 − 1]`. For this problem, assume that your function **returns** `231 − 1` **when the division result overflows**.

 

**Example 1:**

```
Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = truncate(3.33333..) = 3.
```

**Example 2:**

```
Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = truncate(-2.33333..) = -2.
```

**Example 3:**

```
Input: dividend = 0, divisor = 1
Output: 0
```

**Example 4:**

```
Input: dividend = 1, divisor = 1
Output: 1
```

 

**Constraints:**

- `-231 <= dividend, divisor <= 231 - 1`
- `divisor != 0`

## 题目大意

给定一个被除数`dividend`和除数`divisor`，要求不使用乘法、除法和模运算将两数相除，返回被除数除以除数所得到的商`quotient`，

整数除法应该使用趋零截断，舍弃小数部分，例如：truncate(8.345) = 8, truncate(-2.735) = -2,

说明：

* 除数和被除数都可以表示为32为有符号整数，
* 除数不为0
* 如果计算发生溢出返回2^32 - 1,

## 解题思路

这到题目可以用 **二分法 + 倍增乘法**来解决，这道题目先重点理解二分的使用， 

这里附上一个题解，两个题解，用于二分搜索区间划分的调整：

https://leetcode-cn.com/problems/search-insert-position/solution/te-bie-hao-yong-de-er-fen-cha-fa-fa-mo-ban-python-/

本题主要参考的题解：里面有**二分和快速乘法** 的模板

https://leetcode-cn.com/problems/divide-two-integers/solution/shua-chuan-lc-er-fen-bei-zeng-cheng-fa-j-m73b/

## 代码

````c++
class Solution {
public:
    int divide(int dividend, int divisor) {
        long e_dividend = 1L * dividend;
        long e_divisor = 1L * divisor;
        bool negat = false;
        
        if ((e_dividend < 0 && e_divisor > 0)
           || (e_dividend > 0 && e_divisor < 0)) {
            negat = true;
        }
        
        if (e_dividend < 0) {
            e_dividend *= -1;
        }
        if (e_divisor < 0) {
            e_divisor *= -1;
        }
        
        long lo = 0;
        long hi = e_dividend;
        while (lo < hi) {
            long mid = (lo + hi + 1) >> 1;
            if (mul(mid, e_divisor) <= e_dividend) {	// 这里需要重点理解，这里是条件，二分的核心就是根据条件来调整区间
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        
        long res = negat ? -lo : lo;
        if (res > INT_MAX || res < INT_MIN) {
            return INT_MAX;
        }
        return static_cast<int>(res);
    }
    
 private:
    long mul(long a, long k) {
        long res = 0;
        
        while (k > 0) {
            if ((k & 1) == 1) {
                res += a;
            }
            k >>= 1;
            a += a;
        }
        
        return res;
    }
};
````



