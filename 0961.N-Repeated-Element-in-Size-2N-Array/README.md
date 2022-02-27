# [961. N-Repeated Element in Size 2N Array](https://leetcode.com/problems/n-repeated-element-in-size-2n-array/)

## 题目

You are given an integer array `nums` with the following properties:

- `nums.length == 2 * n`.
- `nums` contains `n + 1` **unique** elements.
- Exactly one element of `nums` is repeated `n` times.

Return *the element that is repeated* `n` *times*.

 

**Example 1:**

```
Input: nums = [1,2,3,3]
Output: 3
```

**Example 2:**

```
Input: nums = [2,1,2,5,3,2]
Output: 2
```

**Example 3:**

```
Input: nums = [5,1,5,2,5,3,5,4]
Output: 5
```

 

**Constraints:**

- `2 <= n <= 5000`
- `nums.length == 2 * n`
- `0 <= nums[i] <= 104`
- `nums` contains `n + 1` **unique** elements and one of them is repeated exactly `n` times.

## 题目大意

给定一个含有以下属性的数组：

- 数组的长度等于 `2n`
- 数组有 `n + 1` 个独立的元素
- 只有一个元素重复了 `n` 次，

返回重复了 `n` 次的元素

## 解题思路



### Solution 1: 统计所有字符出现的频数

这种解法啊需要统计出所有字符出现的频数，判断两次

````c++
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        const int len = nums.size();
        unordered_map<int, int> freqs;
        for (int num : nums) {
            ++freqs[num];
        }

        for (const auto& freq : freqs) {
            if (freq.second == len / 2) {
                return freq.first;
            }
        }

        return -1;
    }
};
````
### Solution 2: 一旦发现重复，就直接返回

````c++
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        vector<int> freqs(10001, 0);
        for (int num : nums) {
            if (freqs[num] == 1) {
                return num;
            }
            ++freqs[num];
        }

        return -1;
    }
};
````
