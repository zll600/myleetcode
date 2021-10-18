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
        // 这里使用一个访问数组，记录是否已经选择过了
        vector<bool> visited(nums.size(), 0);
        Backtracking(nums, visited);
        return res_;
    }

 private:
    vector<vector<int>> res_;
    vector<int> path_;

    void Backtracking(vector<int>& nums, vector<bool>& visited) {
        // 递归终止条件
        if (path_.size() == nums.size()) {
            res_.push_back(path_);
            return;
        }
        
        const int size = nums.size();
        for (int i = 0; i < size; ++i) {  // 这里从 0 开始遍历，跳过已经加入的元素
            if (!visited[i]) {
                // 访问
                visited[i] = true;
                path_.push_back(nums[i]);
                // 下一个
                Backtracking(nums, visited);
                // 回溯
                path_.pop_back();
                visited[i] = false;
            }
        }
    }
};
````

