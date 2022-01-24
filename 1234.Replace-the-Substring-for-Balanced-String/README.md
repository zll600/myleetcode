# [1234. Replace the Substring for Balanced String](https://leetcode.com/problems/replace-the-substring-for-balanced-string/)

## 题目

You are given a string s of length `n` containing only four kinds of characters: `'Q'`, `'W'`, `'E'`, and `'R'`.

A string is said to be **balanced** if each of its characters appears `n / 4` times where `n` is the length of the string.

Return *the minimum length of the substring that can be replaced with **any** other string of the same length to make* `s` ***balanced***. If s is already **balanced**, return `0`.

 

**Example 1:**

```
Input: s = "QWER"
Output: 0
Explanation: s is already balanced.
```

**Example 2:**

```
Input: s = "QQWE"
Output: 1
Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is balanced.
```

**Example 3:**

```
Input: s = "QQQW"
Output: 2
Explanation: We can replace the first "QQ" to "ER". 
```

 

**Constraints:**

- `n == s.length`
- `4 <= n <= 105`
- `n` is a multiple of `4`.
- `s` contains only `'Q'`, `'W'`, `'E'`, and `'R'`.



## 题目大意

有一个只含有 ‘Q’, ‘W’, ‘E’, ‘R’ 四种字符，且长度为 n 的字符串。

假如在该字符串中，这四个字符都恰好出现 n/4 次，那么它就是一个「平衡字符串」。给你一个这样的字符串 s，

请通过「替换一个子串」的方式，使原字符串 s 变成一个「平衡字符串」。你可以用和「待替换子串」长度相同的 任何 其他字符串来完成替换。请返回待替换子串的最小可能长度。如果原字符串自身就是一个平衡字符串，则返回 0。

## 解题思路

这道题可以理解为求一段符合题目要求的字符串，具体就是窗口外的字符的频数均满足 `freq[c] <= k`, 此时只需要改变窗口内的字符就可以了，但是这样还不够，如果可以将 窗口中 频数本来就 <= k 的字符排除可以进一步减小 窗口的长度。

### Solution 1: Sliding Window

这种解法可以参考这篇题解：https://books.halfrost.com/leetcode/ChapterFour/1200~1299/1234.Replace-the-Substring-for-Balanced-String/

写滑动窗口可以借鉴霜神的模版来写，理解好其中的含义，也可以改，



````c++
class Solution {
public:
    int balancedString(string s) {
        // 统计每个字母的频数
        unordered_map<char, int> freq;
        for (char c : s) {
            ++freq[c];
        }
        
        const int len = s.size();
        int res = len;
        int k = len / 4; // 每个字母出现的最大次数
        
        // 窗口 [left, right] 表示要替换的部分
        int left = 0, right = -1;
        while (left < len) {
            if (freq['Q'] > k || freq['W'] > k || freq['E'] > k || freq['R'] > k) {
                // 如果窗口外的字符数依旧有 > k 的
                if (right + 1 < len) {
                    ++right;
                    --freq[s[right]]; // 递减窗口内的字母的频数，使窗口外的数字合法
                } else {
                    break;
                }         
            } else {
                res = min(res, right - left + 1);
                ++freq[s[left]]; // 增加窗口外的字符的频数
                ++left;
            }
        }
        
        return res;
    }
};

````

#### 关于滑动窗口，这里有一份列表，可以[参考](https://leetcode.com/problems/replace-the-substring-for-balanced-string/discuss/408978/javacpython-sliding-window/367697)