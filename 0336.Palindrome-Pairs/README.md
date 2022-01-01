# [336. Palindrome Pairs](https://leetcode-cn.com/problems/palindrome-pairs/)

## 题目

Given a list of **unique** words, return all the pairs of the ***distinct\*** indices `(i, j)` in the given list, so that the concatenation of the two words `words[i] + words[j]` is a palindrome.

 

**Example 1:**

```
Input: words = ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]]
Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
```

**Example 2:**

```
Input: words = ["bat","tab","cat"]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["battab","tabbat"]
```

**Example 3:**

```
Input: words = ["a",""]
Output: [[0,1],[1,0]]
```

 

**Constraints:**

- `1 <= words.length <= 5000`
- `0 <= words[i].length <= 300`
- `words[i]` consists of lower-case English letters.

## 题目大意

给定一组 **互不相同** 的单词， 找出所有 **不同** 的索引对 `(i, j)`，使得列表中的两个单词， `words[i] + words[j]` ，可拼接成回文串。

## 解题思路

这里有两个问题要解决：

* 判断一个字符串是否是回文的
* 如何拼接两个字符串

### Solution 1: Bruce Force

这种解法枚举所有可能的组合，然后判断每一个是否合理，这个很容易想到这是会超时的

````c++
class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        const int len = words.size();
        vector<vector<int>> res;
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                // cout << i << " --- " << j << endl;
                if (!IsPalindrome(words[i] + words[j])) {
                    continue;
                }
                res.push_back(vector<int>{i, j});
            }
        }
        return res;
    }
    
 private:
    bool IsPalindrome(const string& word) {
        int i = 0;
        int j = word.size() - 1;
        while (i < j) {
            if (word[i] != word[j]) {
                return false;
            }
            ++i;
            --j;
        }
        return true;
    }
};
````

### Solution 2: Tries

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/palindrome-pairs/solution/java-trie-yi-yu-li-jie-by-copyreadmachine/

这里利用前缀树来做匹配，这里其实也是空间换时间的思想，这里关键要理解的是前缀树是其实也是可以灵活多变的，根据不同的用途，设计成为不同的结构，可以解决不同的问题

````c++
// 前缀树节点
struct Node {
    vector<Node*> children = vector<Node*>(26); // 下一层的孩子节点
    vector<int> words; // 以当前节点结尾的单词，
    vector<int> suffixs; // 这里是字符串前面是回文，用于对words 中的作补充
    
    Node() {}
};


class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        Node *root = new Node();
        const int len = words.size();
        // 将所有的单词逆序插入到前缀树中
        for (int i = 0; i < len; ++i) {
            reverse(words[i].begin(), words[i].end()); // 反转所有单词
            Node *cur = root;
            const int size = words[i].size();
            for (int j = 0; j < size; ++j) {
                char c = words[i][j];
                if (cur->children[c - 'a'] == nullptr) {
                    cur->children[c - 'a'] = new Node();
                }
                cur = cur->children[c - 'a'];
                
                if (IsPalindrome(words[i].substr(j + 1))) {
                    // 这里是逆序插入，
                    // 所以实际上是该节点之前的部分可以i构成回文串
                    cur->suffixs.push_back(i);
                }
            }
            cur->words.push_back(i);
        }
        
        vector<vector<int>> res;
        for (int i = 0; i < len; ++i) {
            // 先将所有的字符串恢复
            reverse(words[i].begin(), words[i].end());
            Node *cur = root;
            int j = 0;
            const int size = words[i].size();
            while (j < size) {
                if (IsPalindrome(words[i].substr(j))) {
                    // 如果 j 位置之后的字符串本身就是一个回文字符串
                    for (int k : cur->words) {
                        if (k != i) {
                            res.push_back(vector<int>{i, k});
                        }
                    }
                }
                
                char c = words[i][j];
                if (cur->children[c - 'a'] == nullptr) {
                    break;
                }
                cur = cur->children[c - 'a'];
                ++j;
            }
            
            if (j == size) {
                for (int k : cur->suffixs) {
                    if (k != i) {
                        res.push_back(vector<int>{i, k});
                    }
                }
            }
        }
        
        return res;
    }
    
 private:
    bool IsPalindrome(const string& word) {
        int i = 0;
        int j = word.size() - 1;
        while (i < j) {
            if (word[i] != word[j]) {
                return false;
            }
            ++i;
            --j;
        }
        return true;
    }
};
````

### Solution 3:

上面的方法最终还是会超时，字典树起到的作用就是加速字符串的比较，

如果字符串 word1 + word2 能构成一个回文串，把 word1 分成 **前半段** 和 **后半段** 两部分，可以有以下以下两种拼接情况：

1. word2 拼接在前，并且 **前半段** 是回文串、**后半段** 是 word2 的逆序；
2. word2 拼接在后，并且 **后半段** 是回文串、**前半段** 是 word2 的逆序；

不过依旧超时，暂时放弃了

```c++
class TrieNode {
 public:
    TrieNode() : is_end_(false), index_(-1), children_(vector<TrieNode*>(26, nullptr)) {
    }
    ~TrieNode() {
        for (TrieNode* child : children_) {
            if (child != nullptr) {
                delete child;
                child = nullptr;
            }
        }
    }
    
    int Index() {
        return index_;
    }
    void SetIndex(int idx) {
        index_ = idx;
    }
    bool IsEnd() {
        return is_end_;
    }
    void SetIsEnd() {
        is_end_ = true;
    }
    
    // 插入单个字符
    TrieNode* InsertTrieNode(char c) {
        if (!isalpha(c)) {
            return nullptr;
        }
        int idx= c - 'a';
        if (children_[idx] == nullptr) {
            children_[idx] = new TrieNode();
        }
        return children_[idx];
    }
    
    // 查找单个字符
    TrieNode* GetTrieNode(char c) {
        if (!isalpha(c)) {
            return nullptr;
        }
        int idx = c - 'a';
        return children_[idx];
    }

 private:
    bool is_end_; // 单词结束标记
    int index_; // 单词序号
    vector<TrieNode*> children_; // 子节点
};

class Trie {
 public:
    Trie() : root_(new TrieNode()) {}
    ~Trie() { delete root_; }
    
    // 插入一个单词
    void Insert(const string& word, int idx) {
        TrieNode *cur = root_;
        for (char c : word) {
            cur = cur->InsertTrieNode(c);
        }
        cur->SetIndex(idx);
        cur->SetIsEnd();
    }
    
    // 查找一个单词
    TrieNode* GetNode(const string& word) {
        TrieNode *cur = root_;
        for (char c : word) {
            cur = cur->GetTrieNode(c);
            if (cur == nullptr) {
                return nullptr;
            }
        }
        return cur;
    }
    
    // 查找单词并设置下标
    bool Search(const string& word, int& idx) {
        TrieNode *cur = GetNode(word);
        if (cur != nullptr) {
            idx = cur->Index();
            return cur->IsEnd();
        }
        return false;
    }

 private:
    TrieNode *root_;
};

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> res; // 结果集
        Trie *trie = new Trie();
        
        const int len = words.size();
        // 将所有单词插入字典树中
        for (int i = 0; i < len; ++i) {
            trie->Insert(words[i], i);
        }
        
        for (int i = 0; i < len; ++i) {
            const int length = words[i].size();
            // cout << words[i] << "----";
            for (int j = 0; j < length; ++j) {
                if (IsPalindrome(words[i], 0, j)) {
                    // 如果前半段[0, j]是回文，
                    // 则如果后半段[j.+ 1, length - 1]的逆序存在于字典树中，就可以组成回文对，或者后半段为空，
                    string tmp = move(words[i].substr(j + 1));
                    // cout << tmp << "----";
                    reverse(tmp.begin(), tmp.end());
                    int index = -1;
                    if (trie->Search(tmp, index)) {
                        if (i != index) {
                            // 如果后半段的逆序存在于字典树中
                            res.push_back(vector<int>{index, i});
                            if (tmp == "") {
                                res.push_back(vector<int>{i, index});
                            }
                        }
                    }
                }
                if (IsPalindrome(words[i], j + 1, length - 1)) {
                    // 如果后半段[j + 1, length - 1]是回文
                    string tmp = move(words[i].substr(0, j + 1));
                    // cout << tmp << "---";
                    reverse(tmp.begin(), tmp.end());
                    int index = -1;
                    if (trie->Search(tmp, index)) {
                        // 如果存在前半段[0, j]的逆序，就可以组成回文对
                        if (i != index) {
                            res.push_back(vector<int>{i, index});
                        }
                    }
                }
            }
            // cout << endl;
        }
        
        return res;
    }
    
 private:
    bool IsPalindrome(const string& word, int left, int right) {
        while (left <= right) {
            if (word[left] != word[right]) {
                return false;
            }
            ++left;
            --right;
        }
        
        return true;
    }
};
```

