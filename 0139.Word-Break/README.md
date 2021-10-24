# [139. Word Break](https://leetcode-cn.com/problems/word-break/)

## 题目

Given a string `s` and a dictionary of strings `wordDict`, return `true` if `s` can be segmented into a space-separated sequence of one or more dictionary words.

**Note** that the same word in the dictionary may be reused multiple times in the segmentation.

 

**Example 1:**

```
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
```

**Example 2:**

```
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.
```

**Example 3:**

```
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
```

 

**Constraints:**

- `1 <= s.length <= 300`
- `1 <= wordDict.length <= 1000`
- `1 <= wordDict[i].length <= 20`
- `s` and `wordDict[i]` consist of only lowercase English letters.
- All the strings of `wordDict` are **unique**.

## 题目答疑

给定一个非空字符串 `s` 和一个包含非空单词的列表 `wordDict`，判定 `s` 是否可以被空格拆分为一个或多个在字典中出现的单词。

注意：你可以重复使用字典中的单词

## 解题思路

这道题可以参考这篇题解：https://leetcode-cn.com/problems/word-break/solution/shou-hui-tu-jie-san-chong-fang-fa-dfs-bfs-dong-tai/

weiwei老师的题解：https://leetcode-cn.com/problems/word-break/solution/dong-tai-gui-hua-python-dai-ma-by-liweiwei1419-2/

### Solution 1: DFS(tle)

````c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // 将所有的单词加入一个哈希集合中，方便查找
        unordered_set<string> dict;
        for (const string& str : wordDict) {
            dict.insert(str);
        }
        
        return DFS(s, 0, dict);
    }
    
 private:
    bool DFS(const string& str, int idx,
             const unordered_set<string>& dict) {
        if (idx == str.size()) {  // 匹配结束，返回 true
            return true;
        }
        
        const int len = str.size();
        for (int i = idx; i < len; ++i) {
            string prefix = str.substr(idx, i - idx + 1);  // 分割字符串
            if (dict.find(prefix) != dict.end()) {  // 如果字典中存在，继续分割，否则回溯，重新切割
                if (DFS(str, i + 1, dict)) {  // 递归查找存在，直接返回
                    return true;
                }
            }
        }
        return false;
    }
};
````

### Solution 2: DFS  + 记忆化

```c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //  构建字典集合，方便查找
        unordered_set<string> dict;
        for (const string& word : wordDict) {
            dict.insert(word);
        }
        
        // 缓存结果
        unordered_map<int, bool> memo;
        return DFS(s, 0, memo, dict);
    }
    
 private:
    bool DFS(const string& str, int idx, unordered_map<int, bool>& memo,
            unordered_set<string>& dict) {
        if (idx == str.size()) {  // 匹配结束，返回 true
            return true;
        }
        if (memo.find(idx) != memo.end()) {  // 已经有结果，直接返回
            return memo.at(idx);
        }
        
        const int len = str.size();  // 长度
        for (int i = idx; i < len; ++i) {
            string prefix = str.substr(idx, i - idx + 1);  // 截取子串
            if (dict.find(str) != dict.end()) {  // 匹配，继续递归查找
                if (DFS(str, idx + 1, memo, dict)) {  // 查找成功
                    memo[idx] = true;  // 缓存结果
                    return true;
                }
            }
        }
        memo[idx] = false;
        return false;
    }
};
```

### Solution 3: BFS

````c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        return BFS(s, wordDict);
    }
    
 private:
    bool BFS(const string& str, const vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        
        const int size = str.size();
        // 用队列来进行状态转移
        queue<int> que;
        que.push(0);
        
        while (!que.empty()) {
            const int start = que.front();
            que.pop();
            
            for (int i = start + 1; i <= size; ++i) {
                // 分割字符串，这里是左闭右开区间
                string prefix = str.substr(start, i - start);
                if (dict.find(prefix) != dict.end()) {
                    // 如果没有匹配结束，加入队列，继续进行匹配，直到结束
                    if (i < size) {
                        que.push(i);
                    } else {  // 匹配结束，直接返回
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
};
````

### Solution 4: BFS 优化

````c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        return BFS(s, wordDict);
    }
    
 private:
    bool BFS(const string& str, const vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        const int size = str.size();
        vector<bool> visited(size);
        // 用队列来进行状态转移
        queue<int> que;
        que.push(0);
        
        while (!que.empty()) {
            const int start = que.front();
            if (visited[start] == true) {  // 如果已经访问过，则直接跳过
                continue;
            }
            visited[start] = true;  // 记录已经访问过了
            que.pop();
            
            for (int i = start + 1; i <= size; ++i) {
                // 分割字符串，这里是左闭右开区间
                string prefix = str.substr(start, i - start);
                if (dict.find(prefix) != dict.end()) {
                    // 如果没有匹配结束，加入队列，继续进行匹配，直到结束
                    if (i < size) {
                        que.push(i);
                    } else {  // 匹配结束，直接返回
                        return true;
                    }
                }  //单词不匹配，重新划分
            }
        }
        
        return false;
    }
};
````

## Solution 5: DP

* 状态定义：dp[i] 表示 [0, i - 1] 之间的子串能否被单词表中单词构成，
* 状态转移方程：





````c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        const int size = s.size();
        // 状态数组
        vector<int> dp(size + 1, false);
        dp[0] = true;  // 没有实际意义，为了让地推可以进行下去
        
        for (int i = 1; i <= size; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                const string prefix = s.substr(j, i - j);
                // 状态转移
                if (dict.find(prefix) != dict.end() && dp[j]) {
                    dp[i] = true;
                    break;  // 一旦匹配成功，直接跳出内层循环，分割下一个单词
                }
            }
        }
        return dp[size];
    }
};
````

### Solution 6: dp + 剪枝

````c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // 初始化字典
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        const int size = s.size();
        // 状态数组
        vector<int> dp(size + 1, false);
        dp[0] = true;  // 没有实际意义，为了让递推可以进行下去
        
        for (int i = 1; i <= size; ++i) {
            if (dp[i] == true) {  // 如果  i 已经计算过，直接跳过
                continue;
            }
            for (int j = i - 1; j >= 0; --j) {
                if (dp[j] == false) {  // 如果 [0, j - 1] 不可能，直接跳过
                    continue;
                }
                
                const string prefix = s.substr(j, i - j);
                // 状态转移
                if (dict.find(prefix) != dict.end() && dp[j]) {
                    dp[i] = true;
                    break;  // 一旦匹配成功，直接跳出内层循环，分割下一个单词
                }
            }
        }
        return dp[size];
    }
};
````

