# [25. Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/description/)

## 题目

Given a linked list, reverse the nodes of a linked list *k* at a time and return its modified list.

*k* is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of *k* then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex1.jpg)

```
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex2.jpg)

```
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
```

**Example 3:**

```
Input: head = [1,2,3,4,5], k = 1
Output: [1,2,3,4,5]
```

**Example 4:**

```
Input: head = [1], k = 1
Output: [1]
```

 

**Constraints:**

- The number of nodes in the list is in the range `sz`.
- `1 <= sz <= 5000`
- `0 <= Node.val <= 1000`
- `1 <= k <= sz`

 

**Follow-up:** Can you solve the problem in O(1) extra memory space?

## 题目大意

K 个相邻的节点一组进行反转，如果不满足 k 个就不反转。

## 解题思路

可以联系第 24 题，两个一组反转，这里是 k 个一组，

* 可以用递归来依次解决
* 既然能用递归，就可以用显式的栈来解决。
* 可以仅仅使用指针来做

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
    // 解法一：递归求解
    /*
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *cur = head;
        for (int i = 0; i < k; ++i) {
            if (cur == nullptr) {
                return head;
            }
            cur = cur->next;
        }
        
        ListNode *node = Reverse(head, cur);
        head->next = reverseKGroup(cur, k);
        return node;
    }*/
    
    // 解法二：显示使用栈
    /*
    ListNode* reverseKGroup(ListNode *head, int k) {
        if (k < 2) {
            return head;
        }
        
        ListNode *new_head = head;
        ListNode *cur = head;
        ListNode *pre= nullptr;
        stack<ListNode*> sta;
        
        while (cur != nullptr) {
            ListNode *tmp = cur->next;
            sta.push(cur);
            
            if (sta.size() == k) {
                pre = Reverse(sta, pre, tmp);
                new_head = new_head == head ? cur : new_head;
            }
            cur = tmp;
        }
        
        return new_head;
    }*/
    
    // 解法三：只使用指针，第一组 k 个节点需要单独处理，会超时
    ListNode* reverseKGroup(ListNode *head, int k) {
        if (k < 2) {
            return head;
        }
        
        ListNode *new_head = head;
        ListNode *pre = nullptr;
        ListNode *start = nullptr;
        ListNode *cur = head;
        
        int count = 0;
        while (cur != nullptr) {
            ++count;
            ListNode *tmp = cur->next;
            
            if (count == k) {
                start = pre == nullptr ? head : pre->next;
                new_head = new_head == head ? cur : new_head;
                Reverse(pre, start, cur, tmp);
                pre = start;
                count = 0;
            }
            cur = tmp;
        }
        return new_head;
    }
    
    
 private:

    ListNode* Reverse(ListNode *first, ListNode *last) {
        ListNode *pre = last;
        while (first != last) {
            ListNode *tmp = first->next;
            first->next = pre;
            pre = first;
            first = tmp;
        }
        return pre;
    }
    
    ListNode* Reverse(stack<ListNode*>& sta, ListNode *left, ListNode *right) {
        ListNode *cur = sta.top();
        if (left != nullptr) {
            left->next = cur;
        }
        
        while (!sta.empty()) {
            ListNode *tmp = sta.top();
            sta.pop();
            cur->next = tmp;
            cur = tmp;
        }
        cur->next = right;
        return cur;
    }
    
    void Reverse(ListNode *left, ListNode *first, ListNode *last, ListNode *right) {
        ListNode *pre = first;
        ListNode *cur = first->next;
        
        while (cur != nullptr) {
            ListNode *tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        if (left != nullptr) {
            left->next = last;
        }
        first->next = right;
    }
};
````

