# [449. Serialize and Deserialize BST](https://leetcode-cn.com/problems/serialize-and-deserialize-bst/)

## 题目

Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a **binary search tree**. There is no restriction on how your serialization/deserialization algorithm should work. You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.

**The encoded string should be as compact as possible.**

 

**Example 1:**

```
Input: root = [2,1,3]
Output: [2,1,3]
```

**Example 2:**

```
Input: root = []
Output: []
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 104]`.
- `0 <= Node.val <= 104`
- The input tree is **guaranteed** to be a binary search tree.

## 题目大意

序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建

设计一个算法来序列化和反序列化 **二叉搜索树** 。 对序列化/反序列化算法的工作方式没有限制。 您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。

编码的字符串应尽可能紧凑


## 解题思路

题目中给的顺序是层序遍历，

对于二叉搜索树来说，因为其特点，所以只需要知道 前序遍历或者后序遍历就可以重新构建整棵树，而对于普通的树，需要中序遍历和 前序遍历或者后序遍历其中一个才可以

另外这里利用 stringstream 来分割字符串，也是一种技巧

### Solution 1:



````c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string data = "";
        serialize(root, data);
        return data;
    }
    
    // 这里使用前序遍历，并使用 ' ' 隔开
    void serialize(TreeNode *root, string& data) {
        if (root == nullptr) {
            return;
        }
        
        data += to_string(root->val) + " ";
        serialize(root->left, data);
        serialize(root->right, data);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }
        // 先构造节点集合
        string tmp = "";
        stringstream ss(data);
        vector<int> nums;
        while (getline(ss, tmp, ' ')) {
            nums.push_back(stoi(tmp));
        }
        
        return deserialize(nums, 0, nums.size() - 1);
    }
    
    // 这里同样适用前序遍历
    TreeNode* deserialize(const vector<int>& data, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        
        TreeNode *root = new TreeNode(data[left]);
        // 找分界点
        int k = left + 1;
        while (k <= right && data[k] < data[left]) {
            ++k;
        }
        root->left = deserialize(data, left + 1, k - 1);
        root->right = deserialize(data, k, right);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;

````

