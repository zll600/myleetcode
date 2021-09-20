# [191. Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)

## 题目

Write a function that takes an unsigned integer and returns the number of '1' bits it has (also known as the [Hamming weight](http://en.wikipedia.org/wiki/Hamming_weight)).

**Note:**

- Note that in some languages, such as Java, there is no unsigned integer type. In this case, the input will be given as a signed integer type. It should not affect your implementation, as the integer's internal binary representation is the same, whether it is signed or unsigned.
- In Java, the compiler represents the signed integers using [2's complement notation](https://en.wikipedia.org/wiki/Two's_complement). Therefore, in **Example 3**, the input represents the signed integer. `-3`.

 

**Example 1:**

```
Input: n = 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.
```

**Example 2:**

```
Input: n = 00000000000000000000000010000000
Output: 1
Explanation: The input binary string 00000000000000000000000010000000 has a total of one '1' bit.
```

**Example 3:**

```
Input: n = 11111111111111111111111111111101
Output: 31
Explanation: The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.
```

 

**Constraints:**

- The input must be a **binary string** of length `32`.

 

**Follow up:** If this function is called many times, how would you optimize it?

## 题目大意

编写一个函数，给定一个无符号整数，计算其二进制位中 1 的个数。

## 解题思路

* 这道题的具体思路就是，不断清除最低位的 1，清除多少次就有多少个 1，n & (n - 1) 这个操作可以清除最低位的 1，

## 代码

``````c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;

        while (n != 0) {
            n &= (n - 1);
            ++res;
        }

        return res;
    }
};
``````

