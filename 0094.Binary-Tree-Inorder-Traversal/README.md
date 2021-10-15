# [94. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)

## 题目

Given the `root` of a binary tree, return *the inorder traversal of its nodes' values*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/15/inorder_1.jpg)

```
Input: root = [1,null,2,3]
Output: [1,3,2]
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

![img](https://assets.leetcode.com/uploads/2020/09/15/inorder_5.jpg)

```
Input: root = [1,2]
Output: [2,1]
```

**Example 5:**

![img](https://assets.leetcode.com/uploads/2020/09/15/inorder_4.jpg)

```
Input: root = [1,null,2]
Output: [1,2]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 100]`.
- `-100 <= Node.val <= 100`



**Follow up:** Recursive solution is trivial, could you do it iteratively?

## 题目大意

二叉树的中序遍历

**进阶要求**：使用迭代而不是递归来做

## 解题思路

### 解法1（递归）

``````
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
    vector<int> inorderTraversal(TreeNode *root) {
    	if (root == nullptr) {
    		return vector<int>();
    	}
        vector<int> res;
        InorderTraversal(root, res);
        return res;
    }
    
 private:
    void InorderTraversal(TreeNode *root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        InorderTraversal(root->left, res);
        res.push_back(root->val);
        InorderTraversal(root->right, res);
    }
};
``````

### 解法2（迭代）

迭代法，使用栈来存储

`````c++
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
    vector<int> inorderTraversal(TreeNode *root) {
        if (root == nullptr) {
            return vector<int>();
        }
        TreeNode *cur = root;
        vector<int> res;
        stack<TreeNode*> sta;
        
        while (!sta.empty() || cur != nullptr) {
            if (cur != nullptr) {
                sta.push(cur);
                cur = cur->left;
            } else {
                cur = sta.top();
                sta.pop();
                
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
        return res;
    }
};
`````

