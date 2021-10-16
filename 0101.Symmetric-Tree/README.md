# [101. Symmetric Tree](https://leetcode.com/problems/symmetric-tree/)

## 题目

Given the `root` of a binary tree, *check whether it is a mirror of itself* (i.e., symmetric around its center).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/symtree1.jpg)

```
Input: root = [1,2,2,3,4,4,3]
Output: true
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/02/19/symtree2.jpg)

```
Input: root = [1,2,2,null,3,null,3]
Output: false
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 1000]`.
- `-100 <= Node.val <= 100`

 

**Follow up:** Could you solve it both recursively and iteratively?

## 题目大意

给定一个二叉树的根节点，检查其是否是镜像对称

**进阶要求**：使用递归和迭代来解决

## 解题思路

这道题目我的做法是将检查一棵树转化为检查两棵树

### Solution 1:Recursive

递归遍历左子树和右子树

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
    bool isSymmetric(TreeNode *root) {
        // 将一棵树的左右子树是否对称转化为两棵树
        return IsSymmetric(root->left, root->right);
    }
    
 private:
    bool IsSymmetric(TreeNode *p, TreeNode *q) {
        // 二者都为空
        if (!q && !p) {
            return true;
        }
        // 其中之一为空
        if (!p || !q) {
            return false;
        }
        
        // cout << p->val << "-----" << q->val << endl;
        if (p->val != q->val) {
            return false;
        }
        
        // 递归比较两棵树
        // 注意这里的递归顺序
        return IsSymmetric(p->left, q->right)
            && IsSymmetric(p->right, q->left);
    }
};
````

### Solution2: Iterative

使用栈来做迭代遍历

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
    bool isSymmetric(TreeNode *root) {
        // 将一棵树的左右子树是否对称转化为两棵树
        return IsSymmetric(root->left, root->right);
    }
    
 private:
    bool IsSame(TreeNode *p, TreeNode *q) {
        if (!q && !p) {
            return true;
        }
        if (!q || !p) {
            return false;
        }
        if (p->val != q->val) {
            return false;
        }
        
        return true;
    }
    
    bool IsSymmetric(TreeNode *p, TreeNode *q) {
        if (!IsSame(p, q)) {
            return false;
        }
        
        // p 树的遍历
        stack<TreeNode*> sta_p;
        sta_p.push(p);
        // q 树的遍历
        stack<TreeNode*> sta_q;
        sta_q.push(q);
        
        // 任意一个栈空就终止循环
        while (!sta_p.empty() && !sta_q.empty()) {
            TreeNode *cur_p = sta_p.top();
            sta_p.pop();
            TreeNode *cur_q = sta_q.top();
            sta_q.pop();
            
            if (!IsSame(cur_p, cur_q)) {
                return false;
            }
            
            // 如果两个都为空，则跳过添加节点的部分
            if (!cur_p && !cur_q) {
                continue;
            }
            
            // 添加 p 树节点
            sta_p.push(cur_p->right);
            sta_p.push(cur_p->left);
            
            // 添加 q 树节点
            sta_q.push(cur_q->left);
            sta_q.push(cur_q->right);
        }
        
        return sta_p.empty() && sta_q.empty();
    }
};
````

### Solution3: Iterative

这种解法可以参考这篇题解中的图:https://leetcode-cn.com/problems/symmetric-tree/solution/dong-hua-yan-shi-101-dui-cheng-er-cha-shu-by-user7/

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
    bool isSymmetric(TreeNode *root) {
        if (!IsSame(root->left, root->right)) {
            return false;
        }
        
        queue<TreeNode*> que;
        que.push(root->left);
        que.push(root->right);
        
        while (!que.empty()) {
            TreeNode *left_cur = que.front();
            que.pop();
            TreeNode *right_cur = que.front();
            que.pop();
            
            if (!IsSame(left_cur, right_cur)) {
                return false;
            }
            
            if (!left_cur && !right_cur) {
                continue;
            }
            
            // 左节点的左孩子和右节点的右孩子
            que.push(left_cur->left);
            que.push(right_cur->right);
            
            // 左节点的右孩子和右节点的左孩子
            que.push(left_cur->right);
            que.push(right_cur->left);
        }
        
        return true;
    }
    
 private:
    bool IsSame(TreeNode *p, TreeNode *q) {
        if (!q && !p) {
            return true;
        }
        if (!q || !p) {
            return false;
        }
        return p->val == q->val;
    }
};
````

