# [1002. Find Common Characters](https://leetcode.com/problems/find-common-characters/)

## 题目

Given a string array `words`, return *an array of all characters that show up in all strings within the* `words` *(including duplicates)*. You may return the answer in **any order**.

 

**Example 1:**

```
Input: words = ["bella","label","roller"]
Output: ["e","l","l"]
```

**Example 2:**

```
Input: words = ["cool","lock","cook"]
Output: ["c","o"]
```

 

**Constraints:**

- `1 <= words.length <= 100`
- `1 <= words[i].length <= 100`
- `words[i]` consists of lowercase English letters.

## 题目大意

给定一个字符串数组 `words`，返回在所有字符串中出现的字符（包括重复出现的），你可以按照任意顺序返回

## 解题思路


### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1000~1099/1002.Find-Common-Characters/)

这里使用两个数组，我们统计每个字符出现的下限即可


````c++
class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        vector<int> freq(26, INT_MAX);
        vector<int> freq_word(26, 0);
        
        for (const string& word : words) {
            for (char c : word) {
                // 统计该单词中的所有字母的频数
                ++freq_word[c - 'a'];
            }
            
            for (int i = 0; i < 26; ++i) {
                // if (freq_word[i] != 0) {
                //     cout << string(1, i + 'a') << " : " << freq_word[i] << endl;
                // }
                // 针对每个字母，只需要最低的频数即可
                freq[i] = min(freq[i], freq_word[i]);
                // 这里直接置 0
                freq_word[i] = 0;
            }
            
        } 
        
        vector<string> ans;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < freq[i]; ++j) {
                ans.push_back(string(1, i + 'a'));
            }
        }
        
        return ans;
    }
};
````
