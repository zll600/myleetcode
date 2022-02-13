# [440. K-th Smallest in Lexicographical Order](https://leetcode-cn.com/problems/k-th-smallest-in-lexicographical-order/)

## 题目

Given two integers `n` and `k`, return *the* `kth` *lexicographically smallest integer in the range* `[1, n]`.

 

**Example 1:**

```
Input: n = 13, k = 2
Output: 10
Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
```

**Example 2:**

```
Input: n = 1, k = 1
Output: 1
```

 

**Constraints:**

- `1 <= k <= n <= 109`

## 题目大意

给定两个整数 `n` 和 `k`， 返回 按照字典序在 `[1, n]` 中第 k 小的整数

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/k-th-smallest-in-lexicographical-order/solution/ben-ti-shi-shang-zui-wan-zheng-ju-ti-de-shou-mo-sh/)


### Solution 1:

这里可以讲字典序，抽象为一棵字典树，只不过，这棵树的子节点是 `[0, 9]`，而对于这棵树的前序遍历就是要求的字典序的的结果，题目要求的是按照字典序来求的第 k 个树，

那么我们需要先锁定一个前缀，然后在这个前缀中去寻找答案，



````c++
class Solution {
public:
    int findKthNumber(int n, int k) {
        int cur = 1; // 当前的位置
        int prefix = 1; // 当前的前缀
        
        while (cur < k) {
            // 得到当前前缀下的所有数字之和
            int cnt = GetCount(prefix, n);
            if (cur + cnt > k) {
                // 如果 k 在当前前缀下，向下一层转移
                prefix *= 10;
                // 移向字典序的下一个
                ++cur;
            } else {
                // 向下一个前缀转移
                ++prefix;
                // 偏移整个前缀
                cur += cnt;
            }
        }
        
        return prefix;
    }
    
 private:
    // 计算当前 前缀下有多少数字
    int GetCount(int prefix, int bound) {
        long cur = prefix; // 当前前缀
        long next = prefix + 1; // 下一个前缀
        
        int count = 0; // 计数
        while (cur <= bound) {
            // count += next - cur;
            // 这里一定不能超过上界
            count += min(1L + bound, next) - cur;
            cur *= 10;
            next *= 10;
        }
        
        return count;
    }
};
````
