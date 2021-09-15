# [677. Map Sum Pairs](https://leetcode.com/problems/map-sum-pairs/)

## 题目

Design a map that allows you to do the following:

- Maps a string key to a given value.
- Returns the sum of the values that have a key with a prefix equal to a given string.

Implement the `MapSum` class:

- `MapSum()` Initializes the `MapSum` object.
- `void insert(String key, int val)` Inserts the `key-val` pair into the map. If the `key` already existed, the original `key-value` pair will be overridden to the new one.
- `int sum(string prefix)` Returns the sum of all the pairs' value whose `key` starts with the `prefix`.

 

**Example 1:**

```
Input
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
Output
[null, null, 3, null, 5]

Explanation
MapSum mapSum = new MapSum();
mapSum.insert("apple", 3);  
mapSum.sum("ap");           // return 3 (apple = 3)
mapSum.insert("app", 2);    
mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)
```

 

**Constraints:**

- `1 <= key.length, prefix.length <= 50`
- `key` and `prefix` consist of only lowercase English letters.
- `1 <= val <= 1000`
- At most `50` calls will be made to `insert` and `sum`.

## 题目大意

设计一个数据结构实现下列功能：

* 映射一个字符串键到给定值
* 返回所有匹配给定前缀的键的值之和

## 解题思路

这道题目主要难点在于对匹配prefix 的字符串都需要计算

## 代码

`````c++
class MapSum {
public:
    /** Initialize your data structure here. */
    MapSum() {
        
        root = new TrieNode;
    }
    
    void insert(string key, int val) {
        if (key.empty()) {
            return;
        }

        TrieNode *node = root;
        for (int i = 0; i < key.size(); ++i) {
            int idx = key[i] - 'a';

            if (node->dict_[idx] == nullptr) {
                node->dict_[idx] = new TrieNode();
            }
            node = node->dict_[idx];
            ++node->path_;
        }
        ++node->end_;
        node->val_ = val;
    }
    
    int sum(string prefix) {
        if (prefix.empty()) {
            return 0;
        }

        TrieNode *node = root;

        for (int i = 0; i < prefix.size(); ++i) {
            int idx = prefix[i] - 'a';
            if (node->dict_[idx] == nullptr) {
                return 0;
            }
            node = node->dict_[idx];
        }

        return Calc(node);
    }

 private:
    struct TrieNode {
        int path_;	// 保存有多少字符串使用该字母
        int end_;	// 保存有多少字符串以当前字母结尾
        int val_;	// 保存值，用于 sum 作计算
        vector<TrieNode*> dict_;

        TrieNode()
            : path_(0),
            end_(0),
            val_(0) {
            dict_.resize(26);
        }
    };

    TrieNode *root;

    int Calc(TrieNode *node) {
        if (node == nullptr) {
            return 0;
        }

        int res = node->val_;
        for (TrieNode *it : node->dict_) {
            res += Calc(it);
        }

        return res;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
`````

