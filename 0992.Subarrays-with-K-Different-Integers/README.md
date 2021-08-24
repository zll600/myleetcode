# [992. Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)

## 题目

Given an integer array `nums` and an integer `k`, return *the number of **good subarrays** of* `nums`.

A **good array** is an array where the number of different integers in that array is exactly `k`.

- For example, `[1,2,3,1,2]` has `3` different integers: `1`, `2`, and `3`.

A **subarray** is a **contiguous** part of an array.

 

**Example 1:**

```
Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
```

**Example 2:**

```
Input: nums = [1,2,1,3,4], k = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
```

 

**Constraints:**

- `1 <= nums.length <= 2 * 104`
- `1 <= nums[i], k <= nums.length`

## 题目大意

给定一个整数数组，给定数 K 表示，子数组中必须存在 K 种不同的数，返回满足条件的子数组的个数

## 解题思路

用滑动窗口去解决该问题时，会发现会漏掉一部分解（建议在窗口滑动时，自己举例模拟以下为好），比如例一中：[1,2,1,2,3]，一般的滑动窗口会漏掉[2,1]这个解，原因时当窗口不能再向右扩时，才会进行窗口的收缩，而此时，右边界已经无法回到之前的位置

* 如果每次窗口收缩时右边界都跟中左边界一起重新开始扩大窗口，但这样做的代价就是会增加时间复杂度

所以这道题需要再使用一个指针，原窗口左右边界表示存在 K 种不同数的最长字数组，多加一个指针，与原来的左边界一起组成 K - 1种不同数的最长数组，这时最终的结果就是 res = AtMost(nums, K) - AtMost(nums, K - 1)

以例一为例：AtMost(nums, K)的结果是：

````
[1],
[1,2],[2],
[1,2,1],[2,1],[1],
[1,2,1,2],[2,1,2],[1,2],[2],
[2,3],[3]
````

每当窗口滑动到把 K 消耗为 0 的时候，res = right - left + 1 。为什么要这么计算，right - left + 1 代表的含义是，终点为 right，至多为 K 个元素的窗口有多少个。[left,right], [left + 1,right], [left + 2,right] …… [right,right]。这样算出来的解是包含这道题最终求得的解的，还多出了一部分解。多出来的部分减掉即可，即减掉最多为 K - 1 个元素的解。

每当窗口滑动到把 K 消耗为0的时候，res = right - left + 1, right - left + 1 的含义是，终点为 right，至多为 K 个元素的窗口有多少个。

[left,right], [left + 1, right],[left + 2, right]...[right, right],这样算出来的解是包含这道题最终求得的解，但还多了一部分解，需要减掉多出来的那部分，即减掉最多为 K - 1 个元素的解

AtMost(nums, K - 1)的结果是：

````
[1]，
[2],
[1],
[2],
[3]
````

二者相减之后得到最终结果：

````
[1,2],
[1,2,1],[2,1],
[1,2,1,2],[2,1,2],[1,2]
[2,3]
````

## 代码

````c++
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return subarrayWithKDistinctSlideWindow(nums, k) 
            - subarrayWithKDistinctSlideWindow(nums, k - 1);
    }
    
 private:
    int subarrayWithKDistinctSlideWindow(const vector<int>& nums, int k) {
        int size = nums.size();
        
        int res = 0;
        int left = 0;
        int right = 0;
        int counter = k;
        
        unordered_map<int, int> freq;
        
        for (right = 0; right < size; ++right) {
            if (freq[nums[right]]== 0) {
                --counter;
            }
            ++freq[nums[right]];
            
            while (counter < 0) {					// 这里必须用 while，不能用 if
                if (--freq[nums[left]] == 0) {
                    ++counter;
                }
                ++left;
            }
            res += right - left + 1;
        }
        return res;
    }
};
````

