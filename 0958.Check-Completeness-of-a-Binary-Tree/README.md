# [958. Check Completeness of a Binary Tree](https://leetcode.com/problems/check-completeness-of-a-binary-tree/)

## 题目

Given the `root` of a binary tree, determine if it is a *complete binary tree*.

In a **[complete binary tree](http://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees)**, every level, except possibly the last, is completely filled, and all  nodes in the last level are as far left as possible. It can have between `1` and `2h` nodes inclusive at the last level `h`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/12/15/complete-binary-tree-1.png)

```
Input: root = [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2018/12/15/complete-binary-tree-2.png)

```
Input: root = [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 100]`.
- `1 <= Node.val <= 1000`

## 题目大意

给定一个二叉树，确定它是否是一个完全二叉树。

百度百科中对完全二叉树的定义如下：

若设二叉树的深度为 `h`，除第 `h` 层外，其它各层 `(1～h-1)` 的结点数都达到最大个数，第 `h` 层所有的结点都连续集中在最左边，这就是完全二叉树。（注：第 h 层可能包含 `1~ 2h` 个节点。）

## 解题思路

### Solution 1:


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
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> que;
        que.push(root);
        
        bool flag = false;
        while (!que.empty()) {
            TreeNode *cur = que.front();
            que.pop();
            
            if (!cur) {
                //  有一个为空
                flag = true;
            } else {
                // 这个不为空的节点之前有一个空节点，直接返回
                if (flag) {
                    return false;
                }
                // 添加节点
                que.push(cur->left);
                que.push(cur->right);
            }
        }
        
        return true;
    }
};
````
