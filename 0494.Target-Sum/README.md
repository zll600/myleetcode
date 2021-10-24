# [494. Target Sum](https://leetcode.com/problems/target-sum/)

## 题目

You are given an integer array `nums` and an integer `target`.

You want to build an **expression** out of nums by adding one of the symbols `'+'` and `'-'` before each integer in nums and then concatenate all the integers.

- For example, if `nums = [2, 1]`, you can add a `'+'` before `2` and a `'-'` before `1` and concatenate them to build the expression `"+2-1"`.

Return the number of different **expressions** that you can build, which evaluates to `target`.

 

**Example 1:**

```
Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
```

**Example 2:**

```
Input: nums = [1], target = 1
Output: 1
```

 

**Constraints:**

- `1 <= nums.length <= 20`
- `0 <= nums[i] <= 1000`
- `0 <= sum(nums[i]) <= 1000`
- `-1000 <= target <= 1000`

## 题目大意

给定一个整数数组 nums 和一个整数 k，你可以通过给每个数字前面增加‘+’或者‘-’，来构造一个表达式，返回你能构造多少种表达式，可以使表达式的值等于 target，

## 解题思路

### Solution 1: DP

* 这是一道 DP 01 背包的问题，
* 状态的定义是 `dp[i][j]` 在[0, i] 的区间中和为 j的方法数
* 最终答案为 `dp[size][target]`
* 初始化，这里利用一个哨兵值，多设置一行，`dp[0][0] = 1` 表示没有数字的情况下凑成0 的方案数为1，
* 状态转移方程为 `dp[i][j] = dp[i - 1][j - nums[i]] + dp[i - 1][j + nums[i]]`
* 这道题目还需要注意的一点是 第二维度的取值范围是：sum 为数组所有元素的总和，j 的范围是 `[-sum, sum]`

这道题目dp 还可以优化，留待以后实现

`````c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        
        if (target < -sum || target > sum) {
            return 0;
        }
        
        int size = nums.size();
        vector<vector<int>> dp(size + 1, vector<int>(2 * sum + 1));
        dp[0][0 + sum] = 1;	// 加上一个偏移，将负数部分转化为非负数部分，
        
        for (int i = 1; i <= size; ++i) {
            for (int j = -sum; j <= sum; ++j) {
                if (j - nums[i - 1] + sum >= 0) {
                    dp[i][j + sum] += dp[i - 1][j - nums[i - 1] + sum];
                }
                if (j + nums[i - 1] + sum <= 2 * sum) {
                    dp[i][j + sum] += dp[i - 1][j + nums[i - 1] + sum];
                }
            }
        }
        return dp[size][target + sum];
    }
};
`````

### Solution 2: DFS

代码比较简单，但是效率有问题

````c++
class Solution {
 public:
    int findTargetSumWays(vector<int>& nums, int target) {
        const int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum < abs(target)) {  // 减枝操作
            return 0;
        }
        
        return DFS(nums, 0, target);
    }

 private:
    int DFS(const vector<int>& nums, int idx, long target) {
        if (idx == nums.size()) {
            return target == 0 ? 1 : 0;
        }

        int res = 0;
        // 使用 "-" 号
        res += DFS(nums, idx + 1, target - nums[idx]);
        // 使用 "+" 号
        res += DFS(nums, idx + 1, target + nums[idx]);

        return res;
    }
};
````

### Solution 3： DFS + 记忆化搜索

````c++
// hash function
struct PairHash {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Solution {
 public:
    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<pair<int, int>, int, PairHash> cache;

        return DFS(nums, 0, target, cache);
    }

 private:
    int DFS(const vector<int>& nums, int idx, int target,
            unordered_map<pair<int, int>, int, PairHash>& cache) {
        // 是否已到边界
        if (idx == nums.size()) {
            return target == 0 ? 1 : 0;  // 更新
        }
        
        // 先查缓存，这里的记录的 key 时 idx 和 target
        pair<int, int> item(idx, target);
        if (cache.find(item) != cache.end()) {
            return cache.at(item);
        }

        // 递归计算
        int add = DFS(nums, idx + 1, target - nums[idx], cache);
        int sub = DFS(nums, idx + 1, target + nums[idx], cache);
        cache[item] = add + sub;  // 更新
        
        return add + sub;
    }
};
````



### Solution 3: DP

这种写法时参考花花酱的写法写的：https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-494-target-sum/

````c++
class Solution {
 public:
    int findTargetSumWays(vector<int>& nums, int target) {
        const int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum < abs(target)) {  // 减枝
            return 0;
        }

        const int offset = sum;  // 因为要使用数组索引来表示，所以加一个偏移
        const int size = nums.size();
        // ways[i][j] 表示由[0, i - 1]位置上的数组成的和为 j - offset 的方法数
        vector<vector<int>> ways(size + 1, vector<int>(sum + offset + 1, 0));
        // 初始化，不用任何数，只能组成 0，方法数为 1
        ways[0][offset] = 1;
        for (int i = 0; i < size; ++i) {
            for (int j = nums[i]; j < 2 * sum + 1 - nums[i]; ++j) {
                // 状态转移
                // 如果 ways[i][j] 是可达的
                if (ways[i][j]) {
                    // 下面两个就是可达的
                    ways[i + 1][j - nums[i]] += ways[i][j];
                    ways[i + 1][j + nums[i]] += ways[i][j];
                }
            }
        }
        // 最后取结果时，一定要加上偏移
        return ways[size][target + offset];
    }
};
````

### 空间优化：

````c++
class Solution {
 public:
    int findTargetSumWays(vector<int>& nums, int target) {
        const int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum < abs(target)) {  // 减枝
            return 0;
        }

        const int offset = sum;  // 因为要使用数组索引来表示，所以加一个偏移
        const int size = nums.size();
        vector<int> ways(sum + offset + 1, 0);
        ways[offset] = 1;
        for (int i = 0; i < size; ++i) {
            vector<int> tmp(2 * sum + 1, 0);  // 使用滚动数组
            for (int j = nums[i]; j < 2 * sum + 1 - nums[i]; ++j) {
                if (ways[j]) {
                    tmp[j + nums[i]] += ways[j];
                    tmp[j - nums[i]] += ways[j];
                }
            }
            swap(tmp, ways);  // 交换
        }

        return ways[target + offset];
    }
};
````

### Solution 4: 0/1 Knapsack

这种解法，可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0494.Target-Sum/

````c++
class Solution {
 public:
    int findTargetSumWays(vector<int>& nums, int target) {
        const int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum < abs(target) || (sum + target) % 2 != 0) {
            return 0;
        }

        const int size = nums.size();
        const int total = (sum + target) / 2;
        vector<int> dp(total + 1, 0);
        dp[0] = 1;
        
        for (int i = 0; i < size; ++i) {
            for (int j = total; j >= nums[i]; --j) {
                dp[j] += dp[j - nums[i]];
            }
        }

        return dp[total];
    }
};
````

