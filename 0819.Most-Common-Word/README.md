# [819. Most Common Word](https://leetcode.com/problems/most-common-word/)

## 题目

Given a string `paragraph` and a string array of the banned words `banned`, return *the most frequent word that is not banned*. It is **guaranteed** there is **at least one word** that is not banned, and that the answer is **unique**.

The words in `paragraph` are **case-insensitive** and the answer should be returned in **lowercase**.

 

**Example 1:**

```
Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.", banned = ["hit"]
Output: "ball"
Explanation: 
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
Note that words in the paragraph are not case sensitive,
that punctuation is ignored (even if adjacent to words, such as "ball,"), 
and that "hit" isn't the answer even though it occurs more because it is banned.
```

**Example 2:**

```
Input: paragraph = "a.", banned = []
Output: "a"
```

 

**Constraints:**

- `1 <= paragraph.length <= 1000`
- paragraph consists of English letters, space `' '`, or one of the symbols: `"!?',;."`.
- `0 <= banned.length <= 100`
- `1 <= banned[i].length <= 10`
- `banned[i]` consists of only lowercase English letters.

## 题目大意

给定一个字符串 `paragraph` 和一个表示被禁止单词的数组 `banned`，返回 *出现次数最多的没有被禁止的单词*，

题目保证至少有一个单词是没有被禁止的，答案是唯一的，

### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0819.Most-Common-Word/)

这里提醒一点，就是在写循环逻辑的时候，一定要考虑充分，所写的循环中的逻辑是否可能会有处理不到的地方，需要及时补充

````c++
class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_map<string, int> freq;
        Split(freq, paragraph);
        // 删掉禁止的单词
        for (const string& ban : banned) {
            freq.erase(ban);
        }

        int max_freq = 0;
        string res = "";
        for (const auto& item : freq) {
            // cout << item.first << "==>" << item.second << endl;
            if (item.second > max_freq) {
                res = item.first;
                max_freq = item.second;
            }
        }

        return res;
    }

 private:
    // 将字符串转化为小写
    string ToLower(const string& str) {
        string res = "";
        for (char c : str) {
            res += tolower(c);
        }

        return res;
    }

    // 计算每个单词出现的频数
    void Split(unordered_map<string, int>& freq, const string& paragraph) {
        const int len = paragraph.size();

        int idx1 = 0;
        for (int idx2 = 1; idx2 < len; ++idx2) {
            if (paragraph[idx2] == ' ' || paragraph[idx2] == ',' || paragraph[idx2] == '?'
               || paragraph[idx2] == '.' || paragraph[idx2] == ';' || paragraph[idx2] == '!'
               || paragraph[idx2] == '\'') {
                if (idx2 > idx1) {
                    string key = ToLower(paragraph.substr(idx1, idx2 - idx1));
                    ++freq[key];
                    // cout << key << "==>" << freq[key] << endl;
                }
                idx1 = idx2 + 1;
            }
        }
        // 这里防止遗忘最后一个
        if (idx1 < len) {
            string key = ToLower(paragraph.substr(idx1));
            ++freq[key];
        }
    }
};
````
