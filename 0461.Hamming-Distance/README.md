# [461. Hamming Distance](https://leetcode.com/problems/hamming-distance/)

## 题目

The [Hamming distance](https://en.wikipedia.org/wiki/Hamming_distance) between two integers is the number of positions at which the corresponding bits are different.

Given two integers `x` and `y`, return *the **Hamming distance** between them*.

 

**Example 1:**

```
Input: x = 1, y = 4
Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different.
```

**Example 2:**

```
Input: x = 3, y = 1
Output: 1
```

 

**Constraints:**

- `0 <= x, y <= 231 - 1`

## 题目大意

两个整数的汉明距离是指这两个数对应二进制位不同的位置的数目

给定两个数 x 和 y，返回他们之间的汉明距离

## 解题思路

* 利用异或运算相应位置上不同值异或结果为 0的特点，只要求出 x 和 y 异或之后有多少个1，就有多少个不同的位置，
* 计算有多少个 1，利用的是 x &= (x - 1)，不断清除最低位的 1，

## 代码

````c++
class Solution {
public:
    int hammingDistance(int x, int y) {
        int res = 0;
        for (int xors = x ^ y; xors != 0; xors &= (xors - 1)) {
            ++res;
        }
        return res;
    }
};
````

