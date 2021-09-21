# [50. Pow(x, n)](https://leetcode.com/problems/powx-n/)

## 题目

Implement [pow(x, n)](http://www.cplusplus.com/reference/valarray/pow/), which calculates `x` raised to the power `n` (i.e., `xn`).

 

**Example 1:**

```
Input: x = 2.00000, n = 10
Output: 1024.00000
```

**Example 2:**

```
Input: x = 2.10000, n = 3
Output: 9.26100
```

**Example 3:**

```
Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
```

 

**Constraints:**

- `-100.0 < x < 100.0`
- `-231 <= n <= 231-1`
- `-104 <= xn <= 104`

## 题目大意

实现函数 pow(x, n)，即计算 x 的 n 次幂函数

## 解题思路

* 这道题目可以利用分治的思想来做，将 n 不断二分下去，但这个题目有几个坑：
* 如果 n 为 负数，需要取倒数
* 如果n 为奇数，由于 C++ 的除法采用趋零截断，所以造成 n / 2 +  n / 2 = n - 1，所以这里还需要 额外乘一个x，
* 另外还需要注意的一点是，如果 n == INT_MIN，则 n = -n，会发生溢出，这个问题有两种解决方法，一种是直接更改形参的类型为 long，但是不是特别建议，二是使用一个新的 long 型的变量来解决，

## 代码

`````c++
class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) {
            return  1;
        }
        if (n == 1) {
            return x;
        }
        
        long b = n;
        if (b < 0) {
            b = -b;
            x = 1 / x;
        }
        
        double tmp = myPow(x, b / 2);
        if (b % 2 != 0) {
            return tmp * tmp * x;
        }
        return tmp * tmp;
   }
};
`````

