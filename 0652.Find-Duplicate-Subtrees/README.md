# [652. Find Duplicate Subtrees](https://leetcode-cn.com/problems/find-duplicate-subtrees/)

## 题目

Given the `root` of a binary tree, return all **duplicate subtrees**.

For each kind of duplicate subtrees, you only need to return the root node of any **one** of them.

Two trees are **duplicate** if they have the **same structure** with the **same node values**.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/08/16/e1.jpg)

```
Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/08/16/e2.jpg)

```
Input: root = [2,1,1]
Output: [[1]]
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2020/08/16/e33.jpg)

```
Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]
```

 

**Constraints:**

- The number of the nodes in the tree will be in the range `[1, 10^4]`
- `-200 <= Node.val <= 200`

## 题目大意 

给定一个二叉树的根节点，返回所有重复的子树，

对每一种重复的子树，你只需要返回他们中的任意一个根节点即可，

如果两棵树具有同样的结构和同样的节点值，则它们是重复的，

## 解题思路

这道题目的关键在于二叉树的序列化可以唯一的表示一棵树，所以我们要判断两棵树是否相同，可以判断两棵树序列化后的字符串是否相同，

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/find-duplicate-subtrees/solution/cji-hu-shuang-bai-de-shen-du-you-xian-ji-9a82/)

这种解法利用一个二叉树序列化后的字符串和全局唯一编号的映射来加速查重，

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
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        DFS(root);

        return res_;
    }

 private:
    // 最终的结果
    vector<TreeNode*> res_;
    // 字符串 -> 唯一的编号
    unordered_map<string, int> str_to_index_;
    // 维护一个全局的编号，这里需要从 1 开始，否则可能会出问题
    int index_ = 1;
    vector<int> index_cnt_ = vector<int>(50000);

    int DFS(TreeNode *cur) {
        // 空节点直接返回 0
        if (!cur) {
            return 0;
        }

        // 构建字符串
        string cur_str = to_string(cur->val) + ","
            + to_string(DFS(cur->left)) + "," + to_string(DFS(cur->right));
        // 如果没存在，赋予新的唯一编号
        if (str_to_index_.find(cur_str) == str_to_index_.end()) {
            str_to_index_[cur_str] = index_;
            ++index_;
        }

        // 读取编号，更新编号出现的次数
        int index = str_to_index_[cur_str];
        ++index_cnt_[index];

        // 如果次数等于 2 次，那么就可以加入到结果集中
        if (index_cnt_[index] == 2) {
            res_.push_back(cur);
        }

        return index;
    }
};
````
