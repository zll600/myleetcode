# [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)

## 题目

Given a binary array `nums` and an integer `k`, return *the maximum number of consecutive* `1`*'s in the array if you can flip at most* `k` `0`'s.

 

**Example 1:**

```
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
```

**Example 2:**

```
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `nums[i]` is either `0` or `1`.
- `0 <= k <= nums.length`

## 题目大意

给定一个只包含0和1的整数数组，K表示可以将0转化为1的最多次数，返回经过变换后，最长的连续的1的个数的字数

## 解题思路

利用“滑动窗口”，不断更新和维护最长长度

* 窗口扩大的条件：
  * 右边界元素为1
  * 右边界元素为0，且K大于0
* 更新最长长度的条件：
  * 如果 k == 0
  * 即使 k > 0 但是右边界已经到达最右

## 代码

````c++
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int size = nums.size();
        
        int left = 0;
        int right = 0;
        int res = 0;
        
        while (left < size) {		// 这里不能用右边界来判断，而应该用左边界（几乎所有的“滑动窗口”求值题目都以左边界来判断）
            if (right < size		// 这样才可以在处理存在重复元素时依旧可以更新最长长度
                && ((nums[right] == 1)
                   || (nums[right] == 0 && k > 0))) {
                if (nums[right] == 0) {
                    --k;
                }
                ++right;
            } else {
                if (k == 0 || (right == size && k > 0)) {	// 处理重复
                    res = max(res, right - left);
                }
                
                if (nums[left] == 0) {
                    ++k;
                }
                ++left;
            }
        }
        
        return res;
    }
};
````



