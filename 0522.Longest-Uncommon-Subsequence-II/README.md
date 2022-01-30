# [522. Longest Uncommon Subsequence II](https://leetcode-cn.com/problems/longest-uncommon-subsequence-ii/)

## 题目

Given an array of strings `strs`, return *the length of the **longest uncommon subsequence** between them*. If the longest uncommon subsequence does not exist, return `-1`.

An **uncommon subsequence** between an array of strings is a string that is a **subsequence of one string but not the others**.

A **subsequence** of a string `s` is a string that can be obtained after deleting any number of characters from `s`.

- For example, `"abc"` is a subsequence of `"aebdc"` because you can delete the underlined characters in `"aebdc"` to get `"abc"`. Other subsequences of `"aebdc"` include `"aebdc"`, `"aeb"`, and `""` (empty string).

 

**Example 1:**

```
Input: strs = ["aba","cdc","eae"]
Output: 3
```

**Example 2:**

```
Input: strs = ["aaa","aaa","aa"]
Output: -1
```

 

**Constraints:**

- `2 <= strs.length <= 50`
- `1 <= strs[i].length <= 10`
- `strs[i]` consists of lowercase English letters.

## 题目大意

给定一个字符串数组 `strs`，返回他们之间的最长的特殊子序列，如果不存在，返回 -1

数组中的特殊子序列，是一个字符串的子数组，但不是其他的，

一个子序列可以字符串中删除一些字符，

## 解题思路

这里和 第 521 题的解决问题的关注点类似

* 优先考虑长度较长的字符串
* 然后判断，字符串是否相同，
* 不过这道题要多判断子串的存在

### Solution 1:

这里有一下几点：
* 优先考虑较长的字符串
* 如果当前字符串只出现过一次，且它不是比它长的字符串的子串，就满足题意了

这道题目的复杂度分析，可以参考 [官方题解](https://leetcode-cn.com/problems/longest-uncommon-subsequence-ii/solution/zui-chang-te-shu-xu-lie-ii-by-leetcode/)


```c++
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        // 建立基本的映射关系
        for (const auto str : strs) {
            data_[str.size()].push_back(str);
        }
        
        for (auto it = data_.rbegin();
             it != data_.rend(); ++it) {
            if (IsValid(it->second))
                // 如果满足条件，直接返回
                return it->first;
            
            // 插入到集合中，后面要用到
            memo_.insert(it->second.begin(), it->second.end());
        }
        return -1;
    }
    
 private:
    map<int, vector<string>> data_; // key: 字符串的长度，val: 相同长度的字符串的集合
    unordered_set<string> memo_; // 这里存储较长，但已经失效的 字符串
    
    bool IsValid(vector<string>& strs) {
        // 排序可以加速判断是存在相同的字符串
        sort(strs.begin(), strs.end());
        
        const int len = strs.size();
        for (int i = 0; i < len; ++i) {
            if ((i > 0 && strs[i] == strs[i - 1])
               || (i < len - 1 && strs[i] == strs[i + 1])) {
                // 如果存在相同，则直接跳过，这个字符串就不可用了
                continue;
            }
            
            if (memo_.empty()) {
                // 如果当前这个就是最长，那直接返回
                return true;
            }
            
            // 接下来判断，是不是较长字符串的子串
            const int len_a = strs[i].size();
            for (const auto& mem : memo_) {
                const int len_b = mem.size();
                
                int a = 0, b = 0;
                while (a < len_a && b < len_b) {
                    if (strs[i][a] == mem[b]) {
                        ++a;
                        ++b;
                    } else {
                        ++b;
                    }
                }
                if (a != len_a) {
                    // 如果不是，直接返回
                    return true;
                }
            }
        }
        return false;
    }
};
```

