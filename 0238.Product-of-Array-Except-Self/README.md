# [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)

## 题目

Given an integer array `nums`, return *an array* `answer` *such that* `answer[i]` *is equal to the product of all the elements of* `nums` *except* `nums[i]`.

The product of any prefix or suffix of `nums` is **guaranteed** to fit in a **32-bit** integer.

You must write an algorithm that runs in `O(n)` time and without using the division operation.

 

**Example 1:**

```
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
```

**Example 2:**

```
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```

 

**Constraints:**

- `2 <= nums.length <= 105`
- `-30 <= nums[i] <= 30`
- The product of any prefix or suffix of `nums` is **guaranteed** to fit in a **32-bit** integer.

 

**Follow up:** Can you solve the problem in `O(1) `extra space complexity? (The output array **does not** count as extra space for space complexity analysis.)

## 题目大意

给定一个整数数组 nums，返回一个数组 answer，answer[i] 的关于nums 中除了 nums[i] 之外所有元素的乘积

## 解题思路

这道题目的暴力解法，就是分别计算每个位置上除了当前位置外，所有其余位置的数的乘积，但是可以看出，这里面包含右大量的重复计算

### 解法1（暴力）

这里暴力解法会超时

``````c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        const int size = nums.size();
        vector<int> ans(size);
        
        for (int i = 0; i < size; ++i) {
            int product = 1;
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    continue;
                }
                
                product *= nums[j];
            }
            ans[i] = product;
        }
        
        return ans;
    }
};
``````

### 解法2

**注意**：这个解法，看是看不出来的，要自己动手去模拟一下

这道题目的解法，可以参考左程云的那本书，具体来说，可以用两个数组，一个从左往右遍历，表示不含但当前位置的左侧元素的乘积，一个从右往左遍历，表示不含当前位置的右侧元素的乘积，最后将这两个数组对应元素相乘得到结果

优化的方案是，之用一个数组来遍历，从右往左时，使用一个临时变量来解决

````c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        const int size = nums.size();
        vector<int> ans(size);
        ans[0] = 1;  // 第一位初始化为 1
        for (int i = 1; i < size; ++i) {  // 计算当前位置左侧的所有元素之积
            ans[i] = ans[i - 1] * nums[i - 1];
        }
        
        int tmp = nums[size - 1];  // 这里保存从右向左所有数的乘积
        for (int i = size - 2; i >= 0; --i) {
            ans[i] *= tmp;  // 之前计算过的从左向右的乘积，乘上累计的从右往左的乘积，就是最终的结果
            tmp *= nums[i];
        }
        
        return ans;
    }
};
````

