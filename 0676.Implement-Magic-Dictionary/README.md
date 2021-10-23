# [676. Implement Magic Dictionary](https://leetcode.com/problems/implement-magic-dictionary/)

## 题目 

Design a data structure that is initialized with a list of **different** words. Provided a string, you should determine if you can change exactly one character in this string to match any word in the data structure.

Implement the `MagicDictionary` class:

- `MagicDictionary()` Initializes the object.
- `void buildDict(String[] dictionary)` Sets the data structure with an array of distinct strings `dictionary`.
- `bool search(String searchWord)` Returns `true` if you can change **exactly one character** in `searchWord` to match any string in the data structure, otherwise returns `false`.

 

**Example 1:**

```
Input
["MagicDictionary", "buildDict", "search", "search", "search", "search"]
[[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
Output
[null, null, false, true, false, false]

Explanation
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // return False
magicDictionary.search("hhllo"); // We can change the second 'h' to 'e' to match "hello" so we return True
magicDictionary.search("hell"); // return False
magicDictionary.search("leetcoded"); // return False
```

 

**Constraints:**

- `1 <= dictionary.length <= 100`
- `1 <= dictionary[i].length <= 100`
- `dictionary[i]` consists of only lower-case English letters.
- All the strings in `dictionary` are **distinct**.
- `1 <= searchWord.length <= 100`
- `searchWord` consists of only lower-case English letters.
- `buildDict` will be called only once before `search`.
- At most `100` calls will be made to `search`.

##  题目大意

实现一个用单词列表初始化的魔法字典，给定一个字符串，改变字符串中的任意一个字母，使其匹配字典中的任意一个字符串，

实现一个字典类：

* `MagicDictionary()` 初始化对象
* `void buildDict(String[] dictionary)` 使用字符串数组 `dictionary` 设定该数据结构，`dictionary` 中的字符串互不相同
* `bool search(String searchWord)` 给定一个字符串 `searchWord` ，判定能否只将字符串中 一个 字母换成另一个字母，使得所形成的新字符串能够与字典中的任一字符串匹配。如果可以，返回 `true` ；否则，返回 `false`

## 解题思路

### Solution 1

这种解法，可以参考霜神的解法：https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0676.Implement-Magic-Dictionary/

不过我认为，这种解法不必使用 set 或者 map，因为是顺序遍历，且题目要求字典中字符串没有重复，所有上面两种数据结构的优势没有用到 

```c++
class MagicDictionary {
public:
    MagicDictionary() {
        
    }
    
    void buildDict(vector<string> dictionary) {
        words_.swap(dictionary);
    }
    
    bool search(string searchWord) {
        const int len = searchWord.size();
        for (const string& word : words_) {
            // 逐个字符比较之前，先比较长度，如果长度不相等，直接下一个
            if (searchWord.size() == word.size()) {
                int n = 0;  // 不一样字符的数量
                for (int i = 0; i < len; ++i) {
                    if (word[i] != searchWord[i]) {
                        ++n;
                    }
                }
                if (n == 1) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
 private:
    vector<string> words_;
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
```

## Solution 2: 

这种解法可以参考这篇题解：

这里采用预处理的方式，提前将所有可能变化的字符串存储到map 中，map 的 value 存储原型字符串，因为题目要求**必须精确的改变一个字符串，既不能改变多余一个，也不能不改变**

```c++
class MagicDictionary {
public:
    MagicDictionary() {
    }
    
    void buildDict(vector<string> dictionary) {
        for (const string& word : dictionary) {
            string str = word;
            const int len = word.size();
            for (int i = 0; i < len; ++i) {
               char c = str[i];
               str[i] = '_';
                // 这个字符串可以由多少中字符串变化而来
               dict_[str].emplace_back(word);
               str[i] = c;
            }
        }
    }
    
    bool search(string searchWord) {
        const int len = searchWord.size();
        const string str = searchWord;
        for (int i = 0; i < len; ++i) {
            char c = searchWord[i];
            searchWord[i] = '_';
            
            // 匹配到相同的字符串，并且需要满足
            // 匹配的字符串有多种原型字符串
            // 或者匹配的到字符串只有一种字符串，且该原型字符串不等于 searchWord
            if (dict_.find(searchWord) != dict_.end()
               && (dict_[searchWord].size() > 1 || dict_[searchWord].front() != str)) {
               return true;
            }

            searchWord[i] = c;
        }
        return false;
    }
    
 private:
    unordered_map<string, vector<string>> dict_;
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
```

## Solution 3:

这道题目也可以利用前缀树的思路来做，将字典中的字符串全部插入到字典树中，查找时，需要做标记与记录，保证满足有且只有一次更改

````c++
// 前缀树节点
struct TrieNode {
    bool end;  // 是否是一个单词的结尾
    vector<TrieNode*> children;  // 子节点

    // 构造函数
    TrieNode() : end(false) {
        children.resize(26);
    }
    // 析构函数
    ~TrieNode() {
      end = false;
      for (auto it : children) {
         delete it;
         it = nullptr;
      }
   }
};

class Trie {
 public:
    Trie() : root_(new TrieNode()) {}
    
    // 插入字符串
    void Insert(const string& word) {
        TrieNode *node = root_;
        for (char c : word) {
            // 如果对应的位置为空，则新建一个节点
            if (!node->children[c - 'a']) {
                node->children[c - 'a'] = new TrieNode();
            }
            node = node->children[c - 'a'];
        }
        node->end = true;  // 设置终止标志
    }
    
    // 搜索字符串
    bool Search(const string& word) {
        return DFS(root_, word, 0, 0);
    }

 private:
    TrieNode *root_;
    
    static bool DFS(TrieNode *node, const string& word, int idx, int cnt) {
        // 如果更改的字母数已经大于 1或者当前节点为空，则直接返回
        if (cnt > 1 || !node) {
            return false;
        }
        // 如果匹配到结束
        // 返回是否是一个单词的结尾，并且修改的次数为 1
        if (idx == word.size()) {
            return node->end && cnt;
        }
        // 设置标志位
        bool flag = false;
        // 本次递归搜索的字符
        char c = word[idx];
        for (int i = 0; i < 26; ++i) {
            // 不需要修改字母
            if (c - 'a' == i) {
                flag |= DFS(node->children[i], word, idx + 1, cnt);
            } else {
                // 需要修改字母
                flag |= DFS(node->children[i], word, idx + 1, cnt + 1);
            }
        }
        
        return flag;
    }
};


class MagicDictionary {
public:
    MagicDictionary() {
    }
    
    void buildDict(vector<string> dictionary) {
        for (const string& word : dictionary) {
            trie_.Insert(word);
        }
    }
    
    bool search(string searchWord) {
        return trie_.Search(searchWord);
    }
    
 private:
    Trie trie_;
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
````

