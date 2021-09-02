# [876. Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/)

##  题目

Given the `head` of a singly linked list, return *the middle node of the linked list*.

If there are two middle nodes, return **the second middle** node.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/07/23/lc-midlist1.jpg)

```
Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The middle node of the list is node 3.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/07/23/lc-midlist2.jpg)

```
Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.
```

 

**Constraints:**

- The number of nodes in the list is in the range `[1, 100]`.
- `1 <= Node.val <= 100`

## 题目大意

给定一个链表，返回这个链表的中间节点。

如果链表节点数为偶数个，则返回第二个中间节点

## 解题思路

* 这道题目可以利用快慢指针，不过需要先判断链表节点是否只有一个，
* 在得到最终的结果时，对于节点数为偶数的链表，快指针移动的条件不同，结果会有所不同，（建议自己画图，就可以比较清晰的得出结论）
  * 条件为 `fast != nullptr && fast->next != nullptr`结果为中间的第二个节点，符合题意
  * 条件为 `fast->next != nullptr && fast->next->next != nullptr` 结果为中间节点的第一个，返回时需要去下一个。

## 代码

````c
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
    ListNode* middleNode(ListNode* head) {
        if ( head->next == nullptr ) 
            return head;
        ListNode *fast = head;
        ListNode *slow = head;
        while ( fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
};
````



