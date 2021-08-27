# [16. 3Sum Closest](https://leetcode.com/problems/3sum-closest/)

## 题目

Given an integer array `nums` of length `n` and an integer `target`, find three integers in `nums` such that the sum is closest to `target`.

Return *the sum of the three integers*.

You may assume that each input would have exactly one solution.

 

**Example 1:**

```
Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
```

**Example 2:**

```
Input: nums = [0,0,0], target = 1
Output: 0
```

 

**Constraints:**

- `3 <= nums.length <= 1000`
- `-1000 <= nums[i] <= 1000`
- `-104 <= target <= 104`

## 题目大意

给定一个数组，找出这个数组中一个三元组，其和最接近 target

## 解题思路

* 注意这里接近 target，有两个方向，正方向和负方向均可，所以更新 res 时，比较的是差值的绝对值
* 还需要处理出现重复数字的情况，先排序，再双指针左右夹逼，时间复杂度 O(n * logn)
* 这道题也可以暴力解，时间复杂度 O(n^3)

````c++
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int size = nums.size();
        int res = 0;
        int diff = INT_MAX;  // diff 比较取最小，先设置为最大
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < size - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            int j = i + 1;
            int k = size - 1;
            
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                
                int dis = abs(sum - target);
                if (dis < diff) {
                    res = sum;
                    diff = dis;
                }
                
                if (sum == target) {
                    return sum;
                } else if (sum > target) {
                    while (j < k && nums[k] == nums[--k]);
                } else {
                    while (j < k && nums[j] == nums[++j]);
                }
            }
        }
        
        return res;
    }   
};

// 解法二：Brute force
class Solution {
 public:
    int threeSumClosest(vector<int>& nums, int target) {
        int size = nums.size();
        int res = 0;
        int diff = INT_MAX;
        
        for (int i = 0; i < size - 2; ++i) {
            for (int j = i + 1; j < size - 1; ++j) {
                for (int k = j + 1; k < size; ++k) {
                    int sum = nums[i] + nums[j] + nums[k];
                    int dis = abs(sum - target);
                    if (dis < diff) {
                        res = sum;
                        diff = dis;
                    }
                }
            }
        }
        return res;
    }
};
````

