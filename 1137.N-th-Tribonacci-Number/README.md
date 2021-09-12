# [1137. N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/)

## 题目

The Tribonacci sequence Tn is defined as follows: 

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given `n`, return the value of Tn.

 

**Example 1:**

```
Input: n = 4
Output: 4
Explanation:
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4
```

**Example 2:**

```
Input: n = 25
Output: 1389537
```

 

**Constraints:**

- `0 <= n <= 37`
- The answer is guaranteed to fit within a 32-bit integer, ie. `answer <= 2^31 - 1`.

## 题目大意

泰波那契序列 Tn 定义如下： 

T0 = 0, T1 = 1, T2 = 1, 且在 n >= 0 的条件下 Tn+3 = Tn + Tn+1 + Tn+2

给你整数 n，请返回第 n 个泰波那契数 Tn 的值。

## 解题思路

* 这里使用的是动态规划的解法，不过在求解的时候，使用有限个变量来代替 dp 数组，

## 代码

````c++
class Solution {
public:
    int tribonacci(int n) {
        if (n < 2) {
            return n;
        }
        if (n == 2) {
            return 1;
        }
        
        int first  = 0;
        int second = 1;
        int third = 1;
        
        for (int i = 3; i <= n; ++i) {
            int tmp1 = third;
            int tmp2 = second;
            
            third = first + second + third;
            second = tmp1;
            first = tmp2;
        }
        return third;
    }
};
````



