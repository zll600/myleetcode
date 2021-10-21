# [103. Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/) 

Given the `root` of a binary tree, return *the zigzag level order traversal of its nodes' values*. (i.e., from left to right, then right to left for the next level and alternate between).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/tree1.jpg)

```
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]
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
- `-100 <= Node.val <= 100`

## 题目

给定一个二叉树，返回其节点值的锯齿形层序遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

## 解题思路

这道题也属于二叉树的层序遍历，

通常解法是利用两个队列来交替写

### Solution 1:

这里采用左神的方法，使用一个双端队列：

* 从左向右时：从前面取出当前层的节点，从后面加入下一层的节点
* 从右向左时：从后面取出当前层的节点，从前面加入下一层的节点

在遍历的过程中维护 last 和 next_last 分别表示当前行的最后一个节点和下一行的最后一个节点

可以自己手动模拟以下

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        // 边界条件
        if (!root) {
            return vector<vector<int>>();
        }
        
        vector<vector<int>> res;
        deque<TreeNode*> que;  // 存储状态转移
        que.push_back(root);
        
        bool left_to_right = true;  // 标志方向
        TreeNode *last = root;  // 当前层的最后一个节点
        TreeNode *next_last = nullptr;  // 下一层的最后一个节点
        int level = 0;  // 层数
        res.push_back({});
        while (!que.empty()) {
            TreeNode *cur = nullptr;
            if (left_to_right) {  // 从左至右遍历
                cur = que.front();  // 从前面出
                que.pop_front();
                res[level].push_back(cur->val);
                
                if (cur->left) {
                    // 更新 next_last
                    next_last = next_last == nullptr ? cur->left : next_last;
                    que.push_back(cur->left);  // 从后面入
                }
                if (cur->right) {
                    // 更新 next_last 
                    next_last = next_last == nullptr ? cur->right : next_last;
                    que.push_back(cur->right);
                }
            } else {  // 从右至左
                cur = que.back();  // 从后面出
                que.pop_back();
                res[level].push_back(cur->val);
                
                if (cur->right) {
                    // 更新 next_last;
                    next_last = next_last == nullptr ? cur->right : next_last;
                    que.push_front(cur->right);  // 从前面入
                }
                if (cur->left) {
                    // 更新 next_last
                    next_last = next_last == nullptr ? cur->left : next_last;
                    que.push_front(cur->left);
                }
            }

            if (cur == last && !que.empty()) {  // 到达一行的末尾，需要进行某些切换
                left_to_right = !left_to_right;  // 切换方向
                last = next_last;  // 更新末尾的指针
                next_last = nullptr;  // 置空，以便下次更新
                res.push_back({});  // 新增一行
                ++level;  // 层数加 
            }
        }
        
        return res;
    }
};
````

