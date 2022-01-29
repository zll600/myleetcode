# [508. Most Frequent Subtree Sum](https://leetcode.com/problems/most-frequent-subtree-sum/)

## 题目

Given the `root` of a binary tree, return the most frequent **subtree sum**. If there is a tie, return all the values with the highest frequency in any order.

The **subtree sum** of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/24/freq1-tree.jpg)

```
Input: root = [5,2,-3]
Output: [2,-3,4]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/04/24/freq2-tree.jpg)

```
Input: root = [5,2,-5]
Output: [2]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 104]`.
- `-105 <= Node.val <= 105`

## 题目大意

给出二叉树的根，找出出现次数最多的子树元素和，如果多个元素出现的次数相同，以任意顺序返回所有出现频数最多的数，

一个节点的 **子树和** 定义为以该节点为根节点的二叉树上的所有元素之和（包括根节点本身）,

## 解题思路



### Solution 1: 二叉树的后续遍历 + map

这种解法使用二叉树的后续遍历来计算累加和出现的频次，然后遍历，更新出现频次最高的集合

````C++
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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        // 先后序遍历增加缓存
        PostOrder(root);
        
        vector<int> res;
        int max_val = 0;
        for (const auto& item : cache_) {
            if (item.second > max_val) {
                // 如果有出现频次更高的值，就更新
                res.clear();
                res.push_back(item.first);
                max_val = item.second;
            } else if (item.second == max_val) {
                // 如果相等就累加缓存
                res.push_back(item.first);
            }
        }
        
        return move(res);
    }
  
 private:
    unordered_map<int, int> cache_; // 缓存 
    
    int PostOrder(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        
        int sum = root->val + PostOrder(root->left) + PostOrder(root->right);
        ++cache_[sum];
        return sum;
    }
};
