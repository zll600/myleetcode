# [21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)

Merge two sorted linked lists and return it as a **sorted** list. The list should be made by splicing together the nodes of the first two lists.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/03/merge_ex1.jpg)

```
Input: l1 = [1,2,4], l2 = [1,3,4]
Output: [1,1,2,3,4,4]
```

**Example 2:**

```
Input: l1 = [], l2 = []
Output: []
```

**Example 3:**

```
Input: l1 = [], l2 = [0]
Output: [0]
```

 

**Constraints:**

- The number of nodes in both lists is in the range `[0, 50]`.
- `-100 <= Node.val <= 100`
- Both `l1` and `l2` are sorted in **non-decreasing** order.

## 题目大意

合并两个有序（非降序）链表，

## 解题思路

* 可以使用迭代法，选取头结点较小的链表作为主链表，然后将另一条链表插入
* 可以使用递归法，更简单，因为每个子文题都是相同的，递归基也很好确定。

## 代码

```c++
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
    // 解法一：迭代法
    /*
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }
        
        ListNode *new_head = l1->val <= l2->val ? l1 : l2;
        ListNode *bigger = new_head == l1 ? l2 : l1;
        ListNode *pre = nullptr;
        ListNode *cur1 = new_head;
        ListNode *cur2 = bigger;
        
        while (cur1 != nullptr && cur2 != nullptr) {
            if (cur1->val <= cur2->val) {
                pre = cur1;
                cur1 = cur1->next;
            } else {
                ListNode *tmp = cur2->next;
                cur2->next = cur1;
                pre->next = cur2;
                pre = cur2;
                cur2 = tmp;
            }
        }
        pre->next = cur1 == nullptr ? cur2 : cur1;
        
        return new_head;
    }*/
    
    // 解法二：递归法
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }
        
        if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
};
```

