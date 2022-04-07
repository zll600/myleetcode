# [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/)

## 题目

You are implementing a program to use as your calendar. We can add a new event if adding the event will not cause a **double booking**.

A **double booking** happens when two events have some non-empty intersection (i.e., some moment is common to both events.).

The event can be represented as a pair of integers `start` and `end` that represents a booking on the half-open interval `[start, end)`, the range of real numbers `x` such that `start <= x < end`.

Implement the `MyCalendar` class:

- `MyCalendar()` Initializes the calendar object.
- `boolean book(int start, int end)` Returns `true` if the event can be added to the calendar successfully without causing a **double booking**. Otherwise, return `false` and do not add the event to the calendar.

 

**Example 1:**

```
Input
["MyCalendar", "book", "book", "book"]
[[], [10, 20], [15, 25], [20, 30]]
Output
[null, true, false, true]

Explanation
MyCalendar myCalendar = new MyCalendar();
myCalendar.book(10, 20); // return True
myCalendar.book(15, 25); // return False, It can not be booked because time 15 is already booked by another event.
myCalendar.book(20, 30); // return True, The event can be booked, as the first event takes every time less than 20, but not including 20.
```

 

**Constraints:**

- `0 <= start < end <= 109`
- At most `1000` calls will be made to `book`.

## 题目大意

实现一个 `MyCalendar` 类来存放你的日程安排。如果要添加的日程安排不会造成 *重复预订* ，则可以存储这个新的日程安排。

当两个日程安排有一些时间上的交叉时（例如两个日程安排都在同一时间内），就会产生 *重复预订* 。

日程可以用一对整数 *start* 和 *end* 表示，这里的时间是半开区间，即 `[start, end)`, 实数 `x` 的范围为，  `start <= x < end` 。

实现 `MyCalendar` 类：

- MyCalendar() 初始化日历对象。
- boolean book(int start, int end) 如果可以将日程安排成功添加到日历中而不会导致重复预订，返回 true 。否则，返回 false 并且不要将该日程安排添加到日历中。

## 解题思路



### Solution 1: BST

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0729.My-Calendar-I/)

这里利用二叉搜索树的特性，可以快速地找到一个可以存放新节点的位置，如果找不到，就返回 false 即可

````c++
// 节点类
struct Event {
    // 起始 和 结束时间
    int start_;
    int end_;

    Event *left_;
    Event *right_;

    Event(int start, int end, Event *left, Event *right)
        : start_(start), end_(end), left_(nullptr), right_(nullptr) {}

    // 递归的插入一个节点
    bool Insert(Event *curr) {
        // 如果发生冲突
        // if (end_ > curr->start_ && curr->end_ > start_) {
        //     return false;
        // }
        // 这里分三种情况，等价于上面的一个判断
        if (curr->start_ >= start_ && curr->end_ <= end_) {
            return false;
        } else if (curr->start_ < start_ && curr->end_ > start_) {
            return false;
        } else if (curr->start_ < end_ && curr->end_ >= end_) {
            return false;
        }

        // 遍历树想其中插入
        if (curr->start_ < start_) {
            if (!left_) {
                left_ = curr;
            } else {
                return left_->Insert(curr);
            }
        } else {
            if (!right_) {
                right_ = curr;
            } else {
                return right_->Insert(curr);
            }
        }
        return true;
    }
};

class MyCalendar {
public:
    MyCalendar() : root_(nullptr) {
    }

    bool book(int start, int end) {
        Event *curr = new Event(start, end, nullptr, nullptr);
        if (!root_ ) {
            root_ = curr;
            return true;
        }
        return root_->Insert(curr);
    }

 private:
    Event *root_;
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
````
