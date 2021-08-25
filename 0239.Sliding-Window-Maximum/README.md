# [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)

## 题目

You are given an array of integers `nums`, there is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return *the max sliding window*.

 

**Example 1:**

```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
```

**Example 2:**

```
Input: nums = [1], k = 1
Output: [1]
```

**Example 3:**

```
Input: nums = [1,-1], k = 1
Output: [1,-1]
```

**Example 4:**

```
Input: nums = [9,11], k = 2
Output: [11]
```

**Example 5:**

```
Input: nums = [4,-2], k = 2
Output: [4]
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-104 <= nums[i] <= 104`
- `1 <= k <= nums.length`

## 题目大意

给定一个整数数组和一个大小为 size 的滑动窗口，滑动窗口从最左边滑向最右边，每次只滑动一个位置，你只能看到窗口中的 k 个数，返回滑动窗口的最大值。

## 解题思路

* 暴力解法，双重循环，时间复杂度O(n * k)
* 利用双端队列，队列的前面保存的永远都是窗口中最大值的下标，另一边保存比最大值小的值的下表，滑动窗口的同时，更新队列，
  * 更新队列的条件是：不断弹出队尾的值，直到找到队列中第一个比当前值大的值的下标或者队列为空，件当前值的下标加入队列
  * 如果当前队列队首保存的下标已经不在窗口中了，就弹出队首。

## 代码

````
class Solution {
public:
    // Bource Force
    /* Time Limit Exceeded
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int size = nums.size();
        
        vector<int> res;
        for (int i = 0; i <= size - k; ++i) {
            int item = nums[i];
            for (int j = 1; j < k; ++j) {
                if (item < nums[i + j]) {
                    item = nums[i + j];
                }
            }
            res.push_back(item);
        }
        return res;
    }
    */
    
    // use  deque
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int size = nums.size();
        
        vector<int> res;
        deque<int> window;
        
        for (int i = 0; i < size; ++i) {
            if (i >= k && window.front() <= i - k) {
                window.pop_front();
            }
            
            while (!window.empty() && nums[window.back()] < nums[i]) {
                window.pop_back();
            }
            window.push_back(i);
            
            if (i >= k - 1) {
                res.push_back(nums[window.front()]);
            }
        }
        
        return res;
    }
    
};
````

