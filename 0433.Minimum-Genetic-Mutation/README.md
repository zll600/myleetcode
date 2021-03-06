# [433. Minimum Genetic Mutation](https://leetcode.com/problems/minimum-genetic-mutation/)

## 题目

A gene string can be represented by an 8-character long string, with choices from `'A'`, `'C'`, `'G'`, and `'T'`.

Suppose we need to investigate a mutation from a gene string `start` to a gene string `end` where one mutation is defined as one single character changed in the gene string.

- For example, `"AACCGGTT" --> "AACCGGTA"` is one mutation.

There is also a gene bank `bank` that records all the valid gene mutations. A gene must be in `bank` to make it a valid gene string.

Given the two gene strings `start` and `end` and the gene bank `bank`, return *the minimum number of mutations needed to mutate from* `start` *to* `end`. If there is no such a mutation, return `-1`.

Note that the starting point is assumed to be valid, so it might not be included in the bank.

 

**Example 1:**

```
Input: start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
Output: 1
```

**Example 2:**

```
Input: start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
Output: 2
```

**Example 3:**

```
Input: start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
Output: 3
```

 

**Constraints:**

- `start.length == 8`
- `end.length == 8`
- `0 <= bank.length <= 10`
- `bank[i].length == 8`
- `start`, `end`, and `bank[i]` consist of only the characters `['A', 'C', 'G', 'T']`.

## 题目大意

现在给定3个参数 — `start`, `end`, `bank`，分别代表起**始基因序列**，**目标基因序列**及**基因库**，请找出能够使起**始基因序列**变化为**目标基因序列**所需的最少变化次数。如果无法实现目标变化，请返回 -1。

## 解题思路

这道题直觉就是与图论有关，最少变化次数即最短路径，类似的题目还有 第 126 题、第 127 题。

### Solution 1: BFS

可以用较为经典的 BFS 来解决

````c++
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> words(bank.begin(), bank.end());
        words.insert(start);
      // 这里可以加一个剪枝
      /* if (words.find(end) != words.end()) {
      		return -1;
      }
      */
        queue<string>  que;
        que.push(start);
        
        int depth = 0;
        while (!que.empty()) {
            ++depth;
            const int len = que.size();
            for (int i = 0; i < len; ++i) {
                string cur = que.front();
                que.pop();
                vector<string> candidates = GetCandidates(cur);
                for (const string& candidate : candidates) {
                    if (words.find(candidate) != words.end()) {
                        if (candidate == end) {
                            return depth;
                        }
                        // 这里是避免循环访问
                        words.erase(candidate);
                        que.push(candidate);
                    }
                }
            }
        }
        return -1;
    }
 private:
    // 这个字符串经过变换后可以得到的字符串
    vector<string> GetCandidates(string& word) {
        const int len = word.size();
        vector<string> res;
        // 每一个位置都有 26 种可能，共 len 个位置
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < len; ++j) {
                char src = word[j];
                word[j] = 'A' + i;
                res.push_back(word);
                word[j] = src;
            }
        }
        return move(res);
    }
};
````

### Solution 2: 双向 BFS 

双向 BFS ，优先从小的集合开始 遍历，两个集合一旦出现交集，就停止遍历

````c++
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> words(bank.begin(), bank.end());
        if (words.find(end) == words.end())  {
            return -1;
        }
        unordered_set<string> st;
        st.insert(start);
        unordered_set<string> ed;
        ed.insert(end);
       
        return BFS(st, ed, words, 0);
    }
 
 private:
    vector<char> mode_ = {
        'A', 'C', 'G', 'T'
    };
    int BFS(unordered_set<string>& st, unordered_set<string>& ed,
            unordered_set<string> words, int depth) {
        if (st.empty()) {
            return -1;
        }
        if (st.size() > ed.size()) {
            // 从小的一端开始
            return BFS(ed, st, words, depth);
        }
        
        unordered_set<string> next;
        for (string start : st) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (start[j] == mode_[i]) {
                        continue;
                    }
                    char src = start[j];
                    start[j] = mode_[i];
                    
                    if (ed.find(start) != ed.end()) {
                        // 如果产生交集，直接返回
                        return depth + 1;
                    }
                    
                    if (words.find(start) != words.end()) {
                        // 如果可以继续做转化，
                        next.insert(start);
                    }
                    start[j] = src;
                }
            }
        }
        
        return BFS(next, ed, words, depth + 1);
    }
};
````









