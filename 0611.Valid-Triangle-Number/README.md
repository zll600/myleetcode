# [611. Valid Triangle Number](https://leetcode.com/problems/valid-triangle-number/)

## 题目

Given an integer array `nums`, return *the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle*.

 

**Example 1:**

```
Input: nums = [2,2,3,4]
Output: 3
Explanation: Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
```

**Example 2:**

```
Input: nums = [4,2,3,4]
Output: 4
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `0 <= nums[i] <= 1000`

## 题目大意

给定一个整数数组 nums，你的任务是统计其中可以组成三角形三条边的三元组个数。

## 解题思路

这道题的做法可以参考这篇题解：https://leetcode-cn.com/problems/valid-triangle-number/solution/ming-que-tiao-jian-jin-xing-qiu-jie-by-jerring/

三条边可以组成三角形的要求是

* 任意两边之和大于第三边，任意两边之差小于第三边
* 如果将数组排序之后，只需验证两个较小边的和大于第三边

### 解法1：

三重循环，枚举所有可能

```c++
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int res = 0;
        const int size = nums.size();
        for (int i = 0; i < size - 2; ++i) {
            for (int j = i + 1; j < size - 1; ++j) {
                for (int k = j + 1; k < size; ++k) {
                    if (nums[i] + nums[j] > nums[k]) {
                        ++res;
                    }
                }
            }
        }
        
        return res;
    }
};
```

### 解法2：

三数之和中可以得到启发，将数组排序，对最内层循环使用二分查找，可以降低时间复杂度

````c++
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int res = 0;
        const int size = nums.size();
        for (int i = 0; i < size - 2; ++i) {
            for (int j = i + 1; j < size - 1; ++j) {
                // 这里改用二分查找，降低时间复杂度
                int left = j + 1;
                int right = size - 1;
                while (left < right) {
                    int mid = left + (right - left + 1) / 2;
                    if (nums[mid] < nums[i] + nums[j]) {  // 找到左边最后一个满足要求的
                        left = mid;
                    } else {
                        right = mid - 1;
                    }
                }
                
                if (nums[right] < nums[i] + nums[j]) {  // 一次算一段
                    res += right - j;
                }
            }
        }
        
        return res;
    }
};
````

### 解法3：

将内存循环改为双指针，每次计算一个区间

这道题曾想过用排列组合来做，但是就没有办法确定双指针的移动，所以这里没有使用，而是逐步调整双指针

````c++
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int res = 0;
        const int size = nums.size();
        for (int i = size - 1; i >= 2; --i) {
            // 采用双指针来作
            int left = 0;
            int right = i - 1;
            while (left < right) {
                if (nums[left] + nums[right] > nums[i]) {  // 此时可以将右指针左移
                    res += right - left;
                    --right;
                } else {
                    // 如果不满足可以将左指针右移
                    ++left;
                }
            }
        }
        
        return res;
    }
};
````

