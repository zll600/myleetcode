# [491. Increasing Subsequences](https://leetcode.com/problems/increasing-subsequences/)

## 题目

Given an integer array `nums`, return all the different possible increasing subsequences of the given array with **at least two elements**. You may return the answer in **any order**.

The given array may contain duplicates, and two equal integers should also be considered a special case of increasing sequence.

 

**Example 1:**

```
Input: nums = [4,6,7,7]
Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
```

**Example 2:**

```
Input: nums = [4,4,3,2,1]
Output: [[4,4]]
```

 

**Constraints:**

- `1 <= nums.length <= 15`
- `-100 <= nums[i] <= 100`

## 题目大意

给定一个整数数组（可能含有重复），返回所有可能的递增自序列，每个子序列至少包含两个元素，含有两个相等元素的序列可以被看作是特殊的递增子序列，

## 解题思路

* 注意子序列的顺序必须和原数组相同，不能出现逆序
* 因为不能改变元素的顺序，所以此题的相同元素不一定相邻，必须采用map 去重

## 代码

````c++
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        Backtracking(nums, 0);
        return res;
    }
    
 private:
    vector<vector<int>> res;
    vector<int> path;
    
    void Backtracking(const vector<int>& nums, int start) {
        if (path.size() > 1) {
            res.push_back(path);    // 这里还没有结束，所以不返回
        }
        
        unordered_set<int> visit;
        for (int i = start; i < nums.size(); ++i) {
            // if (i > start && nums[i - 1] == nums[i]) { 这里去重逻辑错误的原因在于相等的元素不一定相邻
            //     continue;
            // }
            if ((!path.empty() && path.back() > nums[i])
               || (visit).find(nums[i]) != visit.end()) {
                continue;
            }
            
            visit.insert(nums[i]);
            path.push_back(nums[i]);
            Backtracking(nums, i + 1);
            path.pop_back();
        }
    }
};
````

