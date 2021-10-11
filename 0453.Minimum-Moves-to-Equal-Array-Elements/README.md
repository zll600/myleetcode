# [453. Minimum Moves to Equal Array Elements](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/)

## 题目

Given an integer array `nums` of size `n`, return *the minimum number of moves required to make all array elements equal*.

In one move, you can increment `n - 1` elements of the array by `1`.

 

**Example 1:**

```
Input: nums = [1,2,3]
Output: 3
Explanation: Only three moves are needed (remember each move increments two elements):
[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
```

**Example 2:**

```
Input: nums = [1,1,1]
Output: 0
```

 

**Constraints:**

- `n == nums.length`
- `1 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`
- The answer is guaranteed to fit in a **32-bit** integer.

## 题目大意

给定一个大小为 n的整数数组，返回可以使所有元素相等的最少次数，每一次移动，将会使 n - 1 个元素增加 1，

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/minimum-moves-to-equal-array-elements/solution/python3-yi-xing-dai-ma-ji-bai-99-diao-ch-25ar/

## 解法1(数学)

````c++
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int min_val = INT_MAX;
        int sum = 0;
        int len = nums.size();
        
        for (int num : nums) {
            sum += num;
            
            if (min_val > num) {
                min_val = num;
            }
        }
        
        return sum - min_val * len;
    }
};
````

## 库函数

借这道题，学习库函数

````
class Solution {
public:
    int minMoves(vector<int>& nums) {
        auto it = min_element(nums.begin(), nums.end());
        int sum = accumulate(nums.begin(), nums.end(), 0);
        
        return sum - *it * nums.size();
    }
};
````

