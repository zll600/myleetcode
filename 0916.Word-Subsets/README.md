# [916. Word Subsets](https://leetcode.com/problems/word-subsets/)

## 题目

You are given two string arrays `words1` and `words2`.

A string `b` is a **subset** of string `a` if every letter in `b` occurs in `a` including multiplicity.

- For example, `"wrr"` is a subset of `"warrior"` but is not a subset of `"world"`.

A string `a` from `words1` is **universal** if for every string `b` in `words2`, `b` is a subset of `a`.

Return an array of all the **universal** strings in `words1`. You may return the answer in **any order**.

 

**Example 1:**

```
Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
Output: ["facebook","google","leetcode"]
```

**Example 2:**

```
Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["l","e"]
Output: ["apple","google","leetcode"]
```

 

**Constraints:**

- `1 <= words1.length, words2.length <= 104`
- `1 <= words1[i].length, words2[i].length <= 10`
- `words1[i]` and `words2[i]` consist only of lowercase English letters.
- All the strings of `words1` are **unique**.

## 题目大意

我们给出两个单词数组 `words1` 和 `words2`

每个单词都是一串小写字母。现在，如果 b 中的每个字母都出现在 a 中，包括重复出现的字母，那么称单词 b 是单词 a 的子集

- 例如，“wrr” 是 “warrior” 的子集，但不是 “world” 的子集

如果对 B 中的每一个单词 b，b 都是 a 的子集，那么我们称 A 中的单词 a 是通用的。你可以按任意顺序以列表形式返回 A 中所有的通用单词

## 解题思路

这里比较 b 是否是 a 的子集，只需要判断字母出现的频数即可

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0916.Word-Subsets/)

````c++
class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        vector<int> freq(26, 0);

        vector<int> tmp_freq(26, 0);
        // 先统计 words2 中的每个字符的最大频数
        for (const string& word : words2) {
            std::fill(tmp_freq.begin(), tmp_freq.end(), 0);

            for (char c : word) {
                ++tmp_freq[c - 'a'];
            }

            // 只保留最大的即可
            for (int i = 0; i < 26; ++i) {
                freq[i] = max(freq[i], tmp_freq[i]);
            }
        }

        vector<string> res;
        for (const string& word : words1) {
            std::fill(tmp_freq.begin(), tmp_freq.end(), 0);

            for (char c : word) {
                ++tmp_freq[c - 'a'];
            }

            bool flag = false;
            for (int i = 0; i < 26; ++i) {
                // 如果频数小于 words2 中的，就是无效的
                if (freq[i] > tmp_freq[i]) {
                    flag = true;
                    break;
                }
            }

            if (!flag) {
                res.push_back(word);
            }
        }

        return res;
    }
};
````
