 # [212. Word Search II](https://leetcode.com/problems/word-search-ii/)

## 题目

Given an `m x n` `board` of characters and a list of strings `words`, return *all words on the board*.

Each word must be constructed from letters of sequentially adjacent cells, where **adjacent cells** are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/07/search1.jpg)

```
Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/11/07/search2.jpg)

```
Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
```

 

**Constraints:**

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 12`
- `board[i][j]` is a lowercase English letter.
- `1 <= words.length <= 3 * 104`
- `1 <= words[i].length <= 10`
- `words[i]` consists of lowercase English letters.
- All the strings of `words` are unique.

## 题目大意

给定一个m x n 的字符网格和一个字符串列表，返回出现在网格中的所有单词，

每个单词必须按照单词中字母出现的顺序通过网格中相邻的字母进行构建，相邻的字母可以是水平的也可以是垂直的，网格中每个字幕在一个单词中最多只能用一次，

## 解题思路

* 这道题可以和第 79 题一起做，
* 这道题目可以直接使用 79 题的答案，对每一个字符串进行搜索，但是时间复杂度特别高，
* 可以利用前缀树来做（留待实现）

### 解法1（TLE）

直接使用 79 题的做法，

这种解法的不足在于每次查询每一个单词的时候，都需要遍历整个矩阵

````c++
// 暴力解法：超时
class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        rows = board.size();
        cols = board[0].size();
        
        vector<string> res;
        for (const string& str : words) {  // 搜索每一个单词
            if (Exist(str, board)) {
                res.push_back(str);
            }
        }
        
        return res;
    }
    
 private:
    int rows;
    int cols;
    
    // 方向数组
    vector<vector<int>> dirs = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0}
    };
    
    bool IsValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
    
    bool Exist(const string& word, const vector<vector<char>>& board) {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] != word[0]) {
                    continue;
                }
                
                // 从首字符开始
                if (Search(board, i, j, word, 0, visited)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    bool Search(const vector<vector<char>>& board, int x, int y,
                const string& word, int idx, vector<vector<bool>>& visited) {
        // 递归终止状态
        if (idx == word.size() - 1) {
            return board[x][y] == word[idx];
        }
        
        if (board[x][y] == word[idx]) {
            visited[x][y] = true;  // 标记已经能够访问过了
            // 向四个方向搜索
            for (const vector<int>& dir : dirs) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                
                if (IsValid(nx, ny) && !visited[nx][ny]
                   && Search(board, nx, ny, word, idx + 1, visited)) {
                    return true;
                }
            }
            // 回溯
            visited[x][y] = false;
        }
        
        return false;
    }
};
````

### 解法2（字典树）

这种做法及后面的集中优化都是参考这篇题解：https://leetcode-cn.com/problems/word-search-ii/solution/tong-ge-lai-shua-ti-la-yi-ti-si-jie-zi-d-2igi/

这样在就做到在搜索 board 时，判断字符串是否出现，不需要重复遍历 board

我们每遍历一个字符，判断其是否在前缀树当前层，如果在，就向上下左右扩散，同时，前缀树也向下移动一层

除了使用到**前缀树和DFS**外，我们需要求得所有的结果，所以，需要回溯遍历整个board，对于每一个遇到的字符，都要判断其是否在前缀树中，同时，不在前缀树中的字符，直接剪枝掉即可，



`````c++
class Solution {
 public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        unordered_set<string> res;  // 结果集
        string str = "";  // 记录遍历过的元素
        TrieNode *root = BuildTrie(words);  // 字典树
        
        rows = board.size();
        cols = board[0].size();
        
        // 记录是否访问过
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // 从每个元素开始遍历
                DFS(board, i, j, visited, root, res, str);
            }
        }
        return vector<string>(res.begin(), res.end());
    }
 private:
    struct TrieNode {
        bool end_;  // 标志这个节点是不是一个完整的单词
        vector<TrieNode*> dict_;  // 字典节点，因为只有小写字母，可以用 vector 代替 unordered_map
        
        
        TrieNode() : end_(false) {
            dict_.resize(26);
        }
        
        TrieNode(const TrieNode&) =delete;
        TrieNode& operator=(const TrieNode&) =delete;
        
        // 析构函数
        ~TrieNode() {
            for (TrieNode *it : dict_) {
                delete it;
            }
        }
    };
    
    // 建树
    TrieNode* BuildTrie(const vector<string>& words) {
        TrieNode *root = new TrieNode();
        for (const string& word : words) {
            TrieNode *cur = root;
            for (char c : word) {
                int idx = c - 'a';
                if (cur->dict_[idx] == nullptr) {
                    cur->dict_[idx] = new TrieNode();
                }
                cur = cur->dict_[idx];
            }
            cur->end_ = true;
        }
        // cout << "build" << endl;
        return root;
    }
    
    // 方向数组
    vector<vector<int>> dirs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    int rows;
    int cols;
    
    // 检查下标是否有效
    bool IsValid(int x, int y) {
        // cout << "valid" << endl;
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
    
    void DFS(const vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited,
            TrieNode *node, unordered_set<string>& res, string& str) {
        // 如果下标越界，已经访问过了，不存在于字典树中，直接返回
        if (!IsValid(x, y) || visited[x][y]
            || node->dict_[board[x][y] - 'a'] == nullptr) {
            return;
        }
        
        // cout << "dfs" << endl;
        // 记录当前字符
        str.push_back(board[x][y]);
        // 如果有结束字符，加入结果集中
        if (node->dict_[board[x][y] - 'a']->end_) {
            res.insert(str);
        }
        // 记录已经访问过了
        visited[x][y] = true;
        // 向四个方向遍历
        for (const vector<int>& dir : dirs) {
            DFS(board, x + dir[0], y + dir[1], visited, node->dict_[board[x][y] - 'a'], res, str);
        }
        
        //  撤销更改
        visited[x][y] = false;
        str.pop_back();
    }  
};
`````

### 解法3（增加删除操作）

当在board 中找到某个单词，可以把他从字典树中删除，后面再次遍历到，就可以直接返回，

````c++
class Solution {
 public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        unordered_set<string> res;  // 结果集
        string str = "";  // 记录遍历过的元素
        TrieNode *root = BuildTrie(words);  // 字典树
        
        rows = board.size();
        cols = board[0].size();
        
        // 记录是否访问过
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // 从每个元素开始遍历
                DFS(board, i, j, visited, root, root, res, str);
            }
        }
        return vector<string>(res.begin(), res.end());
    }
 private:
    struct TrieNode {
        bool end_;  // 标志这个节点是不是一个完整的单词
        vector<TrieNode*> dict_;  // 字典节点，因为只有小写字母，可以用 vector 代替 unordered_map
        
        
        TrieNode() : end_(false) {
            dict_.resize(26);
        }
        
        TrieNode(const TrieNode&) =delete;
        TrieNode& operator=(const TrieNode&) =delete;
        
        // 析构函数
        ~TrieNode() {
            for (TrieNode *it : dict_) {
                delete it;
            }
        }
    };
    
    // 建树
    TrieNode* BuildTrie(const vector<string>& words) {
        TrieNode *root = new TrieNode();
        for (const string& word : words) {
            TrieNode *cur = root;
            for (char c : word) {
                int idx = c - 'a';
                if (cur->dict_[idx] == nullptr) {
                    cur->dict_[idx] = new TrieNode();
                }
                cur = cur->dict_[idx];
            }
            cur->end_ = true;
        }
        // cout << "build" << endl;
        return root;
    }
    
    bool HasChildren(TrieNode *cur) {
        for (TrieNode *it : cur->dict_) {
            if (it != nullptr) {
                return true;
            }
        }
        return false;
    }
    
    // 返回 true 表示可以将沿途节点删掉，返回 false 表示不能删除沿途节点
    bool Delete(TrieNode *prev, const string& word, int i) {
        if (i == word.size() - 1) {
            // 如果后面还有单词则不能删除，
            TrieNode *cur = prev->dict_[word[i] - 'a'];
            if (HasChildren(cur)) {
                cur->end_ = false;
                return false;
            } else {
                delete prev->dict_[word[i] - 'a'];  // 这里需要手动释放资源
                prev->dict_[word[i] - 'a'] = nullptr;  // 防止空指针
                return true;
            }
        } else {
            // 如果后面的说可以删除，并且当前节点不是单词节点，并且没有其他子节点，那么删除，否则返回false
            if (Delete(prev->dict_[word[i] - 'a'], word, i + 1)
               && !prev->dict_[word[i] - 'a']->end_
               && !HasChildren(prev->dict_[word[i] - 'a'])) {
                prev->dict_[word[i] - 'a'] = nullptr;
                return true;
            }
            return false;
        }
    }
    
    void DeleteWordFromTrie(TrieNode *root, const string& word) {
        // 需要现找到最后一个元素，从下往上删除
        Delete(root, word, 0);
    }
    
    // 方向数组
    vector<vector<int>> dirs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    int rows;
    int cols;
    
    // 检查下标是否有效
    bool IsValid(int x, int y) {
        // cout << "valid" << endl;
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
    
    void DFS(const vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited,
           TrieNode *root, TrieNode *node, unordered_set<string>& res, string& str) {
        // 如果下标越界，已经访问过了，不存在于字典树中，直接返回
        if (!IsValid(x, y) || visited[x][y] || node == nullptr
            || node->dict_[board[x][y] - 'a'] == nullptr) {
            return;
        }
        
        // cout << "dfs" << endl;
        // 记录当前字符
        str.push_back(board[x][y]);
        // 如果有结束字符，加入结果集中
        if (node->dict_[board[x][y] - 'a']->end_) {
            res.insert(str);
            DeleteWordFromTrie(root, str);
        }
        // 记录已经访问过了
        visited[x][y] = true;
        // 向四个方向遍历
        for (const vector<int>& dir : dirs) {
            DFS(board, x + dir[0], y + dir[1], visited, root, node->dict_[board[x][y] - 'a'], res, str);
        }
        
        //  撤销更改
        visited[x][y] = false;
        str.pop_back();
    }  
};
````

