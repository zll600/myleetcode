# [1302. Deepest Leaves Sum](https://leetcode.com/problems/deepest-leaves-sum/)

## 题目

Given the `root` of a binary tree, return *the sum of values of its deepest leaves*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/07/31/1483_ex1.png)

```
Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
Output: 15
```

**Example 2:**

```
Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
Output: 19
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 104]`.
- `1 <= Node.val <= 100`

## 题目大意

给定一棵二叉树的根节点，返回最深层的节点的值的和

### 解题思路

这道题可以参考霜神的题解

维护一个最深的层数，和最深层节点的和，遍历的时候更新这两个值，更新的策略是：

* 如果最深的层数需要更新，则 sum 需要重置
* 如果最深的层数与当前层数相同，则累加sum

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
    int deepestLeavesSum(TreeNode* root) {
        int max_level = 0;
        int sum = 0;
        GetDeepestSum(root, 0, max_level, sum);
        
        return sum;
    }
    
 private:
    // 注意这里的传值调用
    void GetDeepestSum(TreeNode *root, int cur_level,
                        int& max_level, int& sum) {
        if (!root) {
            return;
        }
        
        // 如果最深层数需要更新，则需要重置和
        if (cur_level > max_level) {
            max_level = cur_level;
            sum = root->val;
        } else if (cur_level == max_level) {
            // 如果是最深层，则直接累加即可
            sum += root->val;
        }
        
        // 递归计算左子树
        GetDeepestSum(root->left, cur_level + 1, max_level, sum);
        // 递归计算右子树
        GetDeepestSum(root->right, cur_level + 1, max_level, sum);
    }
};
````

