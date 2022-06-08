# [865. Smallest Subtree with all the Deepest Nodes](https://leetcode.cn/problems/smallest-subtree-with-all-the-deepest-nodes/)

## 题目

Given the `root` of a binary tree, the depth of each node is **the shortest distance to the root**.

Return *the smallest subtree* such that it contains **all the deepest nodes** in the original tree.

A node is called **the deepest** if it has the largest depth possible among any node in the entire tree.

The **subtree** of a node is a tree consisting of that node, plus the set of all descendants of that node.

 

**Example 1:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/01/sketch1.png)

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: We return the node with value 2, colored in yellow in the diagram.
The nodes coloured in blue are the deepest nodes of the tree.
Notice that nodes 5, 3 and 2 contain the deepest nodes in the tree but node 2 is the smallest subtree among them, so we return it.
```

**Example 2:**

```
Input: root = [1]
Output: [1]
Explanation: The root is the deepest node in the tree.
```

**Example 3:**

```
Input: root = [0,1,3,null,2]
Output: [2]
Explanation: The deepest node in the tree is 2, the valid subtrees are the subtrees of nodes 2, 1 and 0 but the subtree of node 2 is the smallest.
```

 

**Constraints:**

- The number of nodes in the tree will be in the range `[1, 500]`.
- `0 <= Node.val <= 500`
- The values of the nodes in the tree are **unique**.

 

**Note:** This question is the same as 1123: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/

## 题目大意

给定一个根为 `root` 的二叉树，每个节点的深度是 *该节点到根的最短距离* 

返回包含原始树中所有 最深节点 的 最小子树

如果一个节点在 整个树 的任意节点之间具有最大的深度，则该节点是 最深的 。

一个节点的 子树 是该节点加上它的所有后代的集合

## 解题思路

这里要解决问题有：

- 找出最大深度
- 判断返回那一个节点
    - 如果最大深度只有一个节点，那么直接返回
    - 如果最大深度有两个节点，返回这两个节点的父节点

所以这里可以使用后序遍历先确定左右子树的情况，然后确定当前节点的情况

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/smallest-subtree-with-all-the-deepest-nodes/solution/cu-su-yi-dong-zhi-jie-kan-dai-ma-he-zhu-z4exw/)

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
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if (!root) {
            return root;
        }

        int left_deepth = GetMaxDeepth(root->left);
        int right_deepth = GetMaxDeepth(root->right);

        // 如果这个节点的左右子树高度相同，说明这个点就是答案
        if (left_deepth == right_deepth) {
            return root;
        }

        // 想高度更大的方向递归
        if (left_deepth > right_deepth) {
            return subtreeWithAllDeepest(root->left);
        }
        return subtreeWithAllDeepest(root->right);
    }

 private:
    unordered_map<int, int> cache_{};

    // 利用记忆化搜索求出每个节点的深度
    int GetMaxDeepth(TreeNode *root) {
        if (!root) {
            return 0;
        }

        int left_deepth = GetMaxDeepth(root->left);
        int right_deepth = GetMaxDeepth(root->right);

        int ans = max(left_deepth, right_deepth) + 1;
        cache_[root->val] = ans;
        return ans;
    }
};
````
