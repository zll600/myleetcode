# [581. Shortest Unsorted Continuous Subarray](https://leetcode.com/problems/shortest-unsorted-continuous-subarray/)

## 题目

Given an integer array `nums`, you need to find one **continuous subarray** that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order.

Return *the shortest such subarray and output its length*.

 

**Example 1:**

```
Input: nums = [2,6,4,8,10,9,15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
```

**Example 2:**

```
Input: nums = [1,2,3,4]
Output: 0
```

**Example 3:**

```
Input: nums = [1]
Output: 0
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-105 <= nums[i] <= 105`

 

**Follow up:** Can you solve it in `O(n)` time complexity?

## 题目大意

给定一个整数数组 `nums`，你需要找到一个连续的子数组，如果你能让这个子数组为升序，那么真个数组都可以排为升序，返回这样的最短的子数组，输出它的长度

## 解题思路

这里有一个难点就是可能出现相等的值，举例有 `[1, 2, 2, 2, 2]`，`[1,3,2,2,2]`


### Solution 1:

这种解法还是比较好理解的，

````c++
class Solution {
 public:
    int findUnsortedSubarray(vector<int>& nums) {
        const int len = nums.size();

        // 复制一个数组，然后排序，
        vector<int> other(nums.begin(), nums.end());
        sort(other.begin(), other.end());

        // 找到开头和结尾都不相同的位置
        int low = 0;
        for (int i = 0; i < len; ++i) {
            if (other[i] != nums[i]) {
                low = i;
                break;
            }
        }

        int high = 0;
        for (int i = len - 1; i >= 0; --i) {
            if (other[i] != nums[i]) {
                high = i;
                break;
            }
        }

        return low == high ? 0 : high - low + 1;
    }
};

````
