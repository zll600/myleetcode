# [1130. Minimum Cost Tree From Leaf Values](https://leetcode-cn.com/problems/minimum-cost-tree-from-leaf-values/)

## 题目

Given an array `arr` of positive integers, consider all binary trees such that:

- Each node has either `0` or `2` children;
- The values of `arr` correspond to the values of each **leaf** in an in-order traversal of the tree.
- The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree, respectively.

Among all possible binary trees considered, return *the smallest possible sum of the values of each non-leaf node*. It is guaranteed this sum fits into a **32-bit** integer.

A node is a **leaf** if and only if it has zero children.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/08/10/tree1.jpg)

```
Input: arr = [6,2,4]
Output: 32
Explanation: There are two possible trees shown.
The first has a non-leaf node sum 36, and the second has non-leaf node sum 32.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/08/10/tree2.jpg)

```
Input: arr = [4,11]
Output: 44
```

 

**Constraints:**

- `2 <= arr.length <= 40`
- `1 <= arr[i] <= 15`
- It is guaranteed that the answer fits into a **32-bit** signed integer (i.e., it is less than 231).
- 

## 题目大意

给你一个正整数数组 `arr`，考虑所有满足以下条件的二叉树：

- 每个节点都有 `0` 个或是 `2` 个子节点。
- 数组 `arr` 中的值与树的中序遍历中每个叶节点的值一一对应。（知识回顾：如果一个节点有 0 个子节点，那么该节点为叶节点。）
- 每个非叶节点的值等于其左子树和右子树中叶节点的最大值的乘积。

在所有这样的二叉树中，返回每个非叶节点的值的最小可能总和。这个和的值是一个 32 位整数。

## 解题思路

### Solution 1: Stack

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/minimum-cost-tree-from-leaf-values/solution/wei-shi-yao-dan-diao-di-jian-zhan-de-suan-fa-ke-xi/)


````c++
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        stack<int> sta;
        sta.push(INT_MAX);

        int mct = 0;
        for (int num : arr) {
            while (num >= sta.top()) {
                int peek = sta.top();
                sta.pop();
                mct += peek * min(sta.top(), num);
            }
            sta.push(num);
        }

        while (sta.size() > 2) {
            int peek = sta.top();
            sta.pop();
            mct += peek * sta.top();
        }

        return mct;
    }
};
````

