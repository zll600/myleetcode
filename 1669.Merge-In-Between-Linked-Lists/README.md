# [1669. Merge In Between Linked Lists](https://leetcode.com/problems/merge-in-between-linked-lists/)

## 题目

You are given two linked lists: `list1` and `list2` of sizes `n` and `m` respectively.

Remove `list1`'s nodes from the `ath` node to the `bth` node, and put `list2` in their place.

The blue edges and nodes in the following figure indicate the result:

![img](https://assets.leetcode.com/uploads/2020/11/05/fig1.png)

*Build the result list and return its head.*

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/05/merge_linked_list_ex1.png)

```
Input: list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
Output: [0,1,2,1000000,1000001,1000002,5]
Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place. The blue edges and nodes in the above figure indicate the result.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/11/05/merge_linked_list_ex2.png)

```
Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
Explanation: The blue edges and nodes in the above figure indicate the result.
```

 

**Constraints:**

- `3 <= list1.length <= 104`
- `1 <= a <= b < list1.length - 1`
- `1 <= list2.length <= 104`

## 题目大意

给你两个链表 `list1` 和 `list2` ，它们包含的元素分别为 `n` 个和 `m` 个。请你将 `list1` 中第 `a` 个节点到第 `b` 个节点删除，并将 `list2` 接在被删除节点的位置

## 解题思路


### Solution 1:

这道题目还是比较简单，这里找到对应的节点，然后连接即可

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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode *list2_tail = list2;
        while (list2_tail->next) {
            list2_tail = list2_tail->next;
        }

        ListNode *prev = list1;
        for (int i = 0; i < a - 1; ++i) {
            prev = prev->next;
        }
        ListNode *after = list1;
        for (int i = 0; i < b + 1; ++i) {
            after = after->next;
        }

        prev->next = list2;
        list2_tail->next = after;
        return list1;
    }
};
````
