# [933. Number of Recent Calls](https://leetcode.com/problems/number-of-recent-calls/)

## 题目

You have a `RecentCounter` class which counts the number of recent requests within a certain time frame.

Implement the `RecentCounter` class:

- `RecentCounter()` Initializes the counter with zero recent requests.
- `int ping(int t)` Adds a new request at time `t`, where `t` represents some time in milliseconds, and returns the number of requests that has happened in the past `3000` milliseconds (including the new request). Specifically, return the number of requests that have happened in the inclusive range `[t - 3000, t]`.

It is **guaranteed** that every call to `ping` uses a strictly larger value of `t` than the previous call.

 

**Example 1:**

```
Input
["RecentCounter", "ping", "ping", "ping", "ping"]
[[], [1], [100], [3001], [3002]]
Output
[null, 1, 2, 3, 3]

Explanation
RecentCounter recentCounter = new RecentCounter();
recentCounter.ping(1);     // requests = [1], range is [-2999,1], return 1
recentCounter.ping(100);   // requests = [1, 100], range is [-2900,100], return 2
recentCounter.ping(3001);  // requests = [1, 100, 3001], range is [1,3001], return 3
recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002], range is [2,3002], return 3
```

 

**Constraints:**

- `1 <= t <= 109`
- Each test case will call `ping` with **strictly increasing** values of `t`.
- At most `104` calls will be made to `ping`.

## 题目大意

写一个 `RecentCounter` 类来计算特定时间范围内最近的请求。

请你实现 `RecentCounter` 类：

* `RecentCounter()` 初始化计数器，请求数为 `0` 。
* `int ping(int t)` 在时间 t 添加一个新请求，其中 `t` 表示以毫秒为单位的某个时间，并返回过去 `3000` 毫秒内发生的所有请求数（包括新请求）。确切地说，返回在 `[t-3000, t]` 内发生的请求数。

保证 每次对 `ping` 的调用都使用比之前更大的 `t` 值。



## 解题思路

这里可以发现，数据是满足先入先出的，所以可以考虑用队列来做

### Solution 1: 队列

这种解法使用队列先进先出的特性，维护队列中数据的有效性，直接返回队列的大小即可

```c++
class RecentCounter {
public:
    RecentCounter() {

    }
    
    int ping(int t) {
        while (!que_.empty() && t - que_.front() > 3000) {
            // 如果队列不为空，且要加入的值与队首的值相差大于 3000
            que_.pop();
        }
        que_.push(t);
        return que_.size();
    }
 
 private:
    queue<int> que_;
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
```

### Solution 2: Binary Search

这里提供的数据显然是有序的，在有序的区间上进行查找，可以使用二分查找，在有序的区间中国呢找到第一个 **小于3000**  的数

````c++
class RecentCounter {
public:
    RecentCounter() {
    }
    
    int ping(int t) {
        data_.push_back(t);
        int left = 0;
        int right = data_.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (data_[mid] >= t - 3000) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return data_.size() - left;
    }
 
 private:
    vector<int> data_;
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
````



