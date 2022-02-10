# [792. Number of Matching Subsequences](https://leetcode.com/problems/number-of-matching-subsequences/)

## 题目

Given a string `s` and an array of strings `words`, return *the number of* `words[i]` *that is a subsequence of* `s`.

A **subsequence** of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

- For example, `"ace"` is a subsequence of `"abcde"`.

 

**Example 1:**

```
Input: s = "abcde", words = ["a","bb","acd","ace"]
Output: 3
Explanation: There are three strings in words that are a subsequence of s: "a", "acd", "ace".
```

**Example 2:**

```
Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
Output: 2
```

 

**Constraints:**

- `1 <= s.length <= 5 * 104`
- `1 <= words.length <= 5000`
- `1 <= words[i].length <= 50`
- `s` and `words[i]` consist of only lowercase English letters.

## 题目大意

给定一个字符串 `s` 和一个字符串数组 `words`，返回 是 `s` 的子序列的 `words[i]` 的数目，

**子序列** 是从原字符串中删除人意字符，保留原来字符的相对顺序，

## 解题思路

这道题目的话，首先想到的就是使用前缀树来做预处理，然后来比对字符串，不过不适合，



### Solution 1:

可以利用双指针来做，去比较字符串，但是这种解法的话，时间复杂度会比较高，

留待以后实现（逃）


### Solution 2: 哈希

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0792.Number-of-Matching-Subsequences/)

将所有的单词按照第一个字母存储在26 个桶中，然后遍历字符串 s，

这里使用 swap 操作清空了 `hash`，并将该部分内容移动到 `members` 中，

````c++
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        // 根据首字母将所有的单词散列到 26 个桶中，
        vector<vector<string>> hash(26);
        for (const string word : words) {
            int idx = word[0] - 'a';
            hash[idx].push_back(word);
        }
        
        int res = 0;
        for (char c : s) {
            // 遍历 s,
            vector<string> members;
            // 将 hash 中该桶的单词移动到 members 中
            members.swap(hash[c - 'a']);
            
            for (const string& member : members) {
                if (member.size() == 1) {
                    ++res;
                    continue;
                }
                // 加入到其他桶中
                hash[member[1] - 'a'].push_back(move(member.substr(1)));
            }
        }
        
        return res;
    }
};
````


