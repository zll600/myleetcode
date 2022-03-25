# [712. Minimum ASCII Delete Sum for Two Strings](https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/)

## 题目

Given two strings `s1` and `s2`, return *the lowest **ASCII** sum of deleted characters to make two strings equal*.

 

**Example 1:**

```
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
```

**Example 2:**

```
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d] + 101[e] + 101[e] to the sum.
Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
```

 

**Constraints:**

- `1 <= s1.length, s2.length <= 1000`
- `s1` and `s2` consist of lowercase English letters.

## 题目大意

给定两个字符串 `s1` 和 `s2`，返回使得两个字符串相等的所需删除的字母的最小 `ASCII` 之和，

## 解题思路

这道题目其实很类似求最长公共子序列问题

### Solution 1: DP

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/solution/lei-si-zui-chang-gong-gong-zi-xu-lie-de-ysu5z/)


````c++
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        const int len1 = s1.size();
        const int len2 = s2.size();
        
        // dp[i][j] 表示 s1[0:i-1] 和 s2[0:j-1] 的最长公共子序列 
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
        
        // 初始化第一行和第一列
        dp[0][0] = 0;
        for (int i = 1; i <= len1; ++i) {
            dp[i][0] = dp[i - 1][0] + s1[i - 1];
        }
        
        for (int j = 1; j <= len2; ++j) {
            dp[0][j] = dp[0][j - 1] + s2[j - 1];
        }
        
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    // 如果当前位置的字符是相同的，那么可以由二者的前一个位置转移过来
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // 否则选择较小的哪一个转移过来
                    dp[i][j] = min(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
                }
            }
        }
        
        return dp[len1][len2];
    }
};
````
