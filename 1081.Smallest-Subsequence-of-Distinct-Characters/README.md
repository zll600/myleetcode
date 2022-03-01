# [1081. Smallest Subsequence of Distinct Characters](https://leetcode-cn.com/problems/smallest-subsequence-of-distinct-characters/)

## 题目

Given a string `s`, return *the lexicographically smallest subsequence of* `s` *that contains all the distinct characters of* `s` *exactly once*.

 

**Example 1:**

```
Input: s = "bcabc"
Output: "abc"
```

**Example 2:**

```
Input: s = "cbacdcbc"
Output: "acdb"
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `s` consists of lowercase English letters.

 

**Note:** This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/

## 题目大意

给定一个字符串，返回字典序最小的，包含所有字符的子串，

## 解题思路

这道题目和第 316 题一摸一样，可以放在一起学习

```c++
class Solution {
public:
    string smallestSubsequence(string s) {
        vector<char> sta; // 这里用数组来模拟栈，可以避免后面的反转字符串的操作，
        vector<bool> record(26); // 记录是否已经入栈
        
        vector<int> cnt(26); // 统计字符串的频数
        for (char c : s) {
            ++cnt[c - 'a'];
        }
        
        for (char c : s) {
            --cnt[c - 'a']; // 更新计数
            if (record[c - 'a']) { // 如果已经入栈，则直接跳过
                continue;
            }
            
            while (!sta.empty() && sta.back() > c) {
                // 栈顶元素大于当前元素
                if (cnt[sta.back() - 'a'] == 0) {
                    // 如果后面没有该字符了，则直接跳出
                    break;
                }
                record[sta.back() - 'a'] = false; // 清楚记录
                sta.pop_back(); // 出栈
            }
            sta.push_back(c); // 入栈
            record[c - 'a'] = true; // 做记录
        }
        
        return string(sta.begin(), sta.end());
    }
};
```

