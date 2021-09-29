# [7. Reverse Integer](https://leetcode.com/problems/reverse-integer/)

## 题目

Given a signed 32-bit integer `x`, return `x` *with its digits reversed*. If reversing `x` causes the value to go outside the signed 32-bit integer range `[-231, 231 - 1]`, then return `0`.

**Assume the environment does not allow you to store 64-bit integers (signed or unsigned).**

 

**Example 1:**

```
Input: x = 123
Output: 321
```

**Example 2:**

```
Input: x = -123
Output: -321
```

**Example 3:**

```
Input: x = 120
Output: 21
```

**Example 4:**

```
Input: x = 0
Output: 0
```

 

**Constraints:**

- `-231 <= x <= 231 - 1`

## 题目大意

给定一个有符号的 32 位整数x，返回将 x 的各个位反转之后得到的数字，注意:假设我们的环境只能存储得下 32 位的有符号整数，则其数值范围为 [−2^31, 2^31 − 1]。请根据这个假设，如果反转后整数溢出那么就返回 0。

这里要求不能使用 64 位的有符号数或无符号数

## 解题思路

这个题在转化的时候要注意边界的处理

* 如果是 0，直接返回 0，
* 如果转换可能越界，下面两种方法，提供了两种思路
* 溢出的条件有两个，分别是大于最大的，小于最小的，

## 解法1

先全部转化完毕后再进行判断是否越界，这里要用一个临时的 long 型变量，不知道到底允许，

``````c++
class Solution {
public:
    int reverse(int x) {
        // 0 不用转换
        if (x == 0) {
            return 0;
        }
        
        long tmp = 0;
        
        while (x != 0) {
            tmp = tmp * 10 + x % 10;
            x /= 10;
        }
        
        if (tmp < INT_MIN || tmp > INT_MAX) {
            return 0;
        }
        
        return tmp;
    }
};
``````

### 解法2

解法二是反转的过程中进行判断，如果发生溢出，则直接返回，这种方法不需要一个 long 型的临时变量

更多的细节，可以参考这篇题解：https://leetcode-cn.com/problems/reverse-integer/solution/hua-jie-suan-fa-7-zheng-shu-fan-zhuan-by-guanpengc/



`````c++
class Solution {
public:
    int reverse(int x) {
        if (x == 0) {
            return 0;
        }
        
        int res = 0;
        while (x != 0) {
            int cur = x % 10;
            // 是否会向上溢出
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && cur > INT_MAX % 10)) {
                return 0;
            } else if (res < INT_MIN / 10 || (res == INT_MIN / 10 && cur < INT_MIN % 10)) {
                // 是否会向下溢出
                return 0;
            }
            
            res = res * 10 + cur;
            x /= 10;
        }
        
        return res;
    }
};
`````

