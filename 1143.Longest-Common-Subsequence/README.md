# [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)

## 题目

Given two strings `text1` and `text2`, return *the length of their longest **common subsequence**.* If there is no **common subsequence**, return `0`.

A **subsequence** of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

- For example, `"ace"` is a subsequence of `"abcde"`.

A **common subsequence** of two strings is a subsequence that is common to both strings.

 

**Example 1:**

```
Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
```

**Example 2:**

```
Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
```

**Example 3:**

```
Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
```

 

**Constraints:**

- `1 <= text1.length, text2.length <= 1000`
- `text1` and `text2` consist of only lowercase English characters.

## 题目大意 

给定两个字符串， text1 和 text2，返回最长公共自序列的长度，如果没有公共自序列，返回 0，

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

* 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。

两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

## 解题思路

这是一道很经典的 dp 问题

## 解法1（DP）

状态定义和转移方程：参见代码

初始化：二维数组的第一行和第一列没有意义，但是状态转移要用到，所以，这里初始化为 0，只是为了让整个状态可以递推下去

````c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int len1 = text1.size();
        int len2 = text2.size();
        
        // 状态定义：
        // dp[i][j] 表示text1[0, i - 1] 和 text2[0, j - 1] 中的最长公共子串
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                if (text1[i - 1] == text2[j - 1]) {  // 如果字符相同，则说明公共子串可以增大
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {  // 否则，选择二者中较大的一个
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[len1][len2];
    }
};
````

