# [1670. Design Front Middle Back Queue](https://leetcode.com/problems/design-front-middle-back-queue/)

## 题目

Design a queue that supports `push` and `pop` operations in the front, middle, and back.

Implement the `FrontMiddleBack` class:

- `FrontMiddleBack()` Initializes the queue.
- `void pushFront(int val)` Adds `val` to the **front** of the queue.
- `void pushMiddle(int val)` Adds `val` to the **middle** of the queue.
- `void pushBack(int val)` Adds `val` to the **back** of the queue.
- `int popFront()` Removes the **front** element of the queue and returns it. If the queue is empty, return `-1`.
- `int popMiddle()` Removes the **middle** element of the queue and returns it. If the queue is empty, return `-1`.
- `int popBack()` Removes the **back** element of the queue and returns it. If the queue is empty, return `-1`.

**Notice** that when there are **two** middle position choices, the operation is performed on the **frontmost** middle position choice. For example:

- Pushing `6` into the middle of `[1, 2, 3, 4, 5]` results in `[1, 2, 6, 3, 4, 5]`.
- Popping the middle from `[1, 2, 3, 4, 5, 6]` returns `3` and results in `[1, 2, 4, 5, 6]`.

 

**Example 1:**

```
Input:
["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
[[], [1], [2], [3], [4], [], [], [], [], []]
Output:
[null, null, null, null, null, 1, 3, 4, 2, -1]

Explanation:
FrontMiddleBackQueue q = new FrontMiddleBackQueue();
q.pushFront(1);   // [1]
q.pushBack(2);    // [1, 2]
q.pushMiddle(3);  // [1, 3, 2]
q.pushMiddle(4);  // [1, 4, 3, 2]
q.popFront();     // return 1 -> [4, 3, 2]
q.popMiddle();    // return 3 -> [4, 2]
q.popMiddle();    // return 4 -> [2]
q.popBack();      // return 2 -> []
q.popFront();     // return -1 -> [] (The queue is empty)
```

 

**Constraints:**

- `1 <= val <= 109`
- At most `1000` calls will be made to `pushFront`, `pushMiddle`, `pushBack`, `popFront`, `popMiddle`, and `popBack`.

## 题目大意

请你设计一个队列，支持在前，中，后三个位置的 `push` 和 `pop` 操作。

请你完成 `FrontMiddleBack` 类：

- `FrontMiddleBack()` 初始化队列。
- `void pushFront(int val)` 将 `val` 添加到队列的 最前面 
- `void pushMiddle(int val)` 将 `val` 添加到队列的 正中间 
- `void pushBack(int val)` 将 `val` 添加到队里的 最后面 
- `int popFront()` 将 最前面 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1
- `int popMiddle()` 将 正中间 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1
- `int popBack()` 将 最后面 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1

请注意当有 两个 中间位置的时候，选择靠前面的位置进行操作。比方说：

- 将 `6` 添加到 `[1, 2, 3, 4, 5]` 的中间位置，结果数组为 `[1, 2, 6, 3, 4, 5]`
- 从 `[1, 2, 3, 4, 5, 6]` 的中间位置弹出元素，返回 3 ，数组变为 `[1, 2, 4, 5, 6]` 

## 解题思路

其实刚开始，以为这道题目是可以用两个双端队列来解决的，后面发现不行

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/design-front-middle-back-queue/solution/she-ji-qian-zhong-hou-dui-lie-by-zerotrac2/)

### Solution 1: 使用 数组 模拟

这种解法使用 c++ 的 vector 来模拟这些操作

````c++
class FrontMiddleBackQueue {
public:
    FrontMiddleBackQueue() {

    }

    void pushFront(int val) {
        data_.insert(data_.begin(), val);
    }

    void pushMiddle(int val) {
        int pos = data_.size() / 2;
        data_.insert(data_.begin() + pos, val);
    }

    void pushBack(int val) {
        data_.push_back(val);
    }

    int popFront() {
        if (data_.empty()) {
            return -1;
        }
        int ret = data_[0];
        data_.erase(data_.begin());
        return ret;
    }

    int popMiddle() {
        if (data_.empty()) {
            return -1;
        }
        int idx = (data_.size() - 1) / 2;
        int ret = data_[idx];
        data_.erase(data_.begin() + idx);
        return ret;
    }

    int popBack() {
        if (data_.empty()) {
            return -1;
        }
        int ret = data_.back();
        data_.pop_back();
        return ret;
    }

 private:
    vector<int> data_;
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */
````

### Solution 2: Deque

这种解法的核心就是维护在所有的操作中，维护不变量 ` prev_.size() == after_.size() || prev_.size() == after_.size() - 1`

每次操作都要更新并检查这个不变量

````c++
class FrontMiddleBackQueue {
public:
    FrontMiddleBackQueue() {

    }

    // 保持不变量
    // prev_.size() == after_.size() || prev_size() == after_.size() - 1
    void pushFront(int val) {
        prev_.push_front(val);
        // 调整
        if (prev_.size() > after_.size()) {
            after_.push_front(prev_.back());
            prev_.pop_back();
        }
    }

    void pushMiddle(int val) {
        prev_.push_back(val);

        if (prev_.size() > after_.size()) {
            after_.push_front(prev_.back());
            prev_.pop_back();
        }
    }

    void pushBack(int val) {
        after_.push_back(val);

        if (after_.size() > prev_.size() + 1) {
            prev_.push_back(after_.front());
            after_.pop_front();
        }
    }

    int popFront() {
        int ret = -1;
        if (!prev_.empty()) {
            ret = prev_.front();
            prev_.pop_front();

            if (after_.size() > prev_.size() + 1) {
                prev_.push_back(after_.front());
                after_.pop_front();
            }
        } else if (!after_.empty()){
            ret = after_.front();
            after_.pop_front();
        }
        return ret;
    }

    int popMiddle() {
        int ret = -1;
        if (!prev_.empty() && prev_.size() == after_.size()) {
            ret = prev_.back();
            prev_.pop_back();
        } else if (prev_.size() + 1 == after_.size()) {
            ret = after_.front();
            after_.pop_front();
        }

        return ret;
    }

    int popBack() {
        int ret = -1;
        if (!after_.empty() && prev_.size() <= after_.size()) {
            ret = after_.back();
            after_.pop_back();

            if (prev_.size() > after_.size()) {
                after_.push_front(prev_.back());
                prev_.pop_back();
            }
        }
        return ret;
    }

 private:
    deque<int> prev_;
    deque<int> after_;
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */


````
