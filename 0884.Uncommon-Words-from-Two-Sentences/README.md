# [884. Uncommon Words from Two Sentences](https://leetcode.com/problems/uncommon-words-from-two-sentences/)

A **sentence** is a string of single-space separated words where each word consists only of lowercase letters.

A word is **uncommon** if it appears exactly once in one of the sentences, and **does not appear** in the other sentence.

Given two **sentences** `s1` and `s2`, return *a list of all the **uncommon words***. You may return the answer in **any order**.

 

**Example 1:**

```
Input: s1 = "this apple is sweet", s2 = "this apple is sour"
Output: ["sweet","sour"]
```

**Example 2:**

```
Input: s1 = "apple apple", s2 = "banana"
Output: ["banana"]
```

 

**Constraints:**

- `1 <= s1.length, s2.length <= 200`
- `s1` and `s2` consist of lowercase English letters and spaces.
- `s1` and `s2` do not have leading or trailing spaces.
- All the words in `s1` and `s2` are separated by a single space.

## 题目大意

一个 **句子** 是一个由 单个空格分隔的由小写字母组成的单词 构成的

如果一个单词只在其中一个句子出现,没有出现在另一个句子中,那么说这个单词是 *不平凡* 的,

给定两个 *句子* `s1` 和 `s2`,返回 所有的不平凡的单词,你可以按照 **任意顺序** 返回

## 解题思路



### Solution:



````c++
class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        // 这里使用一个 map 来做计数
        unordered_map<string, int> rec;
        Split(s1, rec);
        Split(s2, rec);

        vector<string> res;
        for (const auto& item : rec) {
            if (item.second == 1) {
                // 我们只将频数是 1 的单词加入到结果集中
                res.push_back(item.first);
            }
        }

        return res;
    }

 private:
    void Split(const string& str, unordered_map<string, int>& tokens, string delim = " ") {
        int start = str.find_first_not_of(delim, 0);
        int pos = str.find_first_of(delim, start);

        while (start != string::npos || pos != string::npos) {
            ++tokens[str.substr(start, pos - start)];
            start = str.find_first_not_of(delim, pos);
            pos = str.find_first_of(delim, start);
        }
    }
};
````


