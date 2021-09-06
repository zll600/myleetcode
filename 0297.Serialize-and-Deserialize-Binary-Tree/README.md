# [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

## 题目

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

**Clarification:** The input/output format is the same as [how LeetCode serializes a binary tree](https://leetcode.com/faq/#binary-tree). You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/15/serdeser.jpg)

```
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]
```

**Example 2:**

```
Input: root = []
Output: []
```

**Example 3:**

```
Input: root = [1]
Output: [1]
```

**Example 4:**

```
Input: root = [1,2]
Output: [1,2]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 104]`.
- `-1000 <= Node.val <= 1000`

## 题目大意

设计一个算法，序列化和反序列化一个二叉树，没有严格限制你如何序列化或者反序列化，你只需要保证二叉树可以序列化为字符串，字符串可以反序列化为二叉树。

## 解题思路

* 这道题目可以使用 DFS  或者 BFS，遇到 nullptr 添加字符 “#”，每个节点之间的分隔符是“！”，
* 使用 DFS ，序列化的过程就是前序遍历，反序列化的过程就是重做前序遍历
* 使用BFS ，序列化的过程就是层序遍历，反序列化的过程就是重做层序遍历

## 代码

````c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 解法一：DFS
/*
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {  用 "#" 表示空节点，用"!"来分割
            return "#!";
        }
        
        string str = to_string(root->val);
        str += "!";
        str += serialize(root->left);
        str += serialize(root->right);
        
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty() || data == "#!") {
            return nullptr;
        }
        queue<string> que;
        istringstream ss(data);
        string s;
        
        while (getline(ss, s, '!')) {   // 使用 istringstream 
            que.push(s);
        }
        
        return ReconPreOrder(que);
    }
    
 private:
    TreeNode* ReconPreOrder(queue<string>& que) {   // que在整个遍历的过程中变化，所以传引用
        if (que.empty()) {  // 弹出之前必须检查队列是否为空
            return nullptr;
        }
        
        string str = que.front();
        que.pop();
        
        if (str == "#") {
            return nullptr;
        }
        TreeNode *root = new TreeNode(stoi(str));
        root->left = ReconPreOrder(que);
        root->right = ReconPreOrder(que);
        
        return root;
    }
};
*/

// 解法二：BFS
class Codec {
 public:
    string serialize(TreeNode *root) {
        if (root == nullptr) {
            return "#!";
        }
        
        queue<TreeNode*> que;
        que.push(root);
        ostringstream out;
        
        while (!que.empty()) {
            TreeNode *node = que.front();
            que.pop();
            
            if (node == nullptr) {
                out << "#!";
            } else {
                out << node->val << "!";
                que.push(node->left);
                que.push(node->right);
            }
        }
        
        return out.str();
    }
    
    // 使用两个队列来操作
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }
        
        istringstream ss(data);
        queue<string> que;
        
        string str;
        while (getline(ss, str, '!')) {
            que.push(str);
        }
        
        str = que.front();
        que.pop();
        if (str == "#") {
            return nullptr;
        }
        TreeNode *root = new TreeNode(stoi(str));
        queue<TreeNode*> nodes;
        nodes.push(root);
        
        while (!nodes.empty()) {
            TreeNode *node = nodes.front();
            nodes.pop();
            
            str = que.front();
            que.pop();
            if (str == "#") {
                node->left = nullptr;
            } else {
                node->left = new TreeNode(stoi(str));
            }
            
            str = que.front();
            que.pop();
            if (str == "#") {
                node->right = nullptr;
            } else {
                node->right = new TreeNode(stoi(str));
            }
            
            if (node->left != nullptr) {
                nodes.push(node->left);
            }
            if (node->right != nullptr) {
                nodes.push(node->right);
            }
        }
        
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
````

