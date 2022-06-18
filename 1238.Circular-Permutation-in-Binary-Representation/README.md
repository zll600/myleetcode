# [1238. Circular Permutation in Binary Representation](https://leetcode.cn/problems/circular-permutation-in-binary-representation/)

## 题目

Given 2 integers `n` and `start`. Your task is return **any** permutation `p` of `(0,1,2.....,2^n -1) `such that :

- `p[0] = start`
- `p[i]` and `p[i+1]` differ by only one bit in their binary representation.
- `p[0]` and `p[2^n -1]` must also differ by only one bit in their binary representation.

 

**Example 1:**

```
Input: n = 2, start = 3
Output: [3,2,0,1]
Explanation: The binary representation of the permutation is (11,10,00,01). 
All the adjacent element differ by one bit. Another valid permutation is [3,1,0,2]
```

**Example 2:**

```
Input: n = 3, start = 2
Output: [2,6,7,5,4,0,1,3]
Explanation: The binary representation of the permutation is (010,110,111,101,100,000,001,011).
```

 

**Constraints:**

- `1 <= n <= 16`
- `0 <= start < 2 ^ n`



## 题目大意

给你两个整数 n 和 start。你的任务是返回任意 (0,1,2,,...,2^n-1) 的排列 p，并且满足：

    p[0] = start
    p[i] 和 p[i+1] 的二进制表示形式只有一位不同
    p[0] 和 p[2^n -1] 的二进制表示形式也只有一位不同



## 解题思路



### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/circular-permutation-in-binary-representation/solution/di-gui-yi-huo-jie-fa-jue-dui-jing-bao-by-pppp-9/)

难点在于找出对应的状态转移，

题目中给出的下标范围就是 `[0, 2 ^ n - 1]`，那么不难想到这道题目的递归树就有 `n` 层，

````c++
class Solution {
public:
    vector<int> circularPermutation(int n, int start) {
        res_.push_back(start);
        val_ = start;
        cout << val_ << " -- ";
        DFS(n - 1);
        return res_;
    }
    
 private:
    vector<int> res_;
    int val_;
    
    void DFS(int n) {
        if (n == 0) {
            cout << (val_ ^ 1) << endl;
            res_.push_back(val_ ^= 1);
            return;
        }
        
        DFS(n - 1);
        cout << (val_ ^ (1 << n)) << " -- ";
        res_.push_back(val_ ^= (1 << n));
        DFS(n - 1);
    }
};
````

