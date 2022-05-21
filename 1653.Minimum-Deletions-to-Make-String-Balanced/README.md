# [1653. Minimum Deletions to Make String Balanced](https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/)

## 题目

You are given a string `s` consisting only of characters `'a'` and `'b'`.

You can delete any number of characters in `s` to make `s` **balanced**. `s` is **balanced** if there is no pair of indices `(i,j)` such that `i < j` and `s[i] = 'b'` and `s[j]= 'a'`.

Return *the **minimum** number of deletions needed to make* `s` ***balanced***.

 

**Example 1:**

```
Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
```

**Example 2:**

```
Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters.
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is `'a'` or `'b'`.

## 题目大意

给你一个字符串 `s` ，它仅包含字符 `‘a’` 和 `‘b’` 。你可以删除 `s` 中任意数目的字符，使得 `s`  平衡 。我们称 `s` 平衡的 当不存在下标对 `(i,j)` 满足 `i < j` 且 `s[i] = ‘b’` 同时 `s[j]= ‘a’` 

请你返回使 s 平衡 的 最少 删除次数。

## 解题思路@


### Solution 1: DP

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/minimum-deletions-to-make-string-balanced/solution/python-qian-zhui-tong-ji-mei-ge-wei-zhi-8uxmm/)

这种解法 定义了状态 dp[i] 要使 0 到 i 的字符串是平衡的，需要删除的次数

状态转移

- 如果 `s[i]` 是 'b'，不影响平衡
- 如果 `s[i]` 是 'a'，要么删除之前的所有 b，要么删除所有的 a

`````c++
class Solution {
public:
    int minimumDeletions(string s) {
        int ans = 0, cnt = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'b') {
                // 如果第 i 个字符是 'b'，不影响平衡
                ++cnt;
            } else {
                // 如果第 i 个字符是 'a'，
                // 保留这个 'a'，就需要删除之前出现过的所有 b
                // 删除这个 'a'
                ans = min(ans + 1, cnt);
            }
        }
        return ans;
    }
};
````



