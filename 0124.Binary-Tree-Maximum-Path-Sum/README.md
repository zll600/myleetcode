# [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)

## 题目

A **path** in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence **at most once**. Note that the path does not need to pass through the root.

The **path sum** of a path is the sum of the node's values in the path.

Given the `root` of a binary tree, return *the maximum **path sum** of any path*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/13/exx1.jpg)

```
Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/10/13/exx2.jpg)

```
Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 3 * 104]`.
- `-1000 <= Node.val <= 1000`

## 题目大意

二叉树中的一条路径是指从任意节点开始到达任意节点的序列，一个节点只能在序列中出现最多一次，注意这条路经不需要经过根节点，

路径总和是一条路径上的所有节点的值的和

给定一棵二叉树的根节点，返回任意路径的最大路径和

## 解题思路

这种题就是利用二叉树的后序遍历，先算左右子树，再算中间，递归维护最大值，

可以参考这篇题解：https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/solution/er-cha-shu-zhong-de-zui-da-lu-jing-he-by-ikaruga/

### Solution 1:

这种解法，主要参考这篇题解：https://books.halfrost.com/leetcode/ChapterFour/0100~0199/0124.Binary-Tree-Maximum-Path-Sum/

需要递归的维护最大值，

* 最大值由以下几部分：
  * 当前节点可以作为中间节点和左右子树构成最大路径，
  * 也可以只与左子树
  * 或者右子树构成最大路径，
  * 也可以一个点构成最大值
* 当前节点作为其他节点的子树时，只能向上传递三者中的最大值
  * 当前节点自身
  * 当前节点+左子树
  * /当前节点+右子树

上面两部分右明显的重复的，详情可以参考代码

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
    int maxPathSum(TreeNode* root) {
        long res = INT_MIN;
        GetPathSum(root, res);
        
        return static_cast<int>(res);
    }
    
 private:
    long GetPathSum(TreeNode *root, long& res) {
        if (!root) {
            return INT_MIN;
        }
        
        // 先递归的求出左子树的最大路径和
        long left_sum = GetPathSum(root->left, res);
        // 求出右子树的最大路径和
        long right_sum = GetPathSum(root->right, res);
        
        // 当前节点所代表的路径中的最大的一条，
        // 注意这里因为要继续递归，所以这里的最大路径由：根节点+左子树或者右子树中的最大路径组成，
        // 不能同时包含左子树和右子树，否则就不能在递归中起作用了
        long cur_max = max(max(left_sum + root->val, right_sum + root->val), 1L * root->val);
        // 更新最大值结果
        res = max(res, max(cur_max, left_sum + right_sum + root->val));
        
        return cur_max;
    }
};
````

