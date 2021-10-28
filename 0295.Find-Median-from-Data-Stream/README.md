# [295. Find Median from Data Stream](https://leetcode-cn.com/problems/find-median-from-data-stream/)

## 题目

The **median** is the middle value in an ordered integer list. If the size of the list is even, there is no middle value and the median is the mean of the two middle values.

- For example, for `arr = [2,3,4]`, the median is `3`.
- For example, for `arr = [2,3]`, the median is `(2 + 3) / 2 = 2.5`.

Implement the MedianFinder class:

- `MedianFinder()` initializes the `MedianFinder` object.
- `void addNum(int num)` adds the integer `num` from the data stream to the data structure.
- `double findMedian()` returns the median of all elements so far. Answers within `10-5` of the actual answer will be accepted.

 

**Example 1:**

```
Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
```

 

**Constraints:**

- `-105 <= num <= 105`
- There will be at least one element in the data structure before calling `findMedian`.
- At most `5 * 104` calls will be made to `addNum` and `findMedian`.

 

**Follow up:**

- If all integer numbers from the stream are in the range `[0, 100]`, how would you optimize your solution?
- If `99%` of all integer numbers from the stream are in the range `[0, 100]`, how would you optimize your solution?

## 题目大意

中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。

例如，

* `[2,3,4]` 的中位数是 3

* `[2,3]` 的中位数是 `(2 + 3) / 2 = 2.5`

实现一个 MedianFinder 类：

- `MedianFinder()` 初始化 `MedianFinder` 对象
- `void addNum(int num)` 从数据流中将`num` 添加到数据结构中
- `double findMedian()` 返回所有的目前所有数的中位数. Answers within `10-5` of the actual answer will be accepted.

**进阶要求**

* 如果数据流中的整数的范围是[0, 100]，你如何优化你的方案
* 如果数据流中 99% 的证书在范围 [0, 100]，你如何优化你的方案

## 解题思路

这道题目剑指offer 上也有讲过的，

### Solution 1:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/find-median-from-data-stream/solution/gong-shui-san-xie-jing-dian-shu-ju-jie-g-pqy8/

这种解法就是利用一个大顶堆和一个小顶堆来维护中位数，难点在于增加元素的时候，如何调整两个堆中的元素

````c++
class MedianFinder {
public:
    MedianFinder() : size_(0) {
        
    }
    
    void addNum(int num) {
        if (size_ % 2 != 0) {
            // 如果元素数量是奇数
            if (num > max_heap_.top()) {
                // 如果该值大于左侧大顶堆的最大值
                min_heap_.push(num);
            } else {
                min_heap_.push(max_heap_.top());  // 将小顶堆的最大值加入移动到小顶堆的中
                max_heap_.pop();
                max_heap_.push(num);  // 将该值加入小顶堆
            }
        } else {
            // 如果元素数量是偶数
            if (min_heap_.empty() || num <= min_heap_.top()) {
                // 如果右边的小顶堆为空，或者该值小于小顶堆的最小值
                // 直接加入大顶堆
                max_heap_.push(num);
            } else {
                // 反之，如果右边的小顶堆不空，且小顶堆的最小值小于该值
                max_heap_.push(min_heap_.top());  // 取右侧小顶堆的最小值加入左侧大顶堆
                min_heap_.pop();
                min_heap_.push(num);  // 将该值加右侧小顶堆
            }
        }
        ++size_;  // 递增计数
    }
    
    double findMedian() {
        if (size_ % 2 != 0) {
            // 如果是奇数，则从左半边的大顶堆中取
            return max_heap_.top();
        } else {
            // 如果是偶数，则从两个堆中都取
            return (max_heap_.top() + min_heap_.top()) / 2.0;
        }
    }
    
 private:
    int size_;  // 元素数量
    priority_queue<int> max_heap_;  // 左侧的大顶堆
    priority_queue<int, vector<int>, greater<int>> min_heap_;  // 右侧的小顶堆
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
````

