# [728. Self Dividing Numbers](https://leetcode-cn.com/problems/self-dividing-numbers/)



## 题目

A **self-dividing number** is a number that is divisible by every digit it contains.

- For example, `128` is **a self-dividing number** because `128 % 1 == 0`, `128 % 2 == 0`, and `128 % 8 == 0`.

A **self-dividing number** is not allowed to contain the digit zero.

Given two integers `left` and `right`, return *a list of all the **self-dividing numbers** in the range* `[left, right]`.

 

**Example 1:**

```
Input: left = 1, right = 22
Output: [1,2,3,4,5,6,7,8,9,11,12,15,22]
```

**Example 2:**

```
Input: left = 47, right = 85
Output: [48,55,66,77]
```

 

**Constraints:**

- `1 <= left <= right <= 104`

## 题目大意

自除数可以被它自身 **每一位** 上的数整除，自除数本身 **不可以包含0** ，

给定一个范围 `[left, right]` 返回这个范围中的所有自除数的列表

## 解题思路

这道题目的关键就是如何判断一个数是否是自除数

### Solution 1:


````c++
class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> res;
        for (int i = left; i <= right; ++i) {
            if (IsSelfDividingNum(i)) {
                res.push_back(i);
            }
        }
        
        return res;
    }
    
 private:
    bool IsSelfDividingNum(int num) {
        int src = num;
        while (num) {
            int digit = num % 10;
            if (digit == 0 || src % digit != 0) {
                return false;
            }
            num /= 10;
        }
        
        return true;
    }
};
````
