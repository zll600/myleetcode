# [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)

## 题目

A [**trie**](https://en.wikipedia.org/wiki/Trie) (pronounced as "try") or **prefix tree** is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

- `Trie()` Initializes the trie object.
- `void insert(String word)` Inserts the string `word` into the trie.
- `boolean search(String word)` Returns `true` if the string `word` is in the trie (i.e., was inserted before), and `false` otherwise.
- `boolean startsWith(String prefix)` Returns `true` if there is a previously inserted string `word` that has the prefix `prefix`, and `false` otherwise.

 

**Example 1:**

```
Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True
```

 

**Constraints:**

- `1 <= word.length, prefix.length <= 2000`
- `word` and `prefix` consist only of lowercase English letters.
- At most `3 * 104` calls **in total** will be made to `insert`, `search`, and `startsWith`.

## 题目大意

实现一个Trie（前缀树）包含insert, search, startsWith操作

## 解题思路

* 这题就是经典的 Trie 实现，这道题可以作为 Trie 的模板题

## 代码

````c++
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        if (word.empty()) {
           return;
        }
        
        TrieNode *node = root;
        for (int i = 0; i < word.size(); ++i) {
            int idx = word[i] - 'a';
            
            if (node->dict[idx] == nullptr) {
                node->dict[idx] = new  TrieNode();
            }
            node = node->dict[idx];
            ++node->path_;
        }
        ++node->end_;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        if (word.empty()) {
            return false;
        }
        
        TrieNode *node = root;
        for (int i = 0; i < word.size(); ++i) {
            int idx = word[i] - 'a';
            
            if (node->dict[idx] == nullptr) {
                return false;
            }
            node = node->dict[idx];
        }
        return node->end_ != 0;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        if (prefix.empty()) {
            return false;
        }
        
        TrieNode *node = root;
        for (int i = 0; i < prefix.size(); ++i) {
            int idx = prefix[i] - 'a';
            
            if (node->dict[idx] == nullptr) {
                return false;
            }
            node = node->dict[idx];
        }
        
        return node->path_;
    }
    
 private:
    struct TrieNode {        
        TrieNode()
            : path_(0),
            end_(0) {
            dict.resize(26);        
        }
    
        int path_;
        int end_;
        vector<TrieNode*> dict;
    };
    
    TrieNode *root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
````

