# [405. Convert a Number to Hexadecimal](https://leetcode.com/problems/convert-a-number-to-hexadecimal/)

## 题目大意

Given an integer `num`, return *a string representing its hexadecimal representation*. For negative integers, [two’s complement](https://en.wikipedia.org/wiki/Two's_complement) method is used.

All the letters in the answer string should be lowercase characters, and there should not be any leading zeros in the answer except for the zero itself.

**Note:** You are not allowed to use any built-in library method to directly solve this problem.

 

**Example 1:**

```
Input: num = 26
Output: "1a"
```

**Example 2:**

```
Input: num = -1
Output: "ffffffff"
```

 

**Constraints:**

- `-231 <= num <= 231 - 1`

## 题目大意

给定一个整数 num，返回用字符串表示的这个数字的十六进制数，对于负数，我们经常使用二进制补码的方法

注意:

* 十六进制中所有字母(a-f)都必须是小写。
* 十六进制字符串中不能包含多余的前导零。如果要转化的数为0，那么以单个字符'0'来表示；对于其他情况，十六进制字符串中的第一个字符将不会是0字符
* 给定的数确保在32位有符号整数范围内。
* 不能使用任何由库提供的将数字直接转换或格式化为十六进制的方法。

## 解题思路

概括一下，就是将十进制数转化为十六进制数，注意 0  和负数的相关处理

### 解法1

这道题目的总体思路不难，重点在 0 和负数的处理上，

* 如果是 0 ，我们直接返回 0
* 如果是负数，我们需要将负数转化为对应的补码的形式，做法是加上 2 的32次方的，这里可以去看一下《深入理解计算机系统》第二章，有详细介绍

````c++
class Solution {
public:
    string toHex(int num) {
        if (num == 0) {
            return "0";
        }
        
        // 为了避免发生溢出，这里使用 long 型来存储转化之后的补码
        long conv = num;
        if (conv < 0) {
            conv += 1L << 32;
        }
        
        vector<char> alph;
        while (conv) {
            alph.push_back(dict.at(conv % 16));
            conv /= 16;
        }
        reverse(alph.begin(), alph.end());
        
        return string(alph.begin(), alph.end());
    }
    
 private:
    unordered_map<int, char> dict  = {
        {0, '0'},
        {1, '1'},
        {2, '2'},
        {3, '3'},
        {4, '4'},
        {5, '5'},
        {6, '6'},
        {7, '7'},
        {8, '8'},
        {9, '9'},
        {10, 'a'},
        {11, 'b'},
        {12, 'c'},
        {13, 'd'},
        {14, 'e'},
        {15, 'f'}
    };
};
````

