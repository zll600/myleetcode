# [504. Base 7](https://leetcode-cn.com/problems/base-7/)

## 题目

Given an integer `num`, return *a string of its **base 7** representation*.

 

**Example 1:**

```
Input: num = 100
Output: "202"
```

**Example 2:**

```
Input: num = -7
Output: "-10"
```

 

**Constraints:**

- `-107 <= num <= 107`

## 题目大意

给定一个整数 `num`，将其转化为 **7 进制**，并以字符串形式输出。

## 解题思路

解决进制转化问题最常用的就是辗转相除法，这里有一个需要注意的问题就是负数的处理，

### Solution 1:

```c++
class Solution {
public:
    string convertToBase7(int num) {
        if (num == 0) {
            return "0";
        }
        // 判断是正数还是负数
        bool negative = num < 0 ? true : false;
        string str = "";
        while (num) {
            // 这里只加上绝对值的部分
            str += to_string(abs(num%7));
            num /= 7;
        }
        if (negative) {
            str += '-';
        }
        reverse(str.begin(), str.end());
        
        return str;
    }
};
```

这里补充一下小数部分的求法

```c++
class Solution {
 public:
    int RemainToBase(int num, int base, int max_len) {
        string ans = "";
        int len = 0;
        int cur = 1 / base;

        while(num && len < max_len) {
            int tmp = num / cur; // 最多可以含有几个
            ans += to_string(tmp);  // 拼接上去
            num -= tmp * cur; // 从原来的数值中减去
            cur /= base; // 增加次方
            len += 1; // 动态维护结果字符串的长度
        }
        return "." + ans;
    }
};
```

