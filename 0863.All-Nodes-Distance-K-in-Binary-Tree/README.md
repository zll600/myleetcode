# [863. All Nodes Distance K in Binary Tree](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/)

## 题目

Given the `root` of a binary tree, the value of a target node `target`, and an integer `k`, return *an array of the values of all nodes that have a distance* `k` *from the target node.*

You can return the answer in **any order**.

 

**Example 1:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/06/28/sketch0.png)

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.
```

**Example 2:**

```
Input: root = [1], target = 1, k = 3
Output: []
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 500]`.
- `0 <= Node.val <= 500`
- All the values `Node.val` are **unique**.
- `target` is the value of one of the nodes in the tree.
- `0 <= k <= 1000`

## 题目大意

给定一个棵二叉树root，一个目标节点的值 target，和一个整数 k，找到距离目标节点值为 k 的节点的集合

## 解题思路

* 这一题用 DFS 的方法解题。先找到当前节点距离目标节点的距离，如果在左子树中找到了 target，距离当前节点的距离 > 0，则还需要在它的右子树中查找剩下的距离。如果是在右子树中找到了 target，反之同理。如果当前节点就是目标节点，那么就可以直接记录这个点。否则每次遍历一个点，距离都减一。
* 这一题可以用 DFS 的方法来解决。先找到当前节点距离目标节点的距离，如果在左子树中找到了 target，距离当前节点的距离 > 0，则还需要在它的右子树中查找剩下的距离。如果在右子树中找到来 target ，则还需要在 它的左子树中查找剩下的距离。如果当前节点就是目标节点，就可以直接记录这个节点，否则没遍历一步，距离就减一。
* 这道题目可以用 DFS 来解决，与目标节点的距离为 k ，也就是说从需要满足从当前节点到目标节点需要走 k 步，如果在当前节点向左子树中走，没走一步 k 减一，如果到达目标节点 k > 0 ，则说明应该从当前节点的右子树中开始出发，先消耗多余的步数，反之同理，
* 如果当前节点就是目标节点，则应遍历当前节点的左右子树来直接消耗 k 步，这时就是相当于在以目标节点为根节点的书中找到与目标节点相距 k 的节点

## 代码

````c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        FindDistanceK(root, target, k);
        return res;
    }
    
 private:
    vector<int> res;
    
    int FindDistanceK(TreeNode *root, TreeNode *target, int k) {
        if (root == nullptr) {
            return -1;
        }
        
        if (root == target) {
            FindChild(root, k);
            return k - 1;
        }
        
        // 在当前节点的左子树中找 target，返回还需要消耗的步数
        int left_dist = FindDistanceK(root->left, target, k);   
        if (left_dist == 0) {   // 不需要多走了，直接加入
            res.push_back(root->val);
        }
        if (left_dist > 0) {    // 还右剩余步数，进当前节点的右子树进行查找
            FindChild(root->right, left_dist - 1);
            return left_dist - 1;
        }
        
        int right_dist = FindDistanceK(root->right, target, k);
        if (right_dist == 0) {  // 步数消耗完毕，直接加入
            res.push_back(root->val);
        }
        if (right_dist > 0) {   // 还需要在左子树中查找一部分，
            FindChild(root->left, right_dist - 1);
            return right_dist - 1;
        }
        
        return -1;
    }
    
    void FindChild(TreeNode *root, int k) { // 消耗完剩余的步数
        if (root == nullptr) {
            return;
        }
        
        if (k == 0) {
            res.push_back(root->val);
        } else {
            FindChild(root->left, k - 1);
            FindChild(root->right, k - 1);
        }
    }
};
````





