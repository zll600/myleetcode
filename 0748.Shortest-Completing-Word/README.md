# [748. Shortest Completing Word](https://leetcode.com/problems/shortest-completing-word/)

## 题目:  

Given a string `licensePlate` and an array of strings `words`, find the **shortest completing** word in `words`.

A **completing** word is a word that **contains all the letters** in `licensePlate`. **Ignore numbers and spaces** in `licensePlate`, and treat letters as **case insensitive**. If a letter appears more than once in `licensePlate`, then it must appear in the word the same number of times or more.

For example, if `licensePlate`` = "aBc 12c"`, then it contains letters `'a'`, `'b'` (ignoring case), and `'c'` twice. Possible **completing** words are `"abccdef"`, `"caaacab"`, and `"cbca"`.

Return *the shortest **completing** word in* `words`*.* It is guaranteed an answer exists. If there are multiple shortest **completing** words, return the **first** one that occurs in `words`.

 

**Example 1:**

```
Input: licensePlate = "1s3 PSt", words = ["step","steps","stripe","stepple"]
Output: "steps"
Explanation: licensePlate contains letters 's', 'p', 's' (ignoring case), and 't'.
"step" contains 't' and 'p', but only contains 1 's'.
"steps" contains 't', 'p', and both 's' characters.
"stripe" is missing an 's'.
"stepple" is missing an 's'.
Since "steps" is the only word containing all the letters, that is the answer.
```

**Example 2:**

```
Input: licensePlate = "1s3 456", words = ["looks","pest","stew","show"]
Output: "pest"
Explanation: licensePlate only contains the letter 's'. All the words contain 's', but among these "pest", "stew", and "show" are shortest. The answer is "pest" because it is the word that appears earliest of the 3.
```

 

**Constraints:**

- `1 <= licensePlate.length <= 7`
- `licensePlate` contains digits, letters (uppercase or lowercase), or space `' '`.
- `1 <= words.length <= 1000`
- `1 <= words[i].length <= 15`
- `words[i]` consists of lower case English letters.

## 题目大意

如果单词列表 `words` 中的一个单词包含牌照 `licensePlate` 中所有的字母，那么我们称之为 **完整词** 。在所有完整词中，最短的单词我们称之为 **最短完整词**。

单词在匹配牌照中的字母时 **不区分大小写** ，比如牌照中的 `P` 依然可以匹配单词中的 `p` 字母。我们保证一定存在一个最短完整词。当有多个单词都符合最短完整词的匹配条件时取单词列表中最靠前的一个。牌照中可能包含多个相同的字符，比如说：对于牌照 “PP”，单词 “pair” 无法匹配，但是 “supper” 可以匹配。

## 解题思路

对于这道题目，就是要统计给定的字符串，和所有的字符串数组中的字母频数，要注意的点有：

- 拍照字符串中不仅有小写字母，需要排除其他字母，并将大写字母转化为小写字母，然后进行累计频数
- 还有就是答案必须是第一个最短的符合条件的 完整词，所以这里的顺序也是不能改变的,

### Solution 1:


````c++
class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        vector<int> license = GenCenter(licensePlate);
        
        string ans = "";
        for (const string& word : words) {
            if (IsValid(license, word)) {
                if (ans == "" || ans.size() > word.size()) {
                    ans = word;
                }
            }
        }
        
        return ans;
    }
    
 private:
    vector<int> GenCenter(const string& license_plate) {
        vector<int> freq(26, 0);
        for (char c : license_plate) {
            if (::isalpha(c)) {
                ++freq[::tolower(c) - 'a'];
            }
        }
        
        return freq;
    }
    
    bool IsValid(const vector<int>& freq_license, const string& word) {
        vector<int> freq(26, 0);
        for (char c : word) {
            ++freq[c - 'a'];
        }
        
        for (int i = 0; i < 26; ++i) {
            if (freq_license[i] > freq[i]) {
                return false;
            }
        }
        return true;
    }
};
````
