# [813. Largest Sum of Averages](https://leetcode.cn/problems/largest-sum-of-averages/)

## 题目

You are given an integer array `nums` and an integer `k`. You can partition the array into **at most** `k` non-empty adjacent subarrays. The **score** of a partition is the sum of the averages of each subarray.

Note that the partition must use every integer in `nums`, and that the score is not necessarily an integer.

Return *the maximum **score** you can achieve of all the possible partitions*. Answers within `10-6` of the actual answer will be accepted.

 

**Example 1:**

```
Input: nums = [9,1,2,3,9], k = 3
Output: 20.00000
Explanation: 
The best choice is to partition nums into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
We could have also partitioned nums into [9, 1], [2], [3, 9], for example.
That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
```

**Example 2:**

```
Input: nums = [1,2,3,4,5,6,7], k = 4
Output: 20.50000
```

 

**Constraints:**

- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 104`
- `1 <= k <= nums.length`

## 题目大意

给定数组 `nums` 和一个整数 `k` 。我们将给定的数组 `nums` 分成 最多 `k` 个相邻的非空子数组 。 分数 由每个子数组内的平均值的总和构成

注意我们必须使用 `nums` 数组中的每一个数进行分组，并且分数不一定需要是整数

返回我们所能得到的最大 分数 是多少。答案误差在 `10-6` 内被视为是正确的

## 解题思路

这道题目肯定是不能先排序在计算的，所以这里可以考虑枚举所有可能的结果，然后选择最大值，那么这样就需要 dfs 了，

这里分析如果使用 dfs 的时候，可以先画一画图，分析一下状态，递归基，递归终止条件

### Solution 1: DFS

这种解法的状态就是 `{idx, k}`

这里增加了记忆化来进行剪枝

````c++
struct PairHash	{
    template<class T1, class T2>
    size_t operator()(const pair<T1, T2> &x) const {
        hash<T1> h1{};
        hash<T2> h2{};
        return h1(x.first) ^ h2(x.second);
    }
};


class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        unordered_map<pair<int, int>, double, PairHash> memo;
        
        return DFS(nums, 0, k, memo);
    }
    
 private:
    double DFS(const vector<int>& nums, int idx, int k,
              unordered_map<pair<int, int>, double, PairHash>& memo) {
        if (k == 0) {
            return 0.0;
        }
        
        pair<int, int> key{idx, k};
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        double res = 0.0;
        if (k == 1) {
            double sum = accumulate(nums.begin() + idx, nums.end(), 0.0);
            res = sum / (nums.size() - idx);
            memo[key] = res;
            return res;
        }
        
        double total = 0.0;
        for (int i = idx; i <= nums.size() - k; ++i) {
            total += nums[i];.
            double average = total / (i - idx + 1);
            double next = DFS(nums, i + 1, k - 1, memo);
            res = max(res, average + next);
        }
        memo[key] = res;
        
        return res;
    }
};
````

