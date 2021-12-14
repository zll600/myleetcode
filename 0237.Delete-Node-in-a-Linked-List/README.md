# [237. Delete Node in a Linked List](https://leetcode.com/problems/delete-node-in-a-linked-list/)

## 题目

Write a function to **delete a node** in a singly-linked list. You will **not** be given access to the `head` of the list, instead you will be given access to **the node to be deleted** directly.

It is **guaranteed** that the node to be deleted is **not a tail node** in the list.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/01/node1.jpg)

```
Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5, the linked list should become 4 -> 1 -> 9 after calling your function.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/09/01/node2.jpg)

```
Input: head = [4,5,1,9], node = 1
Output: [4,5,9]
Explanation: You are given the third node with value 1, the linked list should become 4 -> 5 -> 9 after calling your function.
```

**Example 3:**

```
Input: head = [1,2,3,4], node = 3
Output: [1,2,4]
```

**Example 4:**

```
Input: head = [0,1], node = 0
Output: [1]
```

**Example 5:**

```
Input: head = [-3,5,-99], node = -3
Output: [5,-99]
```

 

**Constraints:**

- The number of the nodes in the given list is in the range `[2, 1000]`.
- `-1000 <= Node.val <= 1000`
- The value of each node in the list is **unique**.
- The `node` to be deleted is **in the list** and is **not a tail** node

## 题目大意

删除一个单向链表中的给定节点，你将利用直接访问这个要被删除的节点而不是链表的头节点，

题目保证要删除的不是最后一个节点

## 解题思路

单链表中要想删除一个节点，必须得到指向这个节点的前一个节点，但是这道题没有给出单链表的头节点，所有这种方法就是不可行的，

### Solution 1:

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/delete-node-in-a-linked-list/solution/tu-jie-shan-chu-lian-biao-zhong-de-jie-dian-python/

这种解法采用的是直接赋值的形式来做的，但是这种解法有一个限制就是不能删除尾节点，不过这道题目刚好保证了这一点，所以可以将下一个节点的值赋给当前节点，然后删除下一个节点

````c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        ListNode *to_delete = node->next;
        node->next = node->next->next;
        delete to_delete;
    }
};
````

