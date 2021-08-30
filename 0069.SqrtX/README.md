# [69. Sqrt(x)](https://leetcode.com/problems/sqrtx/)

## 题目

Given a non-negative integer `x`, compute and return *the square root of* `x`.

Since the return type is an integer, the decimal digits are **truncated**, and only **the integer part** of the result is returned.

**Note:** You are not allowed to use any built-in exponent function or operator, such as `pow(x, 0.5)` or `x ** 0.5`.

 

**Example 1:**

```
Input: x = 4
Output: 2
```

**Example 2:**

```
Input: x = 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since the decimal part is truncated, 2 is returned.
```

 

**Constraints:**

- `0 <= x <= 231 - 1`

## 题目大意

给定一个非负整数，计算并返回这个数的平方根。由于返回类型是整数类型，所以你只需要返回整数部分即可。

## 解题思路

* 这道题可以使用二分查找来解决，但是在进行二分的时候右许多容易出错的点，可以代码中已经标示出来了。
* while(lo < hi) （[lo, hi]）这中写法将整个区间划分为两部分，一部分，肯定不包含最终的结果，另一部分，可能包含最终的结果。考虑满足怎样条件的 mid 肯定不是最终答案，然后其反面就是最终答案所在的区间。这中写法还有一个好处是，退出循环时 lo == hi，返回任意一个都可以。
* 这道题还需要注意 mid 的求解方法，

## 代码

````c++
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        if (x == 1) {
            return 1;
        }
        
        
        int lo = 1;
        int hi = x / 2;
        
        while (lo < hi) {
            int mid = lo + (hi - lo + 1L) / 2;  // 这里通过 +1L 操作将 mid 改为向上取整，
                                                // 并且进行暂时的整型提升，来避免溢出
            if (mid > x / mid) {       // 这里将乘法转变为除法，避免溢出
                hi = mid - 1;
            } else {
                lo = mid;
            }
        }
        
        return lo;
    }
};
````

