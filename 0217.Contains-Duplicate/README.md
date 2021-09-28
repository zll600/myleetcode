# [217. Contains Duplicate](https://leetcode.com/problems/contains-duplicate/)

## 题目

Given an integer array `nums`, return `true` if any value appears **at least twice** in the array, and return `false` if every element is distinct.

 

**Example 1:**

```
Input: nums = [1,2,3,1]
Output: true
```

**Example 2:**

```
Input: nums = [1,2,3,4]
Output: false
```

**Example 3:**

```
Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`

## 题目大意

给定一个正整数，如果有任何一个值出现至少两次，就返回true，如果没有元素都不相同，则返回 false

## 解题思路

找到数组中的重复数字，这里可以参考这篇题解：https://leetcode-cn.com/problems/contains-duplicate/solution/chao-xiang-xi-kuai-lai-miao-dong-ru-he-p-sf6e/

### 解法1（排序）

这种解法先将原数组排序，这样相同元素就会相邻

````c++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                return true;
            }
        }
        
        return false;
    }
};
````

### 解法2（哈希）

这种解法利用一个哈希表作缓存，记录已经遍历过的元素，如果出现重复，直接返回true

````c++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> cache;
        
        for (int i = 0; i < nums.size(); i++) {
            if (cache.find(nums[i]) != cache.end()) {
                return true;
            }
            cache.insert(nums[i]);
        }
        return false;
    }
};
````

