# [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)

## 题目

Given the `root` of a binary tree, imagine yourself standing on the **right side** of it, return *the values of the nodes you can see ordered from top to bottom*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/14/tree.jpg)

```
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]
```

**Example 2:**

```
Input: root = [1,null,3]
Output: [1,3]
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

给定一棵二叉树的根节点，想象你站在二叉树的右边，自顶向下返回你能看到的节点

## 解题思路

这道题目有两个要求，

* 必须是每一层的最右边
* 结果必须是自顶向下

### Solution 1: BFS

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
    vector<int> rightSideView(TreeNode* root) {
        if (!root) {
            return vector<int>();
        }
        
        queue<TreeNode*> que;
        que.push(root);
        
        vector<int> res;
        while (!que.empty()) {
            const int len = que.size();
            // 一次遍历一层
            for (int i = 0; i < len; ++i) {
                TreeNode *cur = que.front();
                que.pop();
                // 只要最右边的结果
                if (i == len - 1) {
                    res.push_back(cur->val);
                }

                if (cur->left) {
                    que.push(cur->left);
                }
                if (cur->right) {
                    que.push(cur->right);
                }
            }
        }
        
        return res;
    }
};
````

