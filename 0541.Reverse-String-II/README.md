# [541. Reverse String II](https://leetcode.com/problems/reverse-string-ii/)

## 题目

Given a string `s` and an integer `k`, reverse the first `k` characters for every `2k` characters counting from the start of the string.

If there are fewer than `k` characters left, reverse all of them. If there are less than `2k` but greater than or equal to `k` characters, then reverse the first `k` characters and left the other as original.

 

**Example 1:**

```
Input: s = "abcdefg", k = 2
Output: "bacdfeg"
```

**Example 2:**

```
Input: s = "abcd", k = 2
Output: "bacd"
```

 

**Constraints:**

- `1 <= s.length <= 104`
- `s` consists of only lowercase English letters.
- `1 <= k <= 104`

## 题目大意

给定一个字符串 s 和一个整数 k，反转每2 * k 个字符的前 k 个字符，

如果剩下的字符不足 k 个，反转所有，如果剩下的字符比 k 多，比 2 * k 少，则反转前 k 个，剩下的保持不变

## 解题思路

### 解法1

这道题分好类就可以了，

* 反转前 K 的情况：有 2k 个或者 不足2 k但比 k 多
* 反转所有：不足 k 个

然后按照要求作即可

``````c++
class Solution {
public:
    string reverseStr(string s, int k) {    
        for (int i = 0; i < s.size(); i += 2 * k) {
            if (s.size() - i >= k) {
                reverse(s.begin() + i, s.begin() + i + k);
            } else {
                reverse(s.begin() + i, s.end());
            }
        }
        
        return s;
    }
};
``````

