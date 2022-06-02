# [814. Binary Tree Pruning](https://leetcode.cn/problems/binary-tree-pruning/)

## 题目

Given the `root` of a binary tree, return *the same tree where every subtree (of the given tree) not containing a* `1` *has been removed*.

A subtree of a node `node` is `node` plus every node that is a descendant of `node`.

 

**Example 1:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/04/06/1028_2.png)

```
Input: root = [1,null,0,0,1]
Output: [1,null,0,null,1]
Explanation: 
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.
```

**Example 2:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/04/06/1028_1.png)

```
Input: root = [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]
```

**Example 3:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/04/05/1028.png)

```
Input: root = [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,null,1]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 200]`.
- `Node.val` is either `0` or `1`.

## 题目大意

给你二叉树的根结点 `root` ，此外树的每个结点的值要么是 `0` ，要么是 `1`

返回移除了所有不包含 `1` 的子树的原二叉树

节点 `node` 的子树为 `node` 本身加上所有 `node` 的后代

## 解题思路

这道题目要根据子树的状态来确定root 节点，所以这里不难想到使用后序遍历来做，

这里的具体做法就是

- 先遍历左右子树，查看是否出现 1，空节点视为没有出现 1
- 如果左子树没出现过 1，将节点置空，右子树同理
- 处理当前节点，表示当前子树的 1 可以有 3 个来源：
    - 当前节点
    - 当前节点的左子树
    - 当前节点的右子树
    - 三者取或就可以了


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
    TreeNode* pruneTree(TreeNode* root) {
        bool res = DFS(root);
        if (res == false) {
            root = nullptr;
        }

        return root;
    }

 private:
    bool DFS(TreeNode *root) {
        if (root == nullptr) {
            return false;
        }

        bool left_has_one = DFS(root->left);
        bool right_has_one = DFS(root->right);

        if (left_has_one == false) {
            root->left = nullptr;
        }
        if (right_has_one == false) {
            root->right = nullptr;
        }

        return root->val == 1 || left_has_one || right_has_one;
    }
};
````
