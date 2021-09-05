# [993. Cousins in Binary Tree](https://leetcode.com/problems/cousins-in-binary-tree/)

Given the `root` of a binary tree with unique values and the values of two different nodes of the tree `x` and `y`, return `true` *if the nodes corresponding to the values* `x` *and* `y` *in the tree are **cousins**, or* `false` *otherwise.*

Two nodes of a binary tree are **cousins** if they have the same depth with different parents.

Note that in a binary tree, the root node is at the depth `0`, and children of each depth `k` node are at the depth `k + 1`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/02/12/q1248-01.png)

```
Input: root = [1,2,3,4], x = 4, y = 3
Output: false
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/02/12/q1248-02.png)

```
Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2019/02/13/q1248-03.png)

```
Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[2, 100]`.
- `1 <= Node.val <= 100`
- Each node has a **unique** value.
- `x != y`
- `x` and `y` are exist in the tree.

## 题目大意

给出一个二叉树 root ，和树中的两个节点 x 和y，如果 x 和 y 是堂兄弟节点，就返回 true ，否则就返回 false，

两个节点是堂兄弟节点需要满足：

* 两个节点的深度相同，但父亲节点不同

根节点的深度是 0，每个深度为 k 的节点的子节点的深度为 k + 1，

## 解题思路

* DFS 深搜，在深搜的过程中，找到 parent 和 depth，最后比较两个节点的 父节点 和 深度是否满足要求
* BFS 广搜，在广搜的同时，用 map 作记录，搜索结束后查看
* 递归：反别使两个条件满足。

## 代码

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
    // 解法一：使用 DFS，前序遍历 + 记录
    /*
    bool isCousins(TreeNode* root, int x, int y) {
        int depth1, depth2;
        int parent1, parent2;
        
        DFS(root, x, 0, -1, &parent1, &depth1);
        DFS(root, y, 0, -1, &parent2, &depth2);
        
        return depth1 > 1 && depth1 == depth2 && parent1 != parent2;
    }*/
    
    // 解法二：使用 BFS，用一个pair 记录状态变化
    /*
    bool isCousins(TreeNode *root, int x, int y) {
        if (root == nullptr) {
            return false;
        }
        
        unordered_map<int, pair<int, int>> visit;
        visit.insert(make_pair(root->val, make_pair(-1, 0)));
        
        queue<TreeNode*> que;
        que.push(root);
        
        while (!que.empty()) {
            TreeNode *cur = que.front();
            que.pop();
            
            int depth = visit[cur->val].second;
            
            if (cur->left != nullptr) {
                visit.insert(make_pair(cur->left->val, make_pair(cur->val, depth + 1)));
                que.push(cur->left);
            }
            if (cur->right != nullptr) {
                visit.insert(make_pair(cur->right->val, make_pair(cur->val, depth + 1)));
                que.push(cur->right);
            }
        }
        
        if (visit.count(x) == 0 || visit.count(y) == 0) {
            return false;
        }
        
        return visit[x].first != visit[y].first && visit[x].second == visit[y].second;
    }
    */
    
    // 解法三：使用递归，分别查看能否使两个条件满足
    bool isCousins(TreeNode *root, int x, int y) {
        if (root == nullptr) {
            return false;
        }
        
        int levelx = FindLevel(root, x, 0);
        int levely = FindLevel(root, y, 0);
        
        if (levelx != levely) {
            return false;
        }
        
        return !HasSameParent(root, x, y);
    }
    
    
 private:
    void DFS(TreeNode *root, int target, int depth, int last, int *parent, int *res) {
        if (root == nullptr) {
            return;
        }
        
        if (root->val == target) {
            *res = depth;
            *parent = last;
            return;     // 找到之后就返回，不再进行便利
        }
        ++depth;
        
        DFS(root->left, target, depth, root->val, parent, res);
        DFS(root->right, target, depth, root->val, parent, res);
    }
    
    int FindLevel(TreeNode *root, int target, int level) {
        if (root == nullptr) {
            return 0;
        }
        
        if (root->val != target) {
            int left_level = FindLevel(root->left, target, level + 1);
            int right_level = FindLevel(root->right, target, level + 1);
            
            if (left_level == 0) {
                return right_level;
            }
            return left_level;
        }
        return level;
    }
    
    bool HasSameParent(TreeNode *root, int x, int y) {
        if (root == nullptr) {
            return false;
        }
        
        if ((root->left != nullptr && root->right != nullptr
             && root->left->val == x && root->right->val == y)
           || (root->left != nullptr && root->right != nullptr
               && root->left->val == y && root->right->val == x)) {
            return true;
        }
        
        return HasSameParent(root->left, x, y) || HasSameParent(root->right, x, y);
    }
};
````

