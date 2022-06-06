# [889. Construct Binary Tree from Preorder and Postorder Traversal](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)

## 题目

Given two integer arrays, `preorder` and `postorder` where `preorder` is the preorder traversal of a binary tree of **distinct** values and `postorder` is the postorder traversal of the same tree, reconstruct and return *the binary tree*.

If there exist multiple answers, you can **return any** of them.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/07/24/lc-prepost.jpg)

```
Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]
```

**Example 2:**

```
Input: preorder = [1], postorder = [1]
Output: [1]
```

 

**Constraints:**

- `1 <= preorder.length <= 30`
- `1 <= preorder[i] <= preorder.length`
- All the values of `preorder` are **unique**.
- `postorder.length == preorder.length`
- `1 <= postorder[i] <= postorder.length`
- All the values of `postorder` are **unique**.
- It is guaranteed that `preorder` and `postorder` are the preorder traversal and postorder traversal of the same binary tree.

## 题目大意

给定两个整数数组，`preorder` 和 `postorder` ，其中 `preorder` 是一个具有 无重复 值的二叉树的前序遍历，`postorder` 是同一棵树的后序遍历，重构并返回二叉树

如果存在多个答案，您可以返回其中 任何 一个

## 解题思路

这道题目旳核心就是利用 前序 来分割 后序遍历的结果，然后利用前序构建左右子树

### Solution 1:

这里分割的方法利用的是，前序遍历和后序遍历左右子树的节点集合是一样的（顺序不一定相同）

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/solution/kan-wo-jiu-gou-liao-san-chong-bian-li-fang-shi-gou/)

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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        return Construct(preorder, postorder,
                        0, preorder.size() - 1, 0, postorder.size() - 1);
    }

 private:
    TreeNode* Construct(const vector<int>& preorder, const vector<int>& postorder,
                       int pre_start, int pre_end, int post_start, int post_end) {
        if (pre_start > pre_end || post_start > post_end) {
            return nullptr;
        }

        TreeNode *root = new TreeNode(preorder[pre_start]);
        if (pre_start == pre_end) {
            return root;
        }

        int index = post_start;
        while (preorder[pre_start + 1] != postorder[index]) {
            ++index;
        }

        root->left = Construct(preorder, postorder,
                              pre_start + 1, pre_start + 1 + index - post_start,
                              post_start, index);
        root->right = Construct(preorder, postorder,
                               pre_start + 1 + index - post_start + 1, pre_end,
                               index + 1, post_end - 1);

        return root;
    }
};
````
