# [988. Smallest String Starting From Leaf](https://leetcode.cn/problems/smallest-string-starting-from-leaf/)

## 题目

You are given the `root` of a binary tree where each node has a value in the range `[0, 25]` representing the letters `'a'` to `'z'`.

Return *the **lexicographically smallest** string that starts at a leaf of this tree and ends at the root*.

As a reminder, any shorter prefix of a string is **lexicographically smaller**.

- For example, `"ab"` is lexicographically smaller than `"aba"`.

A leaf of a node is a node that has no children.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/01/30/tree1.png)

```
Input: root = [0,1,2,3,4,3,4]
Output: "dba"
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/01/30/tree2.png)

```
Input: root = [25,1,3,1,3,0,2]
Output: "adz"
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2019/02/01/tree3.png)

```
Input: root = [2,2,1,null,1,0,null,0]
Output: "abc"
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 8500]`.
- `0 <= Node.val <= 25`

## 题目大意

给定一颗根结点为 `root` 的二叉树，树中的每一个结点都有一个 `[0, 25]` 范围内的值，分别代表字母 `'a'` 到 `'z'`

返回 按字典序最小 的字符串，该字符串从这棵树的一个叶结点开始，到根结点结束

-   注：字符串中任何较短的前缀在 字典序上 都是 较小 的：
    
-       例如，在字典序上 "ab" 比 "aba" 要小。叶结点是指没有子结点的结点。 

节点的叶节点是没有子节点的节点

## 解题思路

### Solution 1:

这种解法的具体思路是利用前序遍历来求出字符串，然后在叶子节点处，反转当前字符串，得到从叶子节点到根节点的字符串，并更新结果字符串，

这里值得注意的地方就是不要忘记回溯

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
    string smallestFromLeaf(TreeNode* root) {
        string res = "";
        string cur = "";
        DFS(root, cur, res);
        return res;
    }
    
 private:
    void DFS(TreeNode *root, string& cur, string& res) {
        if (!root) {
            return;
        }
        
        cur += root->val + 'a';
        // cout << cur << endl;
        // 遇到叶子节点
        if (!root->left && !root->right) {
            string str = cur;
            reverse(str.begin(), str.end());
            if (res.empty() || res > str) {
                res = str;
            }
            cur.pop_back();
            return;
        }
        
        DFS(root->left, cur, res);
        DFS(root->right, cur, res);
        cur.pop_back(); 
    }
};
````

