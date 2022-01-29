# [557. Reverse Words in a String III](https://leetcode.com/problems/reverse-words-in-a-string-iii/)

## 题目

Given a string `s`, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

 

**Example 1:**

```
Input: s = "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
```

**Example 2:**

```
Input: s = "God Ding"
Output: "doG gniD"
```

 

**Constraints:**

- `1 <= s.length <= 5 * 104`
- `s` contains printable **ASCII** characters.
- `s` does not contain any leading or trailing spaces.
- There is **at least one** word in `s`.
- All the words in `s` are separated by a single space.

## 题目大意

给定一个字符串 s，反转其中每个单词的字母顺序，但是不改变单词的顺序，并保留空格

## 解题思路

按照题意来做，分别反转每个单词即可，这道题目并不难

### Solution 1:

`````c++
class Solution {
public:
    string reverseWords(string s) {
        vector<string> tokens;
        Split(s, tokens, " ");
        
        s.clear(); // 这里是为了省内存 qwq
        for (string& token : tokens) {
            Reverse(token);
            s += token;
            s += " ";
        }
        s.pop_back();
        
        return s;
    }

 private:
    // 分割句子
    void Split(const string& str, vector<string>& tokens, const string& delim = " ") {
        tokens.clear();
        
        auto start = str.find_first_not_of(delim, 0);
        auto pos = str.find_first_of(delim, start);
        while (start != string::npos || pos != string::npos) {
            tokens.push_back(str.substr(start, pos - start));
            
            start = str.find_first_not_of(delim, pos);
            pos = str.find_first_of(delim, start);
        }
    }
    
    // 反转每个单词
    void Reverse(string& word) {
        int left = 0;
        int right = word.size() - 1;
        
        while (left < right) {
            swap(word[left], word[right]);
            ++left;
            --right;
        }
    }
};
`````

