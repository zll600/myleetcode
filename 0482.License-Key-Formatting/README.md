# [482. License Key Formatting](https://leetcode-cn.com/problems/license-key-formatting/)

## 题目

You are given a license key represented as a string `s` that consists of only alphanumeric characters and dashes. The string is separated into `n + 1` groups by `n` dashes. You are also given an integer `k`.

We want to reformat the string `s` such that each group contains exactly `k` characters, except for the first group, which could be shorter than `k` but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.

Return *the reformatted license key*.

 

**Example 1:**

```
Input: s = "5F3Z-2e-9-w", k = 4
Output: "5F3Z-2E9W"
Explanation: The string s has been split into two parts, each part has 4 characters.
Note that the two extra dashes are not needed and can be removed.
```

**Example 2:**

```
Input: s = "2-5g-3-J", k = 2
Output: "2-5G-3J"
Explanation: The string s has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s` consists of English letters, digits, and dashes `'-'`.
- `1 <= k <= 104`

## 题目大意

给定一个只含数字、字母和破折号的字符串，字符串用破折号分割，给定一个整数 k，

给你一个数字 K，请你重新格式化字符串，使每个分组恰好包含 K 个字符。特别地，第一个分组包含的字符个数必须小于等于 K，但至少要包含 1 个字符。两个分组之间需要用 '-'（破折号）隔开，并且将所有的小写字母转换为大写字母。

给定非空字符串 S 和数字 K，按照上面描述的规则进行格式化

## 解题思路

这道题还是比较简单的，从后往前开始转化，最后就可以转化完成

### Solution 1:

`````c++
class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
        string res = "";
        const int len = s.size();
        int cnt = 0;
        for (int i = len - 1; i >= 0; --i) {
            if (s[i] == '-') {
                continue;
            }
            if (cnt == k) {
                res.insert(0, 1, '-');
                cnt = 0;
            }
            res.insert(0, 1, toupper(s[i]));
            ++cnt;
        }
        
        return res;
    }
};
`````

