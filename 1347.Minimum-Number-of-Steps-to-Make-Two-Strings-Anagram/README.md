#### [1347. Minimum Number of Steps to Make Two Strings Anagram](https://leetcode.cn/problems/minimum-number-of-steps-to-make-two-strings-anagram/)

## 题目

You are given two strings of the same length `s` and `t`. In one step you can choose **any character** of `t` and replace it with **another character**.

Return *the minimum number of steps* to make `t` an anagram of `s`.

An **Anagram** of a string is a string that contains the same characters with a different (or the same) ordering.

 

**Example 1:**

```
Input: s = "bab", t = "aba"
Output: 1
Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram of s.
```

**Example 2:**

```
Input: s = "leetcode", t = "practice"
Output: 5
Explanation: Replace 'p', 'r', 'a', 'i' and 'c' from t with proper characters to make t anagram of s.
```

**Example 3:**

```
Input: s = "anagram", t = "mangaar"
Output: 0
Explanation: "anagram" and "mangaar" are anagrams. 
```

 

**Constraints:**

- `1 <= s.length <= 5 * 104`
- `s.length == t.length`
- `s` and `t` consist of lowercase English letters only.

## 题目大意

给你两个长度相等的字符串 s 和 t。每一个步骤中，你可以选择将 t 中的 任一字符 替换为 另一个字符。

返回使 t 成为 s 的字母异位词的最小步骤数。

字母异位词 指字母相同，但排列不同（也可能相同）的字符串

## 解题思路

题目限制 s 和 t 的长度是一样的，最终结果要求s 和 t 是字母异位词，即字母出现的频数相同

### Solution 1: Hash

这里使用两个哈希表分别存每种字符的频数，然后最终做一个比较

- 如果这个字符只出现在 t 中，说明这个字符需要做全部替换，这里不关心如何替换
- 如果这个字符在 t 中出现的次数大于在 s 中出现的次数，说明这个字符需要做部分替换，这里不用关心需要如何替换

````python
class Solution:
    def minSteps(self, s: str, t: str) -> int:
        freq_s = {}
        for c in s:
            if c not in freq_s:
                freq_s[c] = 1
            else:
                freq_s[c] += 1
        
        freq_t = {}
        for c in t:
            if c not in freq_t:
                freq_t[c] = 1
            else:
                freq_t[c] += 1
        ans = 0
        for k, v in freq_t.items():
            # print(f'{k} : {v}')
            if k not in s:
                ans += v
            elif v > freq_s[k]:
                ans += v - freq_s[k]
        
        return ans
````

