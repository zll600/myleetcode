# [372. Super Pow](https://leetcode.com/problems/super-pow/)

## 题目

Your task is to calculate `ab` mod `1337` where `a` is a positive integer and `b` is an extremely large positive integer given in the form of an array.

 

**Example 1:**

```
Input: a = 2, b = [3]
Output: 8
```

**Example 2:**

```
Input: a = 2, b = [1,0]
Output: 1024
```

**Example 3:**

```
Input: a = 1, b = [4,3,3,8,5,2]
Output: 1
```

**Example 4:**

```
Input: a = 2147483647, b = [2,0,0]
Output: 1198
```

 

**Constraints:**

- `1 <= a <= 231 - 1`
- `1 <= b.length <= 2000`
- `0 <= b[i] <= 9`
- `b` doesn't contain leading zeros.

## 题目大意

你的任务是计算 `a^b` 对 1337 取模，其中  a 是一个正整数， b 是以数组形式给出的极大的数组

## 解题思路

这道题对数学要求有点高，这里放上一篇题解，：https://books.halfrost.com/leetcode/ChapterFour/0300~0399/0372.Super-Pow/

### Solution 1:

这种解法还是看一下上面的题解吧

`````c++
class Solution {
public:
    int superPow(int a, vector<int>& b) {
        return SuperPow(a, b, b.size() - 1);
    }
    
 private:
    static const int mod = 1337;
    
    int SuperPow(int a, const vector<int>& b, int idx) {
        if (idx == -1) {  // 如果所有的数字都取完了，直接返回
            return 1;
        }
        
        int last = b[idx];  // 每次取最后一位
        int cur = 1;
        
        // 计算乘方
        for (int i = 0; i < last; ++i) {
            cur = 1L * a * cur % mod;  // 乘法需要注意溢出问题，这里采用短暂的提升
        }
        
        // 除了当前的最后一位之外的前几位
        int next = SuperPow(a, b, idx - 1);
        int rest = 1;
        
        // 
        for (int i = 0; i < 10; ++i) {
            rest = 1L * rest * next % mod;
        }
        
        return 1L * rest * cur % mod;
    }
};
`````

