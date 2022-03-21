# [623. Add One Row to Tree](https://leetcode.com/problems/add-one-row-to-tree/)

Given the `root` of a binary tree and two integers `val` and `depth`, add a row of nodes with value `val` at the given depth `depth`.

Note that the `root` node is at depth `1`.

The adding rule is:

- Given the integer `depth`, for each not null tree node `cur` at the depth `depth - 1`, create two tree nodes with value `val` as `cur`'s left subtree root and right subtree root.
- `cur`'s original left subtree should be the left subtree of the new left subtree root.
- `cur`'s original right subtree should be the right subtree of the new right subtree root.
- If `depth == 1` that means there is no depth `depth - 1` at all, then create a tree node with value `val` as the new root of the whole original tree, and the original tree is the new root's left subtree.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/15/addrow-tree.jpg)

```
Input: root = [4,2,6,3,1,5], val = 1, depth = 2
Output: [4,1,1,2,null,null,6,3,1,5]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/03/11/add2-tree.jpg)

```
Input: root = [4,2,null,3,1], val = 1, depth = 3
Output: [4,2,null,1,1,3,null,null,1]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 104]`.
- The depth of the tree is in the range `[1, 104]`.
- `-100 <= Node.val <= 100`
- `-105 <= val <= 105`
- `1 <= depth <= the depth of tree + 1`

给定一个二叉树的根节点 `root`，和两个整数 `val`, `depth`，在给定深度加上一行值为 `val` 的节点

注意 `root` 的 depth 为 1

增加的规则如下：

- 给定一个深度值 `depth` （正整数），针对深度为 `depth - 1` 层的每一非空节点 `cur`，为 `cur` 创建两个值为 `val` 的左子树和右子树
- `cur` 原来的左子树应该成为新的左节点的左子树
- `cur` 原来的右子树应该成为新的有节点的右子树
- 如果 `depth == 1` 说明没有 `depth - 1`，创建一个值为 `val`的新节点作为原来树的新的根节点，原来的部分，作为新的根节点的左子树

## 解题思路

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0623.Add-One-Row-to-Tree/)

这里应该即可使用 `DFS` 也可以使用 `BFS` 来做


### Solution 1: DFS

这种解法使用 `DFS` 来做，就是需要注意一下边界情况的处理

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
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (depth == 1) {
            return new TreeNode(val, root, nullptr);
        }

        AddTreeRow(root, val, depth, 1);
        return root;
    }

 private:
    // 这里的 level 变量是可回溯的，所以这里可以直接传值
    void AddTreeRow(TreeNode *root, int val, int depth, int level) {
        if (depth - 1 == level) {
            root->left = new TreeNode(val, root->left, nullptr);
            root->right = new TreeNode(val, nullptr, root->right);
            return;
        }

        if (root->left) {
            AddTreeRow(root->left, val, depth, level + 1);
        }
        if (root->right) {
            AddTreeRow(root->right, val, depth, level + 1);
        }
    }
};
````

