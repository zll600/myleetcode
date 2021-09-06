# [40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)

Given a collection of candidate numbers (`candidates`) and a target number (`target`), find all unique combinations in `candidates` where the candidate numbers sum to `target`.

Each number in `candidates` may only be used **once** in the combination.

**Note:** The solution set must not contain duplicate combinations.

**Example 1:**

```
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
```

**Example 2:**

```
Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]
```

 

**Constraints:**

- `1 <= candidates.length <= 100`
- `1 <= candidates[i] <= 50`
- `1 <= target <= 30`

## 题目大意

给定一个可包含重复值的数组和一个目标值，返回数组中和为 target 的所有组合，每个数只能用一次，结果集中不能包含重复。

## 解题思路

* 这是一道组合问题，可以利用回溯法来解决，不过要注意去重。
* 这道题的去重逻辑在于同一层的节点之间不能出现重复，最左侧的节点已经搜索过这个值包含的所有结果（这里建议画图来看，一定要画全，就可以看出来了）

## 代码

````c++
class Solution {
public:

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        Backtracking(candidates, target, 0);
        return res;
    }
    
 private:
    vector<vector<int>> res;
    vector<int> path;
    
    void Backtracking(vector<int>& nums, int target, int idx) {
        /*
        if (target <= 0) {
            if (target == 0) {
                res.push_back(path);
            }
            return;
        }*/
        
        // 已经剪过枝了，所以不会出现 target < 0 的情况
        if (target == 0) {
            res.push_back(path);
            return;
        }
        
        int size = nums.size();
        for (int i = idx; i < size; ++i) {
            if (nums[i] > target) { // 剪枝
                break;
            }
            
            if (i > idx && nums[i] == nums[i - 1]) {    // 去重
                continue;
            }
            
            path.push_back(nums[i]);
            Backtracking(nums, target - nums[i], i + 1);
            path.pop_back();
        }
    }
};
````



