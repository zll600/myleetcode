# [1763. Longest Nice Substring](https://leetcode-cn.com/problems/longest-nice-substring/)

## 题目

A string `s` is **nice** if, for every letter of the alphabet that `s` contains, it appears **both** in uppercase and lowercase. For example, `"abABB"` is nice because `'A'` and `'a'` appear, and `'B'` and `'b'` appear. However, `"abA"` is not because `'b'` appears, but `'B'` does not.

Given a string `s`, return *the longest **substring** of `s` that is **nice**. If there are multiple, return the substring of the **earliest** occurrence. If there are none, return an empty string*.

 

**Example 1:**

```
Input: s = "YazaAay"
Output: "aAa"
Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
"aAa" is the longest nice substring.
```

**Example 2:**

```
Input: s = "Bb"
Output: "Bb"
Explanation: "Bb" is a nice string because both 'B' and 'b' appear. The whole string is a substring.
```

**Example 3:**

```
Input: s = "c"
Output: ""
Explanation: There are no nice substrings.
```

**Example 4:**

```
Input: s = "dDzeE"
Output: "dD"
Explanation: Both "dD" and "eE" are the longest nice substrings.
As there are multiple longest nice substrings, return "dD" since it occurs earlier.
```

 

**Constraints:**

- `1 <= s.length <= 100`
- `s` consists of uppercase and lowercase English letters.

## 题目大意

如果一个字符串中的每个字母的大小写均出现了，则称这个字符串是 nice

给定一个字符串 s，返回是 nice 的最长的子串，如果有多个答案，返回最早出现的那个，如果没有，返回一个空串

## 解题思路

