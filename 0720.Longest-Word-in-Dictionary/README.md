# [720. Longest Word in Dictionary](https://leetcode.com/problems/longest-word-in-dictionary/)

## 题目 

Given an array of strings `words` representing an English Dictionary, return *the longest word in* `words` *that can be built one character at a time by other words in* `words`.

If there is more than one possible answer, return the longest word  with the smallest lexicographical order. If there is no answer, return  the empty string.

 

**Example 1:**

```
Input: words = ["w","wo","wor","worl","world"]
Output: "world"
Explanation: The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
```

**Example 2:**

```
Input: words = ["a","banana","app","appl","ap","apply","apple"]
Output: "apple"
Explanation: Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".
```

 

**Constraints:**

- `1 <= words.length <= 1000`
- `1 <= words[i].length <= 30`
- `words[i]` consists of lowercase English letters.

## 题目大意

给定一个字符串数组 `words` 表示英文字典，返回 `words` 中最长的一个单词，该单词是由 `words` 词典中其他单词逐步添加一个字母组成

如果有多于一个的可能的答案，返回字典序最小的，如果没有答案，返回空字符串

## 解题思路


### Solution 1: map + sort

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0720.Longest-Word-in-Dictionary/)

我们先将字符串排序，然后我们利用 map 来查找和匹配字符串

````c++
class Solution {
public:
    string longestWord(vector<string>& words) {
        // 按照字典序进行排序
        sort(words.begin(), words.end());
        
        string res = "";
        // 存放已经遍历过的可以由已有的字符串生成的字符串
        unordered_set<string> cache;
        for (const string& word : words) {
            const int len = word.size();
            if (len == 1 || cache.find(word.substr(0, len - 1)) != cache.end()) {
                // 如果能够由已经存在的字符串生成
                if (len > res.size()) {
                    // 如果长度大于已经保存的而长度，那么更新结果
                    // 同时这里更新的也一定是字典序最小的
                    res = word;
                }
                // 将可以生成的字符串返回
                cache.insert(word);
            }
        }
        
        return res;
    }
};
````
