# [90. Subsets II](https://leetcode.com/problems/subsets-ii/)

## 题目

Given an integer array `nums` that may contain duplicates, return *all possible subsets (the power set)*.

The solution set **must not** contain duplicate subsets. Return the solution in **any order**.

 

**Example 1:**

```
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
```

**Example 2:**

```
Input: nums = [0]
Output: [[],[0]]
```

 

**Constraints:**

- `1 <= nums.length <= 10`
- `-10 <= nums[i] <= 10`

## 题目大意

给定一个可以包含重复数字的数组，返回所有可能的子集（幂集），结果不能含有重复的数组。

## 解题思路

* 这道题可以联系第78题，都是回溯法来求子集问题，不过要加上去重的条件。

## 代码

````c++
// 解法一：回溯 + 剪枝
/*
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // 含有重复元素，因此需要排序，    
        Backtracking(nums, 0);
        return res;
    }
    
 private:
    vector<vector<int>> res;
    vector<int> path;
    
    void Backtracking(const vector<int>& nums, int start) {
        res.push_back(path);
    
        int size = nums.size();
        for (int i = start; i < size; ++i) {
            if (i > start && nums[i - 1] == nums[i]) {  // 剪枝,可以画图找答案
                continue;
            }
            path.push_back(nums[i]);
            Backtracking(nums, i + 1);
            path.pop_back();
        }
    }  
};
*/

// 解法二：对每种长度的结果，均求一次结果集
class Solution {
 public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 0; i <= nums.size(); ++i) {
            GenerateSubsetWithDup(nums, i, 0);
        }
        return res;
    }

 private:
    vector<vector<int>> res;
    vector<int> path;
    
    void GenerateSubsetWithDup(const vector<int>& nums, int k, int start) {
        if (path.size() == k) {
            res.push_back(path);
            return;
        }
        
        int size = nums.size();
        for (int i = start; i < size - (k - path.size()) + 1; ++i) { // 这里可以剪枝
            if (i > start && nums[i - 1] == nums[i]) {  // 去重条件
                continue;
            }
            path.push_back(nums[i]);
            GenerateSubsetWithDup(nums, k, i + 1);
            path.pop_back();
        }
    }
};
````



