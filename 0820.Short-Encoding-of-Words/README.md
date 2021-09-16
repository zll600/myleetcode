# [820. Short Encoding of Words](https://leetcode.com/problems/short-encoding-of-words/)



A **valid encoding** of an array of `words` is any reference string `s` and array of indices `indices` such that:

- `words.length == indices.length`
- The reference string `s` ends with the `'#'` character.
- For each index `indices[i]`, the **substring** of `s` starting from `indices[i]` and up to (but not including) the next `'#'` character is equal to `words[i]`.

Given an array of `words`, return *the **length of the shortest reference string*** `s` *possible of any **valid encoding** of* `words`*.*

 

**Example 1:**

```
Input: words = ["time", "me", "bell"]
Output: 10
Explanation: A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
words[0] = "time", the substring of s starting from indices[0] = 0 to the next '#' is underlined in "time#bell#"
words[1] = "me", the substring of s starting from indices[1] = 2 to the next '#' is underlined in "time#bell#"
words[2] = "bell", the substring of s starting from indices[2] = 5 to the next '#' is underlined in "time#bell#"
```

**Example 2:**

```
Input: words = ["t"]
Output: 2
Explanation: A valid encoding would be s = "t#" and indices = [0].
```

 

**Constraints:**

- `1 <= words.length <= 2000`
- `1 <= words[i].length <= 7`
- `words[i]` consists of only lowercase letters.

## 题目大意

单词数组 words 的有效编码，由任意的字符串 s 和下标数组组成：

* word.length == indices.length
* 记字符串 s 以 '#' 字符结尾
* 对于每个下标 indices[i] ，s 的一个从 indices[i] 开始、到下一个 '#' 字符结束（但不包括 '#'）的 子字符串 恰好与 words[i] 相等

给定一个字符串数组，返回可以使words 有效编码的最短字符串 s，

## 解题思路

* 这道题目其实也是一道字符串匹配的题目，不过匹配的是后缀，可以参考这篇题解：https://leetcode-cn.com/problems/short-encoding-of-words/solution/99-java-trie-tu-xie-gong-lue-bao-jiao-bao-hui-by-s/

## 代码

``````c++
class Solution {
public:
    
    static bool comp(const string& a, const string& b) {
        return a.size() > b.size();
    }
    int minimumLengthEncoding(vector<string>& words) {
        Tries trie;
        // 我们必须先插入较长的单词，才能避免重复累加长度
        sort(words.begin(), words.end(), comp);
        
        int res = 0;
        for (const string& str : words) {
            res += trie.Insert(str);
        }
        return res;
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
    
    class Tries {
     public:
        Tries() {
            root = new TrieNode();
        }
        
        int Insert(const string& word) {
            if (word.empty()) {
                return 0;
            }
            TrieNode *node = root;
            ++node->path_;
            bool new_word = false;
            // 这里将每个单词倒着插入，目的是为了进行后缀匹配
            for (int i = word.size() - 1; i >= 0; --i) {
                int idx = word[i] - 'a';
                
                if (node->dict_[idx] == nullptr) {
                    new_word = true;
                    node->dict_[idx] = new TrieNode();
                }
                node = node->dict_[idx];
                ++node->path_;
            }
            ++node->end_;
            // 如果是新单词，还需要多插入一个‘#’字符，
            return new_word ? word.size() + 1 : 0;
        }
        
     private:
        TrieNode *root;
    };
    
};
``````

