# [97. Interleaving String](https://leetcode.com/problems/interleaving-string/)

## 题目

Given strings `s1`, `s2`, and `s3`, find whether `s3` is formed by an **interleaving** of `s1` and `s2`.

An **interleaving** of two strings `s` and `t` is a configuration where they are divided into **non-empty** substrings such that:

- `s = s1 + s2 + ... + sn`
- `t = t1 + t2 + ... + tm`
- `|n - m| <= 1`
- The **interleaving** is `s1 + t1 + s2 + t2 + s3 + t3 + ...` or `t1 + s1 + t2 + s2 + t3 + s3 + ...`

**Note:** `a + b` is the concatenation of strings `a` and `b`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/02/interleave.jpg)

```
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
```

**Example 2:**

```
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
```

**Example 3:**

```
Input: s1 = "", s2 = "", s3 = ""
Output: true
```

 

**Constraints:**

- `0 <= s1.length, s2.length <= 100`
- `0 <= s3.length <= 200`
- `s1`, `s2`, and `s3` consist of lowercase English letters.

 

**Follow up:** Could you solve it using only `O(s2.length)` additional memory space?

## 题目大意

给定三个字符串 s1, s2, s3，判断 s3 是否是由 s1 和 s2 交叉组成，

两个字符串 s 和 t 交错 的定义与过程如下，其中每个字符串都会被分割成若干 非空 子字符串：

- s = s1 + s2 + … + sn
- t = t1 + t2 + … + tm
- |n - m| <= 1
- 交错 是 s1 + t1 + s2 + t2 + s3 + t3 + … 或者 t1 + s1 + t2 + s2 + t3 + s3 + …

提示：a + b 意味着字符串 a 和 b 连接。

## 解题思路

这道题目没有太理解题意，没有想到使用动态规划来做，

### Solution 1:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/interleaving-string/solution/dong-tai-gui-hua-zhu-xing-jie-shi-python3-by-zhu-3/

具体的状态定义，初始化都已经写在题解中了

`````c++
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        const int len1 = s1.size();  // s1 的长度
        const int len2 = s2.size();  // s2 的长度
        const int len3 = s3.size();  // s3 的长度
        if (len1 +len2 != len3) {  // 如果长度不匹配，直接返回错误
            return false;
        }
        
        // dp数组，
        // 状态定义：dp[i][j] 表示由 s1 的前 i - 1 个字符和 s2 的前 j - 1 个字符构成 s3 的前i + j - 1 个zifu 
        vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1, false));
        // 初始化
        dp[0][0] = true;
        // s1 的前 i - 1 个字符构成 s3 的前 i.- 1 个字符
        for (int i = 1; i <= len1; i++) {
            if (dp[i - 1][0] && s1[i - 1] == s3[i - 1]) {
                dp[i][0] = true;
            }
        }
        // s2 的前 j - 1 个字符，构成 s3 的前 j - 1 个字符
        for (int j = 1; j <= len2; ++j) {
            if (dp[0][j - 1] && s2[j - 1] == s3[j - 1]) {
                dp[0][j] = true;
            }
        }
        
        // 状态转移
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                // dp[i][j] 可以来自两个方向，分别由 s1 或者由 s2 组成
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1])
                            || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        
        return dp[len1][len2];
    }
};
`````

