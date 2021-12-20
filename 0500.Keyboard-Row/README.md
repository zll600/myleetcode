# [500. Keyboard Row](https://leetcode.com/problems/keyboard-row/)

Given an array of strings `words`, return *the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below*.

In the **American keyboard**:

- the first row consists of the characters `"qwertyuiop"`,
- the second row consists of the characters `"asdfghjkl"`, and
- the third row consists of the characters `"zxcvbnm"`.

![img](https://assets.leetcode.com/uploads/2018/10/12/keyboard.png)

 

**Example 1:**

```
Input: words = ["Hello","Alaska","Dad","Peace"]
Output: ["Alaska","Dad"]
```

**Example 2:**

```
Input: words = ["omk"]
Output: []
```

**Example 3:**

```
Input: words = ["adsdf","sfd"]
Output: ["adsdf","sfd"]
```

 

**Constraints:**

- `1 <= words.length <= 20`
- `1 <= words[i].length <= 100`
- `words[i]` consists of English letters (both lowercase and uppercase). 

## 题目大意

给定一组单词，返回只用键盘中的一排就可以输入的单词，

## 解题思路

这道题目重要的是将 26 个字母划分为 3 组，分别代表 3 行，要求不同的单词中出现的字母都在用一组中即可

### Solution 1:

这里需要注意的就是给定的单词，可能包含大写字母，在进行判断判断时需要进行转化，否则会造成数组下标越界

````c++
class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        // 每行的字母集合
        vector<string> querys = {
            "qwertyuiop",
            "asdfghjkl",
            "zxcvbnm"
        };
        
        // 将所有的字母进行分组
        vector<int> hash(26);
        for (int i = 0; i < 3; ++i) {
            for (char c : querys[i]) {
                hash[c - 'a'] = i;
            }
        }
        
        vector<string> res;
        for (const string& word : words) {
            bool flag = true;
            const int len = word.size();
            for (int i = 0; i < len; ++i) {
                // 如果一个单词中存在不在同一行的字母
                // 这里要注意全部转化为小写字母
                if (i > 0 && hash[tolower(word[i]) - 'a'] != hash[tolower(word[i - 1]) - 'a']) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                res.push_back(word);
            }
        }
        
        return res;
    }
};
````
