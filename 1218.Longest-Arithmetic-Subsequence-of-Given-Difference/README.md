# [1218. Longest Arithmetic Subsequence of Given Difference](https://leetcode.cn/problems/longest-arithmetic-subsequence-of-given-difference/)

## 题目

Given an integer array `arr` and an integer `difference`, return the length of the longest subsequence in `arr` which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals `difference`.

A **subsequence** is a sequence that can be derived from `arr` by deleting some or no elements without changing the order of the remaining elements.

 

**Example 1:**

```
Input: arr = [1,2,3,4], difference = 1
Output: 4
Explanation: The longest arithmetic subsequence is [1,2,3,4].
```

**Example 2:**

```
Input: arr = [1,3,5,7], difference = 1
Output: 1
Explanation: The longest arithmetic subsequence is any single element.
```

**Example 3:**

```
Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
Output: 4
Explanation: The longest arithmetic subsequence is [7,5,3,1].
```

 

**Constraints:**

- `1 <= arr.length <= 105`
- `-104 <= arr[i], difference <= 104`

## 题目大意

给你一个整数数组 `arr` 和一个整数 `difference`，请你找出并返回 `arr` 中最长等差子序列的长度，该子序列中相邻元素之间的差等于 `difference`

子序列 是指在不改变其余元素顺序的情况下，通过删除一些元素或不删除任何元素而从 `arr` 派生出来的序列

## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/longest-arithmetic-subsequence-of-given-difference/solution/gong-shui-san-xie-jie-he-tan-xin-de-zhua-dj1k/)

这里 `dp[i][0]` 定义为前 i 个元素中不选择 ith 元素得到的最大长度，`dp[i][1]` 表示前 i 个元素中，选择 ith 元素的最大长度，

`dp[i][0]` 可以由

- `dp[i - 1][0]` 或者 `dp[i - 1][1]` 表示由前 i - 1 个元素决定


`dp[i][1]` 可以由

- 选择 ith 作为新起点，或者接到 `dp[index(arr[i] - difference)][1]`，index() 表示求的最近的值的下标(arr 中的数不唯一)

````c++
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        const int len = arr.size();
        unordered_map<int, int> records;
        vector<vector<int>> dp(len, vector<int>(2, 0));
        dp[0][1] = 1;
        records[arr[0]] = 0;
        
        for (int i = 1; i < len; ++i) {
            // ignore ith element
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = 1;
            auto it = records.find(arr[i] - difference);
            if (it != records.end()) {
                // cout << it->first << endl;
                dp[i][1] = max(dp[i][1], dp[it->second][1] + 1);
                // cout << dp[i][1] << endl;
            }
            // arr has duplicate values;
            records[arr[i]] = i;
        }
        return max(dp[len - 1][0], dp[len - 1][1]);
    }
};
````
