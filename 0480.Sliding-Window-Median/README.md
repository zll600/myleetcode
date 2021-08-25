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
* 

## 代码

````c++
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
````

