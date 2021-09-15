# [421. Maximum XOR of Two Numbers in an Array](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/)

## 题目

Given an integer array `nums`, return *the maximum result of* `nums[i] XOR nums[j]`, where `0 <= i <= j < n`.

 

**Example 1:**

```
Input: nums = [3,10,5,25,2,8]
Output: 28
Explanation: The maximum result is 5 XOR 25 = 28.
```

**Example 2:**

```
Input: nums = [0]
Output: 0
```

**Example 3:**

```
Input: nums = [2,4]
Output: 6
```

**Example 4:**

```
Input: nums = [8,10,2]
Output: 10
```

**Example 5:**

```
Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
Output: 127
```

 

**Constraints:**

- `1 <= nums.length <= 2 * 105`
- `0 <= nums[i] <= 231 - 1`

## 题目大意

给定一个整数数组返回了两个数的最大异或和，

## 解题思路

`````c++
class Solution {
public:
    // 先确定高位，在确定低位，才能保证这道题的最大值
    // 一位接着一位去确定这个数的大小
    // 利用性质： a ^ b = c, 则 a ^ c = b，且 b ^ c = a
    int findMaximumXOR(vector<int>& nums) {
        int res = 0;
        int mask = 0;

        for (int i = 30; i >= 0; --i) {
            // 注意点1：注意保留前缀的方法，mask，是这样得来的
            // 用异或也是可以的 mask ^ (1 << i)
            mask = mask | (1 << i);

            unordered_set<int> dict;
            for (int num : nums) {
                // 注意点2：这里使用 &，保留前缀的意思（从高位到低位）
                dict.insert(num & mask);
            }

            // 这里假定第 n 位为1，前 n - 1 位 res 为之前迭代求得
            int tmp = res | (1 << i);
            for (int prefix : dict) {
                if (dict.find(prefix ^ tmp) != dict.end()) {
                    res = tmp;
                    break;
                }
            }
        }
        return res;
    }
};
`````

