# [126. Word Ladder II](https://leetcode.com/problems/word-ladder-ii/)

A **transformation sequence** from word `beginWord` to word `endWord` using a dictionary `wordList` is a sequence of words `beginWord -> s1 -> s2 -> ... -> sk` such that:

- Every adjacent pair of words differs by a single letter.
- Every `si` for `1 <= i <= k` is in `wordList`. Note that `beginWord` does not need to be in `wordList`.
- `sk == endWord`

Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return *all the **shortest transformation sequences** from* `beginWord` *to* `endWord`*, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words* `[beginWord, s1, s2, ..., sk]`.

 

**Example 1:**

```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
Explanation: There are 2 shortest transformation sequences:
"hit" -> "hot" -> "dot" -> "dog" -> "cog"
"hit" -> "hot" -> "lot" -> "log" -> "cog"
```

**Example 2:**

```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
```

 

**Constraints:**

- `1 <= beginWord.length <= 5`
- `endWord.length == beginWord.length`
- `1 <= wordList.length <= 1000`
- `wordList[i].length == beginWord.length`
- `beginWord`, `endWord`, and `wordList[i]` consist of lowercase English letters.
- `beginWord != endWord`
- All the words in `wordList` are **unique**.

## 题目大意

给定两个单词 beginword 和 endword，使用一个单词列表完成由 beginword 到 endword 的转换，找出所有的最短转化序列，转化遵循以下条件:

* 相邻两个单词只有一个字母不同
* 转换过程中的中间单词必须是字典中的单词，beginword 不在单词列表中

## 解题思路

这道题是第 127 题的升级版，在这道题中，不仅要求出转化序列的长度，而且要求出转化序列，猜测可能需要用到 DFS

### Solution 1:

这里总体的思路就是 BFS 确定是否可以够转化，转化的最短路径，用 DFS 来求最短路径

`````c++
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // 将单词列表加入 set 中，方便查找
        unordered_set<string> word_set(wordList.begin(), wordList.end());
        // 如果最后无法到达 endWord，直接返回
        if (word_set.find(endWord) == word_set.end()) {
            return vector<vector<string>>();
        }
        // 从 beginWord开始，所以删除，避免发生循环
        word_set.erase(beginWord);
        
        // 记录当前单词是第几次扩展出来的，key:word, value: 层数
        unordered_map<string, int> steps;
        steps.emplace(beginWord, 0);
        // 每个单词可以由那些单词扩展出来
        unordered_map<string, unordered_set<string>> from;
        
        // 先 BFS 判断，
        bool found = BFS(beginWord, endWord, word_set, steps, from);
        
        vector<vector<string>> res;
        if (found) {
            deque<string> path;
            path.push_back(endWord);
            DFS(from, beginWord, endWord, path, res);
        }
        
        
        return res;
    }
    
 private:
    bool BFS(const string& beginWord, const string& endWord,
            unordered_set<string>& word_set,
            unordered_map<string, int>& steps,
            unordered_map<string, unordered_set<string>>& from) {
        queue<string> que;  // 队列
        que.push(beginWord);  // 起点入队
        
        bool found = false;  // 是否找到
        int step = 0;  // 路径长度
        while (!que.empty()) {
            ++step;
            // 每次遍历一层
            const int size = que.size();
            for (int i = 0; i < size; ++i) {
                // 这里先取出来，但是不删除
                string str = que.front();
                
                // 修改单词，状态转移
                int str_len = str.size();
                for (int j = 0; j < str_len; ++j) {
                    char origin = str[j];  // 保留之前的字符
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (str[j] == c) {  // 如果相同，直接跳过
                            continue;
                        }
                        str[j] = c;  // 修改字符
                        
                        // 如果是由
                        if (steps.find(str) != steps.end() && steps.at(str) == step) {
                            from[str].insert(que.front());
                        }
                        
                        // 如果不能转化
                        if (word_set.find(str) == word_set.end()) {
                            continue;
                        }
                        // 删除这个已经出过的单词
                        word_set.erase(str);
                        
                        que.push(str);  // 入队
                        
                        from[str].insert(que.front());
                        steps.emplace(str, step);
                        
                        // 如果找到，不能直接发挥，因为结果肯呢个不止一种，
                        if (str == endWord) {
                            found = true;
                        }
                    }
                    str[j] = origin;  // 回复
                }
                que.pop();  // 在此处弹出
                
            }
            // 遍历完当前层，如果找到了，就直接返回
            if (found) {  // 如果找到，跳出循环
                break;
            }
        }
        
        return found;
    }
    
    
    void DFS(const unordered_map<string, unordered_set<string>>& from,
            const string& beginWord, const string& cur, deque<string>& que,
            vector<vector<string>>& res) {
        // 如果到达起点，直接返回
        if (cur == beginWord) {
            res.push_back(vector<string>(que.begin(), que.end()));
            return;
        }
        
        for (const string& str : from.at(cur)) {
            que.push_front(str);  // 从前面加入
            DFS(from, beginWord, str, que, res);
            que.pop_front();  // 回溯
        }
    }
};
`````

