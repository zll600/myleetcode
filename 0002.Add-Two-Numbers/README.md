# [2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)

## 题目



You are given two **non-empty** linked lists representing two non-negative integers. The digits are stored in **reverse order**, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/02/addtwonumber1.jpg)

```
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.
```

**Example 2:**

```
Input: l1 = [0], l2 = [0]
Output: [0]
```

**Example 3:**

```
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
```

 

**Constraints:**

- The number of nodes in each linked list is in the range `[1, 100]`.
- `0 <= Node.val <= 9`
- It is guaranteed that the list represents a number that does not have leading zeros.

## 题目大意

给定两个非空的链表分别表示两个非负整数，每位数字都是按照逆序存储的，它们的每个节点都包含单独的一位，将两个数相加，返回新的链表

你可以认为两个数都不包含前导0，除了0本身

## 解题思路

概括以下就是要逆序求和

### 解法1

这道题目的思路不难，但是在编码时有很多的细节，

* 建立一个虚拟的头结点，使得建立新链表的逻辑更加统一
* 对链表的节点解引用时，一定要先判断节点是否为空
* 另外判断循环终止的条件不用是 `l1->next ！= nullptr`，这样最后一位还需要额外计算，循环终止条件应该是 `l1 != nullptr`。

`````c++
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode();
        head->val = -1;
        head->next = nullptr;
        
        ListNode *cur = head;
        int carry = 0;  // 表示进位的值
        int num1 = 0;
        int num2 = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            if (l1 == nullptr) {  // 这里一定要防止链表为空
                num1 = 0;
            } else {
                num1 = l1->val;
                l1 = l1->next;
            }
            
            if (l2 == nullptr) {
                num2 = 0;
            } else {
                num2 = l2->val;
                l2 = l2->next;
            }
            
            int sum = num1 + num2 + carry;
            cur->next = new ListNode(sum % 10, nullptr);  //  创建新节点
            cur = cur->next;
            
            carry = sum >= 10 ? 1 : 0;  // 是否有进位产生
        }
        
        return head->next;
    }
};
`````

