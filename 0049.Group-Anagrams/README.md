# [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/)

Given an array of strings `strs`, group **the anagrams** together. You can return the answer in **any order**.

An **Anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

**Example 1:**

```
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
```

**Example 2:**

```
Input: strs = [""]
Output: [[""]]
```

**Example 3:**

```
Input: strs = ["a"]
Output: [["a"]]
```

 

**Constraints:**

- `1 <= strs.length <= 104`
- `0 <= strs[i].length <= 100`
- `strs[i]` consists of lowercase English letters.

## 题目大意

给定一个字符串数组，将 anagrams 放在一起返回

一个 anagrams 是由一个单词重新排列字母得到的，通常原来的每个字母只使用一次

## 解题思路

#### 解法1（使用哈希表）

这道题解决问题的关键是意识到 所有的 anagrams 按照字典序排序之后得到的字符串是一样的，所以可以用这个排序后得到的字符串来作为键，用所有排序后可以得到 key 的字符串的集合来作 val,

``````c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> buckets;
        
        for (int i = 0; i < strs.size(); i++) {
            string tmp = strs[i];  // 创建一个临时变量来排序进行选择
            sort(tmp.begin(), tmp.end());
            buckets[tmp].push_back(strs[i]);
        }
        
        vector<vector<string>> res;
        for (auto& it : buckets) {
            res.push_back(it.second);
        }
        return res;
    }
};
``````

