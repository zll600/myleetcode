# [1019. Next Greater Node In Linked List](https://leetcode.com/problems/next-greater-node-in-linked-list/)

## 题目

You are given the `head` of a linked list with `n` nodes.

For each node in the list, find the value of the **next greater node**. That is, for each node, find the value of the first node that is next to it and has a **strictly larger** value than it.

Return an integer array `answer` where `answer[i]` is the value of the next greater node of the `ith` node (**1-indexed**). If the `ith` node does not have a next greater node, set `answer[i] = 0`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/08/05/linkedlistnext1.jpg)

```
Input: head = [2,1,5]
Output: [5,5,0]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/08/05/linkedlistnext2.jpg)

```
Input: head = [2,7,4,3,5]
Output: [7,0,5,5,0]
```

 

**Constraints:**

- The number of nodes in the list is `n`.
- `1 <= n <= 104`
- `1 <= Node.val <= 109`

## 题目大意

给定一个链表，找到链表中每个节点的下一个严格大于它的节点，返回一个数组，数组中的每个元素是 对应元素的下一个较大的元素，如果没有则为0；

## 解题思路

* 这道题可以用单调栈来解决，具体做法是先将链表中的元素存入到一个数组中，剩下的思路就和 第 739 题一样了。

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
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> nums;
        int size = 0;
        while (head != nullptr) {
            ++size;
            nums.push_back(head->val);
            head = head->next;
        }
        
        vector<int> res(size, 0);
        stack<int> sta;
        
        for (int i = 0; i < size; ++i) {
            while (!sta.empty() && nums[i] > nums[sta.top()]) {
                res[sta.top()] = nums[i];
                sta.pop();
            }
            sta.push(i);
        }
        
        return res;
    }
};
````

