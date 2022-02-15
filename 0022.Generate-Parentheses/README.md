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

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/generate-parentheses/solution/hui-su-suan-fa-by-liweiwei1419/)

* 这道题初看是判断括号的有效，但仔细以下真的这样写，时间复杂度巨高，后来还是看题解吧
* 可以DFS 和 BFS 来解决，

### Solution 1： DFS

`````c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string path = "";
        path.reserve(16);  // 这里可以预分配，减少内存分配
        DFS(n, n, path);
        return res_;
    }

 private:
    vector<string> res_;

    void DFS(int left, int right, string& path) {
        if (left == 0 && right == 0) {  // 左右剩余括号数均为 0
            res_.push_back(path);  // 添加到结果集中
            return;
        }

        if (left > 0) {  // 只要左括号数有剩余，就可以添加
            path.push_back('(');
            DFS(left - 1, right, path);
            path.pop_back();
        }
        if (right > left) {  // 只有右括号剩余严格大于左括号剩余，才可以添加右括号
            path.push_back(')');
            DFS(left, right - 1, path);
            path.pop_back();
        }
    }
};
`````

### Solution 2: BFS


````c++
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

### Solution 3: DFS

这种写法的好处在于，不用显示来进行回溯，但是实际上回溯一直存在，

````c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string str = "";
        DFS(str, n, n);
        
        return res_;
    }
    
 private:
    vector<string> res_;
    
    void DFS(const string& str, int left, int right) {
        if (left == 0 && right == 0) {
            res_.push_back(str);
            return;
        }
        
        if (left > right) {
            return;
        }
        
        if (left > 0) {
            DFS(str + '(', left - 1, right);
        }
        if (right > left) {
            DFS(str + ')', left, right - 1);
        }
    }
};
````
