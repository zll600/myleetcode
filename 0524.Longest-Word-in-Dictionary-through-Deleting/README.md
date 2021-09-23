# [524. Longest Word in Dictionary through Deleting](https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/)

## 题目

Given a string `s` and a string array `dictionary`, return *the longest string in the dictionary that can be formed by deleting some of the given string characters*. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

 

**Example 1:**

```
Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
Output: "apple"
```

**Example 2:**

```
Input: s = "abpcplea", dictionary = ["a","b","c"]
Output: "a"
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `1 <= dictionary.length <= 1000`
- `1 <= dictionary[i].length <= 1000`
- `s` and `dictionary[i]` consist of lowercase English letters.

## 题目大意

给定一个字符串 s 和一个字符串数组 dicionary，返回在字符串数组中通过对原来的字符串的进行删除可以得到的最长的字符串，如果有多个字符串满足条件，按照字典序，返回最小的那一个，如果没有符合条件结果，返回一个空串

## 解题思路

* 这道题实在没办法，就试了以下暴力解法没想到竟然能过，具体思路就是遍历字典中的字符串，如果包含在 s 中，就加入候选数组中，最终在候选数组中找出最长的即可，如果有多个最长的，就返回字典序最小的那个，不过这个时间复杂度是真的高，
* 这道题目我其实不能确定是否是贪心，但是大佬说是贪心，那就是了，大佬的题解：https://leetcode-cn.com/problems/longest-word-in-dictionary-through-deleting/solution/gong-shui-san-xie-xiang-jie-pai-xu-shuan-qi20/，数学证明以后学

## 代码

`````c++
class Solution1 {
public:
    // 暴力解法
    string findLongestWord(string s, vector<string>& dictionary) {
        vector<string> candidates;
        
        for (const string& str : dictionary) {
            if (Contain(str, s)) {
                candidates.push_back(str);  // 可以通过删除得到，就加入到候选数组中，
            }
        }
        
        string res = "";
        for (const string str : candidates) {
            if (str.size() > res.size()) {  // 找到候选数组中最长的那个
                res = str;
            } else if (str.size() == res.size()) {  // 如果有多个最长的，就返回字典许最小的那个即可
                if (str < res) {
                    res = str;
                }
            }
        }
        
        return res;
    }
    
 private:
    bool Contain(const string& small, const string& big) {
        int idx = 0;
        for (char c : big) {
            if (c == small[idx]) {  // 匹配到一个就换下一个位置，直到匹配完毕
                if (++idx == small.size()) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

class Solution {
 public:
    // 解法二：
    string findLongestWord(string s, vector<string>& dictionary) {
        // 先对字典进行排序，
        // 按照长度降序排序
        // 长度相等的，按照字典序升序排序
        sort(dictionary.begin(), dictionary.end(), [](const string& a, const string& b) -> bool {
            if (a.size() != b.size()) {
                return a.size() > b.size();
            }
            return a < b;
        });
        
        for (const string& str : dictionary) {
            if (Contains(s, str)) { // 找到的第一个就是最终的结果
               return str;
            }
        }
        
        return "";
    }
    
 private:
    // 这个判断能否删除的函数，还没找到优化的方法，
    bool Contains(const string& big, const string& small) {
        int idx = 0;
        for (char c : big) {
            if (small[idx] == c) {
                if (++idx == small.size()) {
                    return true;
                }
            }
        }
        
        return false;
    }
};
`````

