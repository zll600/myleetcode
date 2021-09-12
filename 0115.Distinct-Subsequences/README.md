# [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)

## 题目

Given two strings `s` and `t`, return *the number of distinct subsequences of `s` which equals `t`*.

A string's **subsequence** is a new string formed from the original string by deleting some (can be none) of the characters without disturbing the remaining characters' relative positions. (i.e., `"ACE"` is a subsequence of `"ABCDE"` while `"AEC"` is not).

It is guaranteed the answer fits on a 32-bit signed integer.

 

**Example 1:**

```
Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
rabbbit
rabbbit
rabbbit
```

**Example 2:**

```
Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
babgbag
babgbag
babgbag
babgbag
babgbag
```

 

**Constraints:**

- `1 <= s.length, t.length <= 1000`
- `s` and `t` consist of English letters.

## 题目大意

给定两个字符串 s 和 t，返回 s 的字串中出现 t 的次数，

## 解题思路

* 这道题目中包含很多的重复子问题，因此可以考虑使用动态规划来解决，
* 状态定义：`dp[i][j]`表示 s 中 [0, i] 的字符和 t 中 [0, j] 的字符匹配的个数
* 状态转移：
  * 不选 s[i]，那就是用 s 中的 [0,i - 1] 的字符去匹配 t 中的 [0, j] 的字符，即为`dp[i - 1][j]`
  * 选 s[i]，也就是用 s 中的 [0, i - 1] 的字符去匹配 t 中的 [0, j - 1] 的字符，即为 `dp[i - 1][j - 1]`
  * 最终 `dp[i][j]`就是二者之和
* 状态的初始化:这里每个字符串加一个空格，来作为转移的起点
* 这里还需要注意，中间结果可能会溢出，参见代码

## 代码

 `````c++
 class Solution {
 public:
     int numDistinct1(string s, string t) {
         int len1 = s.size();
         int len2 = t.size();
         
         vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
         
         for (int i = 0; i <= len1; ++i) {
             dp[i][0] = 1;
         }
         
         for (int i = 1; i <= len1; ++i) {
             for (int j = 1; j <= len2; ++j) {
                 dp[i][j] = dp[i - 1][j];
                 
                 if (s[i - 1] == t[j - 1]) {
                     dp[i][j] += dp[i - 1][j - 1];
                 }
             }
         }
         return dp[len1][len2];
     }
     
     int numDistinct(string s, string t) {
         int len1 = s.size();
         int len2 = t.size();
         
         vector<int> dp(len2 + 1, 0);
         dp[0] = 1;
         
         for (int i = 1; i <= len1; ++i) {
             for (int j = len2; j >= 1; --j) {
                 if (s[i - 1] == t[j - 1]) {
                     dp[j] += 0L + dp[j - 1] % INT_MAX;  // 边面整数溢出的问题
                 }
             }
         }
         return dp[len2];
     }
 };
 `````

