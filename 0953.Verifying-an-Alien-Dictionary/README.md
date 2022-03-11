# [953. Verifying an Alien Dictionary](https://leetcode.com/problems/verifying-an-alien-dictionary/)

## 题目

In an alien language, surprisingly, they also use English lowercase letters, but possibly in a different `order`. The `order` of the alphabet is some permutation of lowercase letters.

Given a sequence of `words` written in the alien language, and the `order` of the alphabet, return `true` if and only if the given `words` are sorted lexicographically in this alien language.

 

**Example 1:**

```
Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
```

**Example 2:**

```
Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
```

**Example 3:**

```
Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).
```

 

**Constraints:**

- `1 <= words.length <= 100`
- `1 <= words[i].length <= 20`
- `order.length == 26`
- All characters in `words[i]` and `order` are English lowercase letters.

## 题目大意

一门外星语言也使用英文小写字母，但是是不同的顺序，这个顺序是一些小写字母的排列，给定一组使用外星语言写的 `words`，和字母的 `order`,如果给定的 `words` 是满足字典序的，返回 `true`,否则，返回 `false`

## 解题思路

这道题目的具体思路为

- 先根据给定的 `order` 创建一个map来保存顺序，方便后续查询
- 两两比较相邻的字符串

### Solution 1:


````c++
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        // 先创建一个map 用来维护顺序
        unordered_map<char, int> order_map;
        const int order_len = order.size();
        for (int i = 0; i < order_len; ++i) {
            order_map[order[i]] = i;
        }

        const int words_len = words.size();
        // 比较相邻的字符串
        for (int i = 1; i < words_len; ++i) {
            int idx = 0;
            const int len1 = words[i - 1].size(), len2 = words[i].size();
            while (idx < len1 && idx < len2) {
                if (order_map[words[i - 1][idx]] > order_map[words[i][idx]]) {
                    // 这里直接返回错误
                    return false;
                } else if (order_map[words[i - 1][idx]] < order_map[words[i][idx]]) {
                    // 这里直接跳过后续的比较
                    break;
                }
                // 递增下标
                ++idx;
            }
            if (idx < len1 && idx >= len2) {
                // 还要注意长度引起的问题
                return false;
            }
        }

        return true;
    }
};
````
