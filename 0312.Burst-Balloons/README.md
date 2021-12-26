# [312. Burst Balloons](https://leetcode-cn.com/problems/burst-balloons/)

## 题目

You are given `n` balloons, indexed from `0` to `n - 1`. Each balloon is painted with a number on it represented by an array `nums`. You are asked to burst all the balloons.

If you burst the `ith` balloon, you will get `nums[i - 1] * nums[i] * nums[i + 1]` coins. If `i - 1` or `i + 1` goes out of bounds of the array, then treat it as if there is a balloon with a `1` painted on it.

Return *the maximum coins you can collect by bursting the balloons wisely*.

 

**Example 1:**

```
Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
```

**Example 2:**

```
Input: nums = [1,5]
Output: 10
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 500`
- `0 <= nums[i] <= 100`

## 题目大意

按照从 0 到 n - 1的索引，给定n 个气球，每个气球上都标有一个数字，这个数字存储在数组 nums 中，现在要求戳破所有的气球，

戳破第 `i `个气球，你可以获得 `nums[i - 1] * nums[i] * nums[i + 1]` 枚硬币。 这里的 `i - 1` 和`i + 1` 代表和 `i` 相邻的两个气球的序号。如果 `i - 1`或 `i + 1` 超出了数组的边界，那么就当它是一个数字为 1 的气球。

返回您能得到的最大的硬币数，

## 解题思路

这道题目是求最优解的题目，而且是可以用DFS 来做的，那么也就可以考虑DP了，只要满足无后效性，

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/burst-balloons/solution/chao-xiang-xi-hui-su-dao-fen-zhi-dao-dp-by-niu-you/



### Solution 1: DFS(TLE)

这种解法，使用DFS 枚举所有可能，最终结果就是超时，

````c++
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        res_ = 0;
        DFS(nums, 0, 0);
        return res_;
    }
    
 private:
    int res_;
    
    void DFS(vector<int>& nums, int cnt, int last_coins) {
        if (cnt == nums.size()) {
            // 如果所有的气球都被戳破，不能再递归
            if (res_ < last_coins) {
                res_ = last_coins;
            }
            return;
        }
        
        const int len = nums.size();
        for (int i = 0; i < len; ++i) {
            // 选一个没有戳破的
            if (nums[i] == -1) {
                continue;
            }
            
            int tmp_coins = nums[i];
            nums[i] = -1; // 做标记
            
            // 向左查找第一个存在的
            int before = i - 1;
            while (before >= 0 && nums[before] == -1) {
                --before;
            }
            
            // 向右查找第一个 存在的
            int after = i + 1;
            while (after < len && nums[after] == -1) {
                ++after;
            }
            
            int cur_coins = tmp_coins * (before < 0 ? 1 : nums[before]) * (after >= len ? 1 : nums[after]);
            // cout << cur_coins << endl;
            DFS(nums, cnt + 1, last_coins + cur_coins);
            
            nums[i] = tmp_coins; // 回溯
        }
    }
};
````

### Solution 2: Divide and Conquer

这种解法采用分治法，这里的难点在于子问题的定义，

````c++
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        const int len = nums.size();
        // 创建辅助数组
        vector<int> help(len + 2);
        copy(nums.begin(), nums.end(), help.begin() + 1);
        help[0] = 1; // 边界
        help[len + 1] = 1; // 边界
        vector<vector<int>> cache_(len + 2, vector<int>(len + 2, 0));
        
        return Divide(help, 0, help.size() - 1, cache_);
    }
    
 private:    
    int Divide(vector<int>& nums, int start, int end, vector<vector<int>>& cache_) {
        if (start == end - 1) {
            // 递归终止条件
            return 0;
        }
        
        if (cache_[start][end] != 0) {
            // 查询缓存
            return cache_[start][end];
        }
        
        int max_val = 0;
        // 求解子问题
        for (int i = start + 1; i < end; ++i) {
            int coins = Divide(nums, start, i, cache_) + Divide(nums, i, end, cache_)
                        + nums[i] * nums[start] * nums[end];
            max_val = max(max_val, coins);
        }
        
        cache_[start][end] = max_val; // 加缓存
        return max_val;
    }
};
````

### Solution3:DP

这是一道区间dp 的题目，

````c++
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        const int len = nums.size();
        // 创建辅助数组
        vector<int> help(len + 2);
        copy(nums.begin(), nums.end(), help.begin() + 1);
        help[0] = 1; // 边界
        help[len + 1] = 1; // 边界
        vector<vector<int>> dp(len + 2, vector<int>(len + 2, 0));
        
        for (int i = len; i >= 0; --i) {
            for (int j = i + 2; j < len + 2; ++j) {
                // 下面状态转移
                int max_val = 0;
                for (int k = i + 1; k < j; ++k) {
                    int tmp = dp[i][k] + dp[k][j] + help[i] * help[k] * help[j];
                    max_val = max(max_val, tmp);
                }
                dp[i][j] = max_val;
            }
        }
        
        return dp[0][len + 1];
    }
};
````

