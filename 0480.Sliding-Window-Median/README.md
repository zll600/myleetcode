# [480. Sliding Window Median](https://leetcode.com/problems/sliding-window-median/)

## 题目

The **median** is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.

- For examples, if `arr = [2,3,4]`, the median is `3`.
- For examples, if `arr = [1,2,3,4]`, the median is `(2 + 3) / 2 = 2.5`.

You are given an integer array `nums` and an integer `k`. There is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return *the median array for each window in the original array*. Answers within `10-5` of the actual value will be accepted.

 

**Example 1:**

```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
Explanation: 
Window position                Median
---------------                -----
[1  3  -1] -3  5  3  6  7        1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7        3
 1  3  -1  -3 [5  3  6] 7        5
 1  3  -1  -3  5 [3  6  7]       6
```

**Example 2:**

```
Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
```

 

**Constraints:**

- `1 <= k <= nums.length <= 105`
- `231 <= nums[i] <= 231 - 1`

## 题目大意

中位数是一个有序序列中间的数，奇数个数的中位数是中间的数，偶数个数的中位数是中间两个数的平均数，

给定一个数组 nums 和一个窗口大小 k，滑动窗口从最左边滑向最右边，你只能看到窗口中的 k 个数，每次窗口向右滑动一个位置，

返回一个数组，数组中的每个值都是当前窗口的中位数，

## 解题思路

* 暴力解法，将窗口内的元素都排许，时间复杂度 O(n * k)
* 另一种思路是用两个优先队列，大顶堆里面的元素都比小顶堆里面的元素小。小顶堆里面存储排序以后中间靠后的值大的元素，大顶堆里面存储排序以后中间靠前的值小的元素。如果 k 是偶数，那么两个堆都有 k/2 个元素，中间值就是两个堆顶的元素；如果 k 是奇数，那么小顶堆比大顶堆多一个元素，中间值就是小顶堆的堆顶元素。删除一个元素，元素都标记到删除的堆中，取 top 的时候注意需要取出没有删除的元素。时间复杂度 O(n * log k) 空间复杂度 O(k)
* 也可以使用一个大顶堆和一个小顶堆（对顶堆），大顶堆里面的元素都比小顶堆小。大顶堆存储排序后中间考前值比较小的元素，小顶堆存储排序之后中间靠后值大的元素。
  * 初始化：将前 k 个元素全部加入 min_heaps 中，然后从 min_heaps 中将 k / 2 个元素加入到 max_heaps 中
  * 取中位数：如果 k 是偶数，两个堆都有 k / 2 个元素，中位数就是两个堆顶的元素之和的二分之一；如果 k 是奇数，中间值是小顶堆的堆顶元素。
  * 窗口滑动的过程：
    * 假定每次滑动之后，min_heaps 和 max_heaps 的大小相差小于等于 1 ，设置当前滑动之前，delta = 0，delta表示因本次窗口滑动而造成的两个堆之间的差值的增量
    * 删除窗口左边界的元素：left = nums[i - k] ，堆只能删除堆顶的元素
      * 使用一个 map 记录这次要删除的数，等到这个数到堆顶的时候再删除，
      * 做了删除标记之后需要，可以视为这时，两个堆中元素的差量已经发生变化，如果 left <= min_heaps.top()，说明 left 在min_heaps 中，--delta，否则 ++delta
    * 向右扩大窗口：如果 nums[i] <= min_heaps.top() 就加入 min_heaps 中，且 ++delta，否则就加入 max_heaps 中，且 --delta
    * 调整两个堆的大小：根据 delta 标记
      * delta == 0 不用调整，
      * delta < 0 将 max_heap 的元素加入 min_heap 中，
      * delta > 0 将 min_heap 的元素加入 max_heap 中
    * 调整完成后，需要清除部分删除元素，如果 堆顶的元素属于被删除元素，则必须调整堆，不能让被删除元素影响中位数的计算，
      * 这里注意我们只需要清除 会影响计算中位数的 被标记的值（此时肯定在堆顶），其他值可以暂时不用考虑，等到它到堆顶的时候，可以在进行删除
    * 计算添加中位数

## 代码

````c++
// 解法一： 暴力枚举
class Solution {
 public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int size = nums.size();
        
        vector<double> res;
        
        list<int> window(nums.begin(), nums.begin() + k);
        window.sort();
        res.push_back(GetMedian(window, k));
        
        for (int i = k; i < size; ++i) {
            RemoveFromWindow(window, nums[i - k]);
            InsertInWindow(window, nums[i]);
            res.push_back(GetMedian(window, k));
        }
        
        return res;
    }
    
 private:
    double GetMedian(const list<int>& window, int k) {
        auto it = window.begin();
        if (k == 1) {	// 如果窗口为 1 则后面的逻辑不再适用
            return *it;
        }
        
        for (int i = 1; i < k / 2 && it != window.end(); ++i) {
            ++it;
        }
        
        if (k % 2 != 0) { // 为避免 k 为负数，这里不使用 k % 2 == 1
            return *++it;
        }
        
        return (*it / 2.0 + *++it / 2.0);	// 出现加法，需要考虑溢出，先除再加
    }
    
    void RemoveFromWindow(list<int>& window, int val) {
        for(auto it = window.begin(); it != window.end(); ++it) {
            if (*it == val) {
                window.erase(it);
                return; // 这里立即返回，由于在调用erase方法以后，该元素的位置已经被删除，
                        // 如果在根据这个旧的位置来获取下一个位置，则会出现异常。
            }
        }
    }
    
    void InsertInWindow(list<int>& window, int val) {
        for (auto it = window.begin(); it != window.end(); ++it) {
            if (*it >= val) {
                window.insert(it, val);
                return;
            }
        }
        window.push_back(val);
    }
};

// 解法二：用两个堆实现，
class Solution {
 public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        int size = nums.size();
        
        for (int i = 0; i < k; ++i) {
            min_heaps_.push(nums[i]);
        }
        for (int i = 0; i < k / 2; ++i) {
            max_heaps_.push(min_heaps_.top());
            min_heaps_.pop();
        }
        res.push_back(GetMedian(k));
        
        for (int i = k; i < size; ++i) {
            int delta = 0;
            int left = nums[i - k];
            cache_[left]++;
            
            if (!min_heaps_.empty() && left <= min_heaps_.top()) {
                --delta;
            } else {
                ++delta;
            }
            
            if (!min_heaps_.empty() && nums[i] <= min_heaps_.top()) {
                min_heaps_.push(nums[i]);
                ++delta;
            } else {
                max_heaps_.push(nums[i]);
                --delta;
            }
            
            if (delta < 0) {
                min_heaps_.push(max_heaps_.top());
                max_heaps_.pop();
            } else if (delta > 0) {
                max_heaps_.push(min_heaps_.top());
                min_heaps_.pop();
            }
            
            while (!min_heaps_.empty() && cache_[min_heaps_.top()] > 0) {
                --cache_[min_heaps_.top()];
                min_heaps_.pop();
            }
            
            while (!max_heaps_.empty() && cache_[max_heaps_.top()] > 0) {
                --cache_[max_heaps_.top()];
                max_heaps_.pop();
            }
            
            res.push_back(GetMedian(k));
        }
        
        return res;
    }
    
 private:
    priority_queue<int> min_heaps_;
    priority_queue<int, vector<int>, greater<int>> max_heaps_;
    unordered_map<int, int> cache_;
    
    double GetMedian(int k) {
        if (k % 2 != 0) {
            return min_heaps_.top() * 1.0;
        } else {
            return (min_heaps_.top() / 2.0 + max_heaps_.top() / 2.0);
        }
    }
};
````

