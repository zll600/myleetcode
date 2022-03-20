# [641. Design Circular Deque](https://leetcode-cn.com/problems/design-circular-deque/)

## 题目

Design your implementation of the circular double-ended queue (deque).

Implement the `MyCircularDeque` class:

- `MyCircularDeque(int k)` Initializes the deque with a maximum size of `k`.
- `boolean insertFront()` Adds an item at the front of Deque. Returns `true` if the operation is successful, or `false` otherwise.
- `boolean insertLast()` Adds an item at the rear of Deque. Returns `true` if the operation is successful, or `false` otherwise.
- `boolean deleteFront()` Deletes an item from the front of Deque. Returns `true` if the operation is successful, or `false` otherwise.
- `boolean deleteLast()` Deletes an item from the rear of Deque. Returns `true` if the operation is successful, or `false` otherwise.
- `int getFront()` Returns the front item from the Deque. Returns `-1` if the deque is empty.
- `int getRear()` Returns the last item from Deque. Returns `-1` if the deque is empty.
- `boolean isEmpty()` Returns `true` if the deque is empty, or `false` otherwise.
- `boolean isFull()` Returns `true` if the deque is full, or `false` otherwise.

 

**Example 1:**

```
Input
["MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront", "getRear", "isFull", "deleteLast", "insertFront", "getFront"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 2, true, true, true, 4]

Explanation
MyCircularDeque myCircularDeque = new MyCircularDeque(3);
myCircularDeque.insertLast(1);  // return True
myCircularDeque.insertLast(2);  // return True
myCircularDeque.insertFront(3); // return True
myCircularDeque.insertFront(4); // return False, the queue is full.
myCircularDeque.getRear();      // return 2
myCircularDeque.isFull();       // return True
myCircularDeque.deleteLast();   // return True
myCircularDeque.insertFront(4); // return True
myCircularDeque.getFront();     // return 4
```

 

**Constraints:**

- `1 <= k <= 1000`
- `0 <= value <= 1000`
- At most `2000` calls will be made to `insertFront`, `insertLast`, `deleteFront`, `deleteLast`, `getFront`, `getRear`, `isEmpty`, `isFull`.

## 题目大意

设计一个循环的双端队列 (deque):

实现一个 `MyCircularDeque` 的类：

- 'MyCircularDeque' 初始化一个大小为 `k` 的队列，
- `boolean insertFront()` 在队首增加一项，如果操作成功，返回 `true`，否则返回 `false`，
- `boolean insertLast()` 在队尾新增加一项，如果操作成功，返回 `true`，否则返回 `false`,
- `boolean deleteFront()` 删除队首的一项，如果操作成功，返回 `true`,否则返回 `false`
- `boolean deleteLast()` 从队尾删除一项，如果操作成功，返回 `true`，否则返回 `false`
- `int getFront()` 返回队首元素，如果队为空，返回 `-1`
- `int getRear()` 返回队尾元素，如果队列为空，返回 `-1`,
- `boolean isEmpty()` 如果队列为空，返回 `true`，否则返回 `false`
- `boolean isFull()` 如果队列已经满了，返回 `true`, 否则返回 `false`

## 解题思路


### Solution 1: 这里使用 stl 的双向链表来做的话，是比数组要简单的

这种解法是当时腾讯云二面的时候面试官提醒的，之前还是首先会想到数组

````c++
class MyCircularDeque {
public:
    MyCircularDeque(int k) : capacity_(k){
    }

    bool insertFront(int value) {
        if (data_.size() == capacity_) {
            return false;
        }
        data_.push_front(value);
        return true;
    }

    bool insertLast(int value) {
        if (data_.size() == capacity_) {
            return false;
        }
        data_.push_back(value);
        return true;
    }

    bool deleteFront() {
        if (data_.empty()) {
            return false;
        }
        data_.pop_front();
        return true;
    }

    bool deleteLast() {
        if (data_.empty()) {
            return false;
        }
        data_.pop_back();
        return true;
    }

    int getFront() {
        if (data_.empty()) {
            return -1;
        }

        return data_.front();
    }

    int getRear() {
        if (data_.empty()) {
            return -1;
        }

        return data_.back();
    }

    bool isEmpty() {
        return data_.empty();
    }

    bool isFull() {
        return data_.size() == capacity_;
    }

 private:
    std::list<int> data_;
    size_t capacity_;
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
````
