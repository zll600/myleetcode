# [1144. Decrease Elements To Make Array Zigzag](https://leetcode.cn/problems/decrease-elements-to-make-array-zigzag/)

## 题目

Given an array `nums` of integers, a *move* consists of choosing any element and **decreasing it by 1**.

An array `A` is a *zigzag array* if either:

- Every even-indexed element is greater than adjacent elements, ie. `A[0] > A[1] < A[2] > A[3] < A[4] > ...`
- OR, every odd-indexed element is greater than adjacent elements, ie. `A[0] < A[1] > A[2] < A[3] > A[4] < ...`

Return the minimum number of moves to transform the given array `nums` into a zigzag array.

 

**Example 1:**

```
Input: nums = [1,2,3]
Output: 2
Explanation: We can decrease 2 to 0 or 3 to 1.
```

**Example 2:**

```
Input: nums = [9,6,1,6,2]
Output: 4
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `1 <= nums[i] <= 1000`

## 题目大意

给你一个整数数组 `nums`，每次 操作 会从中选择一个元素并 将该元素的值减少 `1`

如果符合下列情况之一，则数组 `A` 就是 锯齿数组：

-   每个偶数索引对应的元素都大于相邻的元素，即 `A[0] > A[1] < A[2] > A[3] < A[4] > ...`
-   或者，每个奇数索引对应的元素都大于相邻的元素，即 `A[0] < A[1] > A[2] < A[3] > A[4] < ...`

返回将数组 nums 转换为锯齿数组所需的最小操作次数

## 解题思路

将题目的要求转化一下就可以得到，其实就是要使得 奇数位置的值小于两侧或者偶数位置的值小于两侧

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/decrease-elements-to-make-array-zigzag/solution/fen-qing-kuang-tao-lun-python3-by-smoon1989/)

评论去中有解释为什么这样可以得到最小操作数，因为这样做只能向下改变，比如 0 位置下降了，则 1 位置一定处于波峰，波峰如果下降，那 2 位置可能还要下降，就需要增加额外的操作数了，

### Solution 1:


````c++
class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
        const int len = nums.size();
        int odd = 0, even = 0;
        for (int i = 0; i < len; ++i) {
            int left = (i > 0) ? nums[i - 1] : 1001;
            int right = (i < len - 1) ? nums[i + 1] : 1001;
            if (i & 1) {
                odd += max(0, nums[i] - std::min(left, right) + 1);
            } else {
                even += max(0, nums[i] - std::min(left, right) + 1);
            }
        }
        return min(odd, even);
    }
};
`````
