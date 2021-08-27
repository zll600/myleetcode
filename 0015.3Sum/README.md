# [15. 3Sum](https://leetcode.com/problems/3sum/)

## 题目

Given an integer array nums, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must not contain duplicate triplets.

 

**Example 1:**

```
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
```

**Example 2:**

```
Input: nums = []
Output: []
```

**Example 3:**

```
Input: nums = [0]
Output: []
```

 

**Constraints:**

- `0 <= nums.length <= 3000`
- `-105 <= nums[i] <= 105`

## 题目大意

给定一个整数数组，找出 相加和为0 的三元组，

结果不能包含重复的三元组

## 解题思路

* 一种方法是用 map 提前记录好两数之后，可以将时间复杂度降低到 O(n^2)，但是最后结果要求不能输出重复的解，数组中同一个元素可能出现多次，同一个数字也可能使用多次，例如 [-1，-1，2] 和 [2, -1, -1]、[-1, 2, -1] 这 3 个解是重复的，即使 -1 可能出现 100 次，每次使用的 -1 的数组下标都是不同的。
* 需要去重和排序。map 记录每个数字出现的次数，然后对 map 的 key 数组进行排序，最后在这个排序以后的数组里面扫，找到另外 2 个数字能和自己组成 0 的组合
* 不使用 map而使用双指针O(nlogn)，很多时候使用双指针可以减少一层循环。

````c++
// 解法一：排序加双指针
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int size = nums.size();
        if (size < 3) {
            return vector<vector<int>>();
        }
        
        sort(nums.begin(), nums.end());
        
        vector<vector<int>> res;
        for (int i = 0; i < size; ++i) {
            if  (nums[i] > 0) {	// 如果排序后 nums[i] > 0，则 nums[j] 和 nums[k] 也必定大于0，不能构成三元组
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {	// 去重逻辑
                continue;
            }
            
            int j = i + 1;
            int k = size - 1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                
                if (sum == 0) {
                    res.emplace_back(vector<int>{nums[i], nums[j], nums[k]});
                    while (j < k && nums[k] == nums[--k]);	// 去重，这里必须两个指针都移动，因为任意一个边界变化后，另一个边界必然不能满足
                    while (j < k && nums[j] == nums[++j]);	// 条件，
                } else if (sum > 0) {
                    while (j < k && nums[k] == nums[--k]);	// 去重
                } else {
                    while (j < k && nums[j] == nums[++j]);	// 去重
                }
            }
        }
        return res;
    }
};

// 解法二： map 作缓存，减少一层循环
class Solution {
 public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int size = nums.size();
        if (size < 3) {
            return vector<vector<int>>();
        }
        vector<vector<int>> res;
        
        unordered_map<int, int> freq;
        for (int i : nums) {
            freq[i]++;
        }
        
        vector<int> uniq_num;
        for (auto it = freq.begin(); it != freq.end(); ++it) {
            uniq_num.push_back(it->first);
        }
        sort(uniq_num.begin(), uniq_num.end());
        
        for (int i = 0; i < uniq_num.size(); ++i) {
            if (uniq_num[i] == 0 && freq[uniq_num[i]] >= 3) {	// 数组中是否至少有 3 个 0，
                res.emplace_back(vector<int>{uniq_num[i], uniq_num[i], uniq_num[i]});
            }
            
            for (int j = i + 1; j < uniq_num.size(); ++j) {
                if (uniq_num[i] * 2L == -uniq_num[j] && freq[uniq_num[i]] > 1) {	// 这里有乘法和加法，需要处理溢出的情况，
                    res.emplace_back(vector<int>{uniq_num[i], uniq_num[i], uniq_num[j]});	// 这里比较时先升级为 long 型，然后自动截断
                }
                
                if (-uniq_num[i] == uniq_num[j] * 2L && freq[uniq_num[j]] > 1) {
                    res.emplace_back(vector<int>{uniq_num[i], uniq_num[j], uniq_num[j]});
                }
                
                int k = 0 - uniq_num[i] - uniq_num[j];
                if (k > uniq_num[j] && freq[k] > 0) {
                    res.emplace_back(vector<int>{uniq_num[i], uniq_num[j], k});
                }
            }
        }
        
        return res;
    }
};
````

