#### [1325. Delete Leaves With a Given Value](https://leetcode.cn/problems/delete-leaves-with-a-given-value/)

## 题目

Given a binary tree `root` and an integer `target`, delete all the **leaf nodes** with value `target`.

Note that once you delete a leaf node with value `target`**,** if its parent node becomes a leaf node and has the value `target`, it should also be deleted (you need to continue doing that until you cannot).

 

**Example 1:**

**![img](https://assets.leetcode.com/uploads/2020/01/09/sample_1_1684.png)**

```
Input: root = [1,2,3,2,null,2,4], target = 2
Output: [1,null,3,null,4]
Explanation: Leaf nodes in green with value (target = 2) are removed (Picture in left). 
After removing, new nodes become leaf nodes with value (target = 2) (Picture in center).
```

**Example 2:**

**![img](https://assets.leetcode.com/uploads/2020/01/09/sample_2_1684.png)**

```
Input: root = [1,3,3,3,2], target = 3
Output: [1,3,null,null,2]
```

**Example 3:**

**![img](https://assets.leetcode.com/uploads/2020/01/15/sample_3_1684.png)**

```
Input: root = [1,2,null,2,null,2], target = 2
Output: [1]
Explanation: Leaf nodes in green with value (target = 2) are removed at each step.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 3000]`.
- `1 <= Node.val, target <= 1000`

### 题目大意

给你一棵以 root 为根的二叉树和一个整数 target ，请你删除所有值为 target 的 叶子节点 。

注意，一旦删除值为 target 的叶子节点，它的父节点就可能变成叶子节点；如果新叶子节点的值恰好也是 target ，那么这个节点也应该被删除。

也就是说，你需要重复此过程直到不能继续删除



### Solution 1: 

这里因为需要由 父节点来处理子节点的情况，所以采用后序遍历，先判断子节点的情况，然后在判断父节点，这样递归进行

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
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        bool res = DFS(root, target);
        if (res) {
            root = nullptr;
        }
        return root;
    }
    
 private:
    bool DFS(TreeNode *root, int target) {
        if (!root) {
            return false;
        }
        
        bool left_res = DFS(root->left, target);
        if (left_res) {
            root->left = nullptr;
        }
        
        bool right_res = DFS(root->right, target);
        if (right_res) {
            root->right = nullptr;
        }
        
        if (!root->left && !root->right) {
            if (root->val == target) {
                return true;
            }
        }
        return false;
    }
};
````

