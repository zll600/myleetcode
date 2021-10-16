# [429.N-ary Tree Level Order Traversal](https://leetcode.com/problems/n-ary-tree-level-order-traversal/)

## 题目

Given an n-ary tree, return the *level order* traversal of its nodes' values.

*Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).*

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png)

```
Input: root = [1,null,3,2,4,null,5,6]
Output: [[1],[3,2,4],[5,6]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/11/08/sample_4_964.png)

```
Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]
```

 

**Constraints:**

- The height of the n-ary tree is less than or equal to `1000`
- The total number of nodes is between `[0, 104]`

## 题目大意

n 叉树的层次遍历，

## 解题思路

解题的关键在于类别二叉树，二叉树遍历每个节点的左节点和右节点两个节点，n 叉树遍历遍历每个节点的所有子节点

### Solution1（Iterative）

````c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if (root == nullptr) {
            return vector<vector<int>>();
        }
        
        vector<vector<int>> res;
        queue<Node*> que;
        que.push(root);
        int depth = 0;
        
        while (!que.empty()) {
            const int size = que.size();  // 这里取出当前层的所有节点的数目
            res.push_back({});  // 新建一行
            
            for (int i = 0; i < size; ++i) {
                Node *cur = que.front();  // 取出当前层的每一个元素
                que.pop();
                res[depth].push_back(cur->val);  // 加入到新建的行中
                
                for (auto it : cur->children) {  // 将当前节点的左右子节点加入到队列中，下次遍历
                    que.push(it);
                }
            }
            ++depth;  // 递增行数
        }
        
        return res;
    }
};
````

### Solution2（Recursive）

这种解法就是利用深搜的方法得到广搜的结果，可以自己画图来求解，

`````c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if (root == nullptr) {
            return vector<vector<int>>();
        }
        vector<vector<int>> res;
        LevelOrder(root, 0, res);
        
        return res;
    }
    
 private:
    void LevelOrder(Node *root, int depth, vector<vector<int>>& res) {
        if (root == nullptr) {
            return;
        }
        
        while (res.size() <= depth) {
            res.push_back({});
        }
        res[depth].push_back(root->val);
        for (auto it : root->children) {
            LevelOrder(it, depth + 1, res);
        }
    }
};
`````



