# [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)

## 题目

Given the `root` of a binary tree, return *the preorder traversal of its nodes' values*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/15/inorder_1.jpg)

```
Input: root = [1,null,2,3]
Output: [1,2,3]
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
Output: [1,2]
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

二叉树的前序遍历



**进阶要求**：使用迭代而不是递归

## 解题思路

#### 解法1（递归）

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
    vector<int> preorderTraversal(TreeNode *root) {
    	if (root == nullptr) {
    		return vector<int>();
    	}
        vector<int> res;
        PreorderTraversal(root, res);
        return res;
    }
    
 private:
    void PreorderTraversal(TreeNode *root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        res.push_back(root->val);
        PreorderTraversal(root->left, res);
        PreorderTraversal(root->right, res);
    }
};
``````

### 解法2（迭代）

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
    vector<int> preorderTraversal(TreeNode *root) {
        if (root == nullptr) {
            return vector<int>();
        }
        
        stack<TreeNode*> sta;
        vector<int> res;
        sta.push(root);
        while (!sta.empty()) {
            TreeNode *cur = sta.top();
            sta.pop();
            res.push_back(cur->val);
            
            if (cur->right) {
                sta.push(cur->right);
            }
            
            if (cur->left) {
                sta.push(cur->left);
            }
        }
        
        return res;
    }
};
````

