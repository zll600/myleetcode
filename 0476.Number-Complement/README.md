# [476. Number Complement](https://leetcode-cn.com/problems/number-complement/)

## 题目

The **complement** of an integer is the integer you get when you flip all the `0`'s to `1`'s and all the `1`'s to `0`'s in its binary representation.

- For example, The integer `5` is `"101"` in binary and its **complement** is `"010"` which is the integer `2`.

Given an integer `num`, return *its complement*.

 

**Example 1:**

```
Input: num = 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
```

**Example 2:**

```
Input: num = 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
```

 

**Constraints:**

- `1 <= num < 231`

 

**Note:** This question is the same as 1009: https://leetcode.com/problems/complement-of-base-10-integer/

## 题目大意

补数就是对数的所有二进制位取反

- 例如，整数 `5` 的二进制表示是 `"101"` ，取反后得到 `"010"` ，再转回十进制表示得到补数 `2` 。

给定一个数，返回它的补数

## 解题思路

这道题目是一道位运算的题目

这道题目可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0476.Number-Complement/

## Solution  1:

先构造合适的 mask，然后异或，这里需要注意整数溢出的情况

````c++
class Solution {
public:
    int findComplement(int num) {
        long tmp = 1;  // 这里使用 long，不然会发生整型溢出
        while (tmp <= num) {
            tmp <<= 1;  // 0000 1000 .... 将 tmp 中比num中最高位的1 还要高的那位置 1
        }
        
        return (tmp - 1) ^ num;  // 然后减一与 nums 异或
    }
};
````

### Solution 2:

位运算还是有很多问题，要自己多练习练习

````c++
// 解法一
func findComplement(num int) int {
	xx := ^0 // ^0 = 1111111111111111111111
	for xx&num > 0 {
		xx <<= 1 // 构造出来的 xx = 1111111…000000，0 的个数就是 num 的长度
	}
	return ^xx ^ num // xx ^ num，结果是前面的 0 全是 1 的num，再取反即是答案
}

````

