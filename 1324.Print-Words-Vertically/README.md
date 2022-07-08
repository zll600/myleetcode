#### [1324. Print Words Vertically](https://leetcode.cn/problems/print-words-vertically/)

Given a string `s`. Return all the words vertically in the same order in which they appear in `s`.
 Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
 Each word would be put on only one column and that in one column there will be only one word.

 

**Example 1:**

```
Input: s = "HOW ARE YOU"
Output: ["HAY","ORO","WEU"]
Explanation: Each word is printed vertically. 
 "HAY"
 "ORO"
 "WEU"
```

**Example 2:**

```
Input: s = "TO BE OR NOT TO BE"
Output: ["TBONTB","OEROOE","   T"]
Explanation: Trailing spaces is not allowed. 
"TBONTB"
"OEROOE"
"   T"
```

**Example 3:**

```
Input: s = "CONTEST IS COMING"
Output: ["CIC","OSO","N M","T I","E N","S G","T"]
```

 

**Constraints:**

- `1 <= s.length <= 200`
- `s` contains only upper case English letters.
- It's guaranteed that there is only one space between 2 words.

给你一个字符串 `s`。请你按照单词在 `s` 中的出现顺序将它们全部竖直返回
单词应该以字符串列表的形式返回，必要时用空格补位，但输出尾部的空格需要删除（不允许尾随空格）
每个单词只能放在一列上，每一列中也只能有一个单词



### Solution 1: Stimulation

简单模拟一下就可以了，最后把后面的所有空格删掉

````c++
class Solution {
public:
    vector<string> printVertically(string s) {
        vector<string> tokens;
        SplitStr(s, tokens, " ");
        
        size_t bound = 0;
        for (const string& token : tokens) {
            bound = max(bound, token.size());
        }
        
        vector<string> ans;
        for (size_t j = 0; j < bound; ++j) {
            string tmp;
            for (size_t i = 0; i < tokens.size(); ++i) {
                if (j < tokens[i].size()) {
                    tmp.append(1, tokens[i][j]);
                } else {
                    tmp.append(1, ' ');
                }
            }
            ans.push_back(tmp);
            // cout << tmp << endl;
        }
        
        for (auto& str : ans) {
            for (size_t i = str.size() - 1; i >= 0; --i) {
                if (str[i] == ' ') {
                    str.pop_back();
                } else {
                    break;
                }
            }
            // cout << str << endl;
        }
        
        return ans;
    }
    
 private:
    void SplitStr(const string& str, vector<string>& tokens, const string delim = " ") {
        auto start = str.find_first_not_of(delim, 0);
        while (start != string::npos) {
            auto next = str.find_first_of(delim, start);
            tokens.push_back(str.substr(start, next - start));
            start = str.find_first_not_of(delim, next);
        }
    }
};
````

