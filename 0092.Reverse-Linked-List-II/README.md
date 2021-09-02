# [92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/)

## 题目

Given the `head` of a singly linked list and two integers `left` and `right` where `left <= right`, reverse the nodes of the list from position `left` to position `right`, and return *the reversed list*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/rev2ex2.jpg)

```
Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
```

**Example 2:**

```
Input: head = [5], left = 1, right = 1
Output: [5]
```

 

**Constraints:**

- The number of nodes in the list is `n`.
- `1 <= n <= 500`
- `-500 <= Node.val <= 500`
- `1 <= left <= right <= n`

## 题目大意

给定一个单链表的头节点，和两个正整数，left 和 right ，翻转 从 left 到 right 这段链表，返回翻转后的链表，

## 解题思路

* 因为没有说明，所有有可能需要翻转头节点，所以先设一个虚拟的头结点，找到翻转区间的前一个节点pre，然后利用“头插法”，将后面的需要反转的节点插入到pre 之后，循环次数用 right - left 表示。
* 利用头插法进行原地反转，将后面的插入到pre 之后的过程，就是 cur 后移的过程，相当于游标已经移动，因此这道题目，不用设置游标，并使用 p = p->next操作，

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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *dummy = new ListNode(-1, head);
        ListNode *pre = dummy;
        
        for (int i = 0; i < left - 1; ++i) {
            pre = pre->next;
        }
        if (pre == nullptr) {
            return head;
        }
        
        ListNode *cur = pre->next;
        for (int i = 0; i < right - left; ++i) {
            ListNode *tmp = pre->next;
            pre->next = cur->next;
            cur->next = cur->next->next;
            pre->next->next = tmp;
        }
        return dummy->next;
    }
};
````

