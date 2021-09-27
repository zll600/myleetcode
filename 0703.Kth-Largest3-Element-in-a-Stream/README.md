# [703. Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/)

## 题目

Design a class to find the `kth` largest element in a stream. Note that it is the `kth` largest element in the sorted order, not the `kth` distinct element.

Implement `KthLargest` class:

- `KthLargest(int k, int[] nums)` Initializes the object with the integer `k` and the stream of integers `nums`.
- `int add(int val)` Appends the integer `val` to the stream and returns the element representing the `kth` largest element in the stream.

 

**Example 1:**

```
Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output
[null, 4, 5, 5, 8, 8]

Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8
```

 

**Constraints:**

- `1 <= k <= 104`
- `0 <= nums.length <= 104`
- `-104 <= nums[i] <= 104`
- `-104 <= val <= 104`
- At most `104` calls will be made to `add`.
- It is guaranteed that there will be at least `k` elements in the array when you search for the `kth` element.

## 题目大意

设计一个类，找到数据流中第 k 大的数，注意是排序后的第 k 大元素，不是第 k 个不同的元素。请实现 KthLargest 类：

- KthLargest(int k, int[] nums) 使用整数 k 和整数流 nums 初始化对象。
- int add(int val) 将 val 插入数据流 nums 后，返回当前数据流中第 k 大的元素。

## 解题思路

这道题目是典型的 topk 问题，这里给出常见的几种解法

这里放上几个相关的链接，我觉得讲的比较好：https://mp.weixin.qq.com/s/FFsvWXiaZK96PtUg-mmtEw

#### 解法1：冒泡排序（TLE）

冒泡排序的问题在于每次插入新的元素，都需要重新查找，这里就增加了时间复杂度

`````c++
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums)
        : k_(k),
        nums_(nums.begin(), nums.end()) {
    }
    
    int add(int val) {
        nums_.push_back(val);
        int cur = 0;
        // 查找 k 次最大的数
        for (int i = 0; i < k_; i++) {
            int idx = FindMaxIndex(cur, nums_.size() - 1);
            swap(nums_[cur], nums_[idx]);
            cur++;
        }
        
        return nums_[cur - 1];
    }
    
 private:
    int k_;
    vector<int> nums_;
    
    // 找出剩余元素中最大的数
    int FindMaxIndex(int lo, int hi) {
        int res = lo;
        int max_val = nums_[lo];
        
        for (int i = lo + 1; i <= hi; i++) {
            if (nums_[i] > max_val) {
                max_val = nums_[i];
                res = i;
            }
        }
        
        return res;
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
`````

### 解法2（快速排序）

### 解法3（堆结构）

这里维护一个最小堆，每次添加新数的时候直接加，加完然后再调整

`````c++
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : k_(k) {
        for (int num : nums) {
            min_heap_.push(num);
        }
    }
    
    int add(int val) {
        min_heap_.push(val);
        
        while (min_heap_.size() > k_) {
            min_heap_.pop();
        }
        
        return min_heap_.top();
    }
    
 private:
    int k_;
    priority_queue<int, vector<int>, greater<int>> min_heap_;
    
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
`````

