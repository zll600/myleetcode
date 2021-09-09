# [22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) 

## 题目

Given `n` pairs of parentheses, write a function to *generate all combinations of well-formed parentheses*.

**Example 1:**

```
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
```

**Example 2:**

```
Input: n = 1
Output: ["()"]
```

 

**Constraints:**

- `1 <= n <= 8`

## 题目大意

给定 n 对括号，生成所有可能并且有效的括号。

## 解题思路

* 这道题初看是判断括号的有效，但仔细以下真的这样写，时间复杂度巨高，后来还是看题解吧
* 可以DFS 和 BFS 来解决，

## 代码

````c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {        
        DFS(n, n);
        return res;
    }
    
 private:
    vector<string> res;
    string path;
    
    void DFS(int left, int right) {
        if (left == 0 && right == 0) {  // 不能再添加括号的时候返回
            res.push_back(path);
            return;
        }
        
        if (left > right) { // 剪枝操作
            return;
        }
        
        if (left > 0) {
            path += '(';
            DFS(left - 1, right);
            path.pop_back();    // 这里需要撤销状态的更改，
        }
        
        if (right > 0) {
            path += ')';
            DFS(left, right - 1);
            path.pop_back();
        }
    }
};

// BFS
class Solution {
public:
    // BFS 需要使用一个结构来记录状态的转移
    struct Node {
        string str_;
        int left_;
        int right_;
        
        Node(string str, int left, int right)
            : str_(str), left_(left), right_(right) {}
    };
    
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        
        queue<Node> que;
        que.push(Node("", n, n));
        
        while (!que.empty()) {
            Node cur = que.front();
            que.pop();
            
            if (cur.left_ == 0 && cur.right_ == 0) {
                res.push_back(cur.str_);
            }
            
            if (cur.left_ > 0) {
                que.push(Node(cur.str_ + "(", cur.left_ - 1, cur.right_));
            }
            
            if (cur.right_ > 0 && cur.right_ > cur.left_) {
                que.push(Node(cur.str_ + ")", cur.left_, cur.right_ - 1));
            }
        }
        return res;
    }
};
````

