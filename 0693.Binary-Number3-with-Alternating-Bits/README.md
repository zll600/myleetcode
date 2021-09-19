# [693. Binary Number with Alternating Bits](https://leetcode.com/problems/binary-number-with-alternating-bits/)

## 题目

Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.

 

**Example 1:**

```
Input: n = 5
Output: true
Explanation: The binary representation of 5 is: 101
```

**Example 2:**

```
Input: n = 7
Output: false
Explanation: The binary representation of 7 is: 111.
```

**Example 3:**

```
Input: n = 11
Output: false
Explanation: The binary representation of 11 is: 1011.
```

**Example 4:**

```
Input: n = 10
Output: true
Explanation: The binary representation of 10 is: 1010.
```

**Example 5:**

```
Input: n = 3
Output: false
```

 

**Constraints:**

- `1 <= n <= 231 - 1`

## 题目大意

* 给定一个整数，检查它是否是交替二进制数，也就是说，相邻的二进制位的值不相同

## 解题思路

## 代码

````c++
class Solution {
public:
    /*
    n               1 0 1 0 1 0
    n >> 1          0 1 0 1 0 1
    n ^ (n >> 1)    1 1 1 1 1 1
    n               1 1 1 1 1 1
    n + 1         1 0 0 0 0 0 0
    n & (n + 1)     0 0 0 0 0 0
    */
    
    bool hasAlternatingBits1(int n) {
        // n 为正整数，所以为了防止出现溢出，这里将 n 强制转换为 unsigned int，
        unsigned int tmp = static_cast<unsigned int>(n);
        
        tmp ^= (tmp >> 1);
        return (tmp & (tmp + 1)) == 0;
    }
    
    // 直接模拟
    bool hasAlternatingBits(int n) {
        int last = 0;
        int curr = 0;
        
        while (n > 0) {
            last = n & 1;
            n >>= 1;
            curr = n & 1;
            // 这里不再进行左移操作，这样这次的 curr 就是下次的 last，可以做到相邻两位进行比较
            if (last == curr) {
                return false;
            }
        }
        return true;
    }
};
````

