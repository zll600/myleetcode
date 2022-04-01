# [1071. Greatest Common Divisor of Strings](https://leetcode-cn.com/problems/greatest-common-divisor-of-strings/)

## 题目

For two strings `s` and `t`, we say "`t` divides `s`" if and only if `s = t + ... + t` (i.e., `t` is concatenated with itself one or more times).

Given two strings `str1` and `str2`, return *the largest string* `x` *such that* `x` *divides both* `str1` *and* `str2`.

 

**Example 1:**

```
Input: str1 = "ABCABC", str2 = "ABC"
Output: "ABC"
```

**Example 2:**

```
Input: str1 = "ABABAB", str2 = "ABAB"
Output: "AB"
```

**Example 3:**

```
Input: str1 = "LEET", str2 = "CODE"
Output: ""
```

 

**Constraints:**

- `1 <= str1.length, str2.length <= 1000`
- `str1` and `str2` consist of English uppercase letters.

## 题目大意

对于字符串 `s` 和 `t`，只有在 `s = t + ... + t`（t 自身连接 1 次或多次）时，我们才认定 “t 能除尽 s”。

给定两个字符串 `str1 和 str2` 。返回 最长字符串 `x` , 要求满足 `x` 能除尽 `str1` 且 `X` 能除尽 `str2` 。


## 解题思路


### Solution 1:


````c++
class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        if (str1 + str2 != str2 + str1) {
            // 这里先做一个判断
            return "";
        }

        return str1.substr(0, gcd(str1.size(), str2.size()));
    }

 private:
    // 求出最大公约数
    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }

        return gcd(b, a % b);
    }
};
````
