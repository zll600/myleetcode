## [1315. Sum of Nodes with Even-Valued Grandparent](https://leetcode.cn/problems/sum-of-nodes-with-even-valued-grandparent/)

## 题目

Given the `root` of a binary tree, return *the sum of values of nodes with an **even-valued grandparent***. If there are no nodes with an **even-valued grandparent**, return `0`.

A **grandparent** of a node is the parent of its parent if it exists.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/08/10/even1-tree.jpg)

```
Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
Output: 18
Explanation: The red nodes are the nodes with even-value grandparent while the blue nodes are the even-value grandparents.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/08/10/even2-tree.jpg)

```
Input: root = [1]
Output: 0
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 104]`.
- `1 <= Node.val <= 100`



## 题目大意

给你一棵二叉树，请你返回满足以下条件的所有节点的值之和：

    该节点的祖父节点的值为偶数。（一个节点的祖父节点是指该节点的父节点的父节点。）

如果不存在祖父节点值为偶数的节点，那么返回 0



## Solution 1: PreOrder Traversal

使用前序遍历来计算即可，递归可以保存 grandparent 和 parent 的信息

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
    int sumEvenGrandparent(TreeNode* root) {
        ans_ = 0;
        DFS(0, 0, root);
        return ans_;
    }
    
 private:
    int ans_;
    
    void DFS(int grandparent, int parent, TreeNode *root) {
        if (!root) {
            return;
        }
        
        if (grandparent && grandparent % 2 == 0) {
            ans_ += root->val;      
        }
        
        DFS(parent, root->val, root->left);
        DFS(parent, root->val, root->right);
    }
};
````

