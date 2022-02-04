# [472. Concatenated Words](https://leetcode-cn.com/problems/concatenated-words/)

## 题目

Given an array of strings `words` (**without duplicates**), return *all the **concatenated words** in the given list of* `words`.

A **concatenated word** is defined as a string that is comprised entirely of at least two shorter words in the given array.

 

**Example 1:**

```
Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
"dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
```

**Example 2:**

```
Input: words = ["cat","dog","catdog"]
Output: ["catdog"]
```

 

**Constraints:**

- `1 <= words.length <= 104`
- `0 <= words[i].length <= 1000`
- `words[i]` consists of only lowercase English letters.
- `0 <= sum(words[i].length) <= 105`

## 题目大意

给定一个没有重复的字符串数组 `words`，返回 `words` 中的所有连接词，

**连接词**的定义为：给定数组中至少两个较短的单词组成的字符串

## 解题思路

这里有这样几个问题：
- 怎样使用较短的单词来拼接较长的单词
- 怎样判断拼接出来的单词依旧存在于 `words` 中

### Solution 1: DFS + Trie (TLE)

这种解法维持了较好的前缀树的相关定义，但是超时，可以参考这篇 [题解](https://leetcode-cn.com/problems/concatenated-words/solution/pythonjavajavascriptgo-zi-dian-shu-shen-3fuzq/)

这种解法判断较长的单词能否由较短的单词拼接而成，为了加速查找，这里使用了 前缀树，这种数据结构.

这里在前缀树的查找函数中做了修改，递归去查找，估计也是这里提高了复杂度，所以超时了

````c++
struct TrieNode {
    bool is_end;
    vector<TrieNode*> children;
    
    TrieNode() {
        is_end = false;
        children = vector<TrieNode*>(26, nullptr);
    }
    ~TrieNode() {
        for (auto& child : children) {
            if (!child) {
                delete child;
            }
        }
    }
};

class Trie {
 public:
    Trie() {
        root_ = new TrieNode();
    }
    ~Trie() {
        if (!root_) {
            delete root_;
        }
    }
    
    // 向树种添加节点
    void Insert(const string& word) {
        if (word.empty()) {
            return;
        }
        
        TrieNode *cur = root_;
        for (char c : word) {
            if (cur->children[c - 'a'] == nullptr) {
                cur->children[c - 'a'] = new TrieNode();
            }
            cur = cur->children[c - 'a'];
        }
        cur->is_end = true;
    }
    
    bool Search(const string& word) {
        if (word.empty()) {
            return false;
        }
        
        TrieNode *cur = root_;
        const int len = word.size();
        for (int i = 0; i < len; ++i) {
            char c = word[i];
            if (cur->is_end) {
                //  如果可以拆分出一个单词，则直接拆出来，后续遍历新的单词
                if (Search(word.substr(i))) {
                    return true;
                }
            }
            
            if (cur->children[c - 'a'] == nullptr) {
                return false;
            }
            cur = cur->children[c - 'a'];
        }
        return cur->is_end;
    }
    
 private:
    TrieNode *root_;
};


class Solution {
public: 
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        // 先按照长度 升序排序
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });
        
        vector<string> res;
        const int len = words.size();
        for (int i = 0; i < len; ++i) {
            if (words[i].empty()) {
                // 如果为空，跳过
                continue;
            }
            
            if (trie_.Search(words[i])) {
                // 如果找到了，就加到结果集中
                res.push_back(words[i]);
            } else {
                // 如果不是拼接字符串才加到 前缀树中，
                // 如果是拼接字符串，可以由较短的构成，也可以验证
                trie_.Insert(words[i]);
            }
        }
        
        return res;
    }
    
 private:
    Trie trie_;
};


````

### Solution 2: DFS + Trie + Cache

这种解法可以通过，但是我没有采用，主要是因为这里的话，破坏了 前缀树的封装性，感觉这里耦合的有点严重，

可以参考这篇 [题解](https://leetcode-cn.com/problems/concatenated-words/solution/wei-rao-li-lun-qian-zhui-shu-dfsji-yi-hu-cqq3/)


````c++
struct Trie {
    bool e; // is end
    vector<Trie*> c;
    Trie() {
        this->c = vector<Trie*>(26, NULL);
        this->e = false;
    }
};

class Solution {
public:
    Trie* t;
    unordered_map<int, unordered_map<int, int>> m;

    void insert(string& w) {
        Trie* cur = t;
        for (auto c: w) {
            if (cur->c[c-'a'] == NULL) cur->c[c-'a'] = new Trie();
            cur = cur->c[c-'a'];
        }
        cur->e = true;
    }

    bool dfs(int pos, string& target, int which) {
        if (m[which][pos] == 1) return false; // which只是为了方便记忆化搜索
        Trie* cur = t; // cur指向trie根节点
        if (pos >= target.size()) return true; // 如果 pos 已经超过单词范围；说明匹配成功
        for (int i = pos; i < target.size(); i++) {
            if (cur->c[target[i]-'a'] == NULL) break; // 如果前缀树上不存在这个字母，说明单词不可能被匹配
            if (cur->c[target[i]-'a']->e) { // 如果当前位置可以被之前某个单词完整匹配
                if (dfs(i+1, target, which)) return true; // 尝试匹配 target[i+1:] 
            }
            cur = cur->c[target[i]-'a']; // 比较trie的下一个节点
        }
        m[which][pos] = 1; // 如果当前单词当前位置开始不可能有解，记录状态，防止重复搜索
        return false;
    }

    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        sort(words.begin(), words.end(), [&](string &a, string &b) {
            return a.size() < b.size();
        });
        vector<string> ans;
        t = new Trie();

        for (int i = 0; i < words.size(); i++) {
            if (words[i] == "") continue;
            if (dfs(0, words[i], i)) {
                ans.push_back(words[i]);
            }
            insert(words[i]);
        }

        return ans;
    }

    
};

````

### Solution 3: DP

上述两种的做法也是状态转移，就是当前字符串，在当前位置之后的子串能否由已经遍历过的单词构成，

这种解法可以参考这篇 [题解](https://leetcode-cn.com/problems/concatenated-words/solution/gong-shui-san-xie-xu-lie-dpzi-fu-chuan-h-p7no/)

这里使用 哈希 来做预处理来降低匹配字符串时的时间复杂度，可以好好看看上面的题解，这道题理解起来还是有一定难度的，


- 状态定义：dp[i] 表示 word 的前 i 个字符，能切分出来的最大的 item 数

````c++
class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        for (const string& word : words) {
            // 这里避免逸出
            unsigned long long hash = 0;
            
            // 对每个字符串进行预哈希
            for (char c : word) {
                hash = hash * kP + (c - 'a') + kOffset;
            }
            memo_.insert(hash);
        }
        
        vector<string> ans;
        for (const string& word : words) {
            if (Check(word)) {
                ans.push_back(word);
            }
        }
        return ans;
    }
    
 private:
    const int kP = 131;
    const int kOffset = 128;
    unordered_set<unsigned long long> memo_;
    
    bool Check(const string& word) {
        const int len = word.size();
        // 默认初始化为 -1，
        // 定义 dp[i]f[i] 为考虑 word 的前 i 个字符（令下标从 1 开始），能够切分出的最大 item 数的个数
        vector<int> dp(len + 1, -1);
        
        dp[0] = 0;
        for (int i = 0; i <= len; ++i) {
            if (dp[i] == -1) {
                // 跳过无效的
                continue;
            }
            
            unsigned long long cur = 0;
            for (int j = i + 1; j <= len; ++j) {
                // 从 i 位置开始的单词
                cur = cur * kP + (word[j - 1] - 'a') + kOffset;
                if (memo_.find(cur) != memo_.end()) {
                    // 如果存在
                    dp[j] = max(dp[j], dp[i] + 1);
                }
            }
            
            if (dp[len] > 1) {
                // 这里相当于一个剪枝，只要满足这个条件，就可以判定满足条件了
                return true;
            }
        }
        
        return false;
    }
};
````

