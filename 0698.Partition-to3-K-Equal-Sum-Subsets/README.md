# [698. Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/)

## 题目

Given an integer array `nums` and an integer `k`, return `true` if it is possible to divide this array into `k` non-empty subsets whose sums are all equal.

 

**Example 1:**

```
Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
```

**Example 2:**

```
Input: nums = [1,2,3,4], k = 3
Output: false
```

 

**Constraints:**

- `1 <= k <= nums.length <= 16`
- `1 <= nums[i] <= 104`
- The frequency of each element is in the range `[1, 4]`.

## 题目大意

给定一个整数数组 nums 和一个整数 k，如果可以将这个数组分为 k 个非空的子数组，且他们的和都是相等的，就返回 true，否则返回 false

## 解体思路

这道题的想法来自于第 416 题，这道题目也相当于求 组合 数，其中每个元素只能用一次，最终可以产生多少种不同的组合

### 解法1（回溯）

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/solution/javahui-su-jian-zhi-shou-ba-shou-jiao-hu-0equ/

利用回溯法，生成和为 sum / k 的组合，任意一个组合生成失败，就返回  false，说明不符合条件，在形成组合的过程中，每个元素只能使用一次，不能多次使用，这里是利用一个数组来作标记，如果使用过了，则直接跳过，

递归的终止条件是：

* 子数组和 为 sum / k
* 子数组和不为 sum / k，但原数组已经遍历完毕

这里可以剪枝的地方：

* 如果 sum 不能被 k 整除，则一定不能分成 k 个和相等的数组
* 每次匹配新组合时，都不使用已经使用过的数组
* 在匹配的过程中，如果出现 nums[i] > targe 则直接跳过，这条路不能再递归下去

`````c++
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);  // 求和函数
        if (sum % k != 0) {  // 如果 sum 不能被 k 整除，则直接返回 false
            return false;
        }
        
        sort(nums.begin(), nums.end(), greater<int>());  // 先排序，从大到小选，尽可能现匹配大的，不然可能放不下
        int target = sum / k;  // 每个子集的和
        int size = nums.size();
        if (nums.back() > target) {  // 剪枝
            return false;
        } 
        vector<bool> visited(size, false);  // 标记数组
        
        for (int i = 0; i < size; ++i) {
            if (visited[i]) {  // 跳过已经使用过的元素，剪枝
                continue;
            }
            
            if (!DFS(nums, i + 1, target - nums[i], visited)) {  // 如果任意一个数不能形成一个组合，直接返回  false
                return false;
            }
        }
        return true;
    }
    
 private:
    bool DFS(const vector<int>& nums, int idx, int target,
            vector<bool>& visited) {
        if (target == 0) {  // 数组和为 target
            return true;
        }
        if (idx == nums.size()) {  // 数组和不为 target，但已遍历完数组，所以这一组不可能凑成 target，返回  false
            return false;
        }
        
        int size = nums.size();
        for (int i = idx; i < size; ++i) {
            if (visited[i] || nums[i] > target) {  // 剪枝优化
                continue;
            }
            
            visited[i] = true;  // 已经使用过了
            if (DFS(nums, i + 1, target - nums[i], visited)) {
                return true;  // 只要匹配成功，就可以直接返回
            }
            visited[i] = false;  // 回溯
        }
        return false;
    }
};
`````

