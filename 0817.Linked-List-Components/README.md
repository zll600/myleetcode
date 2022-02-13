# [817. Linked List Components](https://leetcode.com/problems/linked-list-components/)

## 题目

You are given the `head` of a linked list containing unique integer values and an integer array `nums` that is a subset of the linked list values.

Return *the number of connected components in* `nums` *where two values are connected if they appear **consecutively** in the linked list*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/07/22/lc-linkedlistcom1.jpg)

```
Input: head = [0,1,2,3], nums = [0,1,3]
Output: 2
Explanation: 0 and 1 are connected, so [0, 1] and [3] are the two connected components.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/07/22/lc-linkedlistcom2.jpg)

```
Input: head = [0,1,2,3,4], nums = [0,3,1,4]
Output: 2
Explanation: 0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.
```

 

**Constraints:**

- The number of nodes in the linked list is `n`.
- `1 <= n <= 104`
- `0 <= Node.val < n`
- All the values `Node.val` are **unique**.
- `1 <= nums.length <= n`
- `0 <= nums[i] < n`
- All the values of `nums` are **unique**.

## 题目大意

给定链表头结点 `head`，该链表上的每个结点都有一个 **唯一** 的整型值 。同时给定列表 `nums`，该列表是上述链表中整型值的一个子集。

返回列表 `nums` 中组件的个数，这里对组件的定义为：链表中一段最长连续结点的值（该值必须在列表 `nums` 中）构成的集合。


## 解题思路

注意，这道题其实本身并没有保证链表是有序的，这点在分析的时候需要考虑到

这道题其实可以理解为在链表中找到数组中出现的值的位置，然后在没出现的地方断开链表即可

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.com/problems/linked-list-components/submissions/)

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
    int numComponents(ListNode* head, vector<int>& nums) {
        if (head->next == nullptr) {
            return 1;
        }

        int count = 0;
        ListNode *cur = head;
        // 加速查询
        unordered_set<int> flags;
        for_each(nums.begin(), nums.end(), [&](int num) {
            flags.insert(num);
        });

        while (cur != nullptr) {
            if (flags.find(cur->val) != flags.end()) {
                // 当前位置好是否需呀断开，取决于
                // 当前位置是最后一个位置，且出现在。nums 中
                // 当前位置的下一个位置没有出现在 flags 中
                if (cur->next == nullptr) {
                    // 如果当前位置需要
                    ++count;
                } else {
                    if (flags.find(cur->next->val) == flags.end()) {
                        // 下一个位置没有出现，则说明在当前位置可以断开
                        ++count;
                    }
                }
            }

            cur = cur->next;
        }

        return count;
    }
};
````
