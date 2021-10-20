# [257. Binary Tree Paths](https://leetcode.com/problems/binary-tree-paths/)

## 题目

Given the `root` of a binary tree, return *all root-to-leaf paths in **any order***.

A **leaf** is a node with no children.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/12/paths-tree.jpg)

```
Input: root = [1,2,3,null,5]
Output: ["1->2->5","1->3"]
```

**Example 2:**

```
Input: root = [1]
Output: ["1"]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 100]`.
- `-100 <= Node.val <= 100`

## 题目大意

按照任意顺序返回从根节点到叶子节点的路径

### 解题思路

这道题和第 129 题很像，可以放在一起看一下

这里要注意的 path 并非在整个遍历的过程中有效，而只在一次遍历中，所以这里采用传值，而非传引用

````c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        DFS(root, "");
        return res_;
    }

 private:
    vector<string> res_;
    
    // 这里的 path 采用传值调用，而非传引用
    void DFS(TreeNode *root, string path) {
        if (!root) {
            return;
        }
        
        // 如果是根节点，则不加 "->"
        if (path.empty()) {
            path += to_string(root->val);
        } else {
            // 其余节点
            path += "->";
            path += to_string(root->val);
        }
        
        // 如果是叶子节点，加入结果集中
        if (!root->left && !root->right) {
            res_.push_back(path);
            return;
        }
        
        // 遍历左子树
        DFS(root->left, path);
        // 遍历右子树
        DFS(root->right, path);
    }
};
````



