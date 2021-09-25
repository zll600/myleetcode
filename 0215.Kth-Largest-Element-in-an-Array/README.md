# [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) 

## 题目

Given an integer array `nums` and an integer `k`, return *the* `kth` *largest element in the array*.

Note that it is the `kth` largest element in the sorted order, not the `kth` distinct element.

 

**Example 1:**

```
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
```

**Example 2:**

```
Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
```

 

**Constraints:**

- `1 <= k <= nums.length <= 104`
- `-104 <= nums[i] <= 104`

## 题目大意

给定一个证书数组和一个整数 k，返回第 k 大的元素，

## 解题思路

* 这道题目可以使用暴力解法，现排序然后直接取值，这里注意按照升序排序之后，第 k 大的元素是从右向左数第 k 个，从左向右数是第 len - k 个，其中len 为数组的长度
* 还有一种做法是利用快速排序算法中的 partition 操作来调整，不需要要将整个数组排序，只需要局部有序即可，所以可以提高效率
* 这道题目还可以使用优先级队列来做，利用一个小顶堆来实现，做法就是堆满之后，更新堆时，只有比堆顶大的元素，才会进入堆，

这里放上一篇我觉得比较好的题解：https://leetcode-cn.com/problems/kth-largest-element-in-an-array/solution/partitionfen-er-zhi-zhi-you-xian-dui-lie-java-dai-/

## 代码

``````c++
class Solution1 {
public:
    // 暴力解法
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};

class Solution2 {
 public:
    int findKthLargest(vector<int>& nums, int k) {
        int target = nums.size() - k;
        
        int lo = 0;
        int hi = nums.size() - 1;
        while (true) {
            int pivot_idx = Partition(nums, lo, hi);
            
            if (pivot_idx == target) {
                return nums[target];
            } else if (pivot_idx < target){
                lo = pivot_idx + 1;
            } else {
                hi = pivot_idx - 1;
            }
        }
        
        return -1;
    }
    
 private:
    int Partition(vector<int>& nums, int lo, int hi) {
        if (hi > lo) {  // 这里必须是随机选，否则 partition 的效率会很低
            int pivot_idx = rand() % (hi - lo + 1) + lo;
            swap(nums[lo], nums[pivot_idx]);
        }
        
        int pivot = nums[lo];
        int lt = lo;    // lt 的初始值是 lo，先右移再交换
        
        // 循环不变量
        // all in [lo, lt] < pivot
        // all in [lt + 1, i) >= pivot
        for (int i = lo + 1; i <= hi; i++) {
            if (nums[i] < pivot) {
                ++lt;
                swap(nums[lt], nums[i]);
            }
        }
        // 在之前的遍历过程中满足 [left + 1， lt] < pivot, (lt, i) >= pivot
        swap(nums[lo], nums[lt]);
        // 交换之后 [lo, lt) < pivot, [lt, i]  >= pivot;
        return lt;
    }
};

// 使用优先级度列来维护一个小顶堆，
class Solution {
 public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> que;
        
        // 先压入 k 个元素
        for (int i = 0; i < k; i++) {
            que.push(nums[i]);
        }
        
        // 遍历剩下的所有元素，更新堆
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] > que.top()) {
                que.pop();
                que.push(nums[i]);
            }
        }
        
        return que.top();
    }
};
``````

