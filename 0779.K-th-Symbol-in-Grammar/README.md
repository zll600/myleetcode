# [779. K-th Symbol in Grammar](https://leetcode.cn/problems/k-th-symbol-in-grammar/)

## 题目

We build a table of `n` rows (**1-indexed**). We start by writing `0` in the `1st` row. Now in every subsequent row, we look at the previous row and replace each occurrence of `0` with `01`, and each occurrence of `1` with `10`.

- For example, for `n = 3`, the `1st` row is `0`, the `2nd` row is `01`, and the `3rd` row is `0110`.

Given two integer `n` and `k`, return the `kth` (**1-indexed**) symbol in the `nth` row of a table of `n` rows.

 

**Example 1:**

```
Input: n = 1, k = 1
Output: 0
Explanation: row 1: 0
```

**Example 2:**

```
Input: n = 2, k = 1
Output: 0
Explanation: 
row 1: 0
row 2: 01
```

**Example 3:**

```
Input: n = 2, k = 2
Output: 1
Explanation: 
row 1: 0
row 2: 01
```

 

**Constraints:**

- `1 <= n <= 30`
- `1 <= k <= 2n - 1`

## 解题思路

我们构建了一个包含 `n` 行 `( 索引从 `1`  开始 )的表。首先在第一行我们写上一个 `0`。接下来的每一行，将前一行中的 `0` 替换为 `01`，`1` 替换为 `10`

- 例如，对于 `n = 3` ，第 `1` 行是 `0` ，第 `2` 行是 `01` ，第 `3` 行是 `0110`

给定行数 `n` 和序数 `k`，返回第 `n` 行中第 `k` 个字符。（ `k` 从索引 `1` 开始）

## 题目大意

这道题目如果自己动手画一画，还是不难想到可以抽象成为一个 树的形式来做的，然后在树上，就可以想到使用 dfs 来做

### Solution 1: DFS

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/k-th-symbol-in-grammar/solution/zhao-gui-lu-hou-ban-bu-fen-shi-qian-ban-wahnd/)

这里的关键在于发现这样一个规律，k 如果在 第 n 行的前半部分，那么可以 第 n - 1 航查找，这是一个递归的过程，如果 k 在 第 n 行的后半部分，那么在 第 n - 1 行的前半部分查找到之后，需要做一次反转才可以

````c++

class Solution {
public:
    int kthGrammar(int n, int k) {
        if (n == 1) {
            return 0;
        }

        // 计算第 n 行的长度
        int len = pow(2, (n - 1));
        // 如果 k 在后半部分
        if (k > len / 2) {
            // 在前半部分找，然后反转
            int val = kthGrammar(n - 1, k - len / 2);
            return val == 0 ? 1 : 0;
        }
        // 直接在前半部分找，找到就是答案
        return kthGrammar(n - 1, k);
    }
};
````

