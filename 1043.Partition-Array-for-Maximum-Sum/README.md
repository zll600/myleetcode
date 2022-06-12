# [1043. Partition Array for Maximum Sum](https://leetcode.cn/problems/partition-array-for-maximum-sum/)

## 题目

Given an integer array `arr`, partition the array into (contiguous) subarrays of length **at most** `k`. After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return *the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a **32-bit** integer.*

 

**Example 1:**

```
Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]
```

**Example 2:**

```
Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83
```

**Example 3:**

```
Input: arr = [1], k = 1
Output: 1
```

 

**Constraints:**

- `1 <= arr.length <= 500`
- `0 <= arr[i] <= 109`
- `1 <= k <= arr.length`

## 题目大意

给你一个整数数组 `arr`，请你将该数组分隔为长度最多为 `k` 的一些（连续）子数组。分隔完成后，每个子数组的中的所有值都会变为该子数组中的最大值

返回将数组分隔变换后能够得到的元素最大和

 

注意，原数组和分隔后的数组对应顺序应当一致，也就是说，你只能选择分隔数组的位置而不能调整数组中的顺序


## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/partition-array-for-maximum-sum/solution/fei-chang-hao-li-jie-de-dong-tai-gui-hua-w0wq/)

这里定义状态 dp[i] 表示 0...i 范围内的数据分隔为最多 `k` 的一些（连续）子数组，分隔完成后的最大累加和

状态转移

- `dp[i] = max(dp[i - 1] + arr[i], dp[i - 2] + max(arr, i - 1, i) * (i - i + 1), dp[i - k] + max(arr, i, i - k + 1, i) * k)

由状态转移方程可以得到初始化应该

dp[0].....dp[k - 1]

````c++
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        const int len = arr.size();
        // dp[i] 表示 0...i i + 1 个元素分割为长度小于 k 的连续子数组，分割后能得到的元素最大和
        vector<int> dp(len, 0);
        for (int i = 0; i < k; ++i) {
            auto iter = max_element(arr.begin(), arr.begin() + i + 1);
            // cout << *iter << endl;
            dp[i]  = *iter * (i + 1);
        }
        
        for (int i = k; i < len; ++i) {
            for (int j = 1; j <= k; ++j) {
                auto iter = max_element(arr.begin() + i - j + 1, arr.begin() + i + 1);
                // cout << *iter << endl;
                dp[i] = max(dp[i - j] + *iter * j, dp[i]);
            }
        }
        return dp[len - 1];
    }
};
````
