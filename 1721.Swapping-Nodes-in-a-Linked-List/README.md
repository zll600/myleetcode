# [1721. Swapping Nodes in a Linked List](https://leetcode.com/problems/swapping-nodes-in-a-linked-list/)

## 题目

You are given the `head` of a linked list, and an integer `k`.

Return *the head of the linked list after **swapping** the values of the* `kth` *node from the beginning and the* `kth` *node from the end (the list is **1-indexed**).*

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/21/linked1.jpg)

```
Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]
```

**Example 2:**

```
Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
Output: [7,9,6,6,8,7,3,0,9,5]
```

 

**Constraints:**

- The number of nodes in the list is `n`.
- `1 <= k <= n <= 105`
- `0 <= Node.val <= 100`

## 题目大意

给你链表的头节点 `head` 和一个整数 `k` 。**交换** 链表正数第 `k` 个节点和倒数第 `k` 个节点的值后，返回链表的头节点（链表 **从 1 开始索引**

## 解题思路

这道题按照题目要求去做就可以了

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1700~1799/1721.Swapping-Nodes-in-a-Linked-List/)

这里的难点在于如何找到这两个节点

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
    ListNode* swapNodes(ListNode* head, int k) {
        int cnt = 1;
        ListNode *cur = head;
        ListNode *a = nullptr;
        while (cur != nullptr) {
            if (cnt == k) {
                a = cur;
            }
            ++cnt;
            cur = cur->next;
        }

        const int len = cnt;
        cnt = 1;
        cur = head;
        ListNode *b = nullptr;
        while (cur != nullptr) {
            if (cnt == len - k) {
                b = cur;
            }
            ++cnt;
            cur = cur->next;
        }

        swap(a->val, b->val);
        return head;
    }
};
````
