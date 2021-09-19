# [371. Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/)

## 题目

Given two integers `a` and `b`, return *the sum of the two integers without using the operators* `+` *and* `-`.

 

**Example 1:**

```
Input: a = 1, b = 2
Output: 3
```

**Example 2:**

```
Input: a = 2, b = 3
Output: 5
```

 

**Constraints:**

- `-1000 <= a, b <= 1000`

## 题目大意

不用运算符 ‘+’ 和 '-'，计算两数之和

## 解题思路

* 利用异或运算，我们可以实现不带进位的加法，接下来就是如何解决进位的问题
* 只有当异或的结果是 1 和 1 造成的0时才应该进位，所以只有当 a 和 b 的对应位均为1 的时候才应该进位，

## 代码

````c++
class Solution {
public:
    // 递归法
    int getSum1(int a, int b) {
        if (a == 0) {
            return b;
        }
        if (b == 0) {
            return a;
        }
        
        return getSum(static_cast<unsigned int>(a & b) << 1, a ^ b);
    }
    
    // 迭代法
    int getSum(int a, int b) {
        while(b!=0) tie(a,b)=pair{(a^b),(unsigned int)(a&b)<<1};
        return a;
    }
};
````

