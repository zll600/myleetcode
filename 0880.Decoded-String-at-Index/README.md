# [880. Decoded String at Index](https://leetcode.com/problems/decoded-string-at-index/)

## 题目

You are given an encoded string `s`. To decode the string to a tape, the encoded string is read one character at a time and the following steps are taken:

- If the character read is a letter, that letter is written onto the tape.
- If the character read is a digit `d`, the entire current tape is repeatedly written `d - 1` more times in total.

Given an integer `k`, return *the* `kth` *letter (**1-indexed)** in the decoded string*.

 

**Example 1:**

```
Input: s = "leet2code3", k = 10
Output: "o"
Explanation: The decoded string is "leetleetcodeleetleetcodeleetleetcode".
The 10th letter in the string is "o".
```

**Example 2:**

```
Input: s = "ha22", k = 5
Output: "h"
Explanation: The decoded string is "hahahaha".
The 5th letter is "h".
```

**Example 3:**

```
Input: s = "a2345678999999999999999", k = 1
Output: "a"
Explanation: The decoded string is "a" repeated 8301530446056247680 times.
The 1st letter is "a".
```

 

**Constraints:**

- `2 <= s.length <= 100`
- `s` consists of lowercase English letters and digits `2` through `9`.
- `s` starts with a letter.
- `1 <= k <= 109`
- It is guaranteed that `k` is less than or equal to the length of the decoded string.
- The decoded string is guaranteed to have less than `263` letters.

## 题目大意

给定一个编码的字符串 S，为了解码字符串，并将其写入磁带中，每次只读入一个字符，并遵循下列规则：

* 如果读到的字符是一个字母，就直接将其写入磁带，
* 如果读到的字符是个一个数字 d ，就将整个磁带的内容重复d - 1 次

返回解码字符串的第 k 个字符

## 解题思路

* 这道题目可以用递归来做，只要字母数达到 k 就可以返回，不必非得等到字符串扩展完成，因为扩展之后的字符串可能很大，
* 代码中有不理解的地方，可以手动模拟以下，特别对于需要递归的地方，字符串中的数字，最终不会影响结果。

## 代码

````c++
class Solution {
public:
    string decodeAtIndex(string s, int k) {
        int len = 0;
        int size = s.size();
        
        for (int i = 0; i < size; ++i) {
            if (isalpha(s[i])) {
                if (++len == k) {
                    return string(1, s[i]);
                }
            } else {
                if (1L * len * (s[i] - '0') >= k) { // 这里为了避免发生溢出的情况，这里作一次整型提升。
                    if (k % len != 0) {
                        return decodeAtIndex(s.substr(0, i), k % len);
                    }
                    return decodeAtIndex(s.substr(0, i), len);
                }
                len *= (s[i] - '0');
            }
        }
        
        return "";
    }
};
````



