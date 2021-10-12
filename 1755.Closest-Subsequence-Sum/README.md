# [1755. Closest Subsequence Sum](https://leetcode.com/problems/closest-subsequence-sum/)

## 题目

You are given an integer array `nums` and an integer `goal`.

You want to choose a subsequence of `nums` such that the sum of its elements is the closest possible to `goal`. That is, if the sum of the subsequence's elements is `sum`, then you want to **minimize the absolute difference** `abs(sum - goal)`.

Return *the **minimum** possible value of* `abs(sum - goal)`.

Note that a subsequence of an array is an array formed by removing some elements **(possibly all or none)** of the original array.

 

**Example 1:**

```
Input: nums = [5,-7,3,5], goal = 6
Output: 0
Explanation: Choose the whole array as a subsequence, with a sum of 6.
This is equal to the goal, so the absolute difference is 0.
```

**Example 2:**

```
Input: nums = [7,-9,15,-2], goal = -5
Output: 1
Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
The absolute difference is abs(-4 - (-5)) = abs(1) = 1, which is the minimum.
```

**Example 3:**

```
Input: nums = [1,2,3], goal = -7
Output: 7
```

 

**Constraints:**

- `1 <= nums.length <= 40`
- `-107 <= nums[i] <= 107`
- `-109 <= goal <= 109`

## 题目大意

给定一个整数数组 nums 和一个整数 goal，选出一个子数组，子数组的和是 sum，使得 abs(sum - goal) 的值最小，

返回 abs(sum - goal) 的最小值

## 解题思路

这道题要用到双向 DFS ，可以参考这篇题解：https://leetcode-cn.com/problems/closest-subsequence-sum/solution/cshuang-xiang-dfs-by-xiaoneng-et83/

### 解法1

因为这道题目的数据量比较大，如果直接枚举所有数组的话，时间复杂度会很高，所以这种解法将数组 一分为 2，分别搜索两部分来降低时间复杂度

* 搜索前半部分，枚举所有组合可能产生的和，然后排序
* 搜索后半部分，枚举后半段可能产生的 he，然后二分超找前半段已经排序的结果，找到小于等于目标的最大位
* 每次更新 res，我们都要判断goal 的两边，比较得出最接近 goal 的位置

````c++
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        len_ = nums.size();
        cnt_ = 0;
        goal_ = goal;
        res_ = INT_MAX;
        q_.resize(N);
        
        // 先搜索前一半，给搜索完的数组排序，便于在搜索后一半数组的时候，进行二分
        DFS1(nums, 0, 0);
        sort(q_.begin(), q_.begin() + cnt_);
        // 搜索后一半
        DFS2(nums, (len_ + 1) / 2, 0);
        
        return res_;
    }
    
 private:
    static const int N = 2e6+10;
    int len_;
    int cnt_;
    int goal_;
    int res_;
    vector<int> q_;
    
    void DFS1(const vector<int>& nums, int idx, int sum) {
        // 找到一个可行的解
        if (idx == (len_ + 1) / 2) {  // len_ 向上取整，前半部分为 [0, len_ / 2]
            q_[cnt_++] = sum;
            return;
        }
        
        // 选或者不选
        DFS1(nums, idx + 1, sum);
        DFS1(nums, idx + 1, sum + nums[idx]);
    }
    
    void DFS2(const vector<int>& nums, int idx, int sum) {
        // 找到一个可行的解
        if (idx == len_) {  // 后半部分为 [len_ / 2 + 1, len_ - 1]
            // 对前半部分进行二分查找
            int left = 0;
            int right = cnt_ - 1;
            
            while (left < right) {
                int mid = left + (right - left + 1) / 2;  //向上取整，避免 left 取不到 right造成死循环
                
                if (q_[mid] + sum <= goal_) {  // mid 满足check，向右逼近，mid 可能就是最后的结果，所以 left = mid
                    left = mid;
                } else {  // mid 不满足check，向左逼近，因为mid 不可能是最后的结果，所以 right = mid - 1
                    right = mid - 1;
                }
            }
            
            // 更新 res_ 
            res_ = min(res_, abs(q_[right] + sum - goal_)); 
            // 若 right 有下一个元素，那么最近 goal 的元素要么 <= goal_ 要么 > goal_
            // 如果要判断两个值
            if (right + 1 < cnt_) {
                res_ = min(res_, abs(q_[right + 1] + sum - goal_));
            }
            return;
        }
        
        // 选或者不选
        DFS2(nums, idx + 1, sum);
        DFS2(nums, idx + 1, sum + nums[idx]);
    }
};
````

