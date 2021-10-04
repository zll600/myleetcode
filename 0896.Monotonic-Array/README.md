# [896. Monotonic Array](https://leetcode.com/problems/monotonic-array/)

## 题目

An array is **monotonic** if it is either monotone increasing or monotone decreasing.

An array `nums` is monotone increasing if for all `i <= j`, `nums[i] <= nums[j]`. An array `nums` is monotone decreasing if for all `i <= j`, `nums[i] >= nums[j]`.

Given an integer array `nums`, return `true` *if the given array is monotonic, or* `false` *otherwise*.

 

**Example 1:**

```
Input: nums = [1,2,2,3]
Output: true
```

**Example 2:**

```
Input: nums = [6,5,4,4]
Output: true
```

**Example 3:**

```
Input: nums = [1,3,2]
Output: false
```

**Example 4:**

```
Input: nums = [1,2,4,5]
Output: true
```

**Example 5:**

```
Input: nums = [1,1,1]
Output: true
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-105 <= nums[i] <= 105`

## 题目大意

如果数组是单调递增的或者是单调递减的，则数组是单调的

如果对于所有 i <= j，A[i] <= A[j]，那么数组 A 是单调递增的。 如果对于所有 i <= j，A[i]> = A[j]，那么数组 A 是单调递减的。

给定一个整数数组，如果是单调的就返回 true，否则就返回 false

## 解题思路

这道题目的关键自于单调是 非严格的单调递增与递减，所以想要判断应该检查其是单调递增还是递减，需要找到第一个不相等的数才可以

### 解法1

这种解法需要遍历两次才能解决问题

`````c++
class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        if (nums.size() < 2) {  // 处理特殊情况
            return true;
        }
        
        // 单调递增或者单调递减
        return inc(nums) || dec(nums);
    }
    
 private:
    // 注意这里判断的是非严格递增
    bool inc(const vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i - 1]) {
                return false;
            }
        }
        return true;
    }
    
    // 注意这里判断的是非严格递减
    bool dec(const vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                return false;
            }
        }
        
        return true;
    }
};
`````

### 解法2

这种方法只需要一次遍历即可，在遍历的过程中用两个变量保存结果，

`````c++
class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        if (nums.size() < 2) {  // 处理特殊情况
            return true;
        }
        
        // 只需一次遍历
        // 单调递增或者单调递减
        bool increase = true;
        bool decrease = true;
        for (int i = 1; i < nums.size(); i++) {
            increase &= nums[i] >= nums[i - 1];
            decrease &= nums[i] <= nums[i - 1];
        }
        
        return increase || decrease;
    }
    
 private:
    // 注意这里判断的是非严格递增
    bool inc(const vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i - 1]) {
                return false;
            }
        }
        return true;
    }
    
    // 注意这里判断的是非严格递减
    bool dec(const vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                return false;
            }
        }
        
        return true;
    }
};
`````

