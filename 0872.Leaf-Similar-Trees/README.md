# [872. Leaf-Similar Trees](https://leetcode.com/problems/leaf-similar-trees/)

## 题目

Consider all the leaves of a binary tree, from left to right order, the values of those leaves form a **leaf value sequence***.*

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/16/tree.png)

For example, in the given tree above, the leaf value sequence is `(6, 7, 4, 9, 8)`.

Two binary trees are considered *leaf-similar* if their leaf value sequence is the same.

Return `true` if and only if the two given trees with head nodes `root1` and `root2` are leaf-similar.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/03/leaf-similar-1.jpg)

```
Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
Output: true
```

**Example 2:**

```
Input: root1 = [1], root2 = [1]
Output: true
```

**Example 3:**

```
Input: root1 = [1], root2 = [2]
Output: false
```

**Example 4:**

```
Input: root1 = [1,2], root2 = [2,2]
Output: true
```

**Example 5:**

![img](https://assets.leetcode.com/uploads/2020/09/03/leaf-similar-2.jpg)

```
Input: root1 = [1,2,3], root2 = [1,3,2]
Output: false
```

 

**Constraints:**

- The number of nodes in each tree will be in the range `[1, 200]`.
- Both of the given trees will have values in the range `[0, 200]`.

## 题目大意

给定两棵树，从左到右的叶子节点形成一个叶子序列，如果两棵树的叶子节点使相同的，就认为这两棵树是叶子相似的。

当且仅当两棵树是叶子相似的时候返回 true，

## 解题思路

* 这道题目不难，用前序遍历（因为叶子序列是从左至右），记录所有出现过的叶子节点，最后比较即可

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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> arr1;
        vector<int> arr2;
        
        DFS(root1, arr1);
        DFS(root2, arr2);
        
        if (arr1.size() != arr2.size()) {
            return false;
        }
        
        for (int i = 0; i < arr1.size(); ++i) {
            if (arr1[i] != arr2[i]) {
                return false;
            }
        }
        
        return true;
    }
    
 private:
   
    void DFS(TreeNode *root, vector<int>& arr) {
        if (root ==  nullptr) {
            return;
        }
        
        if (root->left == nullptr && root->right == nullptr) {
            arr.push_back(root->val);
        }
        
        DFS(root->left, arr);
        DFS(root->right, arr);
    }
};
````

