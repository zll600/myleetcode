# [316. Remove Duplicate Letters](https://leetcode-cn.com/problems/remove-duplicate-letters/)

## 题目

Given a string `s`, remove duplicate letters so that every letter appears once and only once. You must make sure your result is **the smallest in lexicographical order** among all possible results.

 

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

- `1 <= s.length <= 104`
- `s` consists of lowercase English letters.

 

**Note:** This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/

## 题目大意

给你一个字符串 `s` ，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证 **返回结果的字典序最小**（要求不能打乱其他字符的相对位置）

## 解题思路

这道题要解决的问题有几个点：

* 每个字母只出现一次
* 字母出现的顺序按照原顺序
* 字母的顺序需要满足最小字典序

解决上面这几个问题，就可以解决这道题目



### Solution 1: Monotonic Stack

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/remove-duplicate-letters/solution/you-qian-ru-shen-dan-diao-zhan-si-lu-qu-chu-zhong-/

这里分析问题的思路是值得学习的

这种解法，利用一个记录数组来确保每个字母只入栈一次，用单调栈确保最小字典序，

```c++
class Solution {
public:
    string removeDuplicateLetters(string s) {
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

