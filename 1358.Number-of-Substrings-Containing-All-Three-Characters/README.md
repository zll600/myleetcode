# [1358. Number of Substrings Containing All Three Characters](https://leetcode-cn.com/problems/number-of-substrings-containing-all-three-characters/)

## 题目

Given a string `s` consisting only of characters *a*, *b* and *c*.

Return the number of substrings containing **at least** one occurrence of all these characters *a*, *b* and *c*.

 

**Example 1:**

```
Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
```

**Example 2:**

```
Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 
```

**Example 3:**

```
Input: s = "abc"
Output: 1
```

 

**Constraints:**

- `3 <= s.length <= 5 x 10^4`
- `s` only consists of *a*, *b* or *c* characters.

## 题目大意

给定一个只包含 a, b 和 c 三个字符的字符串 s，请你返回 a，b 和 c 都 **至少** 出现过一次的子字符串数目

## 解题思路

这道题目是一道区间相关的题目

### Solution 1:

对于滑动窗口的解法，就是窗口中的子串是满足条件的，那么窗口中的子串拼接上 之前的任何长度的子串都依旧满足条件，比如 'abcabc'，当窗口处于 第二个'bc' 时，'abcabc'，‘bcabc’，'cabc', ’abc‘ 都是有效的结果

```c++
class Solution {
public:
    int numberOfSubstrings(string s) {
        // 用来统计字符频数
        vector<int> cnt(3);
        
        const int len = s.size();
        int res = 0;
        int left = 0, right = 0;
        // [left, right)
        while (right < len) {
            ++cnt[s[right] - 'a'];
            
            while (left < right && !!cnt[0] && !!cnt[1] && !!cnt[2]) {
                // 窗口一直缩小，知道不能缩小为止
                --cnt[s[left] - 'a'];
                ++left;
            }
            res += left;

            ++right; // 窗口一直向右扩
        }
        
        return res;
    }
};
```

