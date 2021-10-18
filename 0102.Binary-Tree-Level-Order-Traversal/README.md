# [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)

## 题目

Given the `root` of a binary tree, return *the level order traversal of its nodes' values*. (i.e., from left to right, level by level).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/tree1.jpg)

```
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
```

**Example 2:**

```
Input: root = [1]
Output: [[1]]
```

**Example 3:**

```
Input: root = []
Output: []
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 2000]`.
- `-1000 <= Node.val <= 1000`

## 题目大意

二叉树的层序遍历

## 解题思路

这道题的解法可以参考霜神的题解

### Solution 1：BFS

BFS 的难点在于每次要遍历整整一层

`````c++
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) {
            return vector<vector<int>>();
        }
        
        queue<TreeNode*> que;
        vector<vector<int>> res;
        int level = 0;
        
        que.push(root);
        while (!que.empty()) {
            const int size = que.size();  // 当前层的数目
            res.push_back({});  // 添加新的一行
            
            for (int i = 0; i < size; ++i) {
                TreeNode *cur = que.front();
                que.pop();
                
                res[level].push_back(cur->val);  // 加入到结果集中
                if (cur->left) {
                    que.push(cur->left);
                }
                if (cur->right) {
                    que.push(cur->right);
                }
            }
            ++level;  // 递增层数
        }
        
        return res;
    }
};
`````

### Solution 2: DFS

DFS 的解法在于，每个节点都必须和其层数绑定，即这里的状态转移，除了节点的位置之外，还有节点的层数，

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) {
            return vector<vector<int>>();
        }
        
        LevelOrder(root, 0);
        return res_;
    }
    
 private:
    vector<vector<int>> res_;
    
    void LevelOrder(TreeNode *root, int level) {
        if (!root) {
            return;
        }
        
        // 如果层数到达上限，新建一行
        if (level == res_.size()) {
            res_.push_back({root->val});
        } else {
            // 否则，插入到已有的行中
            res_[level].push_back(root->val);
        }
        
        // 递归遍历左右子树
        LevelOrder(root->left, level + 1);
        LevelOrder(root->right, level + 1);
    }
};
````

