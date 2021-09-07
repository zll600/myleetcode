# [47. Permutations II](https://leetcode.com/problems/permutations-ii/)

## 题目

Given a collection of numbers, `nums`, that might contain duplicates, return *all possible unique permutations **in any order**.*

**Example 1:**

```
Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]
```

**Example 2:**

```
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

 

**Constraints:**

- `1 <= nums.length <= 8`
- `-10 <= nums[i] <= 10`

## 题目大意

给定一个可能包含重复数值的数组，发布会所有唯一的全排列

## 解题思路

* 可以看这里的题解
  * https://leetcode-cn.com/problems/permutations-ii/solution/hui-su-suan-fa-python-dai-ma-java-dai-ma-by-liwe-2/
* 这里需要仔细画图来解决重复问题，剪枝条件是如果当前元素与上一个元素相同，或者相同的元素加入之后又被撤销

## 代码

````c++
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end()); // 去重的关键
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
            if (!used[i]) {
                if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {  // 这里是去重的逻辑
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
};
````

