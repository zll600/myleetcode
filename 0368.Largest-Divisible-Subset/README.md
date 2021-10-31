# [368. Largest Divisible Subset](https://leetcode.com/problems/largest-divisible-subset/)

## 题目

Given a set of **distinct** positive integers `nums`, return the largest subset `answer` such that every pair `(answer[i], answer[j])` of elements in this subset satisfies:

- `answer[i] % answer[j] == 0`, or
- `answer[j] % answer[i] == 0`

If there are multiple solutions, return any of them.

 

**Example 1:**

```
Input: nums = [1,2,3]
Output: [1,2]
Explanation: [1,3] is also accepted.
```

**Example 2:**

```
Input: nums = [1,2,4,8]
Output: [1,2,4,8]
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `1 <= nums[i] <= 2 * 109`
- All the integers in `nums` are **unique**.

## 题目大意

给定一族不同的正整数 nums，返回最大的子集 answer，其中每对(answer[i], answer[j]) 中的元素都满足

* answer[i] % answer[j] == 0 或
* answer[j] % answer[i] == 0

如果有多个解，返回其中任意的

## 解题思路

这道题和第 300 题，最长递增子序列很像，可以参考来作

### Solution 1: DP

这种解法，可以参考这篇题解：https://leetcode-cn.com/problems/largest-divisible-subset/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-0a3jc/

动态规划的各个步骤，已经写在下面了

这道题目需要用到两个数组，需要多一个数组做记录，方便后面恢复数组

````c++
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // 将 数组 按照升序排序，方便判断
        
        const int size = nums.size();
        // 状态定义：
        // dp[i] 表示以 i 位置结尾的最长集合的长度
        vector<int> dp(size);
        // path[i]表示当前集合的前一个元素的下标
        vector<int> path(size);
        
        for (int i = 0; i < size; ++i) {
            int len = 1;  // 初始长度
            int prev = i;  // 由自身转移而来
            for (int j = 0; j < i; ++j) {
                // 如果可以转移，更新结果
                if (nums[i] % nums[j] == 0) {
                    if (dp[j] + 1 > len) {
                        len = dp[j] + 1;
                        prev = j;
                    }
                }
            }
            
            // 维护长度
            dp[i] = len;
            // 前一个结果
            path[i] = prev;
        }
        
        // 找到最长的集合以及最后一个元素的下标
        int max_len = -1;
        int idx = -1;
        for (int i = 0; i < size; ++i) {
            if (max_len < dp[i]) {
                max_len = dp[i];
                idx = i;
            }
        }
        
        vector<int> res;
        while (res.size() < max_len) {
            res.push_back(nums[idx]);  // 倒序加入
            idx = path[idx];  // 逐层查找
        }
        
        return res;
    }
};
````

### Error:

这里给出一种常见的错误解法，这种解法的问题在于要求结果中的所有元素必须是相邻的，这样求得的结果不一定是最长的集合

这里也给一个没有通过的数据

````
input: [5,9,18,54,108,540,90,180,360,720]

Output: [9,18,54,108,540]

Expected: [9,18,90,180,360,720]
````





```c++
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        vector<vector<int>> results;
        size_t max_size = 0;
        
        const int size = nums.size();
        for (int i = 0; i < size; ++i) {
            vector<int> tmp;
            tmp.push_back(nums[i]);
            
            for (int j = i + 1; j < size; ++j) {
                if (IsValid(tmp, nums[j])) {
                    tmp.push_back(nums[j]);
                }
            }
            
            max_size = max(max_size, tmp.size());
            results.push_back(tmp);
        }
        
        for (const auto& vec : results) {
            if (vec.size() == max_size) {
                return vec;
            }
        }
        
        return vector<int>();
    }
    
 private:
    bool IsValid(const vector<int>& nums, int num) {
        const int size = nums.size();
        for (int k = 0; k < size; ++k) {
            if (num % nums[k] != 0 && nums[k] % num != 0) {
                return false;
            }
        }
        
        return true;
    }
};
```

