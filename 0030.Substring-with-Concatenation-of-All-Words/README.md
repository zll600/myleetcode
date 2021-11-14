# [30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)

## 题目

You are given a string `s` and an array of strings `words` of **the same length**. Return all starting indices of substring(s) in `s` that is a concatenation of each word in `words` **exactly once**, **in any order**, and **without any intervening characters**.

You can return the answer in **any order**.

 

**Example 1:**

```
Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
```

**Example 2:**

```
Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
```

**Example 3:**

```
Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
```

 

**Constraints:**

- `1 <= s.length <= 104`
- `s` consists of lower-case English letters.
- `1 <= words.length <= 5000`
- `1 <= words[i].length <= 30`
- `words[i]` consists of lower-case English letters.

## 题目大意

给定一个字符串 s，和一组长度相等的字符产 words，找出 `s` 中恰好可以由 `words` 中所有单词串联形成的子串的起始位置。每个单词只能使用一次，而且不能出现任何中间字符，你可以按照任意顺序返回结果 

## 解题思路

这道题目有几个特点，所有的单词的长度都相同，所有单词都必须无缝的拼接在一起，

### Solution 1:

这种解法可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0001~0099/0030.Substring-with-Concatenation-of-All-Words/

具体做法是，将所有的单词出现的频数做一个统计，然后在遍历 s 的过程中，构造子串，递减字典中的计数，如果字典中所有单词的频数都减小到 0，而且这时遍历的过的总长度恰好等于所有的单词的长度的总和，则可以说明出现了一次合法的起始下标，如果不符合，则从下一个字符重新开始遍历。

````c++
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> freq;  // 记录单词出现的次数
        for (const string& word : words) {
            ++freq[word];
        }
        
        const int len = words[0].size();  // 每个单词的长度
        const int total_len = words.size() * len;  // 所有单词拼接在一起饿长度
        unordered_map<string, int> tmp_freq = freq;  // 设置一个临时的字典
        
        vector<int> res;  // 结果集
        int i = 0;  // 遍历
        int start = 0;  // 起始下标
        while (i < s.size() - len + 1 && start < s.size() - len + 1) {
            string str = s.substr(i, len);  // 切分出一个子串
            if (tmp_freq[str] > 0) {  // 如果频数依旧大于 0，
                --tmp_freq[str];
                if (CheckWords(tmp_freq) && i + len - start == total_len) {
                    res.push_back(start);
                    ++i;
                    continue;
                }
                i += len;
            } else {  // 如果子串的频数已经等于 0，说明，目前的子串无法构成，
                ++start;  // 改变起始下标
                i = start;  // 重新开始遍历
                tmp_freq = freq;  // 重置频数字典
            }
        }
        
        return res;
    }
    
 private:
    // 检查字典中的单词出现的次数是否都是 0
    bool CheckWords(const unordered_map<string, int>& freq) {
        for (const auto& iter : freq) {
            if (iter.second > 0) {
                return false;
            }
        }
        return true;
    }
};
````

