# [147. Insertion Sort List](https://leetcode.com/problems/insertion-sort-list/)

Given the `head` of a singly linked list, sort the list using **insertion sort**, and return *the sorted list's head*.

The steps of the **insertion sort** algorithm:

1. Insertion sort iterates, consuming one input element each repetition and growing a sorted output list.
2. At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list and inserts it there.
3. It repeats until no input elements remain.

The following is a graphical example of the insertion sort algorithm. The partially sorted list (black) initially contains only the first element in the list. One element (red) is removed from the input data and inserted in-place into the sorted list with each iteration.

![img](https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/04/sort1linked-list.jpg)

```
Input: head = [4,2,1,3]
Output: [1,2,3,4]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/03/04/sort2linked-list.jpg)

```
Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
```

 

**Constraints:**

- The number of nodes in the list is in the range `[1, 5000]`.
- `-5000 <= Node.val <= 5000`

## 题目大意

给定一个单链表的头节点，利用插入排序将链表排序，返回排序后的链表

## 解题思路

这道题就是对链表进行插入排序，这里有几点可以优化

* 设置一个虚拟的头节点，使得及时要调整头节点，整体的调整逻辑也是统一的，
* 现找到需要调整的节点，然后从头开始遍历，

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
    ListNode* insertionSortList(ListNode* head) {
        ListNode *dummy = new ListNode(-1, head);   // 设置一个虚拟的头结点，使得插入的逻辑比较同意
        ListNode *cur = head;

        while (cur != nullptr && cur->next != nullptr) {
            // 如果当前是递增的序列则继续遍历，直到出现逆序
            if (cur->val <= cur->next->val) {
                cur = cur->next;
            } else {
                ListNode *tmp = cur->next;  // 保存要插入的节点
                cur->next = cur->next->next;    // 删除要插入的节点，由于则这一步，找节点时不必从头开始
                tmp->next = nullptr;    // 将要插入的节点独立出来

                ListNode *prev = dummy; // 设置要插入位置的前一个位置
                // 找到插入的位置
                while (prev != nullptr && prev->next != nullptr && prev->next->val <= tmp->val) {
                    prev = prev->next;
                }
                tmp->next = prev->next;
                prev->next = tmp;
            }
        }

        return dummy->next;
    }
};
````

