# [890. Find and Replace Pattern](https://leetcode.com/problems/find-and-replace-pattern/)

## 题目

Given a list of strings `words` and a string `pattern`, return *a list of* `words[i]` *that match* `pattern`. You may return the answer in **any order**.

A word matches the pattern if there exists a permutation of letters `p` so that after replacing every letter `x` in the pattern with `p(x)`, we get the desired word.

Recall that a permutation of letters is a bijection from letters to  letters: every letter maps to another letter, and no two letters map to  the same letter.

 

**Example 1:**

```
Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation, since a and b map to the same letter.
```

**Example 2:**

```
Input: words = ["a","b","c"], pattern = "a"
Output: ["a","b","c"]
```

 

**Constraints:**

- `1 <= pattern.length <= 20`
- `1 <= words.length <= 50`
- `words[i].length == pattern.length`
- `pattern` and `words[i]` are lowercase English letters.

## 题目大意

你有一个单词列表 `words` 和一个模式 `pattern`，你想知道 `words` 中的哪些单词与模式匹配。

如果存在字母的排列 `p` ，使得将模式中的每个字母 `x` 替换为 `p(x)` 之后，我们就得到了所需的单词，那么单词与模式是匹配的,

回想一下，字母的排列是从字母到字母的双射：每个字母映射到另一个字母，没有两个字母映射到同一个字母

返回 words 中与给定模式匹配的单词列表。你可以按任何顺序返回答案。


## 解题思路

这道题目的难点在于要同时判断：

- pattern 到 word 的映射是唯一的
- word 到 pattern 中的映射也是唯一的

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0890.Find-and-Replace-Pattern/)

````c++
class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> res;

        for (const string& word : words) {
            if (Match(word, pattern)) {
                res.push_back(word);
            }
        }

        return res;
    }

 private:
    bool Match(const string& word, const string& pattern) {
        // pattern[i] -> word[i] 中的一对一映射
        unordered_map<char, char> relat;
        // word[i] -> pattern[i] 中是一对一映射
        unordered_set<char> used;

        const int len = word.size();
        for (int i = 0; i < len;  ++i) {
            auto it = relat.find(pattern[i]);
            if (it != relat.end()) {
                // 如果存在映射

                if (word[i] != it->second) {
                    // 判断是否相等
                    return false;
                }
            } else {
                // 如果word 中已经存在映射了，直接返回 错误
                if (used.find(word[i]) != used.end()) {
                    return false;
                }

                // pattern[i] -> word[i] 的映射
                relat[pattern[i]] = word[i];
                // word[i] -> pattern[i] 的映射
                used.insert(word[i]);
            }
        }

        return true;
    }
};
````
