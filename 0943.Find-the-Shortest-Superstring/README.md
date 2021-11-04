# [943. Find the Shortest Superstring](https://leetcode-cn.com/problems/find-the-shortest-superstring/)

## 题目

Given an array of strings `words`, return *the smallest string that contains each string in* `words` *as a substring*. If there are multiple valid strings of the smallest length, return **any of them**.

You may assume that no string in `words` is a substring of another string in `words`.

 

**Example 1:**

```
Input: words = ["alex","loves","leetcode"]
Output: "alexlovesleetcode"
Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
```

**Example 2:**

```
Input: words = ["catg","ctaagt","gcta","ttca","atgcatc"]
Output: "gctaagttcatgcatc"
```

 

**Constraints:**

- `1 <= words.length <= 12`
- `1 <= words[i].length <= 20`
- `words[i]` consists of lowercase English letters.
- All the strings of `words` are **unique**.

## 题目大意

给定一个字符串数组 words，找到以 words 中每个字符串作为子字符串的最短字符串，如果有多个有效的短字符串满足题目条件，返回其中任意一个即可

我们可以假设 words 中没有字符串是另一个字符串的字串