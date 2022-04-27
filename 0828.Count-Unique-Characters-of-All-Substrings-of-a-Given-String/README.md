# [828. Count Unique Characters of All Substrings of a Given String](https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/)

## 题目

Let's define a function `countUniqueChars(s)` that returns the number of unique characters on `s`.

- For example, calling `countUniqueChars(s)` if `s = "LEETCODE"` then `"L"`, `"T"`, `"C"`, `"O"`, `"D"` are the unique characters since they appear only once in `s`, therefore `countUniqueChars(s) = 5`.

Given a string `s`, return the sum of `countUniqueChars(t)` where `t` is a substring of `s`.

Notice that some substrings can be repeated so in this case you have to count the repeated ones too.

 

**Example 1:**

```
Input: s = "ABC"
Output: 10
Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
Evey substring is composed with only unique letters.
Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
```

**Example 2:**

```
Input: s = "ABA"
Output: 8
Explanation: The same as example 1, except countUniqueChars("ABA") = 1.
```

**Example 3:**

```
Input: s = "LEETCODE"
Output: 92
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s` consists of uppercase English letters only.

## 题目大意

如果一个字符在字符串 `S` 中有且仅有出现一次，那么我们称其为独特字符。例如，在字符串 `S = “LETTER”` 中，`“L”` 和 `“R”` 可以被称为独特字符。我们再定义 `UNIQ(S)` 作为字符串 `S` 中独特字符的个数。那么，在 `S = “LETTER”` 中， `UNIQ(“LETTER”) =  2`。

对于给定字符串 `S`，计算其所有非空子串的独特字符的个数（即 `UNIQ(substring)`）之和。如果在 `S` 的不同位置上出现两个甚至多个相同的子串，那么我们认为这些子串是不同的。

考虑到答案可能会非常大，规定返回格式为：结果 `mod 10 ^ 9 + 7`。

## 解题思路



### Solution 1: TLE

暴力解法最终会超时

````c++
class Solution {
public:
    int uniqueLetterString(string s) {
        int res = 0;
        
        // 设置缓存
        unordered_map<string, int> cnt;
        const int len = s.size();
        for (int i = 0; i < len; ++i) {
            for (int j = i + 1; j <= len; ++j) {
                string key = s.substr(i, j - i);
                auto it = cnt.find(key);
                if (it != cnt.end()) {
                    res += it->second;
                } else {
                    cnt[key] = Calc(key);
                    res += cnt[key];
                }
            }
        }
        
        return res;
    }
    
 private:
    // 计算频数
    int Calc(const string& str) {
        vector<int> freq(26, 0);
        for (char c : str) {
            ++freq[c - 'A'];
        }
        
        int res = 0;
        for_each(freq.begin(), freq.end(), [&](int cnt) {
            if (cnt == 1) {
                ++res;
            }
        });
        
        return res;
    }
};
````

### Solution 2:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0828.Count-Unique-Characters-of-All-Substrings-of-a-Given-String/)

````c++
class Solution {
public:
    int uniqueLetterString(string s) {
        int res = 0;
            
        const int len = s.size();
        for (int i = 0; i < len; ++i) {
            int left = i - 1;
            while (left >= 0 && s[left] != s[i]) {
                --left;
            }
            int right = i + 1;
            while (right < len && s[right] != s[i]) {
                ++right;
            }
            
            res = (res + 1L * (i - left) * (right - i)) % mod_;
        }
        
        return res;
    }
    
 private:
    const int mod_ = 1e9 + 7;
};
````
