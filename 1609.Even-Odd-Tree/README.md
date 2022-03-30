# [1609. Even Odd Tree](https://leetcode.com/problems/even-odd-tree/)

## 题目

A binary tree is named **Even-Odd** if it meets the following conditions:

- The root of the binary tree is at level index `0`, its children are at level index `1`, their children are at level index `2`, etc.
- For every **even-indexed** level, all nodes at the level have **odd** integer values in **strictly increasing** order (from left to right).
- For every **odd-indexed** level, all nodes at the level have **even** integer values in **strictly decreasing** order (from left to right).

Given the `root` of a binary tree, *return* `true` *if the binary tree is **Even-Odd**, otherwise return* `false`*.*

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/15/sample_1_1966.png)

```
Input: root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
Output: true
Explanation: The node values on each level are:
Level 0: [1]
Level 1: [10,4]
Level 2: [3,7,9]
Level 3: [12,8,6,2]
Since levels 0 and 2 are all odd and increasing and levels 1 and 3 are all even and decreasing, the tree is Even-Odd.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/09/15/sample_2_1966.png)

```
Input: root = [5,4,2,3,3,7]
Output: false
Explanation: The node values on each level are:
Level 0: [5]
Level 1: [4,2]
Level 2: [3,3,7]
Node values in level 2 must be in strictly increasing order, so the tree is not Even-Odd.
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2020/09/22/sample_1_333_1966.png)

```
Input: root = [5,9,1,3,5,7]
Output: false
Explanation: Node values in the level 1 should be even integers.
```

 

**Constraints:**


- The number of nodes in the tree is in the range `[1, 105]`.
- `1 <= Node.val <= 106`
 
## 题目大意

如果一棵二叉树满足下述几个条件，则可以称为 *奇偶树* ：

- 二叉树根节点所在层下标为 `0` ，根的子节点所在层下标为 `1` ，根的孙节点所在层下标为 `2` ，依此类推。
- 偶数下标 层上的所有节点的值都是 `奇` 整数，从左到右按顺序 *严格递增*
- 奇数下标 层上的所有节点的值都是 `偶` 整数，从左到右按顺序 *严格递减*

给你二叉树的根节点，如果二叉树为 奇偶树 ，则返回 true ，否则返回 false 。

## 解题思路

这道题目就是利用 BFS 来收集每一层的结果，然后进行判断

### Solution 1: BFS

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1600~1699/1609.Even-Odd-Tree/)

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
    bool isEvenOddTree(TreeNode* root) {
        if (!root) {
            return false;
        }

        // BFS
        queue<TreeNode*> que;
        que.push(root);
        int level = 0;

        while (!que.empty()) {
            const int len = que.size();
            vector<int> nums;
            for (int i = 0; i < len; ++i) {
                TreeNode *cur = que.front();
                que.pop();

                // 构建数组
                nums.push_back(cur->val);

                // 将左右节点加入队列中
                if (cur->left != nullptr) {
                    que.push(cur->left);
                }
                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }

            if (level % 2 == 0) {
                // 偶数层
                if (!IsEven(nums)) {
                    return false;
                }
            } else {
                // 奇数层
                if (!IsOdd(nums)) {
                    return false;
                }
            }

            ++level;
        }

        return true;
    }

 private:
    // 偶数层是否满足条件
    bool IsEven(const vector<int>& nums) {
        const int len = nums.size();
        int cur = nums[0];
        if (cur % 2 == 0) {
            return false;
        }

        for (int i = 1; i < len; ++i) {
            if (nums[i] <= nums[i - 1]) {
                return false;
            }
            if (nums[i] % 2 == 0) {
                return false;
            }
        }

        return true;
    }

    // 奇数层是否满足条件
    bool IsOdd(const vector<int>& nums) {
        const int len = nums.size();
        int cur = nums[0];
        if (cur % 2 != 0) {
            return false;
        }

        for (int i = 1; i < len; ++i) {
            if (nums[i] >= nums[i - 1]) {
                return false;
            }
            if (nums[i] % 2 != 0) {
                return false;
            }
        }

        return true;
    }
};
````
