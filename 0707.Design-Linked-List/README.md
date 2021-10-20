# [707. Design Linked List](https://leetcode.com/problems/design-linked-list/)

Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
A node in a singly linked list should have two attributes: `val` and `next`. `val` is the value of the current node, and `next` is a pointer/reference to the next node.
If you want to use the doubly linked list, you will need one more attribute `prev` to indicate the previous node in the linked list. Assume all nodes in the linked list are **0-indexed**.

Implement the `MyLinkedList` class:

- `MyLinkedList()` Initializes the `MyLinkedList` object.
- `int get(int index)` Get the value of the `indexth` node in the linked list. If the index is invalid, return `-1`.
- `void addAtHead(int val)` Add a node of value `val` before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
- `void addAtTail(int val)` Append a node of value `val` as the last element of the linked list.
- `void addAtIndex(int index, int val)` Add a node of value `val` before the `indexth` node in the linked list. If `index` equals the length of the linked list, the node will be appended to the end of the linked list. If `index` is greater than the length, the node **will not be inserted**.
- `void deleteAtIndex(int index)` Delete the `indexth` node in the linked list, if the index is valid.

 

**Example 1:**

```
Input
["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
[[], [1], [3], [1, 2], [1], [1], [1]]
Output
[null, null, null, null, 2, null, 3]

Explanation
MyLinkedList myLinkedList = new MyLinkedList();
myLinkedList.addAtHead(1);
myLinkedList.addAtTail(3);
myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
myLinkedList.get(1);              // return 2
myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
myLinkedList.get(1);              // return 3
```

 

**Constraints:**

- `0 <= index, val <= 1000`
- Please do not use the built-in LinkedList library.
- At most `2000` calls will be made to `get`, `addAtHead`, `addAtTail`, `addAtIndex` and `deleteAtIndex`.

### 题目大意

这里就直接抄力扣了

设计链表的实现。您可以选择使用单链表或双链表。单链表中的节点应该具有两个属性：val 和 next。val 是当前节点的值，next 是指向下一个节点的指针/引用。如果要使用双向链表，则还需要一个属性 prev 以指示链表中的上一个节点。假设链表中的所有节点都是 0-index 的。

在链表类中实现这些功能：

get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。
addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。

## 解题思路

这道题可参考花花酱的题解，多看看优秀的代码，对自己是有好处的：https://zxi.mytechroad.com/blog/list/leetcode-707-design-linked-list/

```c++
class MyLinkedList {
public:
    /** Initialize your data structure here. */
    MyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {
    }
    
    ~MyLinkedList() {
        while (head_) {
            ListNode *tmp = head_->next;
            delete head_;
            head_ = tmp;
        }
        tail_ = nullptr;
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index < 0 || index >= size_) {
            return -1;
        }
        
        ListNode *cur = head_;
        while (index--) {
            cur = cur->next;
        }
        return cur->val;
    }
     
    void addAtHead(int val) {
        head_ = new ListNode(val, head_);
        if (size_++ == 0) {
            tail_ = head_;
        }
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        ListNode *node = new ListNode(val);
        
        if (size_++ == 0) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = tail_->next;
        }
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, 
	the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size_) {
            return;
        }
        if (index == 0) {
            return addAtHead(val);
        }
        if (index == size_) {
            return addAtTail(val);
        }
        
        ListNode *prev = new ListNode(0, head_);
        while (index--) {
            prev = prev->next;
        }
        prev->next = new ListNode(val, prev->next);
        ++size_;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
	/*
	
	1->2->3->4
	*/
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size_) {
            return;
        }
        
        ListNode *prev = new ListNode(0, head_);
        for (int i = 0; i < index; ++i) {
            if (!prev) {
                return;
            }
            prev = prev->next;
        }
        
        ListNode *node_to_delete = prev->next;
        prev->next = prev->next->next;
        if (index == 0) {
            head_ = prev->next;
        }
        if (index == size_ - 1) {
            tail_ = prev;
        }
        delete node_to_delete;
        --size_;
    }
    
 private:
    struct ListNode {
        int val;
        ListNode *next;
        
        ListNode(int _val) : val(_val), next(nullptr) {}
        ListNode(int _val, ListNode *_next) : val(_val), next(_next) {}
    };
    
    ListNode *head_;
    ListNode *tail_;
    int size_;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```

