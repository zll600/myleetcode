# [301. Remove Invalid Parentheses](https://leetcode-cn.com/problems/remove-invalid-parentheses/)

## 题目

Given a string `s` that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.

Return *all the possible results*. You may return the answer in **any order**.

 

**Example 1:**

```
Input: s = "()())()"
Output: ["(())()","()()()"]
```

**Example 2:**

```
Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]
```

**Example 3:**

```
Input: s = ")("
Output: [""]
```

 

**Constraints:**

- `1 <= s.length <= 25`
- `s` consists of lowercase English letters and parentheses `'('` and `')'`.
- There will be at most `20` parentheses in `s`.

## 题目大意

给定一个字符串 s，包含括号和字母，返回删除的最小的括号数，让输入字符串有效，返回所有有效的结果，你可以按照任何顺序返回，

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/remove-invalid-parentheses/solution/gong-shui-san-xie-jiang-gua-hao-de-shi-f-asu8/

这道题目的难点在于怎样判断字符串是有效的，对于括号来说，只要括号是成对匹配的，我们就认为是有效的，所以我们在遍历字符串的时候记录左括号和右括号的的数目，

* 最终左括号数目 == 右括号数目
* 遍历过程中右括号数目始终小于左括号数目

### Solution 1: DFS



````c++
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int left = 0, right = 0;
        for (char c : s) {
            if (c == '(') {
                ++left;
            } else if (c == ')') {
                ++right;
            }
        }
        
        max_score_ = min(left, right); // 这里是最大的括号对数
        DFS(s, 0, 0, "");
        return vector<string>(cache_.begin(), cache_.end());
    }
    
 private:
    int max_len_; // 结果字符串的最大长度
    unordered_set<string> cache_; // 做缓存
    int max_score_; // 最多对数
    
    void DFS(const string& s, int idx, int score, string path) {
        if (score < 0 || score > max_score_) {
            // 剪枝操作，
            return;
        }
        if (idx == s.size()) {
            if (score == 0 && path.size() >= max_len_) {
                if (path.size() > max_len_) {
                    // 如果出现更长的长度，就更新
                    cache_.clear();
                }
                max_len_ = path.size();
                cache_.insert(path);
            }
            return;
        }
        
        char c = s[idx];
        if (c == '(') {
            // 选或者不选
            DFS(s, idx + 1, score + 1, path + c);
            DFS(s, idx + 1, score, path);
        } else if (c == ')') {
            DFS(s, idx + 1, score - 1, path + c);
            DFS(s, idx + 1, score, path);
        } else {
            // 字母直接加入
            DFS(s, idx + 1, score, path + c);
        }
    }
};
````

### Solution 2:

这种解法，通过预处理得到最长的字符串长度，

```c++
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int left = 0, right = 0;
        for (char c : s) {
            if (c == '(') {
                ++left;
            } else if (c == ')') {
                ++right;
            }
        }        
        max_score_ = min(left, right); // 这里是最大的括号对数
        
        // 下面是为了得到需要删除的左括号数，右括号数
        left = right = 0;
        for (char c : s) {
            if (c == '(') {
                ++left;
            } else if (c == ')') {
                if (left != 0) {
                    --left;
                } else {
                    ++right;
                }
            }
        }
        max_len_ = s.size() - left - right; // 最大长度
        
        DFS(s, 0, 0, left, right, "");
        return vector<string>(cache_.begin(), cache_.end());
    }
    
 private:
    int max_len_; // 结果字符串的最大长度
    unordered_set<string> cache_; // 做缓存
    int max_score_; // 最多对数
    
    void DFS(const string& s, int idx, int score, int left, int right, string path) {
        if (left < 0 || right < 0 || score < 0 || score > max_score_) {
            // 剪枝操作，
            return;
        }
        
        if (left == 0 && right == 0) {
            if (path.size() == max_len_) {
                cache_.insert(path);
            }
        }
        if (idx == s.size()) {
            return;
        }
        
        char c = s[idx];
        if (c == '(') {
            // 选或者不选
            DFS(s, idx + 1, score + 1, left, right, path + c); 
            DFS(s, idx + 1, score, left - 1, right, path); // 这里的不选就等效于删除一个
        } else if (c == ')') {
            DFS(s, idx + 1, score - 1, left, right, path + c);
            DFS(s, idx + 1, score, left, right - 1, path); // 同上
        } else {
            // 字母直接加入
            DFS(s, idx + 1, score, left, right, path + c);
        }
    }
};
```

