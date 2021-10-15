# [114. Flatten Binary Tree to Linked List](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/)

Given the `root` of a binary tree, flatten the tree into a "linked list":

- The "linked list" should use the same `TreeNode` class where the `right` child pointer points to the next node in the list and the `left` child pointer is always `null`.
- The "linked list" should be in the same order as a [**pre-order** **traversal**](https://en.wikipedia.org/wiki/Tree_traversal#Pre-order,_NLR) of the binary tree.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/14/flaten.jpg)

```
Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]
```

**Example 2:**

```
Input: root = []
Output: []
```

**Example 3:**

```
Input: root = [0]
Output: [0]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 2000]`.
- `-100 <= Node.val <= 100`

 

**Follow up:** Can you flatten the tree in-place (with `O(1)` extra space)?

## 题目大意

给定一个二叉树的根节点，将这个二叉树展开为 链表

* 在这个链表中应该继续使用 `TreeNode` ，其右孩子节点指向链表中的下一个位置，左还是为空
* 链表应该按照前序遍历的顺序来构造



进阶要求：你能只使用O(1) 的空间吗

## 解题思路

这道题的所有解法，都强烈建议自己动手取模拟以下，就会比较好理解

### 解法1（队列）

这种解法使用一个队列缓存前序遍历的结果，然后清空队列，这里要注意的是，需要将每个节点的左节点置空

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
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        PreOrder(root);
        
        TreeNode *cur = que_.front();
        que_.pop();
        cur->left = nullptr;  // 这里要将左节点置空
        while (!que_.empty()) {
            TreeNode *node = que_.front();
            que_.pop();
            node->left = nullptr;  // 置空左节点
            cur->right = node;
            cur = node;
        }
    }
    
 private:
    queue<TreeNode*> que_;
   
    void PreOrder(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        que_.push(root);
        PreOrder(root->left);
        PreOrder(root->right);
    }
};
````

### 解法2（原地修改）

这个解法参考霜神的题解

先写递归版，这里按照**右左中**的顺序遍历二叉树，在遍历的过程中让每个节点的右节点指向前一个元素，左节点指向后一个元素

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
    Solution() : prev_(nullptr) {}
    
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        
        flatten(root->right);
        flatten(root->left);
        root->right = prev_;
        root->left = nullptr;
        prev_ = root;
    }
    
 private:
   TreeNode *prev_;
};
`````

### 解法3（原地修改）

以下两种解法参考这篇题解：https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/solution/biao-biao-zhun-zhun-de-hou-xu-bian-li-dai-ma-jian-/

这里使用的后序遍历，遍历完左右子树之后，然后修改左右子树，相当于从下至上依次将左子树插入到右子树中，这里需要注意的是：

* 将找到的最右侧节点的左节点要置为空
* 将中间节点更改之后，左节点要置为空

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
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        
        // 先遍历完左右子树，然后改边节点的指向
        flatten(root->left);
        flatten(root->right);
        if (root->left != nullptr) {  // 如果左不为空的话
            TreeNode *cur = root->left;
            while (cur->right != nullptr) {  // 找到左子树中最右侧的节点，
                cur = cur->right;
            }
            cur->right = root->right;
            cur->left = nullptr;
            root->right = root->left;
            root->left = nullptr;
        }
    }
};
````

### 解法4

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
    void flatten(TreeNode* root) {
        while (root != nullptr) {
            if (root->left != nullptr) {  // 如果左边不为空
                // 找到左子树中最右侧的节点，中序遍历时其下一个节点将是链表要链接的节点
                TreeNode *most_right = root->left;  
                while (most_right->right != nullptr) {
                    most_right = most_right->right;
                }
                most_right->right = root->right;  // 将最右侧节点的右节点指向当前根节点的右子树
                root->right = root->left;  // 更改根节点
                root->left = nullptr;  // 置空
            }
            root = root->right;  // 继续下一个
        }
    }
};
`````

