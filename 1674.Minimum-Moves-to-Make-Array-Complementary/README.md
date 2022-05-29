# [1674. Minimum Moves to Make Array Complementary](https://leetcode.com/problems/minimum-moves-to-make-array-complementary/)

## 题目

You are given an integer array `nums` of **even** length `n` and an integer `limit`. In one move, you can replace any integer from `nums` with another integer between `1` and `limit`, inclusive.

The array `nums` is **complementary** if for all indices `i` (**0-indexed**), `nums[i] + nums[n - 1 - i]` equals the same number. For example, the array `[1,2,3,4]` is complementary because for all indices `i`, `nums[i] + nums[n - 1 - i] = 5`.

Return the ***minimum** number of moves required to make* `nums` ***complementary***.

 

**Example 1:**

```
Input: nums = [1,2,4,3], limit = 4
Output: 1
Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
nums[0] + nums[3] = 1 + 3 = 4.
nums[1] + nums[2] = 2 + 2 = 4.
nums[2] + nums[1] = 2 + 2 = 4.
nums[3] + nums[0] = 3 + 1 = 4.
Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.
```

**Example 2:**

```
Input: nums = [1,2,2,1], limit = 2
Output: 2
Explanation: In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to 3 since 3 > limit.
```

**Example 3:**

```
Input: nums = [1,2,1,2], limit = 2
Output: 0
Explanation: nums is already complementary.
```

 

**Constraints:**

- `n == nums.length`
- `2 <= n <= 105`
- `1 <= nums[i] <= limit <= 105`
- `n` is even.

## 题目大意

给你一个长度为 偶数 `n` 的整数数组 `nums` 和一个整数 `limit` 。每一次操作，你可以将 `nums` 中的任何整数替换为 `1` 到 `limit` 之间的另一个整数

如果对于所有下标 `i`（下标从 `0` 开始），`nums[i] + nums[n - 1 - i]` 都等于同一个数，则数组 `nums` 是 互补的 。例如，数组 `[1,2,3,4]` 是互补的，因为对于所有下标 `i` ，`nums[i] + nums[n - 1 - i] = 5` 

返回使数组 互补 的 最少 操作次数

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/minimum-moves-to-make-array-complementary/solution/shi-shu-zu-hu-bu-de-zui-shao-cao-zuo-ci-shu-by-zer/)

### Solution 1:

这种解法最终会超时

````c++
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        const int len = nums.size();
        int ans = INT_MAX;
        for (int i = 2; i <= 2 * limit; ++i) {
            int operations = 0;
            for (int j = 0; j < len / 2; ++j) {
                if (nums[j] + nums[len - 1 - j] == i) {
                    continue;
                } else if (i >= 1 + min(nums[j], nums[len - 1 - j])
                           && i <= limit + max(nums[j], nums[len - 1 - j])) {
                    operations += 1;
                } else {
                    operations += 2;
                }
            }
            ans = min(ans, operations);
        }
        return ans;
    }
};
````

### Solution 2: 差分数组 和 哈希


````c++
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        const int len = nums.size();
        // 差分数组
        vector<int> d(2 * limit + 2);
        // 记录 nums[i] + nums[n - i + 1] 的频数
        unordered_map<int, int> freq;
        for (int i = 0; i + i < len; ++i) {
            ++freq[nums[i] + nums[len - i - 1]];
            // 更新差分数组
            ++d[1 + min(nums[i], nums[len - i - 1])];
            --d[limit + max(nums[i], nums[len - i - 1]) + 1];
        }

        int ans = len * 2;
        // 0/1 贡献的数量
        int contrib01 = 0;
        for (int  k = 2; k <= 2 * limit; ++k) {
            contrib01 += d[k];
            /// 对 0 贡献的数目
            int contrib0 = freq[k];
            // 只贡献 1
            int contrib1 = contrib01 - contrib0;
            // 贡献 2
            int contrib2 = len / 2 - contrib01;
            ans = min(ans, contrib1 + contrib2 * 2);
        }
        return ans;
    }
};
````
