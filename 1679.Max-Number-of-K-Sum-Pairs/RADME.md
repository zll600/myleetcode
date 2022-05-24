# [1679. Max Number of K-Sum Pairs](https://leetcode.com/problems/max-number-of-k-sum-pairs/)

## 题目

You are given an integer array `nums` and an integer `k`.

In one operation, you can pick two numbers from the array whose sum equals `k` and remove them from the array.

Return *the maximum number of operations you can perform on the array*.

 

**Example 1:**

```
Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Starting with nums = [1,2,3,4]:
- Remove numbers 1 and 4, then nums = [2,3]
- Remove numbers 2 and 3, then nums = []
There are no more pairs that sum up to 5, hence a total of 2 operations.
```

**Example 2:**

```
Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Starting with nums = [3,1,3,4,3]:
- Remove the first two 3's, then nums = [1,4,3]
There are no more pairs that sum up to 6, hence a total of 1 operation.
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `1 <= nums[i] <= 109`
- `1 <= k <= 109`

## 题目大意

给你一个整数数组 nums 和一个整数 k 。每一步操作中，你需要从数组中选出和为 k 的两个整数，并将它们移出数组。返回你可以对数组执行的最大操作数

## 解题思路

这道题目不难想到使用哈希表来做，先统计所有元素的频数，然后遍历，

如果当前遍历到的数是 x，那么可以这个数可以贡献的操作数就是 min(freq[x], freq[k - x])，另外，如果 2 * x == k，那么就是 freq[x] / 2

还有一个点需要注意，如果依次遍历，那么遍历 x 的时候会计算一次 min(freq[x], freq[k - x])，遍历到 k - x 的时候，会计算一次 min(freq[x], freq[k - x])，这种情况狂的解决办法就是，遍历的时候之对 x * 2 < k 或者 x * == k 的数做计算，

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/max-number-of-k-sum-pairs/solution/k-he-shu-dui-de-zui-da-shu-mu-by-zerotra-qcv9/)

### Solution 1:

````c++
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int num : nums) {
            ++freq[num];
        }
        
        int ans = 0;
        for (auto& [val, cnt] : freq) {
            if (val * 2 == k) {
                ans += cnt / 2;
            } else if (val * 2 < k && freq.find(k - val) != freq.end()) {
                ans += min(cnt, freq[k - val]);
            }
        }
        return ans;
    }
};
````

