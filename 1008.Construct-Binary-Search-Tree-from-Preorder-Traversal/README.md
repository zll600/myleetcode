# [1008. Construct Binary Search Tree from Preorder Traversal](https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/)

## 题目

Given an array of integers preorder, which represents the **preorder traversal** of a BST (i.e., **binary search tree**), construct the tree and return *its root*.

It is **guaranteed** that there is always possible to find a binary search tree with the given requirements for the given test cases.

A **binary search tree** is a binary tree where for every node, any descendant of `Node.left` has a value **strictly less than** `Node.val`, and any descendant of `Node.right` has a value **strictly greater than** `Node.val`.

A **preorder traversal** of a binary tree displays the value of the node first, then traverses `Node.left`, then traverses `Node.right`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/03/06/1266.png)

```
Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]
```

**Example 2:**

```
Input: preorder = [1,3]
Output: [1,null,3]
```

 

**Constraints:**

- `1 <= preorder.length <= 100`
- `1 <= preorder[i] <= 1000`
- All the values of `preorder` are **unique**.

##  题目大意

给定一个二叉搜索数的前序遍历序列，构建这棵树，然后返回其根节点，

题目保证，对于给定的测试用例，总能找到满足要求的二叉搜索树。

一个二叉搜索树的左节点严格小于

(回想一下，二叉搜索树是二叉树的一种，其每个节点都满足以下规则，对于 `node.left `的任何后代，值总 `< node.val`，而 `node.right `的任何后代，值总 > `node.val`。此外，前序遍历首先显示节点 `node` 的值，然后遍历` node.left`，接着遍历 `node.right`。）

## 解题思路

这道题目的解法可以参考这篇题解：https://leetcode-cn.com/problems/construct-binary-search-tree-from-preorder-traversal/solution/javadai-ma-de-5chong-jie-ti-si-lu-by-sdwwld/

### 解法1（插入法）

遍历数组中的每个元素，将所有的元素插入进树中

先放上递归版本

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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        TreeNode *root = new TreeNode(preorder[0]);
        const int size = preorder.size();
        for (int i = 1; i < size; ++i) {  // 遍历数组，将每一个元素插入数组中
            AddNode(root, preorder[i]);
        }
        
        return root;
    }
    
 private:
    TreeNode* AddNode(TreeNode *root, int val) {
        if (root == nullptr) {  // 如果为空，构造节点
            return new TreeNode(val);
        } else if (val < root->val) {  // 向左插入
            root->left = AddNode(root->left, val);
        } else {  // 向右插入
            root->right = AddNode(root->right, val);
        }
        return root;
    }
};
````

#### 插入法非递归版

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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        TreeNode *root = new TreeNode(preorder[0]);
        const int size = preorder.size();
        for (int i = 1; i < size; ++i) {  // 遍历数组，将每一个元素插入数组中
            AddNode(root, preorder[i]);
        }
        
        return root;
    }
    
 private:
    void AddNode(TreeNode *root, int val) {
        TreeNode *node = new TreeNode(val);
        
        while (true) {
            if (val < root->val) {  // 向左找
                if (root->left == nullptr) {  // 找到位置就插入
                    root->left = node;
                    break;
                } else {  // 可以继续向左
                    root = root->left;
                }
            }
            
            if (val > root->val) {  // 向右找
                if (root->right == nullptr) {  // 找到位置就插入
                    root->right = node;
                    break;
                } else {  // 可以继续向右找
                    root = root->right;
                }
            }
        }
    }
};
`````

### 解法2（二分）

先序遍历数组的第一个元素，就相当于是新的中间节点，用这个中间节点的值来划分数组，分别递归构建左子树和右子树，需要注意的点已经写在代码中了

注意这里我用了左闭右闭区间

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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return BuildBST(preorder, 0, preorder.size() - 1);
    }
    
 private:
    // 切分后对应的范围是 [start, last] 左闭右闭
    TreeNode* BuildBST(const vector<int>& preorder, int left, int right) {
        if (left > right) {  // 递归终止
            return nullptr;
        }
        
        // 建立中间节点
        TreeNode *root = new TreeNode(preorder[left]);
        if (left == right) {  // 如果只剩一个节点，插入完成后立刻返回
            return root;
        }
        
        // 找到大于中间节点的第一个值，用来划分区间
        int i = left;
        while (i + 1 <= right && preorder[i + 1] < preorder[left]) {
            ++i;
        }
        
        root->left = BuildBST(preorder, left + 1, i);
        root->right = BuildBST(preorder, i + 1, right);
        
        return root;
    }
};
````

### 解法3（先序遍历）

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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        // 求出数组中的最大元素，也就是最右侧的节点
        auto it = max_element(preorder.begin(), preorder.end());
        // 记录构建到第几个节点了
        int index = 0;
        return BSTFromPreorder(preorder, index, *it);
    }
    
 private:
    TreeNode* BSTFromPreorder(const vector<int>& preorder, int& index, int max_val) {
        // 第二个判断条件不能省略，否则在递归的逻辑中不好处理左右子树的划分
        if (index == preorder.size() || preorder[index] > max_val) {
            return nullptr;
        }
        
        // 取出数组的第一个元素构造中间节点
        TreeNode *root = new TreeNode(preorder[index++]);
        // 左侧节点不能大于 root->val 
        root->left = BSTFromPreorder(preorder, index, root->val);
        // 右侧节点不能 max_val
        root->right = BSTFromPreorder(preorder, index, max_val);
        
        return root;
    }
};c
`````

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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        stack<TreeNode*> sta;
        TreeNode *root = new TreeNode(preorder[0]);
        sta.push(root);
        
        const int size = preorder.size();
        for (int i = 1; i < size; ++i) {
            TreeNode *node = new TreeNode(preorder[i]);
            // 保存栈顶元素，后面元素可能是其左节点或者右节点
            TreeNode *parent = sta.top();
            
            // 如果栈顶元素大于当前元素，
            if (preorder[i] < parent->val) {
                parent->left = node;  // 当前元素作为栈顶元素的左子树
            } else {
                // 如果栈顶元素小于当前元素，则一直出栈，直到栈空或者栈顶元素大于当前元素，
                // 则当前节点就是上一个出栈节点的右子树
                while (!sta.empty() && preorder[i] > sta.top()->val) {
                    parent = sta.top();
                    sta.pop();
                }
                parent->right = node;
            }
            
            // 入栈
            sta.push(node);
        }
        
        return root;
    }
};
`````

