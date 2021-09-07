# [78. Subsets](https://leetcode.com/problems/subsets/)

## 题目

Given an integer array `nums` of **unique** elements, return *all possible subsets (the power set)*.

The solution set **must not** contain duplicate subsets. Return the solution in **any order**.

 

**Example 1:**

```
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

**Example 2:**

```
Input: nums = [0]
Output: [[],[0]]
```

 

**Constraints:**

- `1 <= nums.length <= 10`
- `-10 <= nums[i] <= 10`
- All the numbers of `nums` are **unique**.

## 题目大意

给定一个不包含重覆元素的数组，返回所有可能的子集（幂集），结果不能包含重复

## 解题思路

* 这道题可以用回溯法来解决，不过先画图再说

## 代码

````c++
class Solution {
public:
    // 解法一：回溯法
    vector<vector<int>> subsets(vector<int>& nums) {
        Backtracking(nums, 0);
        return res;
    }
    
    /*内存超出限制
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        res.push_back(vector<int>());
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < res.size(); ++j) {
                vector<int> tmp(res[j]);
                tmp.push_back(nums[i]);
                res.push_back(tmp);
            }
        }
        
        return res;
    }*/
    
 private:
    vector<vector<int>> res;
    vector<int> path;
    
    void Backtracking(const vector<int>& nums, int start) { // 只能选后面的数，所有用一个状态变量表示起点
        res.push_back(path);    // 结果集是所有的节点，所以每一个都加入，这里的逻辑也加入了空的集合
        for (int i = start; i < nums.size(); ++i) {
            path.push_back(nums[i]);
            Backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    
};
````

