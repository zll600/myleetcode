# [46. Permutations](https://leetcode.com/problems/permutations/)

## 题目

Given an array `nums` of distinct integers, return *all the possible permutations*. You can return the answer in **any order**.

**Example 1:**

```
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

**Example 2:**

```
Input: nums = [0,1]
Output: [[0,1],[1,0]]
```

**Example 3:**

```
Input: nums = [1]
Output: [[1]]
```

 

**Constraints:**

- `1 <= nums.length <= 6`
- `-10 <= nums[i] <= 10`
- All the integers of `nums` are **unique**.

## 题目大意

给定一组整数，返回所有可能的全排列。

## 解题思路

这是一道排列的题目，可以使用回溯法来解决，排列的题目使用used数组来进行判断是否已经选择过，

## 代码

````c++
class Solution {
public:
    
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        Backtracking(nums, used);
        return res;
    }
    
 private:
    vector<vector<int>> res;
    vector<int> path;
    
    void Backtracking(const vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        
        int size = nums.size();
        for (int i = 0; i < size; ++i) {
            if (used[i] == true) {
                continue;
            }
            
            path.push_back(nums[i]);
            used[i] = true;
            Backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
};
````

