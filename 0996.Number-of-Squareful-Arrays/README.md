# [996. Number of Squareful Arrays](https://leetcode.com/problems/number-of-squareful-arrays/)

## 题目

An array is **squareful** if the sum of every pair of adjacent elements is a **perfect square**.

Given an integer array nums, return *the number of permutations of* `nums` *that are **squareful***.

Two permutations `perm1` and `perm2` are different if there is some index `i` such that `perm1[i] != perm2[i]`.

 

**Example 1:**

```
Input: nums = [1,17,8]
Output: 2
Explanation: [1,8,17] and [17,8,1] are the valid permutations.
```

**Example 2:**

```
Input: nums = [2,2,2]
Output: 1
```

 

**Constraints:**

- `1 <= nums.length <= 12`
- `0 <= nums[i] <= 109`

## 题目大意

给定一个非负整数数组 A，如果相邻两个数之和是一个完全平方数，则称这个数组为正方形数组，给定一个数组nums，返回它的正方形数组的数目。两个排列不同的条件是：如果存在一个下表 i 使得 perm1[i] != perm2[i]

## 解题思路

这道题目可以联系第 47 题，求出一个数组不重复的全排列，不过要加上额外的条件，判断是否符合相邻两个数之和是一个完全平方数

## 代码

`````c++
class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end()); // 这里很关键
        Backtracking(nums, used);
        return res;
    }
    
 private:
    int res;
    vector<int> path;
    
    void Backtracking(const vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            ++res;
            return;
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            if (!used[i]) {
                if (i > 0 && nums[i - 1] == nums[i] && !used[i - 1]) { // 去重
                    continue;
                }
                
                if (path.size() > 0 && !CheckSquare(nums[i] + path.back())) { // 剪枝
                    continue;
                }
                
                path.push_back(nums[i]);
                used[i] = true;
                Backtracking(nums, used);
                used[i] = false;
                path.pop_back();
            }
        }
    }
    
    bool CheckSquare(int num) {
        int tmp = sqrt(num);
        if (tmp * tmp== num) {
            return true;    
        }
        
        return false;
    }
};
`````



