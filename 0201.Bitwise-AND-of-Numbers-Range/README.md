# [201. Bitwise AND of Numbers Range](https://leetcode.com/problems/bitwise-and-of-numbers-range/)

## 题目

Given two integers `left` and `right` that represent the range `[left, right]`, return *the bitwise AND of all numbers in this range, inclusive*.

 

**Example 1:**

```
Input: left = 5, right = 7
Output: 4
```

**Example 2:**

```
Input: left = 0, right = 0
Output: 0
```

**Example 3:**

```
Input: left = 1, right = 2147483647
Output: 0
```

 

**Constraints:**

- `0 <= left <= right <= 231 - 1`

## 题目大意

求给定区间[left, right] 内所有数 AND 操作之后的结果

## 解题思路

* 这道题目直接遍历会 TLE
* 这道题利用与运算的特性：如果与元素的位上有任意一位为0，则这一位结果为0，
* 另外还有另外一个条件就是位于 left 和 right 之间的数，和 left 或者 right 一定具有相同的前缀，除前缀之外的其他位均会出现0，所以与运算的结果为0
* 所以这道题目我们只需要排除低位为0 的位置，具体办法是同时右移左边界和右边界，直到二者的值相等，然后通过左移补上对应位数的0

## 代码

````c++
class Solution {
public:
    // 暴力解法，超时
    int rangeBitwiseAnd1(int left, int right) {
        int res = left;
        
        for (int i = left + 1; i <= right; ++i) {
            res &= i;
        }
        
        return res;
    }
    
    // 排除低位的0
    int rangeBitwiseAnd2(int left, int right) {
        if (left == 0) {
            return 0;
        }
        
        int moved = 0;
        while (left != right) { // 同时右移左边界和右边界，
            left >>= 1;
            right >>= 1;
            ++moved;
        }
        
        return left << static_cast<unsigned int>(moved);
    }
    
    // Brian Kernighan 算法。
    int rangeBitwiseAnd(int left, int right) {
        if (left == 0) {
            return 0;
        }
        
        while (left < right) {
            right &= (right - 1);
        }
        
        return right;
    }
};
````

