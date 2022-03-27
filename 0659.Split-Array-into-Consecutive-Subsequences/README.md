# [659. Split Array into Consecutive Subsequences](https://leetcode-cn.com/problems/split-array-into-consecutive-subsequences/)

You are given an integer array `nums` that is **sorted in non-decreasing order**.

Determine if it is possible to split `nums` into **one or more subsequences** such that **both** of the following conditions are true:

- Each subsequence is a **consecutive increasing sequence** (i.e. each integer is **exactly one** more than the previous integer).
- All subsequences have a length of `3` **or more**.

Return `true` *if you can split* `nums` *according to the above conditions, or* `false` *otherwise*.

A **subsequence** of an array is a new array that is  formed from the original array by deleting some (can be none) of the  elements without disturbing the relative positions of the remaining  elements. (i.e., `[1,3,5]` is a subsequence of `[1,2,3,4,5]` while `[1,3,2]` is not).

 

**Example 1:**

```
Input: nums = [1,2,3,3,4,5]
Output: true
Explanation: nums can be split into the following subsequences:
[1,2,3,3,4,5] --> 1, 2, 3
[1,2,3,3,4,5] --> 3, 4, 5
```

**Example 2:**

```
Input: nums = [1,2,3,3,4,4,5,5]
Output: true
Explanation: nums can be split into the following subsequences:
[1,2,3,3,4,4,5,5] --> 1, 2, 3, 4, 5
[1,2,3,3,4,4,5,5] --> 3, 4, 5
```

**Example 3:**

```
Input: nums = [1,2,3,4,4,5]
Output: false
Explanation: It is impossible to split nums into consecutive increasing subsequences of length 3 or more.
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-1000 <= nums[i] <= 1000`
- `nums` is sorted in **non-decreasing** order.

## 题目大意

给你一个 *按非降序序排序* 的整数数组 `nums`，

请你将它们分割成一个或者多个满足下列要求的数组:

- 数组的长度至少为 3 的子序列，
- 其中每个子序列都由连续整数组成

如果可以完成上述分割，返回 true ；否则，返回 false 。

## 解题思路


### Solution 1: 

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/split-array-into-consecutive-subsequences/solution/tan-xin-suan-fa-jian-cha-shu-zu-neng-fou-bei-fen-w/)

这里注意，下面的 if 分支的顺序是不能更改的，必须先判断能否和之前的数组拼接到一起，然后再判断能否自己构成一个新的数组，这样才能做到贪心的判断，我们优先构成连续的数组

另外因为这里是循环遍历原来的有序数组，所以可以这里不会出现有的数组过长，导致后面剩下的元素没有办法构成数组，我们一定先消耗完所有小的值，并让他们构成合法的数组，如果一个位置出错，直接返回 false



````c++
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        // 统计数字的频数
        unordered_map<int, int> freq;
        for (int num : nums) {
            ++freq[num];
        }

        // 记录以当前数字结尾的合法数组的数目
        unordered_map<int, int> tail;
        for (int num : nums) {
            if (freq[num] <= 0) {
                continue;
            }

            if (tail[num - 1] > 0 ) {
                // 能否与上一个接上
                --tail[num - 1];
                --freq[num];
                ++tail[num];
            } else if (freq[num] > 0 && freq[num + 1] > 0 && freq[num + 2] > 0) {
                // 形成一个最短的符合条件的数组
                --freq[num];
                --freq[num + 1];
                --freq[num + 2];
                ++tail[num + 2];
            } else {
                return false;
            }
        }

        return true;
    }
};
````
