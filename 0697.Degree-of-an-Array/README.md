# [697. Degree of an Array](https://leetcode.com/problems/degree-of-an-array/)

## 题目大意

Given a non-empty array of non-negative integers `nums`, the **degree** of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of `nums`, that has the same degree as `nums`.

 

**Example 1:**

```
Input: nums = [1,2,2,3,1]
Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
```

**Example 2:**

```
Input: nums = [1,2,2,3,1,4,2]
Output: 6
Explanation: 
The degree is 3 because the element 2 is repeated 3 times.
So [2,2,3,1,4,2] is the shortest subarray, therefore returning 6.
```

 

**Constraints:**

- `nums.length` will be between 1 and 50,000.
- `nums[i]` will be an integer between 0 and 49,999.

## 解题思路

给定一个由非负整数组成的非空数组，数组的度的定义是指数组里任一元素出现频数的最大值。你的任务是找到与 `nums` 拥有相同大小的度的最短连续子数组，返回其长度


### Solution 1:

 [这种解法](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0697.Degree-of-an-Array/),就是在遍历的时候需要去做一个记录,然后跳出符合条件的即可

````c++
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        // tuple<int, int, int> freq, start, end,
        unordered_map<int, tuple<int, int, int>> freq;
        int max_freq = 0;
        const int len = nums.size();
        // 遍历的时候设置 freq
        for (int i = 0; i < len; ++i) {
            if (freq.find(nums[i]) == freq.end()) {
                // 这里初始化一个数的记录
                freq.emplace(nums[i], make_tuple(1, i, i));
            } else {
                // 更新记录
                ++get<0>(freq[nums[i]]);
                get<2>(freq[nums[i]]) = i;
            }
            
            // max_freq = max(max_freq, freq[nums[i]].get<0>());
            if (max_freq < get<0>(freq[nums[i]])) {
                max_freq = get<0>(freq[nums[i]]);
            }
        }
        
        int res = INT_MAX;
        for (const auto item : freq) {
            if (get<0>(item.second) == max_freq
                && get<2>(item.second) - get<1>(item.second) < res) {
                res = get<2>(item.second) - get<1>(item.second) + 1;
            }
        }
        
        return res;
    }
};
````

