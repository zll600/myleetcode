# [65. Valid Number](https://leetcode.com/problems/valid-number/)

## 题目

A **valid number** can be split up into these components (in order):

1. A **decimal number** or an **integer**.
2. (Optional) An `'e'` or `'E'`, followed by an **integer**.

A **decimal number** can be split up into these components (in order):

1. (Optional) A sign character (either `'+'` or `'-'`).
2. One of the following formats:
   1. One or more digits, followed by a dot `'.'`.
   2. One or more digits, followed by a dot `'.'`, followed by one or more digits.
   3. A dot `'.'`, followed by one or more digits.

An **integer** can be split up into these components (in order):

1. (Optional) A sign character (either `'+'` or `'-'`).
2. One or more digits.

For example, all the following are valid numbers: `["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"]`, while the following are not valid numbers: `["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"]`.

Given a string `s`, return `true` *if* `s` *is a **valid number***.

 

**Example 1:**

```
Input: s = "0"
Output: true
```

**Example 2:**

```
Input: s = "e"
Output: false
```

**Example 3:**

```
Input: s = "."
Output: false
```

**Example 4:**

```
Input: s = ".1"
Output: true
```

 

**Constraints:**

- `1 <= s.length <= 20`
- `s` consists of only English letters (both uppercase and lowercase), digits (`0-9`), plus `'+'`, minus `'-'`, or dot `'.'`.

## 题目大意

一个有效的数字（按顺序）可以分成如下一个部分：

1. 一个小数或者一个整数
2. （可选）一个 `'e'` 或 `'E'` ，后面跟着一个 **整数**

一个小数（按顺序）可以分为如下几个部分：

1. （可选的）一个符号可以是`‘+’` 或者 `-`
2. 下述格式之一：
   1. 至少一位数字，后面跟着一个点 `'.'`
   2. 至少一位数字，后面跟着一个点 `'.'` ，后面再跟着至少一位数字
   3. 一个点 `'.'` ，后面跟着至少一位数字

**整数**（按顺序）可以分成以下几个部分：

1. （可选）一个符号字符（`'+'` 或 `'-'`）
2. 至少一位数字

部分有效数字列举如下：

`````
["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"]
`````


部分无效数字列举如下：

`````
["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"]
`````

给你一个字符串 s ，如果 s 是一个 有效数字 ，请返回 true 。

## 解题思路

这道题目就是一道字符串模拟的题目，不过条件有点多，难就难在如何设计好分支判断

### 解法1（模拟）

可以利用e/E 来分割数字，e 之前可以是小数也可以是整数， E 之后只能是整数，

* 对于整数而言，至少存在一个数字，如果有符号，第一位是符号位
* 对于小数而言：
  * 只能存在一个 '.'，除此之外只能出现数字
  * 至少有一位数字
  * 可能由符号位

`````c++
class Solution {
public:
    bool isNumber(string str) {
        bool is_decimal = false;
        // 查找字符串中是否有 分隔符
        int spl = -1;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '.') {  // '.' 必定出现在 'e'/'E'之前，所以可以检测出
                is_decimal = true;
            }
            
            if (str[i] == 'e' || str[i] == 'E') {
                if (spl == -1) {
                    spl = i;
                } else {
                    return false;
                }
            }
        }
        
        bool res = true;
        if (spl != -1) {
            // 判断 e 之前的部分
            if (is_decimal) {
                res &= IsDecimal(str, 0, spl - 1);
            } else {
                res &= IsInteger(str, 0, spl - 1);
            }
            
            // 判断之后的部分
            res &= IsInteger(str, spl + 1, str.size() - 1);
            
            return res;
        }
        
        return is_decimal ? IsDecimal(str, 0, str.size() - 1) : IsInteger(str, 0, str.size() - 1);
    }
    
 private:
    // 检查 [first, last] 区间的数是否为整数
    bool IsInteger(const string& str, int first, int last) {
        if (first > last) {
            return false;
        }
        
        // 判断符号位
        if (str[first] == '+' || str[first] == '-') {
            first++;
        }
        // 至少由一位数字
        if (first > last) {
            return false;
        }
        
        while (first <= last) {
            // 是否有不合发的字符
            if (!isdigit(str[first])) {
                return false;
            }
            first++;
        }
        
        return true;
    }
    
    // 检查 [first, last] 区间的数是否为小数
    bool IsDecimal(const string& str, int first, int last) {
        if (first > last) {  // 输入是否合法
            return false;
        }
        
        // 是否有符号位
        if (str[first] == '+' || str[first] == '-') {
            first++;
        }
        
        bool dot = true;
        bool before = false;
        while (first <= last && str[first] != '.') {
            if (isdigit(str[first])) {
                before = true;
            }
            
            // '.'之前只能出席数字
            if (!isdigit(str[first])) {
                return false;
            }
            
            first++;
        }
        
        // 没有 '.'
        if (first > last) {
            return false;
        }
        
        first++;  // 跳过 '.'
        bool after  = false;
        while (first <= last) {
           if (isdigit(str[first])) {
                after = true;
            }
            
            // '.'后面只能出现数字
            if (!isdigit(str[first])) {
                return false;
            }
            
            first++;
        }
        
        return before || after;
    }
};
`````

