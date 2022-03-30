# [1608. Special Array With X Elements Greater Than or Equal X](https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/)

## 题目

You are given an array `nums` of non-negative integers. `nums` is considered **special** if there exists a number `x` such that there are **exactly** `x` numbers in `nums` that are **greater than or equal to** `x`.

Notice that `x` **does not** have to be an element in `nums`.

Return `x` *if the array is **special**, otherwise, return* `-1`. It can be proven that if `nums` is special, the value for `x` is **unique**.

 

**Example 1:**

```
Input: nums = [3,5]
Output: 2
Explanation: There are 2 values (3 and 5) that are greater than or equal to 2.
```

**Example 2:**

```
Input: nums = [0,0]
Output: -1
Explanation: No numbers fit the criteria for x.
If x = 0, there should be 0 numbers >= x, but there are 2.
If x = 1, there should be 1 number >= x, but there are 0.
If x = 2, there should be 2 numbers >= x, but there are 0.
x cannot be greater since there are only 2 numbers in nums.
```

**Example 3:**

```
Input: nums = [0,4,3,0,4]
Output: 3
Explanation: There are 3 values that are greater than or equal to 3.
```

 

**Constraints:**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 1000`

## 题目大意

给你一个非负整数数组 `nums` 。如果存在一个数 `x` ，使得 `nums` 中恰好有 `x` 个元素 大于或者等于 `x` ，那么就称 `nums` 是一个 特殊数组 ，而 `x` 是该数组的 特征值 。（注意： `x` 不必 是 `nums` 的中的元素。）

如果数组 `nums` 是一个 *特殊数组* ，请返回它的特征值 `x` 。否则，返回 `-1` 。可以证明的是，如果 `nums` 是特殊数组，那么其特征值 `x` 是 唯一的 。

## 解题思路



### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1600~1699/1608.Special-Array-With-X-Elements-Greater-Than-or-Equal-X/)

这里我们先将数组进行排序，排序之后，那么 x 和 大于等于 x 的值的个数就可以关联起来了，

然后顺序遍历数组，如果有满足答案的直接返回，如果当前不满足，但是递减 x 之后满足了，那么就可以说明后面都不可能满足，所以这里直接报错就可以了

````c++
class Solution {
public:
    int specialArray(vector<int>& nums) {
        // 先排序，排序之后就 len - i 就是大于等于 x 的数的数目
        sort(nums.begin(), nums.end());

        const int len = nums.size();
        int x = len;
        for (int i = 0; i < len; ++i) {
            // 满足结果直接返回
            if (nums[i] >= x) {
                return x;
            }
            // 更新 x 的值
            --x;
            if (nums[i] >= x) {
                // 这里相当于剪枝，如果当前这里已经满足了，但是数目达不到要求，那么肯定是不成立的
                return -1;
            }
        }

        return -1;
    }
};
````
