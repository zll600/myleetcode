# [44. Wildcard Matching](https://leetcode.com/problems/wildcard-matching/)

## 题目

Given an input string (`s`) and a pattern (`p`), implement wildcard pattern matching with support for `'?'` and `'*'` where:

- `'?'` Matches any single character.
- `'*'` Matches any sequence of characters (including the empty sequence).

The matching should cover the **entire** input string (not partial).

 

**Example 1:**

```
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
```

**Example 2:**

```
Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.
```

**Example 3:**

```
Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
```

**Example 4:**

```
Input: s = "adceb", p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
```

**Example 5:**

```
Input: s = "acdcb", p = "a*c?b"
Output: false
```

 

**Constraints:**

- `0 <= s.length, p.length <= 2000`
- `s` contains only lowercase English letters.
- `p` contains only lowercase English letters, `'?'` or `'*'`.

## 解题思路

给定一个输入字符串 s ，和一个模式 p，实现一个支持 `?`和`*`的通配符匹配：

* ‘？’ 可以匹配任何单个字符，
* ‘*’ 可以匹配任意字符串（包括空字符串）

你应该匹配整个字符串而不能匹配部分

## 解题思路

* 这是一道 字符串匹配问题，可以利用 dp 来求解，
* 状态定义：`dp[i][j]`表示 s 中 以 i 位置结尾和字符串和 p 中 以 j 位置结尾的字符串匹配的结果
* 状态转移：
  * p[j] 为普通字符，匹配的条件是当前位置，和前面所有的位置都要匹配，即为 `dp[i][j] = dp[i - 1][j - 1] && s[i] == p[j]`
  * p[j] 为‘？’，配的条件是前面所有的位置都匹配，即为`dp[]`

## 代码

