# [1493. Longest Subarray of 1's After Deleting One Element](https://leetcode-cn.com/problems/longest-subarray-of-1s-after-deleting-one-element/)

## 题目

Given a binary array `nums`, you should delete one element from it.

Return *the size of the longest non-empty subarray containing only* `1`*'s in the resulting array*. Return `0` if there is no such subarray.
 

**Example 1:**

```
Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.
```

**Example 2:**

```
Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray with value of 1's is [1,1,1,1,1].
```

**Example 3:**

```
Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `nums[i]` is either `0` or `1`.

## 题目大意

给你一个二进制数组 nums ，你需要从中删掉一个元素。

请你在删掉元素的结果数组中，返回最长的且只包含 1 的非空子数组的长度。

如果不存在这样的子数组，请返回 0 。

## 解题思路

这里我们要解决的问题有
- 如果字符串中没有 0，那么几句删除一个 1即可
- 如果字符串中有 0，找到一个位置，删除该位置的 0，使得两侧的 1 的数量之和最大，


### Solution 1:

这种解法就是遍历每一个为 0 的位置，求出两侧 1 的数量最大的地方，

````c++
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        const int len = nums.size();
        
        int res = 0;
        bool never = true;
        for (int i = 0; i < len; ++i) {
            if (nums[i] == 1) {
                continue;
            }
            
            never = false;
            res = max(res, Calc(nums, i));
        }
        
        return never ? len - 1 : res;
    }
    
 private:
    int Calc(const vector<int>& nums, int idx) {
        const int len = nums.size();
        
        int left = idx - 1;
        while (left >= 0 && nums[left] == 1) {
            --left;
        }
        
        int right = idx + 1;
        while (right < len && nums[right] == 1) {
            ++right;
        }
        
        return idx - left - 1 + right - idx - 1;
    }
};
````
