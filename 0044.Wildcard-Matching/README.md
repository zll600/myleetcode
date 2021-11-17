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

### Solution 1:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/wildcard-matching/solution/zi-fu-chuan-dong-tai-gui-hua-bi-xu-miao-dong-by-sw/

字符串类型的动态规划题目，状态定义等可以参考代码，这道题难的还是 '*' 的处理和初始化，



````c++
class Solution {
public:
    bool isMatch(string s, string p) {
        const int len1 = s.size();  // 目标串
        const int len2 = p.size();  // 格式串
        // 状态定义:
        // dp[i][j] 表示 s 的前 i - 1 个字符和 p 的前 j - 1 个字符相匹配的结果
        vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1));
        // 初始化
        dp[0][0] = true;
        // 处理 p 以'*'开头的情况
        for (int i = 1; i <= len2; ++i) {
            if (p[i - 1] != '*') {
                break;
            }
            dp[0][i] = true;
        }
        
        // 状态转移
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    // 匹配单个字符字符
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    // 这里分两种情况讨论
                    // 1、匹配空串，即 dp[i][j - 1]
                    // 1、 匹配当前位置 dp[i - 1][j]
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
            }
        }
        
        return dp[len1][len2];
    }
};
````



