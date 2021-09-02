# [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/description/)

## 题目

Given the `head` of a singly linked list, reverse the list, and return *the reversed list*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/rev1ex1.jpg)

```
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/02/19/rev1ex2.jpg)

```
Input: head = [1,2]
Output: [2,1]
```

**Example 3:**

```
Input: head = []
Output: []
```

 

**Constraints:**

- The number of nodes in the list is the range `[0, 5000]`.
- `-5000 <= Node.val <= 5000`

 

**Follow up:** A linked list can be reversed either iteratively or recursively. Could you implement both?

## 题目大意

给定一个链表，反转这个链表，并返回它

## 解题思路

* 可以使用迭代进行反转
* 也可以使用递归进行反转。

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
    /* 解法一：迭代
    ListNode* reverseList(ListNode* head) {
        ListNode *behind = nullptr;
        
        while (head != nullptr) {
            ListNode *tmp = head->next;
            
            head->next = behind;
            
            behind = head;
            head = tmp;
        }
        
        return behind;
    }*/
    
    // 解法二：递归
    ListNode* Reverse(ListNode *head, ListNode *pre) {
        if (head == nullptr) {
            return pre;
        }
        
        ListNode *tmp = head->next;
        head->next = pre;
        return Reverse(tmp, head);
    }
    
    ListNode* reverseList(ListNode *head) {
        return Reverse(head, nullptr);
    }
};
````



