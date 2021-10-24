# [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)

## 题目

Given a **non-empty** array `nums` containing **only positive integers**, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

 

**Example 1:**

```
Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
```

**Example 2:**

```
Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
```

 

**Constraints:**

- `1 <= nums.length <= 200`
- `1 <= nums[i] <= 100`

## 题目大意

给定一个非空的正整数数组，能否将这个数组分为两个子集使这两个子集之和相等，

## 解题思路

* 这是一道 DP 01 背包问题，可以认为题目想要求的使能够在原数组中找出一个子集，使得这个子集中所有元素的和为原数组和的一半，，
* 这里提供两种途径，第一种，先算除能否求出 sum / 2，
* 第二种就是直接利用布尔数组进行判断，可以设立一个哨兵，避免分类讨论，降低代码的复杂程度

### Solution 1: DP

* 状态定义：`dp[i][j]`表示[0, i] 个元素中，任取一些元素，能否构成 j，注意也可以一个都不取，就可以凑成0
* 状态转移：参考代码，有三个方向
* 初始化：`dp[0][nums[0]]` = true
* 结果：`dp[size - 1][[target]`

```c++
class Solution {
public:    
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) {
            return false;
        }
        
        const int target = sum / 2;
        const int size = nums.size();
        if (size < 2) {
            return false;
        }
        // dp 的定义：dp[i][j] 表示 [0, i]范围内，任取n 个数，能否组成 j
        vector<vector<bool>> dp(size, vector<bool>(target + 1, false));
        // 初始化
        for (int i = 0; i < size; ++i) {
            dp[i][0] = true;  // 前 i 个数中，任意取（也可以不取），一定能构成 0
            if (nums[i] <= target) {  // 这里的判断不能少，否则可能会造成数组下标越界
                dp[i][nums[i]] = true;
            }
        }
        
        for (int i = 1; i < size; ++i) {
            for (int j = 0; j < target + 1;  ++j) {
                // 状态转移
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i]];
                }
                
                if (dp[i][target]) {  // 剪枝
                    return true;
                }
            }
        }
        // 返回结果
        return dp[size - 1][target];
    }
};
```

### Solution 2: DP + 空间优化

````c++
class Solution {
public:    
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) {
            return false;
        }
        
        const int target = sum / 2;
        const int size = nums.size();
        if (size < 2) {
            return false;
        }
        
        vector<bool> dp(target + 1, false);
        dp[0] = true;  // 一个都不选，可以组成 0
        if (nums[0] <= target) {  // 这里的判断不能少，否则会发生越界
            dp[nums[0]] = true;
        }
        
        for (int i = 1; i < size; ++i) {
            for (int j = target; j >= nums[i]; --j) {
                dp[j] = dp[j] || dp[j - nums[i]];
                
                if (dp[target]) {  // 剪枝操作
                    return true;
                }
            }
        }
        
        return dp[target];
    }
};
````



### Solution : DFS(TLE)

````c++
class Solution {
public:    
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) {  // 剪枝操作哦
            return false;
        }
        
        return DFS(nums, 0, sum / 2);
    }
    
 private:
    bool DFS(const vector<int>& nums, int idx, int target) {
        // 如果下标越界，返回 false
        if (idx >= nums.size()) {
            return false;
        }
        
        //  如果小于 0，直接返回 false
        if (target < 0) {
            return false;
        }
        // 如果等于 0，返回 true
        if (target == 0) {
            return true;
        }
        
        return DFS(nums, idx + 1, target - nums[idx]) || DFS(nums, idx + 1, target);
    }
};
````

### Solution : DFS + Memory

```c++
// 哈希函数
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
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) {  // 剪枝操作哦
            return false;
        }
        unordered_map<pair<int, int>, bool, PairHash> cache;
        
        return DFS(nums, 0, sum / 2, cache);
    }
    
 private:
    bool DFS(const vector<int>& nums, int idx, int target,
             unordered_map<pair<int, int>, bool, PairHash>& cache) {
        // 如果下标越界，返回 false
        if (idx >= nums.size()) {
            return false;
        }
        //  如果小于 0，直接返回 false
        if (target < 0) {
            return false;
        }
        // 如果等于 0，返回 true
        if (target == 0) {
            return true;
        }
        // 先查缓存
        pair<int, int> item(idx, target);
        if (cache.find(item) != cache.end()) {
            return cache.at(item);
        }
        // 递归去比较，选和不选
        bool res = DFS(nums, idx + 1, target - nums[idx], cache) || DFS(nums, idx + 1, target, cache);
        cache[item] = res;
        return res;
    }
};
```









`````c++
class Solution {
public:
    // 二维数组
    /*
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        
        int size = nums.size();
        int cap = sum / 2;
        // 如果总和为奇数，则肯定无法拆为两部分
        if (cap * 2 != sum) {
            return false;
        }
        
        vector<vector<int>> dp(size, vector<int>(cap + 1, 0));
        
        // 初始化放第一件物品，
        for (int i = 0 ; i <= cap; ++i) {
            if (nums[0] <= i) {
                dp[0][i] = nums[0]; 
            }
        }
        
        for (int i = 1; i < size; ++i) {
            for (int j = 0; j <= cap; ++j) {
                // 不选
                dp[i][j] = dp[i - 1][j];
                // 选
                if (j >= nums[i]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - nums[i]] + nums[i]);
                }
            }
        }
        return dp[size - 1][cap] == cap;
    }*/
    
    // 滚动数组
    /*
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        
        if (sum % 2 != 0) {
            return false;
        }
        
        int cap = sum / 2;
        int size = nums.size();
        vector<vector<int>> dp(size, vector<int>(cap + 1, 0));
        
        for (int i = 0; i <= cap; ++i) {
            if (i >= nums[0]) {
                dp[0][i] = nums[0];
            }
        }
        
        for (int i = 1; i < size; ++i) {
            for (int j = 0; j <= cap; ++j) {
                dp[i & 1][j] = dp[(i - 1) & 1][j];
                if (j >= nums[i]) {
                    dp[i & 1][j] = max(dp[i & 1][j], dp[(i - 1) & 1][j - nums[i]] + nums[i]);
                }
            }
        }
        
        return dp[(size - 1) & 1][cap] == cap;
    }*/
    
    /*
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        
        if (sum % 2 != 0) {
            return false;
        }
        
        int cap = sum / 2;
        int size = nums.size();
        vector<int> dp(cap + 1, 0);
        for (int i = 0; i <= cap; ++i) {
            if (i >= nums[0]) {
                dp[i] = nums[0];
            }
        }/
        
        for (int i = 1; i < size; ++i) {
            for (int j = cap; j >= 0; --j) { //一维数组中 第二维的条件可以改为 j >= nums[i]，否则无法选择，只能继承上一次的结果。
                if (j >= nums[i]) {
                    dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
                }
            }
        }
        
        return dp[cap] == cap;
    }*/
    
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        if (sum % 2 != 0) {
            return false;
        }
        
        int cap = sum / 2;
        int size = nums.size();
        // 这里加一个哨兵值，来帮助递推
        vector<vector<bool>> dp(size + 1, vector<bool>(cap + 1, false));
        dp[0][0] = true;
        
        for (int i = 1; i <= size; ++i) {
            for (int j = 0; j <= cap; ++j) {
                dp[i][j] = dp[i - 1][j];
                
                if (j >= nums[i - 1]) {
                    dp[i][j] = dp[i][j] | dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        
        return dp[size][cap];
    }
};
`````

