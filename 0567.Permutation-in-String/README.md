# [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)

## 题目

Given two strings `s1` and `s2`, return `true` *if* `s2` *contains a permutation of* `s1`*, or* `false` *otherwise*.

In other words, return `true` if one of `s1`'s permutations is the substring of `s2`.

 

**Example 1:**

```
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
```

**Example 2:**

```
Input: s1 = "ab", s2 = "eidboaoo"
Output: false
```

 

**Constraints:**

- `1 <= s1.length, s2.length <= 104`
- `s1` and `s2` consist of lowercase English letters.

## 题目大意

给定两个字符串`s1`和`s2`，判断`s2`中是否包含`s1`

## 解题思路

利用“滑动窗口”，只需要判断是否存在即可

## 代码

````c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int len1 = s1.size();
        int len2 = s2.size();
        if (len2 < len1) {
            return false;
        }
        
        vector<int> dict(256, 0);
        for (const char c : s1) {
            ++dict[c];
        }
        
        int left = 0;
        int right = 0;
        int count = len1;
        
        while (right < len2) {
            if (dict[s2[right]] >= 1) {
                --count;
            }
            --dict[s2[right]];
            ++right;
            
            if (count == 0) {
                return true;
            }
            
            if (right - left == len1) {
                if (dict[s2[left]] >= 0) {
                    ++count;
                }
                ++dict[s2[left]];
                ++left;
            }
        }
        
        return false;
    }
};
````

