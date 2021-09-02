# [23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

## 题目

You are given an array of `k` linked-lists `lists`, each linked-list is sorted in ascending order.

*Merge all the linked-lists into one sorted linked-list and return it.*

 

**Example 1:**

```
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
```

**Example 2:**

```
Input: lists = []
Output: []
```

**Example 3:**

```
Input: lists = [[]]
Output: []
```

 

**Constraints:**

- `k == lists.length`
- `0 <= k <= 10^4`
- `0 <= lists[i].length <= 500`
- `-10^4 <= lists[i][j] <= 10^4`
- `lists[i]` is sorted in **ascending order**.
- The sum of `lists[i].length` won't exceed `10^4`.

## 题目大意

给定 k 个按升序已经排序的链表，合并为一个链表，并返回

## 解题思路

* 使用分治法，一步一步拆分为合并两个链表的行为。
* 使用优先级队列，维护一个小根堆（C++默认是一个大根堆），比较函数，满足 **结点的值大于等于**，可以参考代码

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
    // 解法一:使用分治的想法，然后进行两个链表合并。
    /*
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int size = lists.size();
        if (size < 1) {
            return nullptr;
        }
        if (size == 1) {
            return lists[0];
        }
        
        return Merge(lists, 0, lists.size() - 1);
    }*/
    
    // 解法二：使用优先级队列（这里需要使用小顶堆）
    static bool Cmp(ListNode *l1, ListNode *l2) {
        return l1->val >= l2->val;
    }
    
    ListNode *mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        
        priority_queue<ListNode*, vector<ListNode*>, function<bool(ListNode*, ListNode*)>> pq(Cmp);
        for (ListNode *list : lists) {
            if (list != nullptr) {
                pq.push(list);
            }
        }
        
        ListNode *dummy = new ListNode(-1, nullptr);
        ListNode *pre = dummy;
        while (!pq.empty()) {
            ListNode *list = pq.top();  // 取出头结点最小的链表，
            pq.pop();
            
            pre->next = list;
            pre = pre->next;
            
            if (list->next != nullptr) {    // 如果该链表仍不为空，则再次加入队列中。
                pq.push(list->next);
            }
        }
        
        return dummy->next;
    }
    
 private:
    // 借助分治的思想，将 k 个链表亮亮合并    
    ListNode* MergeTwoLists(ListNode *l1, ListNode *l2) {
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
    }
    
    ListNode *Merge(vector<ListNode*>& lists, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        if (left == right) {
            return lists[left];
        }
        
        int mid = left + (right - left) / 2;
        ListNode *first = Merge(lists, left, mid);
        ListNode *last = Merge(lists, mid + 1, right);
        
        return MergeTwoLists(first, last);
    }
};
````





