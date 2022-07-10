#### [1328. Break a Palindrome](https://leetcode.cn/problems/break-a-palindrome/)

Given a palindromic string of lowercase English letters `palindrome`, replace **exactly one** character with any lowercase English letter so that the resulting string is **not** a palindrome and that it is the **lexicographically smallest** one possible.

Return *the resulting string. If there is no way to replace a character to make it not a palindrome, return an **empty string**.*

A string `a` is lexicographically smaller than a string `b` (of the same length) if in the first position where `a` and `b` differ, `a` has a character strictly smaller than the corresponding character in `b`. For example, `"abcc"` is lexicographically smaller than `"abcd"` because the first position they differ is at the fourth character, and `'c'` is smaller than `'d'`.

 

**Example 1:**

```
Input: palindrome = "abccba"
Output: "aaccba"
Explanation: There are many ways to make "abccba" not a palindrome, such as "zbccba", "aaccba", and "abacba".
Of all the ways, "aaccba" is the lexicographically smallest.
```

**Example 2:**

```
Input: palindrome = "a"
Output: ""
Explanation: There is no way to replace a single character to make "a" not a palindrome, so return an empty string.
```

 

**Constraints:**

- `1 <= palindrome.length <= 1000`
- `palindrome` consists of only lowercase English letters.



### 题目大意

给你一个由小写英文字母组成的回文字符串 `palindrome` ，请你将其中 一个 字符用任意小写英文字母替换，使得结果字符串的 字典序最小 ，且 不是 回文串。

请你返回结果字符串。如果无法做到，则返回一个 空串 。

如果两个字符串长度相同，那么字符串 a 字典序比字符串 b 小可以这样定义：在 `a` 和 `b` 出现不同的第一个位置上，字符串 `a` 中的字符严格小于 `b` 中的对应字符。例如，`"abcc”` 字典序比 `"abcd"` 小，因为不同的第一个位置是在第四个字符，显然 `'c'` 比 `'d'` 小



### Solution 1: Simulation

需要考虑的点有这些

- 如果回文串的长度为1,那么无论怎么修改都是回文串
- 考虑一般情况：从左向右遍历左半边子串，找到尽可能靠前且不是 `'a'` 的字符，将其修改为 `'a'`，
- 还需要考虑回文串长度的奇偶，如果是偶数，只遍历左半边即可，如果是奇数，遍历左半边，不包括对称中心
- 如果所有位置都是 `'a'`，找到最后的一个 'a'，修改为 'b' 即可



````c++
class Solution {
public:
    string breakPalindrome(string palindrome) {
        const int len = palindrome.size();
        if (len == 1) {
            return "";
        }
        
        for (int i = 0; i < len / 2; ++i) {
            if (palindrome[i] != 'a') {
                palindrome[i] = 'a';
                return palindrome;
            }
        }
        
        palindrome[len - 1] = 'b';
        return palindrome;
    }
};
````




