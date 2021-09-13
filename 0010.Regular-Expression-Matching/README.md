# [10. Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/)

## 题目

Given an input string `s` and a pattern `p`, implement regular expression matching with support for `'.'` and `'*'` where:

- `'.'` Matches any single character.
- `'*'` Matches zero or more of the preceding element.

The matching should cover the **entire** input string (not partial).



**Example 1:**

```
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
```

**Example 2:**

```
Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
```

**Example 3:**

```
Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
```

**Example 4:**

```
Input: s = "aab", p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
```

**Example 5:**

```
Input: s = "mississippi", p = "mis*is*p*."
Output: false
```

 

**Constraints:**

- `1 <= s.length <= 20`
- `1 <= p.length <= 30`
- `s` contains only lowercase English letters.
- `p` contains only lowercase English letters, `'.'`, and `'*'`.
- It is guaranteed for each appearance of the character `'*'`, there will be a previous valid character to match.

## 题目大意

给定一个字符串 s 和模式 p，实现一个支持‘*’和'.'的正则表达式匹配

- `'.'` 匹配任意单个字符
- `'*'` 匹配零个或多个前面的那一个元素

应该匹配整个字符串而不是部分

## 解题思路

* 这道题其实是一道字符串匹配的题目，可以用 DP 来解决
* 状态的定义：`dp[i][j]`表示 s 中以 i 结尾的字符串和 p 中以 j 结尾的字符串是否匹配，最终结果就是 `dp[s.size()][t.size()]`
* 状态转移：
  * p [j]是普通字符：匹配的条件是前面的字符匹配且但钱字符匹配`dp[i - 1][j - 1] && s[i] == p[j]`
  * p[j]是 `'.'`：匹配的条件是前面的字符匹配，即：`dp[i - 1][j - 1] && p[j] == '.'`
  * `p[j] `是`*`，这个时候需要枚举和 s 中多少字符相匹配，
* 初始化

## 代码

`````c++
class Solution {
public:
    bool isMatch(string s, string p) {
        int len1 = s.size();
        int len2 = p.size();
        
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, false));
        dp[0][0] = true;    // 初始化
        
        for (int i = 0; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                // 如果下一个字符是'*'，则跳过这一轮，但前字符不能担负匹配
                if (j + 1 <= len2 && p[j] == '*') {
                    continue;
                }
                
                // 如果p[j]是一个普通字符，或者是一个p[j]是'.'
                if (i - 1 >= 0 && p[j - 1] != '*') {
                    dp[i][j]  = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                } else if (p[j - 1] == '*'){
                    dp[i][j] = (j - 2 >= 0 && dp[i][j - 2])
                        || (i - 1 >= 0 && j - 2 >= 0 && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
                }
            }
        }
        
        return dp[len1][len2];
    }
};
`````

