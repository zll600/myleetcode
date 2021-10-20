# [445. Add Two Numbers II](https://leetcode.com/problems/add-two-numbers-ii/)

## 题目

You are given two **non-empty** linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/09/sumii-linked-list.jpg)

```
Input: l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]
```

**Example 2:**

```
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [8,0,7]
```

**Example 3:**

```
Input: l1 = [0], l2 = [0]
Output: [0]
```

 

**Constraints:**

- The number of nodes in each linked list is in the range `[1, 100]`.
- `0 <= Node.val <= 9`
- It is guaranteed that the list represents a number that does not have leading zeros.

 

**Follow up:** Could you solve it without reversing the input lists?

## 题目大意

给定两个非空链表分别代表两个非负整数，数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

数字中不含任何前导 0，除了0 本身

**进阶要求**：你不能翻转链表

## 解题思路

这道题目可以联系 第 2 题来解决

### Solution 1:

最直接的想法，反转链表，然后按照第 2 题的做法来作

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
        if (l1->val == 0) {
            return l2;
        }
        if (l2->val == 0) {
            return l1;
        }
        
        l1 = Reverse(l1);  // 反转链表
        l2 = Reverse(l2);
        ListNode *head = new ListNode(0);
        
        int num1 = 0;
        int num2 = 0;
        int carry = 0;
        ListNode *cur = head;
        while (l1 || l2 || carry != 0) {
            if (!l1) {
                num1 = 0;
            } else {
                num1 = l1->val;
                l1 = l1->next;
            }
            
            if (!l2) {
                num2 = 0;
            } else {
                num2 = l2->val;
                l2 = l2->next;
            }
            
            cur->next = new ListNode((num1 + num2 + carry) % 10);
            cur = cur->next;
            carry = (num1 + num2 + carry) / 10;
        }
        
        return Reverse(head->next);
    }
    
 private:
    ListNode* Reverse(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *tmp = nullptr;
        
        while (head) {
            tmp = head->next;
            head->next = prev;
            prev = head;
            head = tmp;
        }
        
        return prev;
    }
};
`````

### Solutino 2:

这种解法，可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0445.Add-Two-Numbers-II/

可以利用递归来处理进位和连接，就是将较短的链表加到较长的链表上

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1->val == 0) {
            return l2;
        }
        if (l2->val == 0) {
            return l1;
        }
        
        int len1 = GetLength(l1);
        int len2 = GetLength(l2);
        
        // 注意这里初始化为 1，是为了后面的进位作处理
        ListNode *head = new ListNode(1);
        if (len1 < len2) {
            head->next = AddNode(l2, l1, len2 - len1);
        } else {
            head->next = AddNode(l1, l2, len1 - len2);
        }
        
        // 检测是否发生了进位
        if (head->next->val > 9) {
            head->next->val %= 10;
            return head;
        }
        return head->next;
    }
    
 private:
    // 得到链表的长度
    int GetLength(ListNode *head) {
        int res = 0;
        while (head) {
            ++res;
            head = head->next;
        }
        
        return res;
    }
    
    ListNode* AddNode(ListNode *l1, ListNode *l2, int offset) {
        if (l1 == nullptr) {
            return nullptr;
        }
        
        ListNode *res = nullptr;
        ListNode *node = nullptr;
        
        if (offset == 0) {
            // 如果已经同步了，则同时使用两条链表
            res = new ListNode(l1->val + l2->val);
            node = AddNode(l1->next, l2->next, offset);
        } else {
            // 如果还未同步，则只使用长的那条链表
            res = new ListNode(l1->val);
            node = AddNode(l1->next, l2, offset - 1);
        }
        
        // 如果下一个节点不为空，检查是否发生进位
        if (node && node->val > 9) {
            ++res->val;
            node->val %= 10;
        }
        res->next = node;  // 连接
        
        return res;
    }
};
````

### Solution 3:

这道题也可以用栈来做，可以参考花花酱的解法