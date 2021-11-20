# [95. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/)

## 题目

Given an integer `n`, return *all the structurally unique **BST'**s (binary search trees), which has exactly* `n` *nodes of unique values from* `1` *to* `n`. Return the answer in **any order**.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/18/uniquebstn3.jpg)

```
Input: n = 3
Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
```

**Example 2:**

```
Input: n = 1
Output: [[1]]
```

 

**Constraints:**

- `1 <= n <= 8`

## 题目大意

给定一个整数 n，生成所有 1.... n 的数字组成的唯一的二叉树，

## 解题思路

这道题目有两个子问题：

* 以每个值作为每棵树的根节点
* 构建每棵树

所以如果利用递归求解的话，需要解决这两个问题，

### Solution 1:

这种解法的可以参考霜神的这篇题解：https://books.halfrost.com/leetcode/ChapterFour/0001~0099/0095.Unique-Binary-Search-Trees-II/

具体做法是外层循环枚举每棵树包括子树的根节点，内层递归求解左右子树部分，然后利用组合的方式，构建子树

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
    vector<TreeNode*> generateTrees(int n) {
        return GenerateTrees(1, n);
    }
    
 private:    
    vector<TreeNode*> GenerateTrees(int lo, int hi) {
        vector<TreeNode*> trees;
        
        if (lo > hi) {  // 递归基，终止条件
            trees.push_back(nullptr);
            return trees;
        }
        
        // 外层循环以每个值为根节点构建 BST
        for (int i = lo; i <= hi; ++i) {
            // 先递归的构建左子树部分
            vector<TreeNode*> left_parts = GenerateTrees(lo, i - 1);
            // 再递归的构建右子树部分
            vector<TreeNode*> right_parts = GenerateTrees(i + 1, hi);
            
            // 左右子树的所有组合可以构成一棵完整的 BST
            for (TreeNode* left_part : left_parts) {
                for (TreeNode* right_part : right_parts) {
                    TreeNode *root = new TreeNode(i, left_part, right_part);
                    trees.push_back(root);
                }
            }
        }
        
        return trees;
    }
};
````

