# [211. Design Add and Search Words Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/)

## 题目

Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the `WordDictionary` class:

- `WordDictionary()` Initializes the object.
- `void addWord(word)` Adds `word` to the data structure, it can be matched later.
- `bool search(word)` Returns `true` if there is any string in the data structure that matches `word` or `false` otherwise. `word` may contain dots `'.'` where dots can be matched with any letter.

 

**Example:**

```
Input
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output
[null,null,null,null,false,true,true,true]

Explanation
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True
```

 

**Constraints:**

- `1 <= word.length <= 500`
- `word` in `addWord` consists lower-case English letters.
- `word` in `search` consist of `'.'` or lower-case English letters.
- At most `50000` calls will be made to `addWord` and `search`.

## 题目大意

设计一个数据结构，支持添加新的字符串和匹配先前加入的字符串，

实现字典类：

* WordDictionary() 初始化词典对象
* void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
* bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true ；否则，返回  false 。word 中可能包含一些 '.' ，每个 . 都可以表示任何一个字母

## 解题思路

* 这是一道前缀树的题目，这道题目在 208 题的基础上要求实现 addWrod(word)和search(word)功能，增加了模糊查找的实现，

## 代码

````c++
class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        if (word.empty()) {
            return;
        }

        TrieNode *node = root;
        for (int i = 0; i < word.size(); ++i) {
            int idx = word[i] - 'a';
            if (node->dict_[idx] == nullptr) {
                node->dict_[idx] = new TrieNode();
            }
            node = node->dict_[idx];
            ++node->path_;
        }
        ++node->end_;
    }
    
    bool search(string word) {
        if (word.empty()) {
            return false;
        }

        return Match(word, root, 0);
    }
    
 private:
    struct TrieNode {
        int path_;
        int end_;
        vector<TrieNode*> dict_;

        TrieNode()
            : path_(0),
            end_(0) {
            dict_.resize(26);
        }
    };

    TrieNode *root;
    
    bool Match(const string& word, TrieNode *node, int start) {
        if (start == word.size()) {
            return node->end_;
        }
        
        if (word[start] == '.') {
            for (TrieNode* tmp : node->dict_) {
                if (tmp != nullptr && Match(word, tmp, start + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            int idx = word[start] - 'a';
            
            if (node->dict_[idx] == nullptr) {
                return false;
            }
            
            return Match(word, node->dict_[idx], start + 1);
        }
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
````

