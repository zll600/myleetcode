# [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)

## 题目

Given two strings `s` and `p`, return *an array of all the start indices of* `p`*'s anagrams in* `s`. You may return the answer in **any order**.

An **Anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

**Example 1:**

```
Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
```

**Example 2:**

```
Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
```

 

**Constraints:**

- `1 <= s.length, p.length <= 3 * 104`
- `s` and `p` consist of lowercase English letters.

## 题目大意

给定一个字符串`s`和一个非空字符串`p`，找出`s`是`p`的`anagrams`的字符串的子串起始索引，

一个`anagrams`的意思是和一个字符串的字符都一样，只是排列组合不一样

## 解题思路

利用“滑动窗口”，利用一个数组`dict`来保存每个字符出现的频率，每次向右扩展时，递减 `s` 中出现的每个字符的次数，如果是`p`中的字符，则也递减计数器`count`，当`count`递减为0的时候，将这时的左边界加入到结果集中，如果窗口中出现`p`中没有包含的字符时，即使此时窗口大小等`p` 的长度`count`不会减为0，直到缩小左边界，将不合法的字符去除，`count`才有可能为0

## 代码

````
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int s_len = s.size();
        int p_len = p.size();
        if (s_len < p_len) {
            return vector<int>();
        }
        
        vector<int> dict(256, 0);
        for (char c : p) {
            ++dict[static_cast<unsigned char>(c)];
        }
        
        vector<int> res;
        int left = 0;
        int right = 0;		// 左闭右闭区间，初始时区间长度为 1，
        int count = p_len;
        
        while (right < s_len) {
            if (dict[s[right]] >= 1) {
               --count;
            }
            --dict[s[right]];
            ++right;
            
            if (count == 0) {
                res.push_back(left);
            }
            
            if (right - left == p_len) { // 此时已经是左闭右开区间
                if (dict[s[left]] >= 0) {
                    ++count;
                }
                ++dict[s[left]];
                ++left;
            }
        }
        
        return res;
    }
};
````

