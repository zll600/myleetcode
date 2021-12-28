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

