# [655. Print Binary Tree](https://leetcode-cn.com/problems/print-binary-tree/)

## 题目

Given the `root` of a binary tree, construct a **0-indexed** `m x n` string matrix `res` that represents a **formatted layout** of the tree. The formatted layout matrix should be constructed using the following rules:

- The **height** of the tree is `height` and the number of rows `m` should be equal to `height + 1`.
- The number of columns `n` should be equal to `2height+1 - 1`.
- Place the **root node** in the **middle** of the **top row** (more formally, at location `res[0][(n-1)/2]`).
- For each node that has been placed in the matrix at position `res[r][c]`, place its **left child** at `res[r+1][c-2height-r-1]` and its **right child** at `res[r+1][c+2height-r-1]`.
- Continue this process until all the nodes in the tree have been placed.
- Any empty cells should contain the empty string `""`.

Return *the constructed matrix* `res`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/05/03/print1-tree.jpg)

```
Input: root = [1,2]
Output: 
[["","1",""],
 ["2","",""]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/05/03/print2-tree.jpg)

```
Input: root = [1,2,3,null,4]
Output: 
[["","","","1","","",""],
 ["","2","","","","3",""],
 ["","","4","","","",""]]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 210]`.
- `-99 <= Node.val <= 99`
- The depth of the tree will be in the range `[1, 10]`.

## 题目大意

在一个 `m*n` 的二维字符串数组中输出二叉树，并遵守以下规则：

- 行数 `m` 应当等于给定二叉树的高度
- 列数 `n` 应当总是奇数
- 根节点的值（以字符串格式给出）应当放在可放置的 *第一行正中间* 。根节点所在的行与列会将剩余空间划分为两部分（左下部分和右下部分）。你应该将 *左子树输出在左下部分*，*右子树输出在右下部分*。左下和右下部分应当有相同的大小。即使一个子树为空而另一个非空，你不需要为空的子树输出任何东西，但仍需要为另一个子树留出足够的空间。然而，如果两个子树都为空则不需要为它们留出任何空间
- 每个未使用的空间应包含一个空的字符串""
- 使用相同的规则输出子树

## 解题思路

### Solution 1: DFS + 分治

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/print-binary-tree/solution/shu-chu-er-cha-shu-dfsfen-zhi-by-travell-dfd3/)

这里使用 DFS 来求出树的高度，再利用分治来求出分别打印左右子树

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
    vector<vector<string>> printTree(TreeNode* root) {
        // 求出高度和宽度
        int height = GetHeight(root);
        int width = static_cast<int>(std::pow(2, height)) - 1;
        
        // 保存结果
        vector<vector<string>> res(height, vector<string>(width, ""));
        // 打印结果
        PrintTree(root, 0, width - 1, 0, res);
        
        return res;
    }
    
 private:
    // 用 DFS 来求出高度
    int GetHeight(TreeNode *root) {
        if (!root) {
            return 0;
        }
        
        int left_height = GetHeight(root->left);
        int right_height = GetHeight(root->right);
        
        return left_height > right_height ? left_height + 1 : right_height + 1;
    }
    
    // 打印树
    void PrintTree(TreeNode *root, int low, int high, int row, vector<vector<string>>& res) {
        if (!root) {
            return;
        }
        
        // 找到中间位置
        const int mid = low + (high - low) / 2;
        res[row][mid] = to_string(root->val);
        // 递归打印左子树和右子树
        PrintTree(root->left, low, mid - 1, row + 1, res);
        PrintTree(root->right, mid + 1, high, row + 1, res);
    }
};
````
