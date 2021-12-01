# [172. Factorial Trailing Zeroes](https://leetcode.com/problems/factorial-trailing-zeroes/)

## 题目

Given an integer `n`, return *the number of trailing zeroes in* `n!`.

Note that `n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1`.

 

**Example 1:**

```
Input: n = 3
Output: 0
Explanation: 3! = 6, no trailing zero.
```

**Example 2:**

```
Input: n = 5
Output: 1
Explanation: 5! = 120, one trailing zero.
```

**Example 3:**

```
Input: n = 0
Output: 0
```

 

**Constraints:**

- `0 <= n <= 104`

 

**Follow up:** Could you write a solution that works in logarithmic time complexity?

## 题目大意

给定一个整数 n，返回 n! 结果尾数中零的数量。说明: 你算法的时间复杂度应为 O(log n) 。

## 解题思路

求一个数结尾的0，就是求这个数可以被 10 整除多少次，但是这道题如果直接乘法计算的话，肯定是会超时的，数据规模有点大

这道题是一道比较考验数学能力的题目，也可以参考这篇题解：https://leetcode-cn.com/problems/factorial-trailing-zeroes/solution/xiang-xi-tong-su-de-si-lu-fen-xi-by-windliang-3/

### Solution 1:

这种解法可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0100~0199/0172.Factorial-Trailing-Zeroes/

````c++
class Solution {
public:
    int trailingZeroes(int n) {
        if (n / 5 == 0) {
            return 0;
        }
        
        return n / 5 + trailingZeroes(n / 5);
    }
};
````

