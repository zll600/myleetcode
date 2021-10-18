# [1658. Minimum Operations to Reduce X to Zero](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/) 

## 题目

You are given an integer array `nums` and an integer `x`. In one operation, you can either remove the leftmost or the rightmost element from the array `nums` and subtract its value from `x`. Note that this **modifies** the array for future operations.

Return *the **minimum number** of operations to reduce* `x` *to **exactly*** `0` *if it is possible**, otherwise, return* `-1`.

 

**Example 1:**

```
Input: nums = [1,1,4,2,3], x = 5
Output: 2
Explanation: The optimal solution is to remove the last two elements to reduce x to zero.
```

**Example 2:**

```
Input: nums = [5,6,7,8,9], x = 4
Output: -1
```

**Example 3:**

```
Input: nums = [3,2,20,1,1,3], x = 10
Output: 5
Explanation: The optimal solution is to remove the last three elements and the first two elements (5 operations in total) to reduce x to zero.
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `1 <= nums[i] <= 104`
- `1 <= x <= 109`

## 题目大意

给定一个整数数组 nums 和一个整数 x，每一次操作时，你应当移除数组 nums 最左边或最右边的元素，然后从 x 中减去该元素的值。请注意，需要 修改 数组以供接下来的操作使用。如果可以将 x 恰好 减到 0 ，返回 最小操作数 ；否则，返回 -1 。

##  解题思路

题目要求的是移除左右两边的数字使得数组中剩下的元素和为 x 的操作次数，可以反过来求数组中的子串，只要 原数组的总和 - 子串的总和 =  x，就可以更新结果，

如果是求数组中和为定值的子串问题，可以利用滑动窗口来解决

这里有两个边界条件：

* 原数组的和小于 x
* 原数组的最左边和最右边元素都大于 x

````c++
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int target = accumulate(nums.begin(), nums.end(), 0);  // 原数组的总和
        if (target < x || (nums.back() > x && nums.front() > x)) {  // 边界情况
            return -1;
        }
        // 子数组的总和要达到的值
        target -= x;
        
        int left = 0;  // 左边界
        int right = 0;  // 右边界
        int sum = 0;  // 子数组的和
        int res = INT_MAX;  // 要取最小值
        
        const int size = nums.size();
        // [left, right) ，初始为空
        while (right < size) {
            sum += nums[right];  // 右移右边界
            ++right;
            
            while (sum > target) {  // 右移左边界
                sum -= nums[left];
                ++left;
            }
            
            if (sum == target) {
                res = min(res, size - (right - left));
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
};
````

