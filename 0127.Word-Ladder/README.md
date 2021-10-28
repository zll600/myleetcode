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

### 双向 BFS

