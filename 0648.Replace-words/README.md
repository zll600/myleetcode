# [648. Replace Words](https://leetcode.com/problems/replace-words/) 

In English, we have a concept called **root**, which can be followed by some other word to form another longer word - let's call this word **successor**. For example, when the **root** `"an"` is followed by the **successor** word `"other"`, we can form a new word `"another"`.

Given a `dictionary` consisting of many **roots** and a `sentence` consisting of words separated by spaces, replace all the **successors** in the sentence with the **root** forming it. If a **successor** can be replaced by more than one **root**, replace it with the **root** that has **the shortest length**.

Return *the `sentence`* after the replacement.

 

**Example 1:**

```
Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
```

**Example 2:**

```
Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
Output: "a a b c"
```

**Example 3:**

```
Input: dictionary = ["a", "aa", "aaa", "aaaa"], sentence = "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa"
Output: "a a a a a a a a bbb baba a"
```

**Example 4:**

```
Input: dictionary = ["catt","cat","bat","rat"], sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
```

**Example 5:**

```
Input: dictionary = ["ac","ab"], sentence = "it is abnormal that this solution is accepted"
Output: "it is ab that this solution is ac"
```

 

**Constraints:**

- `1 <= dictionary.length <= 1000`
- `1 <= dictionary[i].length <= 100`
- `dictionary[i]` consists of only lower-case letters.
- `1 <= sentence.length <= 10^6`
- `sentence` consists of only lower-case letters and spaces.
- The number of words in `sentence` is in the range `[1, 1000]`
- The length of each word in `sentence` is in the range `[1, 1000]`
- Each two consecutive words in `sentence` will be separated by exactly one space.
- `sentence` does not have leading or trailing spaces.

## 题目大意

在英语中，我们有一个概念叫做root（词根），它可以和一些词组组成其他词，我们称作继承词（successor），例如词根“an”，后面跟随“other”，可以形成新词“another”，

现在给定一个由词根组成的字典，和一个由空格分开的单词组成的句子，将句子中的单词的继承词用词根替换掉，如果一个继承词可以被多个词根替换，选取最短的那一个，返回替换后的句子

## 解题思路

* 这道题目可以用 Tries 的思想来解决，在匹配句子中的继承词时，可以将词根列表保存到Tries 中，只需要在匹配的时候，匹配到第一个就直接退出返回即可

## 代码

`````c++
class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        Tries prefix;
        for (const string& str : dictionary) {
            prefix.Add(str);
        }
        
        stringstream ss(sentence);
        string res = "";
        string tmp;
        while (ss >> tmp) {	// 这里由一个细节，就是空格的添加
            tmp = prefix.Match(tmp);
            res = res + tmp + " ";
        }
        res.pop_back();
        
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
        
        void Add(const string& word) {
            if (word.empty()) {
                return;
            }
            
            TrieNode *node = root;
            ++node->path_;
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
        
        string Match(const string& word) {
            if (word.empty()) {
                return "";
            }
            
            TrieNode *node = root;
            string res = word;
            for (int i = 0; i < word.size(); ++i) {
                int idx = word[i] - 'a';
                
                if (node->dict_[idx] != nullptr) {
                    node = node->dict_[idx];
                    if (node->end_ != 0) {
                        res = word.substr(0, i + 1);    // 这里注意[0, i]是一个左闭右闭的区间
                        break;
                    }
                } else {
                    break;
                }
            }
            
            return res;
        }
        
     private:
        TrieNode *root;
    };
};
`````

