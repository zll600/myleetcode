# [456. 132 Pattern](https://leetcode.com/problems/132-pattern/) 

## 题目

Given an array of `n` integers `nums`, a **132 pattern** is a subsequence of three integers `nums[i]`, `nums[j]` and `nums[k]` such that `i < j < k` and `nums[i] < nums[k] < nums[j]`.

Return *`true` if there is a **132 pattern** in `nums`, otherwise, return `false`.*

 

**Example 1:**

```
Input: nums = [1,2,3,4]
Output: false
Explanation: There is no 132 pattern in the sequence.
```

**Example 2:**

```
Input: nums = [3,1,4,2]
Output: true
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
```

**Example 3:**

```
Input: nums = [-1,3,2,0]
Output: true
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 2 * 105`
- `-109 <= nums[i] <= 109`

## 解题思路

给定一个 n 个整数的数组 nums，

一个 **132 模式**的子序列 nums[i], nums[j]. nums[k] 满足 i < j < k 且 nums[i] <  nums[k] < nums[j]

如果在 nums 有一个**132模式**，则返回 true ，否则返回false。

## 解题思路

* 使用暴力法，超时
* 从数组末尾开始扫，维护一个递减的单调栈，具体题做法是如果遇到比当前栈顶大的元素，则一直弹出当前栈顶元素直到栈为空或者，栈顶元素大于当前的元素，详情可以参考代码，再举一两个例子，就不难理解了。

## 代码

````c++
class Solution {
public:
    // 解法三：使用单调栈来模拟
    /*
    bool find132pattern(vector<int>& nums) {
        int size = nums.size();
        if (size < 3) {
            return false;
        }
        
        stack<int> sta;
        int bound = INT_MIN;
        for (int i = size - 1; i >= 0; --i) {
            if (nums[i] < bound) {
                return true;
            }
            
            while (!sta.empty() && nums[i] > sta.top()) {
                bound = sta.top();
                sta.pop();
            }
            sta.push(nums[i]);
        }
        
        return false;
    } */
    
    // 解法二：优化后的暴力（这个方法有bug， 以后再补）
    /*
    bool find132pattern(vector<int>& nums) {
        int size = nums.size();
        if (size < 3) {
            return false;
        }
        
        for (int j = 0; j < size; ++j) {
            stack<int> sta;
            for (int i = j; i < size; ++i) {
                if (sta.empty() || (!sta.empty() && nums[i] > nums[sta.top()])) {
                    sta.push(i);
                } else if (nums[i] < nums[sta.top()]) {
                    while (!sta.empty()) {
                        if (nums[i] > nums[sta.top()]) {
                            return true;
                        }
                        sta.pop();
                    }
                }
            }
        }
        
        return false;
    }*/
    
    
    // 解法一：暴力枚举所有组合 超时
    /*
    bool find132pattern(vector<int>& nums) {
        int size = nums.size();
        if (size < 3) {
            return false;
        }
        
        for (int i = 0; i < size - 2; ++i) {
            for (int j = i + 1; j < size - 1; ++j) {
                for (int k = j + 1; k < size; ++k) {
                    if (nums[i] < nums[k] && nums[k] < nums[j]) {
                        return true;
                    }
                }
            } 
        }
        return false;
    }*/
};
````

