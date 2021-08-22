# [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

## 题目

Given two strings `s` and `t` of lengths `m` and `n` respectively, return *the **minimum window substring** of* `s` *such that every character in* `t` *(**including duplicates**) is included in the window. If there is no such substring**, return the empty string* `""`*.*

The testcases will be generated such that the answer is **unique**.

A **substring** is a contiguous sequence of characters within the string.

 

**Example 1:**

```
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
```

**Example 2:**

```
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
```

**Example 3:**

```
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
```

 

**Constraints:**

- `m == s.length`
- `n == t.length`
- `1 <= m, n <= 105`
- `s` and `t` consist of uppercase and lowercase English letters.



## 题目大意

给定一个长度分别为`m`和`n`的字符串`s`和`t`，返回`s`的一个窗口，要求这个窗口包含每一个在`t`中出现的字符（包括重复的字符），如果存在多个窗口，则返回最小的一个，如果不存在这样的窗口，则返回空字符串

* 测试用例保证答案是唯一的
* 字串是一个字符串中的连续序列



## 解题思路

这道题可以用滑动窗口来求解，求解的过程中，不断的包含`t`中的字符，直到全部包含，记下此时的左边界和右边界，然后缩小左边界，再扩展右边界，不断重复，记录最优的左边界和右边界值，

## 代码

````c++
class Solution {
public:
    string minWindow(string s, string t) {
        int m = s.size();
        int n = t.size();
        if (n > m) {	// 如果 t 比 s 长，则直接返回空字符
            return "";
        }
        
        vector<int> s_dict(256);
        vector<int> t_dict(245);
        
        for (int i = 0; i < n; ++i) {
            ++t_dict[t[i]];
        }
        
        int left = 0;
        int right = -1;
        int final_left = -1;
        int final_right = -1;
        int min_win = m + 1; // 这里 m + 1 是为了解决 s 和 t 的长度相等的情况
        int t_idx = 0;
        
        while (left < m) {
            if (right + 1 < m && t_idx < n) {
                ++s_dict[s[right + 1]];
                if (s_dict[s[right + 1]] <= t_dict[s[right + 1]]) {
                    ++t_idx;
                }
                ++right;
            } else {
                if (right - left + 1 < min_win && t_idx == n) {
                    min_win = right - left + 1;
                    final_left = left;
                    final_right = right;
                }
                
                if (s_dict[s[left]] == t_dict[s[left]]) {
                    --t_idx;
                }
                --s_dict[s[left]];
                ++left;
            }
        }
        
        return final_left == -1 ? "" : s.substr(final_left, min_win);
    }
};
````



