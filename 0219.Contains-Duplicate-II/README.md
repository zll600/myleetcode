# [219. Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/)

Given an integer array `nums` and an integer `k`, return `true` if there are two **distinct indices** `i` and `j` in the array such that `nums[i] == nums[j]` and `abs(i - j) <= k`.

 

**Example 1:**

```
Input: nums = [1,2,3,1], k = 3
Output: true
```

**Example 2:**

```
Input: nums = [1,0,1,1], k = 1
Output: true
```

**Example 3:**

```
Input: nums = [1,2,3,1,2,3], k = 2
Output: false
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`
- `0 <= k <= 105`

## 题目大意

给定一个整数数组和一个整数 k，如果存在两个不同的下标索引 i, j 在数组中有 nums[i] == nums[j]，且abs(i - j) <= k,则返回true，否则返回 false

## 解题思路

### 解法1（利用哈希）

利用哈希表存储这个数上一次出现的位置，如果与当前数相距小于等于 k，即满足条件

`````c++
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> dict;  // 表示这个数上一次出现的位置，需要不断维护更新
 		dict.insert(make_pair(nums[0], 0));

 		for (int i = 1; i < nums.size(); i++) {
 			if (dict.find(nums[i]) != dict.end()
 				&& i - dict.at(nums[i]) <= k) {
 				return true;
 			}
            dict[nums[i]] = i;  // 这里即可能是更新也可能是插入
 		}

 		return false;
    }
};
`````

### 解法2（哈希）

这中解法和解法无本质区别，只是限制了哈希表的大小，

`````c++
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        if (k == 0) {
            return false;
        }
        // 这里使用了一个大小为 k 的哈希表
        unordered_map<int, int> dict;  // 表示这个数上一次出现的位置，需要不断维护更新
 		dict.insert(make_pair(nums[0], 0));

 		for (int i = 1; i < nums.size(); i++) {
 			if (dict.find(nums[i]) != dict.end()) {
                return true;
            }
            dict[nums[i]] = i;
            if (dict.size() > k) {
                dict.erase(nums[i - k]);
            }
 		}

 		return false;
    }
};
`````

