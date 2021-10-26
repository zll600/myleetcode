# [673. Number of Longest Increasing Subsequence](https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/)

## 题目

Given an integer array `nums`, return *the number of longest increasing subsequences.*

**Notice** that the sequence has to be **strictly** increasing.

 

**Example 1:**

```
Input: nums = [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
```

**Example 2:**

```
Input: nums = [2,2,2,2,2]
Output: 5
Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.
```

 

**Constraints:**

- `1 <= nums.length <= 2000`
- `-106 <= nums[i] <= 106`

## 题目大意

给定一个整数数组 nums，然会最长的递增子序列，

注意这个序列必须是严格递增的

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/solution/673-zui-chang-di-zeng-zi-xu-lie-de-ge-sh-g7a0/

和这一篇：https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/solution/gong-shui-san-xie-lis-de-fang-an-shu-wen-obuz/

这道题目可以参考第 300 题，二者还是比较相似的

### Solution 1:

```c++
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        const int size = nums.size();
        if (size < 2) {  // 边界情况
            return 1;
        }
        // dp[i] 表示以 i 位置结尾的的最长递增子序列的长度
        vector<int> dp(size, 1);
        // cnt[i] 表示 i 位置结尾的最长递增子序列的 长度
        vector<int> cnt(size, 1);
        
        // 初始化：两个状态数组的每一项均是初始化为 1
        
        int max_len = 1;  // 保存最长长度
        for (int i = 1; i < size; ++i) {
            // 状态转移
            for (int j = 0; j < i; ++j) {
                // 满足条件可以更新 dp
                if (nums[j] < nums[i]) {
                    // 直接更新 cnt
                    if (dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1;
                        cnt[i] = cnt[j];
                    } else if (dp[i] == dp[j] + 1) {
                        // 累加 cnt
                        cnt[i] += cnt[j];
                    }
                }
            }
            // 更新最大长度
            max_len = max(max_len, dp[i]);
        }
        
        int res = 0;
        for (int i = 0; i < size; ++i) {
            // 累加长度为最大长度的结果
            if (dp[i] == max_len) {
                res += cnt[i];
            }
        }
        
        return res;
    }
};
```



