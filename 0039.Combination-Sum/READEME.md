# [39. Combination Sum](https://leetcode.com/problems/combination-sum/)

## 题目

Given an array of **distinct**integers `candidates` and a target integer `target`, return *a list of all **unique combinations** of* `candidates` *where the chosen numbers sum to* `target`*.* You may return the combinations in **any order**.

The **same** number may be chosen from `candidates` an **unlimited number of times**. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is **guaranteed** that the number of unique combinations that sum up to `target` is less than `150` combinations for the given input.

 

**Example 1:**

```
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
```

**Example 2:**

```
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
```

**Example 3:**

```
Input: candidates = [2], target = 1
Output: []
```

**Example 4:**

```
Input: candidates = [1], target = 1
Output: [[1]]
```

**Example 5:**

```
Input: candidates = [1], target = 2
Output: [[1,1]]
```

 

**Constraints:**

- `1 <= candidates.length <= 30`
- `1 <= candidates[i] <= 200`
- All elements of `candidates` are **distinct**.
- `1 <= target <= 500`

## 题目大意

给定一个没有重复数字的整数数组 candidates和一个target，返回这个数组中所有和为 target 的组合。一个数可以被选用无数次，同一个数字被选用的次数不同也代表是不同的组合。

## 解题思路

* 这是一道组合问题，可以用回溯来解决，不过这里要注意组合的去重。

## 代码

````c++
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        if (candidates.empty()) {
            return vector<vector<int>>();
        }
        sort(candidates.begin(), candidates.end());
        Backtracking(candidates, target, 0);
        return res;
    }
    
 private:
    vector<vector<int>> res;
    vector<int> path;
    
    void Backtracking(vector<int>& candidates, int target, int idx)  {
        /*
        if (target <= 0) {
            if (target == 0) {
                res.push_back(path);
            }
            return;
        }*/
        
        if (target == 0) {
            res.push_back(path);
            return;
        }

        int size = candidates.size();
        for (int i = idx; i < size; ++i) {
            if (candidates[i] > target) {   // 这里可以做剪枝优化
                break;
            }
            
            path.push_back(candidates[i]);
            Backtracking(candidates, target - candidates[i], i);  // 因为可以重复选，所以下一层递归传idx
            path.pop_back();
        }
    }
};
````

