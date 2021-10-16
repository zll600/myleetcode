# [590. N-ary Tree Postorder Traversal](https://leetcode.com/problems/n-ary-tree-postorder-traversal/)

## 题目

Given the `root` of an n-ary tree, return *the postorder traversal of its nodes' values*.

Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png)

```
Input: root = [1,null,3,2,4,null,5,6]
Output: [5,6,3,2,4,1]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/11/08/sample_4_964.png)

```
Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 104]`.
- `0 <= Node.val <= 104`
- The height of the n-ary tree is less than or equal to `1000`.

 

**Follow up:** Recursive solution is trivial, could you do it iteratively?

## 题目大意

n 叉树的后序遍历

### 解题思路

这道题目可以参考第 489 题，第 589 题，均属于 n 叉树的遍历问题

### Solution1: Recursive

`````c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> postorder(Node* root) {
        if (root == nullptr) {
            return vector<int>();
        }
        
        vector<int> res;
        Postorder(root, res);
        
        return res;
    }
    
 private:
    void Postorder(Node *root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        for (auto it : root->children) {
            Postorder(it, res);
        }
        
        res.push_back(root->val);
    }
};
`````

### Solution 2: Iterative

````c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> postorder(Node* root) {
        if (root == nullptr) {
            return vector<int>();
        }
        
        deque<int> res;
        stack<Node*> sta;
        sta.push(root);
        
        while (!sta.empty()) {
            Node *cur = sta.top();
            sta.pop();
            
            res.push_front(cur->val);
            for (auto it : cur->children) {
                if (it) {
                    sta.push(it);
                }
            }
        }
        
        return vector<int>(res.begin(), res.end());
    }
};
````

