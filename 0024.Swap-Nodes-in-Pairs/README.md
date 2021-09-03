# [24. Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/description/)

## 题目

Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/03/swap_ex1.jpg)

```
Input: head = [1,2,3,4]
Output: [2,1,4,3]
```

**Example 2:**

```
Input: head = []
Output: []
```

**Example 3:**

```
Input: head = [1]
Output: [1]
```

 

**Constraints:**

- The number of nodes in the list is in the range `[0, 100]`.
- `0 <= Node.val <= 100`

## 题目大意

给定一个链表，交换每两个相邻的节点，返回新的头节点，你必须在不改变链表节点的值前提下，解决问题，

## 解题思路

* 这道题目主要考察对于指针的掌握，关键在于理清各个节点之间的关系，同时可以添加一个虚拟头节点，使遍历的逻辑更加统一

## 代码

````c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *dummy = new ListNode(-1, head);
        
        ListNode *cur = dummy;
        // 循环条件，这里保证 当前节点之后还有必定至少还有两个节点
        while (cur->next != nullptr && cur->next->next != nullptr) {
            ListNode *first = cur->next;
            ListNode *last = cur->next->next;
            
            cur->next = last;
            first->next = last->next;
            last->next = first;
            cur = first;
        }
        
        return dummy->next;
    }
};
````



