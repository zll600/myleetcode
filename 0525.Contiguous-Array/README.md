# [525. Contiguous Array](https://leetcode.com/problems/contiguous-array/) 

## 题目

Given a binary array `nums`, return *the maximum length of a contiguous subarray with an equal number of* `0` *and* `1`.

 

**Example 1:**

```
Input: nums = [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
```

**Example 2:**

```
Input: nums = [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `nums[i]` is either `0` or `1`.

## 题目大意

给定一个二进制数组，返回含有相同数量的 0 和 1 得最长子数组，

## 解题思路

* 相等数量的 0 和 1的子数组可以转化子数组所有元素之和为0，题目也就成为了一个区间求和问题，也就可以理解为一个前缀和问题，所以对于区间[i, j]，需要满足 pre_sum[j] - pre_sum[i]  = 0，即pre_sum[i] = pre_sum[j]，
* 这里不用预处理得前缀和数组，可以将前缀和放在遍历数组得过程中进行计算，如果遇到同样大小得 key ，就更新最大值

## 代码

````c++
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> dict;
        dict.insert(make_pair(0, -1));

        int count = 0;
        int size = nums.size();
        int res = 0;
        for (int i = 0; i < size; ++i) {
            if (nums[i] == 0) {
                --count;
            } else {
                ++count;
            }

            if (dict.find(count) != dict.end()) {
                res = max(res, i - dict.at(count)); // 这里形成的是一个左闭右开的区间
            } else  {
                dict.insert(make_pair(count, i));
            }
        }

        return res;
    }
};
````

