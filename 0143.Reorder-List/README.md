# [143. Reorder List](https://leetcode.com/problems/reorder-list/)

## 题目

You are given the head of a singly linked-list. The list can be represented as:

```
L0 → L1 → … → Ln - 1 → Ln
```

*Reorder the list to be on the following form:*

```
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
```

You may not modify the values in the list's nodes. Only nodes themselves may be changed.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/04/reorder1linked-list.jpg)

```
Input: head = [1,2,3,4]
Output: [1,4,2,3]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/03/09/reorder2-linked-list.jpg)

```
Input: head = [1,2,3,4,5]
Output: [1,5,2,4,3]
```

 

**Constraints:**

- The number of nodes in the list is in the range `[1, 5 * 104]`.
- `1 <= Node.val <= 1000`

## 题目大意

按照指定规则重新排序链表：第一个元素和最后一个元素排列在一起，接着第二个元素和倒数第二个元素排在一起，接着第三个元素和倒数第三个元素排在一起。

## 解题思路

链表的题目尽量画图模拟一下

这道题可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0100~0199/0143.Reorder-List/

## Solution 1: 

使用数组来做，

但是这样做对于 C/C++来说，会造成内存泄漏

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
    void reorderList(ListNode* head) {
        // 如果链表元素少于三个直接返回
        if (!head->next || !head->next->next) {
            return;
        }
        
        vector<int> vals = ListToArray(head);
        const int size = vals.size();
        ListNode *cur = head;
        ListNode *last = head;
        // 将后半部分插入到前半部分中
        for (int i = 0; i < size / 2; ++i) {
            ListNode *tmp = new ListNode(vals[size - 1 - i], cur->next);
            cur->next = tmp;
            cur = tmp->next;
            last = tmp;
        }
        
        // 如果 size 是奇数，从cur 处断开后面的元素
        if (size % 2 != 0) {
            cur->next = nullptr;
        } else {
            // size 为偶数，从 last 处断开
            last->next = nullptr;
        }
    }
    
 private:
    // 将链表暂存在数组中
    vector<int> ListToArray(ListNode *head) {
        vector<int> res;
        while (head) {
            res.push_back(head->val);
            head = head->next;
        }
        
        return res;
    }
};
````

### Solution 

将后半段链表翻转，然后插入