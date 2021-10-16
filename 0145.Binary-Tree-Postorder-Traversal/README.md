# [145. Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/)

## 题目

Given the `root` of a binary tree, return *the postorder traversal of its nodes' values*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/08/28/pre1.jpg)

```
Input: root = [1,null,2,3]
Output: [3,2,1]
```

**Example 2:**

```
Input: root = []
Output: []
```

**Example 3:**

```
Input: root = [1]
Output: [1]
```

**Example 4:**

![img](https://assets.leetcode.com/uploads/2020/08/28/pre3.jpg)

```
Input: root = [1,2]
Output: [2,1]
```

**Example 5:**

![img](https://assets.leetcode.com/uploads/2020/08/28/pre2.jpg)

```
Input: root = [1,null,2]
Output: [2,1]
```

 

**Constraints:**

- The number of the nodes in the tree is in the range `[0, 100]`.
- `-100 <= Node.val <= 100`

 

**Follow up:** Recursive solution is trivial, could you do it iteratively?

### 题目大意

二叉树的后序遍历



**进阶要求**：使用迭代而不是递归

## 解题思路

### 解法1（递归）

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
    vector<int> postorderTraversal(TreeNode *root) {
        if (root == nullptr) {
            return vector<int>();
        }
        
        vector<int> res;
        PostorderTraversal(root, res);
        return res;
    }
    
 private:
    void PostorderTraversal(TreeNode *root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        PostorderTraversal(root->left, res);
        PostorderTraversal(root->right, res);
        
        res.push_back(root->val);
    } 
};
`````

### 解法2（递归）

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
    vector<int> postorderTraversal(TreeNode *root) {
        if (root == nullptr) {
            return vector<int>();
        }
        
        vector<int> res;
        const vector<int> left = postorderTraversal(root->left);
        const vector<int> right = postorderTraversal(root->right);
        res.insert(res.end(), left.begin(), left.end());
        res.insert(res.end(), right.begin(), right.end());
        res.push_back(root->val);
        return res;
    }
};
`````

### 解法3（迭代）

利用双向队列，也可以使用一个将“中左右”改为 “右左中”，

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
    vector<int> postorderTraversal(TreeNode *root) {
        if (root == nullptr) {
            return vector<int>();
        }
        deque<int> res;
        stack<TreeNode*> sta;
        sta.push(root);
        
        while (!sta.empty()) {
            TreeNode *cur = sta.top();
            sta.pop();
            res.push_front(cur->val);
            
            if (cur->left) {
                sta.push(cur->left);
            }
            if (cur->right) {
                sta.push(cur->right);
            }
        }
        
        return vector<int>(res.begin(), res.end());        
    }
};
`````

### 解法4（迭代）

这种解法的思路可以参考这篇题解：https://leetcode-cn.com/problems/binary-tree-postorder-traversal/solution/fei-di-gui-hou-xu-guan-jian-jie-ti-si-lu-cru8/

使用一个栈，这里多用一个指针表示刚才遍历的位置，如果刚才遍历的是右子树，接下来应该遍历中间节点，否则转向右子树，且不能弹出当前栈顶

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
    vector<int> postorderTraversal(TreeNode *root) {
        if (root == nullptr) {
            return vector<int>();
        }
        TreeNode *cur = root;
        TreeNode *prev = nullptr;
        stack<TreeNode*> sta;
        vector<int> res;
        
        while (!sta.empty() || cur) {
            while (cur) {
                sta.push(cur);
                cur = cur->left;
            }
            cur = sta.top();
            if (cur->right == nullptr || cur->right == prev) {
                res.push_back(cur->val);
                sta.pop();
                prev = cur;
                cur = nullptr;
            } else {
                cur = cur->right;
            }
        }
        
        return res;
    }
};
`````

