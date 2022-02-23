# [330. Patching Array](https://leetcode-cn.com/problems/patching-array/)

## 题目

Given a sorted integer array `nums` and an integer `n`, add/patch elements to the array such that any number in the range `[1, n]` inclusive can be formed by the sum of some elements in the array.

Return *the minimum number of patches required*.

 

**Example 1:**

```
Input: nums = [1,3], n = 6
Output: 1
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
```

**Example 2:**

```
Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].
```

**Example 3:**

```
Input: nums = [1,2,2], n = 5
Output: 0
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `1 <= nums[i] <= 104`
- `nums` is sorted in **ascending order**.
- `1 <= n <= 231 - 1`

## 题目大意

给定一个已排序的数组 nums 和一个整数 n，从 [1, n] 区间内选取任意个数字补充到 nums 中，使得 [1, n] 区间内的任何数字都可以用 nums 中某几个数字的和来表示。请输出满足上述要求的最少需要补充的数字个数。

## 解题思路

这里注意，题目给出的数据是有序的。

这道题目利用了贪心的思想，如果数组中的数不能形成数组上边界的连续移动，就必须添加额外的数

### Soluton 1:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/patching-array/solution/an-yao-qiu-bu-qi-shu-zu-tan-xin-suan-fa-b4bwr/



```c++
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int total = 0; // 当前的上界
        int count = 0; // 需要补的数的数目
        const int len = nums.size(); // 长度
        int idx = 0; // 数组下标
        while (total < n) {
            if (idx < len && nums[idx] <= total + 1) {
                // 如果数组能组成的数字范围是[1,total]，那么加上nums[index]
                // 就变成了[1,total]U[nums[index],total+nums[index]]
                // 结果就是[1,total+nums[index]]
                total += nums[idx++]; // 更新上界
            } else {
                // 否则需要补一个数
                total += total + (total + 1);
                ++count;
            }
        }
        
        return count;
    }
};
```

