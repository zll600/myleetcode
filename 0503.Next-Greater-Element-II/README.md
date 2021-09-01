# [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/)

## 题目

Given a circular integer array `nums` (i.e., the next element of `nums[nums.length - 1]` is `nums[0]`), return *the **next greater number** for every element in* `nums`.

The **next greater number** of a number `x` is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return `-1` for this number.

 

**Example 1:**

```
Input: nums = [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; 
The number 2 can't find next greater number. 
The second 1's next greater number needs to search circularly, which is also 2.
```

**Example 2:**

```
Input: nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`

## 题目大意

给定一个循环的整数数组（最后一个元素的下一个元素是第一个元素），返回每个元素的下一个最大值，如果没有，返回 -1

## 解题思路

* 这道题可以和第 496 题一起看，多了一个循环数组的条件。
* 可以利用单调栈来考虑，不过这里需要对数组遍历两次，并对下标进行取模操作，

## 代码

````c++
class Solution {
public:
    // 解法一：单调栈
    /*
    vector<int> nextGreaterElements(vector<int>& nums) {
        int size = nums.size();
        vector<int> res(size, -1);
        
        stack<int> idx;
        for (int i = 0; i < size * 2L; ++i) {
            int val = nums[i % size];
            
            while (!idx.empty() && val > nums[idx.top()]) {
                res[idx.top()] = val;
                idx.pop();
                
            }
            idx.push(i % size);
        }
        
        return res;
    }*/
    
    // 解法二：优化遍历
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> res;
        
        int size = nums.size();
        for (int i = 0; i < size; ++i) {
            bool find = false;
            int j = (i + 1) % size;
            
            while (j != i) {
                if (nums[j] > nums[i]) {
                    res.push_back(nums[j]);
                    find = true;
                    break;
                }
                j = (j + 1) % size;
            }
            
            if (find == false) {
                res.push_back(-1);
            }
        }
        
        return res;
    }
};
````

