# [140. Word Break II](https://leetcode-cn.com/problems/word-break-ii/)

Given a string `s` and a dictionary of strings `wordDict`, add spaces in `s` to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in **any order**.

**Note** that the same word in the dictionary may be reused multiple times in the segmentation.

 

**Example 1:**

```
Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]
```

**Example 2:**

```
Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.
```

**Example 3:**

```
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
```

 

**Constraints:**

- `1 <= s.length <= 20`
- `1 <= wordDict.length <= 1000`
- `1 <= wordDict[i].length <= 10`
- `s` and `wordDict[i]` consist of only lowercase English letters.
- All the strings of `wordDict` are **unique**.

## 题目大意

给定一个字符串 s 和一个包含字符串的字典 `wordDict`，在字符串中增加空格来构建一个句子，使得句子中所有的单词都在词典中。返回所有这些可能的句子。

说明：

* 分隔时可以重复使用字典中的单词。
* 你可以假设字典中没有重复的单词。

## 解题思路

这道题可以参考这篇题解：https://leetcode-cn.com/problems/word-break-ii/solution/dong-tai-gui-hua-hui-su-qiu-jie-ju-ti-zhi-python-d/

这道题可以和第 139 题放在一起来做

这道题的话，因为涉及到要求所有的方案，所以 dp 肯定是没办法的，只能使用 DFS 来解决，每一层递归我们从未切割的部分中选一个出现在字典中的单词，切割出来，然后组合为一个句子，

关键还是涉及到回溯和递归，尽量画出相关的树形图，然后分析

### Solution 1: DFS

````c++
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // 构建字典集合，加速查询操作
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        const int size = s.size();
        // dp[i] 表示 [0, i）范围内的子串能否被拆分为字典中的单词
        // 所以结果是 dp[size]
        vector<bool> dp(size + 1, false);
        // [0, 0) 表示一个空的字符串，没有任何意义
        dp[0] = true;
        
        // 切分子串，从前往后
        for (int i = 1; i < size + 1; ++i) {
            // 判断每一个子串能否被切分，从后往前
            // 因为
            // for (int j = i - 1; j >= 0; --j) {
            for (int j = 0; j < i; ++j) {
                // 如果之前计算过，不能拆分，跳过
                if (!dp[j]) {
                    continue;
                }
                
                // 切分子串，生成单词
                const string str = s.substr(j, i - j);
                // 查到单词
                if (dict.find(str) != dict.end()) {
                    dp[i] = true;
                    break;  // 只要确定可以拆分，且满足条件，直接跳出循环
                }
            }
        }
        
        // 如果最终不能拆分，直接返回
        if (!dp[size]) {
            return vector<string>();
        }
        
        vector<string> res;
        DFS(s, size, dict, dp, "", res);
        return res;
    }
    
 private:    
    void DFS(const string& s, int idx, const unordered_set<string>& dict,
            const vector<bool>& dp, string path, vector<string>& res) {
        // 如果已经切结束，直接返回
        if (!idx) {
            path.pop_back();
            res.push_back(path);
            return;
        }
        
        // 拆分[i, idx)
        for (int i = idx - 1; i >= 0; --i) {
            if (!dp[i]) {  // [0, i) 不能拆分，则跳过
                continue;
            }
            // 切分子串
            const string str = s.substr(i, idx - i);
            if (dict.find(str) != dict.end()) {
                DFS(s, i, dict, dp, str + " " + path, res);
            }
        }
    }
};
````



