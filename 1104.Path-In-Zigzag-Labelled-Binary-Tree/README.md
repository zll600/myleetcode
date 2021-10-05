# [1104. Path In Zigzag Labelled Binary Tree](https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/)

## 题目

In an infinite binary tree where every node has two children, the nodes are labelled in row order.

In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.

![img](https://assets.leetcode.com/uploads/2019/06/24/tree.png)

Given the `label` of a node in this tree, return the labels in the path from the root of the tree to the node with that `label`.

 

**Example 1:**

```
Input: label = 14
Output: [1,3,4,14]
```

**Example 2:**

```
Input: label = 26
Output: [1,2,6,10,26]
```

 

**Constraints:**

- `1 <= label <= 10^6`

## 题目大意

在一棵无限的二叉树上，每个节点有两个孩子，所有的节点**按行**进行标记，

在奇数行（如：第 1 行，第 3 行）从左至右进行标记，在偶数行（如: 第 2 行，第 4 行），从右至左进行标记，

给定树上某一个节点的标号，返回从根节点到该节点的路径。

## 解题思路

这道题目的关键是如何从当前行确定上一行，

这里也利用了满二叉树的性质来确定位置

可以参考这篇题解：https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/submissions/

### 解法1

我采用的方法是，当前行从小到大遍历，则上一行一定是从大到小遍历

`````c++
class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        // 计算目标节位于第几层
        int level = 1;
        while (GetEnd(level) < label) {
            level++;
        }
        
        
        vector<int> res(level);
        int idx = level - 1;
        int cur = label;
        
        while (idx >= 0) {
            res[idx] = cur;  // 找到路径中的一个节点，加入到结果中
            idx--;
            // 全部都找完了，此时level 为 1，下面的话会出现level 为0
            if (idx == -1) {
                break;
            }
            // int total = pow(2, level - 1);  // 这是因为 level -1 为0，如果再传入GetStart 中，则会出现移为负数的情况
            int total = 1 << level - 1;
            
            int first = GetStart(level);
            int last = GetEnd(level);
            // 这里只需要记住，当前层从小往大遍历，上一层就一定是从大往小遍历
            if (level % 2 == 0) {  // 当前位于偶数行，从右往左递增，上一行就是从右往左
                int prev_end = GetEnd(level - 1);
                for (int i = first; i <= last - 1; i += 2, prev_end--) {
                    if (i == cur || i + 1 == cur) {
                        break;
                    }
                }
                cur = prev_end;
            } else {  // 当前位于奇数行，从左往右递增，上一行就是从右往左递增
                int prev_end = GetEnd(level - 1);
                for (int i = first; i <= last - 1; i += 2, prev_end--) {
                    if (i == cur || i + 1 == cur) {
                        break;
                    }
                }
                cur = prev_end;
            }
            level--;
        }
        
        return res;
    }
    
 private:
    // 注意这里不能使用移位操作，因为这里的level有可能会出席那负数
    int GetStart(int level) {
        // return pow(2, level - 1);
        return 1 << level - 1;
    }
    
    int GetEnd(int level) {
        return 2 * GetStart(level) - 1;
    }
};
`````

