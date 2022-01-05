# [382. Linked List Random Node](https://leetcode-cn.com/problems/linked-list-random-node/)

## 题目

Given a singly linked list, return a random node's value from the linked list. Each node must have the **same probability** of being chosen.

Implement the `Solution` class:

- `Solution(ListNode head)` Initializes the object with the integer array nums.
- `int getRandom()` Chooses a node randomly from the list and returns its value. All the nodes of the list should be equally likely to be choosen.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/16/getrand-linked-list.jpg)

```
Input
["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
[[[1, 2, 3]], [], [], [], [], []]
Output
[null, 1, 3, 2, 2, 3]

Explanation
Solution solution = new Solution([1, 2, 3]);
solution.getRandom(); // return 1
solution.getRandom(); // return 3
solution.getRandom(); // return 2
solution.getRandom(); // return 2
solution.getRandom(); // return 3
// getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
```

 

**Constraints:**

- The number of nodes in the linked list will be in the range `[1, 104]`.
- `-104 <= Node.val <= 104`
- At most `104` calls will be made to `getRandom`.

 

**Follow up:**

- What if the linked list is extremely large and its length is unknown to you?Could you solve this efficiently without using extra space?

## 题目大意

给定一个单链表，随机选择链表的一个节点，并返回相应的节点值。保证每个节点**被选的概率一样**。

实现 `Solution` 类

* `Solution()`用整数数组初始化单链表
* `int getRandom()`从链表中随机选择一个节点并返回，保证选择任何节点都是等可能的



进阶要求

* 如果链表的长度很长，而且具体不可知
* 不使用额外空间来解决这个问题

## 解题思路

这道题目的考点是 **蓄水池抽样算法**，可以这样描，蓄水池就是装水的池子，当池子满的时候，每倒入一滴水就有一滴水被替换。

应用：大数据流中的随机抽样问题，从未知大小并且数据只能访问一次的数据流随机选取k个数据，保证每个数据被抽取到的概率相等

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/linked-list-random-node/solution/xu-shui-chi-chou-yang-suan-fa-by-jackwener/

### Solution 1:

````c++
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:

    def __init__(self, head: Optional[ListNode]):
        self.head = head;

    def getRandom(self) -> int:
        count = 0
        reserve = 0
        cur = self.head
        while cur:
            count += 1
            rand = random.randint(1, count)
            if rand == count:
                reserve = cur.val
            cur = cur.next
            
        return reserve


# Your Solution object will be instantiated and called as such:
# obj = Solution(head)
# param_1 = obj.getRandom()
````

### Solution 2:

我用C++写的结果，过不了，这里 `uniform_int_distribution rand(1, count)`和 python3 的的写法是一致的，但是过不了

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
    Solution(ListNode* head) : head_(head) {
    }
    
    int getRandom() {
        int count = 0;
        int res = 0;
        ListNode *cur = head_;
        
        default_random_engine random;
        while (cur) {
            ++count;
            uniform_int_distribution rand(1, count);
            if (rand(random) == count) {
                res = cur->val;
            }
            cur = cur->next;
        }
        return res;
    }
    
 private:
    ListNode *head_;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
````

