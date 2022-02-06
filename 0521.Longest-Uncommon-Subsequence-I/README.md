# [521. Longest Uncommon Subsequence I](https://leetcode-cn.com/problems/longest-uncommon-subsequence-i/)

## 题目

Given two strings `a` and `b`, return *the length of the **longest uncommon subsequence** between* `a` *and* `b`. If the longest uncommon subsequence does not exist, return `-1`.

An **uncommon subsequence** between two strings is a string that is a **subsequence of one but not the other**.

A **subsequence** of a string `s` is a string that can be obtained after deleting any number of characters from `s`.

- For example, `"abc"` is a subsequence of `"aebdc"` because you can delete the underlined characters in `"aebdc"` to get `"abc"`. Other subsequences of `"aebdc"` include `"aebdc"`, `"aeb"`, and `""` (empty string).

 

**Example 1:**

```
Input: a = "aba", b = "cdc"
Output: 3
Explanation: One longest uncommon subsequence is "aba" because "aba" is a subsequence of "aba" but not "cdc".
Note that "cdc" is also a longest uncommon subsequence.
```

**Example 2:**

```
Input: a = "aaa", b = "bbb"
Output: 3
Explanation: The longest uncommon subsequences are "aaa" and "bbb".
```

**Example 3:**

```
Input: a = "aaa", b = "aaa"
Output: -1
Explanation: Every subsequence of string a is also a subsequence of string b. Similarly, every subsequence of string b is also a subsequence of string a.
```

 

**Constraints:**

- `1 <= a.length, b.length <= 100`
- `a` and `b` consist of lower-case English letters.

## 题目大意

给定两个字符串 a 和 b，返回这两个字符串的最长特殊序列，不存在的话，返回-1，

**特殊子序列**就是一个字符串独有的的子串

一个子序列可以由一个子串删除其中一部分字母得到，空字符串是任意字符串的子串 

## 解题思路

这道题目看上去很难，但是仔细分析，情况并不多

* 如果长度不想等，选最长的
* 如果长度相等，但是字符串不相同，就是字符串长度
* 如果长度相等，字符串相同，就是 -1

### Solution 1

时间复杂度 O(n)，比较字符串是否相等

```c++
class Solution {
public:
    int findLUSlength(string a, string b) {
        const int len_a = a.size();
        const int len_b = b.size();
        if (len_a != len_b) {
            // 如果不想等，那么就取最长的那个
            return max(len_a, len_b);
        }
        
        if (a != b) {
            // 如果长度相等，但是字符串不想等，那么最长就是二者的长度
            return len_a;
        }
        
        // 如果长度相等，字符串相等，就是 -1
        return -1;
    }
};
```

