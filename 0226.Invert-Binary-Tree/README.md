# [226. Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)

## 题目

Given the `root` of a binary tree, invert the tree, and return *its root*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/14/invert1-tree.jpg)

```
Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/03/14/invert2-tree.jpg)

```
Input: root = [2,1,3]
Output: [2,3,1]
```

**Example 3:**

```
Input: root = []
Output: []
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 100]`.
- `-100 <= Node.val <= 100`

## 题目大意

给定一个二叉树的根节点，反转这个二叉树

## 解题思路

这道题目可以使用前序遍历和后序遍历，但是不能使用中序遍历，可以自己画图去模拟以下步骤

### Solution: Recursive

这种解法利用的是后序遍历，先递归处理左子树和右子树，然后处理前节点

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
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        // 先反转当前节点的左子树和右子树
        invertTree(root->left);
        invertTree(root->right);
        // 交换当前节点的做左孩子和右孩子
        swap(root->left, root->right);
        
        return root;
    }
};
````

### Solution2

使用前序遍历

```c++
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
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        // 先交换当前节点的做左孩子和右孩子
        swap(root->left, root->right);
        
        // 反转当前节点的左子树和右子树
        invertTree(root->left);
        invertTree(root->right);
        
        
        return root;
    }
};
```

