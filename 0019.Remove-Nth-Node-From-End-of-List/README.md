# [19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)

## 题目

Given the `head` of a linked list, remove the `nth` node from the end of the list and return its head.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)

```
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
```

**Example 2:**

```
Input: head = [1], n = 1
Output: []
```

**Example 3:**

```
Input: head = [1,2], n = 1
Output: [1]
```

 

**Constraints:**

- The number of nodes in the list is `sz`.
- `1 <= sz <= 30`
- `0 <= Node.val <= 100`
- `1 <= n <= sz`

 

**Follow up:** Could you do this in one pass?

## 题目大意

给定一个链表，删除倒数第 n 个节点，返回新的头节点，

提高：可以仅仅在一次遍历中完成这个任务吗？

## 解题思路

* 需要注意，可能要删除头节点，
* 一次遍历，可以使用快慢指针，快指针先走 n 步，然后移动慢指针，
* 遍历两次，第一次获取链表的长度，第二次找到需要删除节点的前一个节点，

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
    // 解法一：one pass
    /*
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(-1, head);
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *before = dummy;
        
        while (fast != nullptr) {
            if (n <= 0) {
                before = slow;
                slow = slow->next;
            }
            --n;
            fast = fast->next;
        }
        before->next = slow->next;
        delete slow;
        slow = nullptr;
        
        return dummy->next;
    }*/
    
    // 解法二：两次遍历
    ListNode* removeNthFromEnd(ListNode *head, int n) {
        ListNode *cur = head;
        int len = 0;
        while (cur != nullptr) {
            ++len;
            cur = cur->next;
        }
        
        if (len == n) {
            cur = head;
            head = head->next;
            delete cur;
            cur = nullptr;
            return head;
        }
        cur = head;
        for (int i = 0; i < len; ++i) {
            if (i == len - n - 1) {
                ListNode *del_node = cur->next;
                cur->next = cur->next->next;
                delete del_node;
                del_node = nullptr;
                return head;
            }
            cur = cur->next;
        }
        
        return head;
    }
};
````

