# [987. Vertical Order Traversal of a Binary Tree](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/)

## 题目

Given the `root` of a binary tree, calculate the **vertical order traversal** of the binary tree.

For each node at position `(row, col)`, its left and right children will be at positions `(row + 1, col - 1)` and `(row + 1, col + 1)` respectively. The root of the tree is at `(0, 0)`.

The **vertical order traversal** of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.

Return *the **vertical order traversal** of the binary tree*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/29/vtree1.jpg)

```
Input: root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Explanation:
Column -1: Only node 9 is in this column.
Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
Column 1: Only node 20 is in this column.
Column 2: Only node 7 is in this column.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/01/29/vtree2.jpg)

```
Input: root = [1,2,3,4,5,6,7]
Output: [[4],[2],[1,5,6],[3],[7]]
Explanation:
Column -2: Only node 4 is in this column.
Column -1: Only node 2 is in this column.
Column 0: Nodes 1, 5, and 6 are in this column.
          1 is at the top, so it comes first.
          5 and 6 are at the same position (2, 0), so we order them by their value, 5 before 6.
Column 1: Only node 3 is in this column.
Column 2: Only node 7 is in this column.
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/01/29/vtree3.jpg)

```
Input: root = [1,2,3,4,6,5,7]
Output: [[4],[2],[1,5,6],[3],[7]]
Explanation:
This case is the exact same as example 2, but with nodes 5 and 6 swapped.
Note that the solution remains the same since 5 and 6 are in the same location and should be ordered by their values.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 1000]`.
- `0 <= Node.val <= 1000`

## 题目大意

给定一个树节点计算计算树的垂序遍历，对于每一个节点(row, col)，左右节点分别是(row + 1，col - 1)，右节点是(row + 1, col + 1)，树的根节点是(0, 0)，二叉树的垂序遍历，从左到右按列索引每一列，形成一个从上到下的列表，如果在同行同列上有多个节点，从小到大排序，

返回二叉树的垂序遍历

## 解题思路

这道题目要求按列来求：列号从小到大，同列，行号从小到大，同列同行，按照值的大小从小到大

Solution1: 

这里的解法参考了这篇题解：https://zxi.mytechroad.com/blog/tree/leetcode-987-vertical-order-traversal-of-a-binary-tree/

这篇题解的中的代码已经不能通过了，因为如果同行同列出现同样大小的值 set 只能保留一个，因此这里必须使用 multiset 来代替，

这里的思路是，用一个映射表示位置和值之间的关系，又因为题目要求有序，所以这里利用了 map 和 multiset 的有序性，

为了确定最终数组的大小，这里使用了两个值来维护遍历时行坐标的上界和下界（这两个值要在整个遍历过程中更新，因此应该传引用），



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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        int min_x = INT_MAX;  // 横坐标的下限
        int max_x = INT_MIN;  // 横坐标的上限
        
        // 这里的值是有可能重复的，所以这里用 multiset
        map<pair<int, int>, multiset<int>> hash;  // {y, x} -> {val}
        // 遍历树，添加结果
        Traversal(root, hash, 0, 0, min_x, max_x);
        vector<vector<int>> res(max_x - min_x + 1);
        // 遍历结果集中的所有元素，添加到对应的数组中
        for (const auto& it : hash) {
            int x = it.first.second - min_x;
            res[x].insert(end(res[x]), begin(it.second), end(it.second));
        }
        
        return res;
    }
    
 private:
    // 这里采用的是中序遍历
    void Traversal(TreeNode *root, map<pair<int, int>, multiset<int>>& hash, 
                  int x, int y, int& min_x, int& max_x) {
        if (!root) {
            return;
        }
        
        min_x = min(min_x, x);  // 维护 x 的下限
        max_x = max(max_x, x);  // 维护 x 的上限
        hash[{y, x}].insert(root->val);  // 插入到对应的结果集中
        // 遍历左子树
        Traversal(root->left, hash, x - 1, y + 1, min_x, max_x);
        // 遍历右子树
        Traversal(root->right, hash, x + 1, y + 1, min_x, max_x);
    }
};
````

