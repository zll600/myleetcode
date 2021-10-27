# [1512. Number of Good Pairs](https://leetcode.com/problems/number-of-good-pairs/)

## 题目

Given an array of integers `nums`, return *the number of **good pairs***.

A pair `(i, j)` is called *good* if `nums[i] == nums[j]` and `i` < `j`.

 

**Example 1:**

```
Input: nums = [1,2,3,1,1,3]
Output: 4
Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.
```

**Example 2:**

```
Input: nums = [1,1,1,1]
Output: 6
Explanation: Each pair in the array are good.
```

**Example 3:**

```
Input: nums = [1,2,3]
Output: 0
```

 

**Constraints:**

- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

## 题目大意

给你一个整数数组 nums。如果一组数字 (i,j) 满足 nums[i] == nums[j] 且 i < j ，就可以认为这是一组好数对。返回好数对的数目。

## 解题思路

### Solution 1:

这种解法直接两层循环就可以解决

````c++
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int res = 0;
        const int size = nums.size();
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if (nums[i] == nums[j]) {
                    ++res;
                }
            }
        }
        
        return res;
    }
};
````

### Solution 2:

这种解法，可以参考这篇题解：https://leetcode-cn.com/problems/number-of-good-pairs/solution/zhe-gu-ji-shi-wo-xie-zen-yao-duo-ti-yi-lai-zui-dua/

这种解法的关键在于，后面每新增一个数，都可以和前面的所有数配对一次，

`````c++
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int res = 0;
        const int size = nums.size();
        vector<int> cnt(101);
        
        for (int num : nums) {
            res += cnt[num];
            ++cnt[num];
        }
        
        return res;
    }
};
`````

