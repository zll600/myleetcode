# [367. Valid Perfect Square](https://leetcode.com/problems/valid-perfect-square/)
## 题目

Given a **positive** integer *num*, write a function which returns True if *num* is a perfect square else False.

**Follow up:** **Do not** use any built-in library function such as `sqrt`.

 

**Example 1:**

```
Input: num = 16
Output: true
```

**Example 2:**

```
Input: num = 14
Output: false
```

 

**Constraints:**

- `1 <= num <= 2^31 - 1`

## 题目大意

判断一个正整数是不是完全平方数，

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/valid-perfect-square/solution/gong-shui-san-xie-yi-ti-shuang-jie-er-fe-g5el/

这道题目可以理解为有序集合中进行查找，所以可以利用二分查找

### Solution 1: Binary Search

````c++
class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num == 1) {
            return true;
        }
        
        // 这里我们搜索的范围是：[1， num / 2]
        int lo = 1;
        int hi = num / 2;
        
        // 使用二分搜索来做
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            // cout << lo << "---" << mid << "---" << hi << endl;
            long cur =1L *  mid * mid;
            
            if (cur == num) {
                return true;
            } else if (cur > num) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return false;
    }
};
````

