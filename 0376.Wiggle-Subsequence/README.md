# [376. Wiggle Subsequence](https://leetcode.com/problems/wiggle-subsequence/)

## 题目

A **wiggle sequence** is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.

- For example, `[1, 7, 4, 9, 2, 5]` is a **wiggle sequence** because the differences `(6, -3, 5, -7, 3)` alternate between positive and negative.
- In contrast, `[1, 4, 7, 2, 5]` and `[1, 7, 4, 5, 5]` are not wiggle sequences. The first is not because its first two differences are positive, and the second is not because its last difference is zero.

A **subsequence** is obtained by deleting some elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.

Given an integer array `nums`, return *the length of the longest **wiggle subsequence** of* `nums`.

 

**Example 1:**

```
Input: nums = [1,7,4,9,2,5]
Output: 6
Explanation: The entire sequence is a wiggle sequence with differences (6, -3, 5, -7, 3).
```

**Example 2:**

```
Input: nums = [1,17,5,10,13,15,10,5,16,8]
Output: 7
Explanation: There are several subsequences that achieve this length.
One is [1, 17, 10, 13, 10, 16, 8] with differences (16, -7, 3, -3, 6, -8).
```

**Example 3:**

```
Input: nums = [1,2,3,4,5,6,7,8,9]
Output: 2
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `0 <= nums[i] <= 1000`

 

**Follow up:** Could you solve this in `O(n)` time?

## 题目大意

一个摆动序列是指这个序列连续的数字的差，严格的在正数和负数之间交替，第一个两数之差可以为正数也可以为负数，一个只含有一个数字的序列和两个不相等数字的序列也被认为是摆动序列，

* 例如， [1, 7, 4, 9, 2, 5] 是一个 摆动序列 ，因为差值 (6, -3, 5, -7, 3) 是正负交替出现的。

* 相反，[1, 4, 7, 2, 5] 和 [1, 7, 4, 5, 5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。

子序列可以通过从原序列中删除一些数（也可以不删除）得到，留下的元素保持原来的顺序

给定一个数组，求这个数组的最长摆动子序列，

## 解题思路

这道题目中我们需要判断相邻两数之差的正负情况，这里偷个懒，只需要判断两个数的大小情况即可，强烈建议画图来计算

这道题目我们不需要真的作删除，只需要做记录就可以，

这道题如果将其画出来，我们只需要记录峰值点即可，这道题在找峰值的时候也利用了一些哨兵的思想，

## 代码

``````c++
class Solution {
public:
    int wiggleMaxLength1(vector<int>& nums) {
        if (nums.size() == 1) {
            return 1;
        }
        if (nums.size() == 2 && nums[1] != nums[0]) {
            return 2;
        }
        
        int cur_diff = 0;   // 当前一对差值
        int pre_diff = 0;   // 前一对差值
        int res = 1;    // 记录出现的峰值数目
        
        for (int i = 0; i < nums.size() - 1; ++i) {
            cur_diff = nums[i + 1] - nums[i];
            // 出现峰值
            if ((cur_diff > 0 && pre_diff <= 0)
               || (cur_diff < 0 && pre_diff >= 0)) {
                ++res;
                pre_diff = cur_diff;
            }
        }
        
        return res;
    }
    
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        
        int res = 1;
        // 保存上一次的状态，这里取0 利用了哨兵的思想
        // 0 表示相等（可以理解为向前插入一个相等的），1 表示当前的比前一个大，-1，表示当前的比前一个小
        int state = 0;
        
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1] && (state == 0 || state == -1)) {
                ++res;
                state = 1;
            } else if (nums[i] < nums[i - 1] && (state == 0 || state == 1)) {
                ++res;
                state = -1;
            }
        }
        
        return res;
    }
};
``````

