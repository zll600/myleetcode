# [589. N-ary Tree Preorder Traversal](https://leetcode.com/problems/n-ary-tree-preorder-traversal/)

## 题目

Given the `root` of an n-ary tree, return *the preorder traversal of its nodes' values*.

Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png)

```
Input: root = [1,null,3,2,4,null,5,6]
Output: [1,3,5,6,2,4]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/11/08/sample_4_964.png)

```
Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 104]`.
- `0 <= Node.val <= 104`
- The height of the n-ary tree is less than or equal to `1000`.

 

**Follow up:** Recursive solution is trivial, could you do it iteratively?

## 题目大意

给定一个 n 叉树的根节点，返回 它的前序遍历

**进阶要求**：使用迭代而不是递归

## 解题思路

这道题可以看下 第 429 题，思想都是一样的，二叉树有两个子节点，n 叉树右 n 个子节点，二叉树的先左后右就是 n 叉树的从前向后遍历，反之就需要从后向前遍历

### Solution1 : Recursive

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
    vector<int> preorder(Node* root) {
        if (root == nullptr) {
            return vector<int>();
        }
        
        vector<int> res;
        Preorder(root, res);
        
        return res;
    }
    
 private:
    void Preorder(Node *root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        res.push_back(root->val);  // 当前节点
        // 当前节点的所有子节点
        for (auto it : root->children) {
            Preorder(it, res);
        }
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
    vector<int> preorder(Node* root) {
        if (root == nullptr) {
            return vector<int>();
        }
        
        vector<int> res;
        stack<Node*> sta;
        sta.push(root);
        
        while (!sta.empty()) {
            Node *cur = sta.top();
            sta.pop();
            res.push_back(cur->val);
            
            // 这里建议多用迭代器
            for (auto it = cur->children.crbegin(); it != cur->children.crend(); ++it) {
                if (*it != nullptr) {
                    sta.push(*it);
                }
            }
        }
        
        return res;
    }
};
````

