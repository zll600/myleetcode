# [328. Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/)

## 题目

Given the `head` of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return *the reordered list*.

The **first** node is considered **odd**, and the **second** node is **even**, and so on.

Note that the relative order inside both the even and odd groups should remain as it was in the input.

You must solve the problem in `O(1)` extra space complexity and `O(n)` time complexity.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/10/oddeven-linked-list.jpg)

```
Input: head = [1,2,3,4,5]
Output: [1,3,5,2,4]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/03/10/oddeven2-linked-list.jpg)

```
Input: head = [2,1,3,5,6,4,7]
Output: [2,3,6,7,1,5,4]
```

 

**Constraints:**

- `n == `number of nodes in the linked list
- `0 <= n <= 104`
- `-106 <= Node.val <= 106`

## 题目大意

给定一个单链表，将所有的偶数节点排在奇数节点之后，第一个节点是奇数，第二个节点是偶数，使奇数节点和偶数节点内部保持原来的相对顺序，

## 解题思路

* 这道题的思路和第 86 题很像，解法也很相似

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
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        ListNode *odd_head = head;
        ListNode *odd = odd_head;
        head = head->next;
        ListNode *even_head = head;
        ListNode *even = even_head;
        head = head->next;
        
        bool is_odd = true;
        while (head != nullptr) {
            if (is_odd) {
                odd->next = head;
                odd = odd->next;
            } else {
                even->next = head;
                even = even->next;
            }
            is_odd = !is_odd;
            head = head->next;
        }
        even->next = nullptr;
        odd->next = even_head;
        
        return odd_head;
    }
};
````

