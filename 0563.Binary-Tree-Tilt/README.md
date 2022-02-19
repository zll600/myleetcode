# [563. Binary Tree Tilt](https://leetcode.com/problems/binary-tree-tilt/)

## 题目

Given the `root` of a binary tree, return *the sum of every tree node's **tilt**.*

The **tilt** of a tree node is the **absolute difference** between the sum of all left subtree node **values** and all right subtree node **values**. If a node does not have a left child, then the sum of the left subtree node **values** is treated as `0`. The rule is similar if there the node does not have a right child.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/20/tilt1.jpg)

```
Input: root = [1,2,3]
Output: 1
Explanation: 
Tilt of node 2 : |0-0| = 0 (no children)
Tilt of node 3 : |0-0| = 0 (no children)
Tilt of node 1 : |2-3| = 1 (left subtree is just left child, so sum is 2; right subtree is just right child, so sum is 3)
Sum of every tilt : 0 + 0 + 1 = 1
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/10/20/tilt2.jpg)

```
Input: root = [4,2,9,3,5,null,7]
Output: 15
Explanation: 
Tilt of node 3 : |0-0| = 0 (no children)
Tilt of node 5 : |0-0| = 0 (no children)
Tilt of node 7 : |0-0| = 0 (no children)
Tilt of node 2 : |3-5| = 2 (left subtree is just left child, so sum is 3; right subtree is just right child, so sum is 5)
Tilt of node 9 : |0-7| = 7 (no left child, so sum is 0; right subtree is just right child, so sum is 7)
Tilt of node 4 : |(3+5+2)-(9+7)| = |10-16| = 6 (left subtree values are 3, 5, and 2, which sums to 10; right subtree values are 9 and 7, which sums to 16)
Sum of every tilt : 0 + 0 + 0 + 2 + 7 + 6 = 15
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2020/10/20/tilt3.jpg)

```
Input: root = [21,7,14,1,1,2,2,3,3]
Output: 9
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 104]`.
- `-1000 <= Node.val <= 1000`

## 题目大意

给定一棵二叉树，计算整个树的坡度，也就是所有节点的坡度之和

一个树的节点的坡度定义为，该节点的左子树节点之和右子树节点之和的差的绝对值，空节点的坡度为0，


## 解题思路

这道题目我们可以在求 每个节点的左子树和右子树和的同时，求出这个点的坡度，并做累加，

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0500~0599/0563.Binary-Tree-Tilt/)


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
    int findTilt(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        
        int tilt = 0;
        PostOrder(root, tilt);
        
        return tilt;
    }
    
 private:
    int PostOrder(TreeNode *root, int& tilt) {
        if (root == nullptr) {
            return 0;
        }
        
        // 分别计算左右子树的 和 
        int sum_left = PostOrder(root->left, tilt);
        int sum_right = PostOrder(root->right, tilt);
        
        // 累计计算坡度
        tilt += abs(sum_left - sum_right);
        
        // 返回累加和
        return root->val + sum_left + sum_right;
    }
};
````
