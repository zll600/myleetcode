# [784. Letter Case Permutation](https://leetcode.com/problems/letter-case-permutation/)

## 题目

Given a string `s`, we can transform every letter individually to be lowercase or uppercase to create another string.

Return *a list of all possible strings we could create*. You can return the output in **any order**.

 

**Example 1:**

```
Input: s = "a1b2"
Output: ["a1b2","a1B2","A1b2","A1B2"]
```

**Example 2:**

```
Input: s = "3z4"
Output: ["3z4","3Z4"]
```

**Example 3:**

```
Input: s = "12345"
Output: ["12345"]
```

**Example 4:**

```
Input: s = "0"
Output: ["0"]
```

 

**Constraints:**

- `s` will be a string with length between `1` and `12`.
- `s` will consist only of letters or digits.

## 题目大意

给定一个字符串，可以对这个字符串中的字母进行大小写转化创造一个新的字符串，返回你可以所有你可以创造的字符串

## 解题思路

* 这道题目其实就是求字符串中所有字母的大小写组合有多少种，
* 可以使用 DFS 或者 BFS

## 代码

````c++
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        DFS(s, 0);
        
        return res;
    }

 private:
    vector<string> res;
    string path;
    
    // 这是最直接，最笨的方法，

    void DFS(string s, int idx) {
        if (idx == s.size()) {
            res.push_back(path);
            return;
        }
        /*
        if (isdigit(s[idx])) {
            path.push_back(s[idx]);
            DFS(s, idx + 1);
            path.pop_back();
        } else if (islower(s[idx])) {
            path.push_back(s[idx]);
            DFS(s, idx + 1);
            path.pop_back();
            
            path.push_back(toupper(s[idx]));
            DFS(s, idx + 1);
            path.pop_back();
        } else if (isupper(s[idx])) {
            path.push_back(s[idx]);
            DFS(s, idx + 1);
            path.pop_back();
            
            path.push_back(tolower(s[idx]));
            DFS(s, idx + 1);
            path.pop_back();
        }*/
        
        path.append(1, s[idx]);
        DFS(s, idx + 1);
        path.pop_back();
        
        if (isdigit(s[idx])) {
            return;
        } else {
            if (islower(s[idx])) {
                path.append(1, toupper(s[idx]));
            } else {
                path.append(1, tolower(s[idx]));
            }
            DFS(s, idx + 1);
            path.pop_back();
        }
    }
};
````

