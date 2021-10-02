# [413. Arithmetic Slices](https://leetcode.com/problems/arithmetic-slices/)

## 题目

An integer array is called arithmetic if it consists of **at least three elements** and if the difference between any two consecutive elements is the same.

- For example, `[1,3,5,7,9]`, `[7,7,7,7]`, and `[3,-1,-5,-9]` are arithmetic sequences.

Given an integer array `nums`, return *the number of arithmetic **subarrays** of* `nums`.

A **subarray** is a contiguous subsequence of the array.

 

**Example 1:**

```
Input: nums = [1,2,3,4]
Output: 3
Explanation: We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and [1,2,3,4] itself.
```

**Example 2:**

```
Input: nums = [1]
Output: 0
```

 

**Constraints:**

- `1 <= nums.length <= 5000`
- `-1000 <= nums[i] <= 1000`

## 题目大意

如果一个数列至少含有 3 个元素，且连续两个相邻的元素的差是一样的

* 例如，[1,3,5,7,9]、[7,7,7,7] 和 [3,-1,-5,-9] 都是等差数列。

给你一个整数数组 nums ，返回数组 nums 中所有为等差数组的 子数组 个数。

子数组 是数组中的一个连续序列。

## 解题思路

## 解法1（双指针）

这道题目可以用双指针来作，具体来说，对于区间 [i, j]， 我们只求以 i位置开头的最长的等差数组，然后计算出这段等差数组可以产生出多少长度小于其的等差数组，这里注意对边界条件的处理

这里可以参考这篇题解：https://leetcode-cn.com/problems/arithmetic-slices/solution/gong-shui-san-xie-shuang-zhi-zhen-qiu-ji-ef1q/

`````c++
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        if (nums.size() < 3) {  // 这里处理边界情况
            return 0;
        }
        
        int res = 0;
        
        int i = 0;
        while (i < nums.size() - 2) {
            int j = i;
            int diff = nums[i + 1] - nums[i];  // 计算差值
            // 这里的循环不变量是 [i, j] 是当前可以得到的最长的等差数组
            while (j + 1 < nums.size() && nums[j + 1] - nums[j] == diff) {
                j++;
            }
            
            int len = j - i + 1;  // 等差数组的长度
            int a1 = 1;  // 长度为 len 的等差数组数目
            int an = len - 3 + 1;  // 长度为 3 的等差数组的数目
            int cnt = (a1 + an) * an / 2;  // 等差数组的数目
            res += cnt;
            i = j;
        }
        
        return res;
    }
};
`````

### 解法2（动态规划）

这道题可以利用动态规划来解决是因为我们可以认为 len 的等差数组增加一个元素后得到的 len + 1 得到的数组可以产生的新的等差数组的数目一定可以由 len 的等差数组可以产生的等差数组推出

状态定义：dp[i] 表示以  i 位置为结尾，可以产生的等差数组的数目

状态转移方程的得出可以参考这篇题解：https://leetcode-cn.com/problems/arithmetic-slices/solution/hua-dong-chuang-kou-dong-tai-gui-hua-jav-3vpp/

`````c++
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        if (nums.size() < 3) {  // 这里处理边界情况
            return 0;
        }
        
        int res = 0;
        int dp = 0;  // 这里的 dp 数组可以利用一个变量来代替
        
        // 这个状态转移方程可以利用画图找规律来写
        for (int i = 2; i < nums.size(); i++) {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                dp++;  // 这里其实是状态转移方程 dp[i] = dpp[i - 1] + 1
                res += dp;
            } else {
                dp = 0;
            }
        }
        
        return res;
    }
};
`````

