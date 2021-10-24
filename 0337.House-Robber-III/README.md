# [337. House Robber III](https://leetcode.com/problems/house-robber-iii/)

## 题目

The thief has found himself a new place for his thievery again. There is only one entrance to this area, called `root`.

Besides the `root`, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if **two directly-linked houses were broken into on the same night**.

Given the `root` of the binary tree, return *the maximum amount of money the thief can rob **without alerting the police***.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/10/rob1-tree.jpg)

```
Input: root = [3,2,3,null,3,null,1]
Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/03/10/rob2-tree.jpg)

```
Input: root = [3,4,5,1,3,null,1]
Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 104]`.
- `0 <= Node.val <= 104`

## 题目大意

个新的可行窃的地区只有一个入口，称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

## 解题思路

这道题可以和第 198 题、第 213 题一起类别来做，

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/house-robber-iii/solution/san-chong-fang-fa-jie-jue-shu-xing-dong-tai-gui-hu/

### Solution 1:

这中解法的具体思路就是利用 DFS来做，现递归的求出左右子树的结果，然后比较得出当前节点的结果

对于每一个节点，状态转移如下：

* 如果选当前节点，那么子节点就一定不能选
* 如果不选当前节点，那么取子节点选或者不选的最大值

```c++
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
    int rob(TreeNode* root) {
        pair<int, int> item = Robtree(root);
        return max(item.first, item.second);
    }
    
 private:
    pair<int, int> Robtree(TreeNode *root) {
        if (root == nullptr) {
            return pair<int, int>(0, 0);
        }
        
        pair<int, int> left_res = Robtree(root->left);
        pair<int, int> right_res = Robtree(root->right);
        
        // first 表示不选当前节点
        int first = max(left_res.first, left_res.second) + max(right_res.first, right_res.second);
        // second 表示选当前节点
        int second = root->val + left_res.first + right_res.first;
        
        return pair<int, int>(first, second);
    }
};
```

