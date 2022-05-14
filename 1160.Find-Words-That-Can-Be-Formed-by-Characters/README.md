# [1160. Find Words That Can Be Formed by Characters](https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/)

## 题目

You are given an array of strings `words` and a string `chars`.

A string is **good** if it can be formed by characters from chars (each character can only be used once).

Return *the sum of lengths of all good strings in words*.

 

**Example 1:**

```
Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation: The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
```

**Example 2:**

```
Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
Output: 10
Explanation: The strings that can be formed are "hello" and "world" so the answer is 5 + 5 = 10.
```

 

**Constraints:**

- `1 <= words.length <= 1000`
- `1 <= words[i].length, chars.length <= 100`
- `words[i]` and `chars` consist of lowercase English letters.

## 题目大意

给你一份『词汇表』（字符串数组） `words` 和一张『字母表』（字符串） `chars`。假如你可以用 `chars` 中的『字母』（字符）拼写出 `words` 中的某个『单词』（字符串），那么我们就认为你掌握了这个单词。

注意：每次拼写时，chars 中的每个字母都只能用一次。

返回词汇表 words 中你掌握的所有单词的 长度之和

## 解题思路

这道题目要解决的问题还是比较直白的，

- words 中的字符串能否由 chars 构成

### Solution 1:

这里现统计出 chars 中每个字母的频数，然后进行判断即可

````c++
class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        vector<int> chars_freq(26, 0);
        for (char c : chars) {
            ++chars_freq[c - 'a'];
        }

        int res = 0;
        for (const auto& word : words) {
            if (CanBeFormed(chars_freq, word)) {
                res += word.size();
            }
        }
        return res;
    }

 private:
    // 判断是能否形成
    bool CanBeFormed(const vector<int>& chars_freq, const string& word) {
        vector<int> freq(26, 0);
        for (char c : word) {
            ++freq[c - 'a'];
        }

        for (int i = 0; i < 26; ++i) {
            if (freq[i] > chars_freq[i]) {
                return false;
            }
        }
        return true;
    }
};
````



