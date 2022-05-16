# [1296. Divide Array in Sets of K Consecutive Numbers](https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/)

## 题目

Given an array of integers `nums` and a positive integer `k`, check whether it is possible to divide this array into sets of `k` consecutive numbers.

Return `true` *if it is possible*. Otherwise, return `false`.

 

**Example 1:**

```
Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
```

**Example 2:**

```
Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].
```

**Example 3:**

```
Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.
```

 

**Constraints:**

- `1 <= k <= nums.length <= 105`
- `1 <= nums[i] <= 109`

 

**Note:** This question is the same as 846: https://leetcode.com/problems/hand-of-straights/

## 题目大意

给你一个整数数组 `nums` 和一个正整数 `k`，请你判断是否可以把这个数组划分成一些由 `k` 个连续数字组成的集合

如果可以，请返回 true；否则，返回 false

## 解题思路

这道题目可以这样想，将整个数组排序之后，用值较小的作为首元素求 k 个连续的数，一旦不满足，就直接报错即可，所以这里就可以想到贪心的思路

### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1200~1299/1296.Divide-Array-in-Sets-of-K-Consecutive-Numbers/)

利用贪心的思想

- 统计所有数字的频数
- 将数组排序
- 优先选择较小的数字开始组成 k 个连续元素，一旦无法组成，就直接报错，这个阶段同时还需要递减频数

````c++
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        // 统计频数
        unordered_map<int, int> freq;
        for (int num : nums) {
            ++freq[num];
        }
        
        // 数组元素按照升序排序
        sort(nums.begin(), nums.end());
        // 找出连续的 k 个元素
        for (int num : nums) {
            // 如果这个元素已经不能再选了
            if (!freq[num]) {
                continue;
            }
            
            for (int diff = 0; diff < k; ++diff) {
                if (!freq[num + diff]) {
                    cout << num << endl;
                    return false;
                }
                --freq[num + diff];
            }
        }
        return true;
    } 
};
````
