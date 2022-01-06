# [354. Russian Doll Envelopes](https://leetcode-cn.com/problems/russian-doll-envelopes/)

## 题目

You are given a 2D array of integers `envelopes` where `envelopes[i] = [wi, hi]` represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.

Return *the maximum number of envelopes you can Russian doll (i.e., put one inside the other)*.

**Note:** You cannot rotate an envelope.

 

**Example 1:**

```
Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
```

**Example 2:**

```
Input: envelopes = [[1,1],[1,1],[1,1]]
Output: 1
```

 

**Constraints:**

- `1 <= envelopes.length <= 5000`
- `envelopes[i].length == 2`
- `1 <= wi, hi <= 104`

## 题目大意

给你一个二维整数数组 `envelopes` ，其中 `envelopes[i] = [wi, hi]` ，表示第 `i` 个信封的宽度和高度。

当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，

返回你可以嵌套的最大数量的信封

你不能旋转信封

## 解题思路

这道题目是求最优解的题目，而且重复子问题可以理解为前 i 个信封最多可以嵌套多少个，所以可以转化为一个求最长递增子序列的题目，但是在这里两个维度都需要递增才可以

### Solution 1: 两个维度都按照升序排序

````c++
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // 两个维度均按照升序排序
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            } else {
                return a[1] < b[1];
            }
        });
        
        const int len = envelopes.size();
        // dp[i] 表示从 0 到 i 个可以嵌套的信封的数量
        // 这里初始化为 1，
        vector<int> dp(len, 1);
        
        for (int i = 1; i < len; ++i) {
            // 状态转移
            for (int j = 0; j < i; ++j) {
                if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1]) {
                    // 两个维度同时小才满足
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
````

### Solution 2: 一个维度升序，一个维度降序

这里放上一个例子`[[4,5],[4,6],[6,7],[2,3],[1,1]]`

这里优化的关键在于 一个维度相同时，两个时不能嵌套的，这样让另一个倒序排序，就可以优化一部分

````c++
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // 一个维度升，一个维度降
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            } else {
                return a[1] > b[1];
            }
        });
        
        const int len = envelopes.size();
        // dp[i] 表示从 0 到 i 个可以嵌套的信封的数量
        // 这里初始化为 1，
        vector<int> dp(len, 1);
        
        for (int i = 1; i < len; ++i) {
            // 状态转移
            for (int j = 0; j < i; ++j) {
                if (envelopes[j][1] < envelopes[i][1]) {
                    // 两个维度同时小才满足
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end()); // 取最大值
    }
};
````

这里放上一篇关于求最长递增子序列的题目
