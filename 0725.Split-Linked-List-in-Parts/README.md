# [725. Split Linked List in Parts](https://leetcode.com/problems/split-linked-list-in-parts/)

## 题目

Given the `head` of a singly linked list and an integer `k`, split the linked list into `k` consecutive linked list parts.

The length of each part should be as equal as possible: no two parts should have a size differing by more than one. This may lead to some parts being null.

The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal to parts occurring later.

Return *an array of the* `k` *parts*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/06/13/split1-lc.jpg)

```
Input: head = [1,2,3], k = 5
Output: [[1],[2],[3],[],[]]
Explanation:
The first element output[0] has output[0].val = 1, output[0].next = null.
The last element output[4] is null, but its string representation as a ListNode is [].
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/06/13/split2-lc.jpg)

```
Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
Output: [[1,2,3,4],[5,6,7],[8,9,10]]
Explanation:
The input has been split into consecutive parts with size difference at most 1, and earlier parts are a larger size than the later parts.
```

 

**Constraints:**

- The number of nodes in the list is in the range `[0, 1000]`.
- `0 <= Node.val <= 1000`
- `1 <= k <= 50`

## 题目大意

给定一个链表的头节点 `head`，将这个链表分割为连续的 `k` 个部分，

每个部分的长度尽量相同，任意两个部分的长度相差不能大于 1，允许存在空节点，

每个部分出现的顺序应该同输入链表，早出现的部分的长达应该大于等于晚出现的部分的长度，

返回 `k` 个部分的数组

## 解题思路

这里分割的时候每部分的数量需要尽可能的相同，所以这里就不需要考虑从前面开始个部分依次递减的情况了，


### Solution 1: 

先尽量均分，如果不能完全均分，就将多余的节点再次均分在前面的部分中，

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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int list_len = 0;
        ListNode *cur = head;
        while (cur != nullptr) {
            ++list_len;
            cur = cur->next;
        }
        
        // 每部分有多少个节点
        int per_parts = list_len / k;
        // 如果不能均分，有多少部分需要多一个节点
        // 因为题目要求每部分的数量尽量相同，所以这里不考虑从前面开始长度依次递减的情况，
        int more_nums = list_len % k;
        
        vector<ListNode*> ans;
        cur = head;
        ListNode *pre = nullptr;
        // 整个循环中，都要注意空指针的判断
        while (cur != nullptr) {
            // 只需要加入一次
            ans.push_back(cur);
            
            for (int i = 0; i < per_parts && cur != nullptr; ++i) {
                pre = cur;
                cur = cur->next;
            }
            
            // 如果需要添加多余的节点
            if (more_nums > 0 && cur != nullptr) {
                --more_nums;
                pre = cur;
                cur = cur->next;
            }
            
            pre->next = nullptr; // 直接从这里断开就可以了
        }
        
        while (ans.size() < k) {
            // 蔬果不够 k 部分，补空节点
            ans.push_back(nullptr);
        }
        
        return ans;
    }
};
````
