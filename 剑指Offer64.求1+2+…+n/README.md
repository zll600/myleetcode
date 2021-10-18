# [剑指 Offer 64. 求1+2+…+n](https://leetcode-cn.com/problems/qiu-12n-lcof/)

## 题目

求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

 

示例 1：

输入: n = 3
输出: 6
示例 2：

输入: n = 9
输出: 45


限制：

1 <= n <= 10000

## 解题思路

### Solution 1:

这个解法很简洁，也很好理解（狗头保命）

````c++
class Solution {
public:
    int sumNums(int n) {
        bool a[n][n+1];
        return sizeof(a)>>1;
    }
};
````

### Solution 2: 求和公式

不过这种解法要用到除法，不满足题目要求

````c++
class Solution {
public:
    int sumNums(int n) {
        // return n * (n + 1) / 2;
        return n * (n + 1) >> 1;
    }
};
````

### Solution 3: 迭代

这种解法要用到循环，所以不满足题目要求

````c++
class Solution {
public:
    int sumNums(int n) {
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            res += i;
        }

        return res;
    }
};
````

### Solution 4: 递归

这种解法要用到 if 判断，所以不满足要求

````c++
class Solution {
public:
    int sumNums(int n) {
        if (n == 1) {
            return 1;
        }

        n += sumNums(n - 1);
        return n;
    }
};
````

### Solution :

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/qiu-12n-lcof/solution/mian-shi-ti-64-qiu-1-2-nluo-ji-fu-duan-lu-qing-xi-/



````c++
class Solution {
public:
    Solution() : res_(0) {}

    int sumNums(int n) {
        bool x = n > 0 && sumNums(n - 1);  // 用这个表达式换掉 if 条件判断
        res_ += n;
        return res_;
    }

 private:
    int res_;
};
````

