# [855. Exam Room](https://leetcode-cn.com/problems/exam-room/)

## 题目

There is an exam room with `n` seats in a single row labeled from `0` to `n - 1`.

When a student enters the room, they must sit in the seat that maximizes the distance to the closest person. If there are multiple such seats, they sit in the seat with the lowest number. If no one is in the room, then the student sits at seat number `0`.

Design a class that simulates the mentioned exam room.

Implement the `ExamRoom` class:

- `ExamRoom(int n)` Initializes the object of the exam room with the number of the seats `n`.
- `int seat()` Returns the label of the seat at which the next student will set.
- `void leave(int p)` Indicates that the student sitting at seat `p` will leave the room. It is guaranteed that there will be a student sitting at seat `p`.

 

**Example 1:**

```
Input
["ExamRoom", "seat", "seat", "seat", "seat", "leave", "seat"]
[[10], [], [], [], [], [4], []]
Output
[null, 0, 9, 4, 2, null, 5]

Explanation
ExamRoom examRoom = new ExamRoom(10);
examRoom.seat(); // return 0, no one is in the room, then the student sits at seat number 0.
examRoom.seat(); // return 9, the student sits at the last seat number 9.
examRoom.seat(); // return 4, the student sits at the last seat number 4.
examRoom.seat(); // return 2, the student sits at the last seat number 2.
examRoom.leave(4);
examRoom.seat(); // return 5, the student sits at the last seat number 5.
```

 

**Constraints:**

- `1 <= n <= 109`
- It is guaranteed that there is a student sitting at seat `p`.
- At most `104` calls will be made to `seat` and `leave`.

## 题目大意

这里有一个考试的教室，里面有 n 个座位排成一排，从 0 到 n - 1，当一个学生进入教室，他必须坐在离他最近的人最远距离的位置上，如果有多个符合条件的座位，返回最小的一个，如果教室里面没有人，学生应该坐在 0 位置上。

## 解题思路

贪心的枚举所有的可能，返回最大的值，这里利用了 set 的有序性来做

### Solution 1

这种解法，参考了这篇题解：https://leetcode-cn.com/problems/exam-room/solution/855-cchao-93de-you-xu-setde-tan-xin-jie-4ypnq/

`````c++
class ExamRoom {
public:
    // 初始化需要保留最后一个位置
    ExamRoom(int n) : size_(n) {
    }
    
    int seat() {
        // 如果位置为空，坐在第一个位置
        if (pos_.empty()) {
            pos_.insert(0);
            return 0;
        }
        
        int res = 0;  // 最终应该放置的位置
        int pre = -1;  // 保存前一个位置
        int max_dist = 0;  // 最大距离
        for (int cur : pos_) {
            // 取相邻节点的中间位置
            int dist = (cur - pre) >> 1;
            // 可以更新结果
            if (dist > max_dist) {
                // 更新位置
                res = pre == -1 ? 0 : pre + dist;
                max_dist = dist;
            }
            pre = cur;
        }
        
        // 考虑最后一个位置
        if (size_ - 1 - pre > max_dist) {
            res = size_ - 1;
        }
        pos_.insert(res);
        return res;
    }
    
    void leave(int p) {
        // 离开直接删除即可
        pos_.erase(p);
    }
    　
 private:
    int size_;   // 最后一个位置
    set<int> pos_;  // 位置的集合
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
`````

