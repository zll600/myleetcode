# [127. Word Ladder](https://leetcode.com/problems/word-ladder/)

## 题目

A **transformation sequence** from word `beginWord` to word `endWord` using a dictionary `wordList` is a sequence of words `beginWord -> s1 -> s2 -> ... -> sk` such that:

- Every adjacent pair of words differs by a single letter.
- Every `si` for `1 <= i <= k` is in `wordList`. Note that `beginWord` does not need to be in `wordList`.
- `sk == endWord`

Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return *the **number of words** in the **shortest transformation sequence** from* `beginWord` *to* `endWord`*, or* `0` *if no such sequence exists.*

 

**Example 1:**

```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
```

**Example 2:**

```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
```

 

**Constraints:**

- `1 <= beginWord.length <= 10`
- `endWord.length == beginWord.length`
- `1 <= wordList.length <= 5000`
- `wordList[i].length == beginWord.length`
- `beginWord`, `endWord`, and `wordList[i]` consist of lowercase English letters.
- `beginWord != endWord`
- All the words in `wordList` are **unique**.

## 题目大意

* 给定两个单词，一个 beginword 和一个 endword，和一个单词列表，找到从 beginword 到 endword 的最短转化序列，
* 相邻的两个单词只有一个字母不相同，也就意味着，每次只能改变一个字母，
* 转换过程中的单词都在 单词列表中，

## 解题思路

这是一条求最短路径的题目，可以利用图论的BFS来解决，这里放上一篇题解

 https://leetcode-cn.com/problems/word-ladder/solution/yan-du-you-xian-bian-li-shuang-xiang-yan-du-you-2/



### Solution 1: 单向 BFS

这里需要注意的就是特殊的状态转移

````c++
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 将 wordList 中的单词加入 set 中方便查找
        unordered_set<string> word_set(wordList.begin(), wordList.end());
        if (word_set.find(endWord) == word_set.end()) {  // 剪枝：如果word_set 中不含 endWord，直接返回0
            return 0;
        }
        // 下面这句注释掉之后也可以过
        // word_set.erase(beginWord);  // 从 word_set 中删除 beginWord
        
        queue<string> que;  // 队列
        que.push(beginWord);
        unordered_set<string> visited;  // 已访问过的集合
        visited.insert(beginWord);
        
        int step = 1;  // 初始时记一次转化
        while (!que.empty()) {
            const int size = que.size();  // 每次遍历一层
            for (int i = 0; i < size; ++i) {
                string str = que.front();
                que.pop();
                
                // 如果 str 转化后可以与 endWord 相等，直接返回
                if (WordCanTransfor(str, endWord, que, visited, word_set)) {
                    return step + 1;
                }
            }
            ++step;  //  递增步数
        }
        
        return 0;
    }
    
 private:
    bool WordCanTransfor(string& str, const string& endWord,
                        queue<string>& que, unordered_set<string>& visited,
                        const unordered_set<string>& word_set) {
        // 修改str 中的每一个字符，判断能否转化到 endWord
        const int size = str.size();
        for (int i = 0; i < size; ++i) {
            char origin = str[i];  // 保留原来字符
            for (char k = 'a'; k <= 'z'; ++k) {
                if (k == origin) {
                    continue;
                }
                str[i] = k;
                
                // 如果可以转化
                if (word_set.find(str) != word_set.end()) {
                    // 判断是否相等
                    if (str == endWord) {
                        return true;
                    }
                    
                    // 如果不相等，且没有访问过
                    if (visited.find(str) == visited.end()) {
                        que.push(str);  // 加入队列中
                        visited.insert(str);  // 记录已访问，否则可能会多次入队
                    }
                }
            }
            str[i] = origin;  // 恢复
        }
        
        return false;
    }
};
````

### Solution 2:双向 BFS

从起点和终点同时开始，每次选择一个较小的集合开始扩散，直到状态转移之后，出现在另一个集合中，此时可以说明已经找到答案，

`````c++
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 将wordList 加入set 中加速查找
        unordered_set<string> word_set(wordList.begin(), wordList.end());
        // 如果 word_set中没有 endWord 直接返回
        if (word_set.find(endWord) == word_set.end()) {
            return 0;
        }
        
        // 所有访问过的字符串
        unordered_set<string> visited;
        // 分别用从左边和从右边扩展的哈希来代替原来的单向 BFS 队列，他们在双向 bfs 中交替使用
        unordered_set<string> begin_visited;
        begin_visited.insert(beginWord);
        unordered_set<string> end_visited;
        end_visited.insert(endWord);
        
        // 双向 BFS，
        int step = 1;  // 转化的步骤数
        while (!begin_visited.empty() && !end_visited.empty()) {
            // 优先选择小的哈希表进行扩散
            if (begin_visited.size() > end_visited.size()) {
                swap(begin_visited, end_visited);
            }
            
            // 保存下一轮需要遍历的单词
            unordered_set<string> next_level_visited;
            
            for (const string& word : begin_visited) {
                if (WordCanTransfor(word, end_visited, visited, word_set, next_level_visited)) {
                    return step + 1;
                }
            }
            // 遍历完成后交换
            begin_visited.swap(next_level_visited);
            
            ++step;
        }
        
        return 0;
    }
    
 private:
    bool WordCanTransfor(string str, unordered_set<string>& end_visited,
                        unordered_set<string>& visited, unordered_set<string>& word_set,
                        unordered_set<string>& next_level_visited) {
        const int size = str.size();
        for (int i = 0; i < size; ++i) {
            char origin = str[i];
            for (char k = 'a'; k <= 'z'; ++k) {
                str[i] = k;
                // 如果可以发生状态转移
                if (word_set.find(str) != word_set.end()) {
                    // 下一个状态在另一侧的集合中，直接返回
                    if (end_visited.find(str) != end_visited.end()) {
                        return true;
                    }
                    
                    // 这个状态如果没有访问过，增加到队列中
                    if (visited.find(str) == visited.end()) {
                        next_level_visited.insert(str);
                        visited.insert(str);  // 直接增加
                    }
                }
            }
            str[i] = origin;  // 恢复
        }
        
        return false;
    }
};
`````

