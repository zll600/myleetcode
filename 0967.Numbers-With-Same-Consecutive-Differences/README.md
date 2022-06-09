# [967. Numbers With Same Consecutive Differences](https://leetcode.cn/problems/numbers-with-same-consecutive-differences/)

## 题目

Return all **non-negative** integers of length `n` such that the absolute difference between every two consecutive digits is `k`.

Note that **every** number in the answer **must not** have leading zeros. For example, `01` has one leading zero and is invalid.

You may return the answer in **any order**.

 

**Example 1:**

```
Input: n = 3, k = 7
Output: [181,292,707,818,929]
Explanation: Note that 070 is not a valid number, because it has leading zeroes.
```

**Example 2:**

```
Input: n = 2, k = 1
Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
```

 

**Constraints:**

- `2 <= n <= 9`
- `0 <= k <= 9`

## 题目大意

返回所有长度为 `n` 且满足其每两个连续位上的数字之间的差的绝对值为 `k` 的 非负整数

请注意，除了 数字 `0` 本身之外，答案中的每个数字都 *不能* 有前导零。例如，`01` 有一个前导零，所以是无效的；但 0 是有效的

你可以按 任何顺序 返回答案

## 解题思路

### Solution 1: DFS

这道题目 dfs 中的状态就是 idx 和 cur，

递归过程中的状态转移就是 +k 和 -k 两种可能，这里特别注意 k = 0的情况需要特殊处理

````c++
class Solution {
public:
    vector<int> numsSameConsecDiff(int n, int k) {
        vector<int> res;
        for (int i = 1; i <= 9; ++i) {
            DFS(1, i, n, k, res);
        }
        return res;
    }
    
 private:
    // 
    void DFS(int idx, int cur, int n, int k, vector<int>& res) {
        if (idx == n) {
            res.push_back(cur);
            return;
        }
        
        int last = cur % 10;
        if (last + k >= 0 && last + k <= 9) {
            DFS(idx + 1, cur * 10 + last + k, n, k, res);
        }
        
        // 如果 k == 0，那么就 + k 和 -k 的结果是一样的
        if (k == 0) {
            return;
        }
        
        if (last - k >= 0 && last - k <= 9) {
            DFS(idx + 1, cur * 10 + last - k, n, k, res);
        }
    }
};
````
