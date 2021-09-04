# [148. Sort List](https://leetcode.com/problems/sort-list/)

## 题目

Given the `head` of a linked list, return *the list after sorting it in **ascending order***.

**Follow up:** Can you sort the linked list in `O(n logn)` time and `O(1)` memory (i.e. constant space)?

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/14/sort_list_1.jpg)

```
Input: head = [4,2,1,3]
Output: [1,2,3,4]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/09/14/sort_list_2.jpg)

```
Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
```

**Example 3:**

```
Input: head = []
Output: []
```

 

**Constraints:**

- The number of nodes in the list is in the range `[0, 5 * 104]`.
- `-105 <= Node.val <= 105`

## 题目大意

给定一个链表，返回按照升序排序的链表。

提高：时间复杂度 O(logn) 和空间复杂度O(1)

## 解题思路

* 最直接的思路还是，将链表转化为数组，然后对数组尽心排序，排序后再转化为链表。
* 使用自顶向下的归并排序，
* 使用自底向上的归并排序。这道题目使用自底向上的迭代法效率更高。

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
    // 解法一：使用自顶向下的归并排序
    /*
    ListNode* sortList(ListNode* head) {
        int len = 0;
        ListNode *cur = head;
        while (cur != nullptr) {
            ++len;
            cur = cur->next;
        }
        if (len <= 1) {
            return head;
        }
        
        ListNode *mid = MiddleNode(head);
        cur = mid->next;
        mid->next = nullptr; // 断开链表（很重要）
        mid = cur;
        
        ListNode *left = sortList(head);
        ListNode *right = sortList(mid);
        return MergeTwoLists(left, right);
    }*/
    
    // 解法二：自底向上归并排序
    ListNode* sortList(ListNode *head) {
        ListNode *cur = head;
        int len = 0;
        while (cur != nullptr) {
            cur = cur->next;
            ++len;
        }
        
        ListNode *dummy = new ListNode(100001, head);
        for (int sz = 1; sz < len; sz = sz + sz) {  // 自底向上的归并排序
            ListNode *pre = dummy;
            cur = pre->next;    // 这里不能些 head，因为每轮排序后虚拟头结点后面的第一个节点会变化
            
            while (cur != nullptr) {    // 遍历整个链表进行切分，
                // 划分链表,先找一组的左起点
                int i = sz;
                ListNode *l1 = cur;
                while (cur != nullptr && i > 0) {
                    cur = cur->next;
                    --i;
                }
                if (i > 0) {    // 如果 cur 为空，说明不会再有右起点，
                    break;
                }
                
                // 再找这一组的右起点
                ListNode *l2 = cur; 
                i = sz;
                while (cur != nullptr && i > 0) {
                    cur = cur->next;
                    --i;
                }
                
                int c1 = sz;    // 这里是因为两组链表不一定等长，第一粗可能比第二组长
                int c2 = sz - i;
                while (c1 > 0 && c2 > 0) {  // 合并划分出来的两个链表
                    if (l1->val < l2->val) {
                        pre->next = l1;
                        l1 = l1->next;
                        --c1;
                    } else {
                        pre->next = l2;
                        l2 = l2->next;
                        --c2;
                    }
                    pre = pre->next;
                }
                pre->next = c1 == 0 ? l2 : l1;
                
                while (c1 > 0 || c2 > 0) {  // 让pre 移动到排序链表的最后一个节点
                    pre = pre->next;
                    --c1;
                    --c2;
                }
                pre->next = cur;    // 将已经排序好的部分和未排序部分连接起来
            }
        }
        
        return dummy->next;
    }
    
 private:
    // 得到中间节点
    ListNode* MiddleNode(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    
    // 合并两个有序的单链表（递归版）超时
    /*
    ListNode *MergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }
        
        if (l1->val < l2->val) {
            l1->next = MergeTwoLists(l1->next, l2);
            return l1;
        }
        l2->next = MergeTwoLists(l1, l2->next);
        return l2;
    }*/
    
    // 合并两个有序链表迭代版
    ListNode* MergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }
        
        ListNode *res = new ListNode(-1, nullptr);
        ListNode *pre = res;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                pre->next = l1;
                l1 = l1->next;
            } else {
                pre->next = l2;
                l2 = l2->next;
            }
            pre = pre->next;
        }
        pre->next = l1 != nullptr ? l1 : l2;
        
        return res->next;
    }
};
````



