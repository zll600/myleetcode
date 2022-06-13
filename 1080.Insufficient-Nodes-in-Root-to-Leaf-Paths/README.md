# [1080. Insufficient Nodes in Root to Leaf Paths](https://leetcode.cn/problems/insufficient-nodes-in-root-to-leaf-paths/)

## 题目

Given the `root` of a binary tree and an integer `limit`, delete all **insufficient nodes** in the tree simultaneously, and return *the root of the resulting binary tree*.

A node is **insufficient** if every root to **leaf** path intersecting this node has a sum strictly less than `limit`.

A **leaf** is a node with no children.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/06/05/insufficient-11.png)

```
Input: root = [1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14], limit = 1
Output: [1,2,3,4,null,null,7,8,9,null,14]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/06/05/insufficient-3.png)

```
Input: root = [5,4,8,11,null,17,4,7,1,null,null,5,3], limit = 22
Output: [5,4,8,11,null,17,4,7,null,null,null,5]
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2019/06/11/screen-shot-2019-06-11-at-83301-pm.png)

```
Input: root = [1,2,-3,-5,null,4,null], limit = -1
Output: [1,null,-3,4]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 5000]`.
- `-105 <= Node.val <= 105`
- `-109 <= limit <= 109`

## 题目大意

给定一棵二叉树的根 `root`，请你考虑它所有 从根到叶的路径：从根到任何叶的路径。（所谓一个叶子节点，就是一个没有子节点的节点）

假如通过节点 `node` 的每种可能的 “根-叶” 路径上值的总和全都小于给定的 `limit`，则该节点被称之为「不足节点」，需要被删除

请你删除所有不足节点，并返回生成的二叉树的根

## 解题思路

这篇题解有 weiwei 老师的 [题解](https://leetcode.cn/problems/insufficient-nodes-in-root-to-leaf-paths/solution/hou-xu-bian-li-python-dai-ma-java-dai-ma-by-liweiw/) 可以好好学学

### Solution 1:

这里刚开始想的是使用前序遍历来做，后来定时递归函数返回 bool 值来判断是否需要删除子节点，于是想到后序遍历应该会更好

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
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        if (PostOrder(root, 0, limit)) {
            return nullptr;
        }
        return root;
    }
    
 private:
    bool PostOrder(TreeNode *root, int cur, int limit) {
        if (!root) {
            return true;
        }
        
        if (!root->left && !root->right) {
            return cur + root->val < limit;
        }
        
        bool delete_left = PostOrder(root->left, cur + root->val, limit);
        bool delete_right = PostOrder(root->right, cur + root->val, limit);
        if (delete_left) {
            root->left = nullptr;
        }
        if (delete_right) {
            root->right = nullptr;
        }
        
        return delete_left && delete_right;
    }
};
````
