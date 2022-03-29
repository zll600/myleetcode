# [606. Construct String from Binary Tree](https://leetcode-cn.com/problems/construct-string-from-binary-tree/)

## 题目大意

Given the `root` of a binary tree, construct a string consisting of parenthesis and  integers from a binary tree with the preorder traversal way, and return  it.

Omit all the empty parenthesis pairs that do not affect the  one-to-one mapping relationship between the string and the original  binary tree.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/05/03/cons1-tree.jpg)

```
Input: root = [1,2,3,4]
Output: "1(2(4))(3)"
Explanation: Originally, it needs to be "1(2(4)())(3()())", but you need to omit all the unnecessary empty parenthesis pairs. And it will be "1(2(4))(3)"
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/05/03/cons2-tree.jpg)

```
Input: root = [1,2,3,null,4]
Output: "1(2()(4))(3)"
Explanation: Almost the same as the first example, except we cannot omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 104]`.
- `-1000 <= Node.val <= 1000`

## 题目大意 

给定一个二叉树的根节点，荣国前序遍历构建一个由括号和整数组成的字符串

空节点则用一对空括号 "()" 表示。而且你需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/construct-string-from-binary-tree/solution/by-ac_oier-i2sk/)

### Solution 1: Recursion


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
    string tree2str(TreeNode* root) {
        res_ = "";
        DFS(root);

        const int len = res_.size();
        return string(res_.begin() + 1, res_.begin() + len - 1);
    }

 private:
    string res_;

    void DFS(TreeNode *root) {
        res_.append(1, '(');
        res_.append(to_string(root->val));

        if (root->left) {
            // 左子树不为空，进行递归
            DFS(root->left);
        } else if (root->right) {
            // 左子树为空，但是右子树不为空
            res_.append("()");
        }

        // 右子树不为空
        if (root->right) {
            DFS(root->right);
        }

        res_.append(1, ')');
    }
};
````
