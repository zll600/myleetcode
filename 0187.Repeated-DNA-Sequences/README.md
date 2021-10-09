# [187. Repeated DNA Sequences](https://leetcode.com/problems/repeated-dna-sequences/)

## 题目

The **DNA sequence** is composed of a series of nucleotides abbreviated as `'A'`, `'C'`, `'G'`, and `'T'`.

- For example, `"ACGAATTCCG"` is a **DNA sequence**.

When studying **DNA**, it is useful to identify repeated sequences within the DNA.

Given a string `s` that represents a **DNA sequence**, return all the **`10`-letter-long** sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in **any order**.

 

**Example 1:**

```
Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC","CCCCCAAAAA"]
```

**Example 2:**

```
Input: s = "AAAAAAAAAAAAA"
Output: ["AAAAAAAAAA"]
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is either `'A'`, `'C'`, `'G'`, or `'T'`.

## 题目大意

所有 DNA 由一系列缩写为 A，C，G 和 T 的核苷酸组成，例如：“ACGAATTCCG”。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。编写一个函数来查找 DNA 分子中所有出现超多一次的10个字母长的序列（子串）。

## 解题思路

首先要注意这道题的数据范围，注意特殊数据的处理

## 解法1（滑动窗口）

枚举所有长度为 10 的子串，选出最终的结果即可

`````c++
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if (s.size() < 10) {  // 边界情况
            return vector<string>();
        }
        
        unordered_set<string> dict;  // 收集出现过的子串，这里每个出现过子串只记录一次
        
        unordered_set<string> ans;  // 收集最终的结果，这里是为了去重
        for (int i = 0; i < s.size() - 9; ++i) {
            string str = s.substr(i, 10);
            if (dict.find(str) != dict.end()) {  // 如果出现过，就加入到
                // cout << str << endl;
                ans.insert(str);
            } else {
                dict.insert(str);
            }
        }
        
        return vector<string>(ans.begin(), ans.end());
    }
};
`````



## 解法2

和解法1相同的思路，不过这里直接在最终结果上去重，我个人觉得这里是时间换空间了

`````c++
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if (s.size() < 10) {  // 边界情况
            return vector<string>();
        }
        
        unordered_set<string> dict;  // 收集出现过的子串，这里每个出现过子串只记录一次
        
        vector<string> res;
        for (int i = 0; i < s.size() - 9; ++i) {
            string str = s.substr(i, 10);
            if (dict.find(str) != dict.end()) {  // 如果出现过，就加入到
                if (find(res.begin(), res.end(), str) == res.end()) {
                    res.push_back(str);
                }
            } else {
                dict.insert(str);
            }
        }
        
        return res;
    }
};
`````

