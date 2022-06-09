# [962. Maximum Width Ramp](https://leetcode.cn/problems/maximum-width-ramp/)

## 题目

A **ramp** in an integer array `nums` is a pair `(i, j)` for which `i < j` and `nums[i] <= nums[j]`. The **width** of such a ramp is `j - i`.

Given an integer array `nums`, return *the maximum width of a **ramp** in* `nums`. If there is no **ramp** in `nums`, return `0`.

 

**Example 1:**

```
Input: nums = [6,0,8,2,1,5]
Output: 4
Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1] = 0 and nums[5] = 5.
```

**Example 2:**

```
Input: nums = [9,8,1,0,1,9,4,0,4,1]
Output: 7
Explanation: The maximum width ramp is achieved at (i, j) = (2, 9): nums[2] = 1 and nums[9] = 1.
```

 

**Constraints:**

- `2 <= nums.length <= 5 * 104`
- `0 <= nums[i] <= 5 * 104`

## 题目大意

给定一个整数数组 `A`，坡是元组 `(i, j)`，其中  `i < j` 且 `A[i] <= A[j]`。这样的坡的宽度为 `j - i`

找出 A 中的坡的最大宽度，如果不存在，返回 0

## 解题思路

### Solution 1:

暴力解法，最终超时

````c++
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        const int len = nums.size();
        int ans = 0;

        for (int i = 0; i < len; ++i) {
            for (int j = len - 1; j > i; --j) {
                if (nums[j] >= nums[i]) {
                    ans = max(ans, j - i);
                    break;
                }
            }
        }
        return ans;
    }
};

````

### Solution 2: Sort + Greedy

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/maximum-width-ramp/solution/962-cjian-dan-yi-dong-de-pai-xu-jia-tan-ahgte/)

排序之后，后面的数一定大于前面的数，所以只需要根据下标来更新最终的结果就可以了


````c++
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        const int len = nums.size();
        vector<int> indices(len);
        for (int i = 0; i < len; ++i) {
            indices[i] = i;
        }

        sort(indices.begin(), indices.end(), [&nums](int a, int b) {
            if (nums[a] != nums[b]) {
                return nums[a] < nums[b];
            }
            // 大小相等的，按照下标来排序
            return a < b;
        });

        int res = 0;
        int min_indice = len;
        for (int indice : indices) {
            // 更新结果
            res = max(res, indice - min_indice);
            // 找到最小的下边
            min_indice = min(min_indice, indice);
        }

        return res;
    }
};
`````
