# [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)

## 题目

You are given a string `s` and an integer `k`. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most `k` times.

Return *the length of the longest substring containing the same letter you can get after performing the above operations*.

 

**Example 1:**

```
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.
```

**Example 2:**

```
Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s` consists of only uppercase English letters.
- `0 <= k <= s.length`

## 题目大意

 给定一个字符串和可转换次数 K，找到经过至多 K 次转换之后，最长的重复字符的子串

## 解题思路

这道题可诶利用“滑动窗口"，不过在窗口向右扩展的时候，需要记录当前窗口中出现频数最高的数，此时将其他数转换至多 K 次就可以得到最终结果，窗口收缩的条件是，`当前窗口的长度 - 出现次数最高的字母的次数 > K`,此时需要递减相应字母出现的次数，缩小窗口直至转换至多 K 次后，当前窗口的所有字母都相同，然后更新结果

````c++
class Solution {
public:
    int characterReplacement(string s, int k) {
        int size = s.size();
        
        int len = 0;
        int left = 0;
        int right = 0;
        int freq = 0;
        vector<int> dict(26, 0);
        
        for (; right < size; ++right) {	// 扩大窗口
            ++dict[s[right] - 'A'];
            freq = max(freq, dict[s[right] - 'A']);
            while (right - left + 1 - freq > k) {	// 收缩窗口
                --dict[s[left] - 'A'];
                
                ++left;
            }
            len = max(len, right - left + 1);
        }
        
        return len;
    }
};
````

