# [667. Beautiful Arrangement II](https://leetcode.com/problems/beautiful-arrangement-ii/)

## 题目

Given two integers `n` and `k`, construct a list `answer` that contains `n` different positive integers ranging from `1` to `n` and obeys the following requirement:

- Suppose this list is `answer = [a1, a2, a3, ... , an]`, then the list `[|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|]` has exactly `k` distinct integers.

Return *the list* `answer`. If there multiple valid answers, return **any of them**.

 

**Example 1:**

```
Input: n = 3, k = 1
Output: [1,2,3]
Explanation: The [1,2,3] has three different positive integers ranging from 1 to 3, and the [1,1] has exactly 1 distinct integer: 1
```

**Example 2:**

```
Input: n = 3, k = 2
Output: [1,3,2]
Explanation: The [1,3,2] has three different positive integers ranging from 1 to 3, and the [2,1] has exactly 2 distinct integers: 1 and 2.
```

 

**Constraints:**

- `1 <= k < n <= 104`

## 题目大意

给定两个整数 n 和 k，你需要实现一个数组，这个数组包含从 1 到 n 的 n 个不同整数，同时满足以下条件：

- 如果这个数组是 `[a1, a2, a3, … , an]` ，那么数组 `[|a1 - a2|, |a2 - a3|, |a3 - a4|, … , |an-1 - an|]` 中应该有且仅有 `k` 个不同整数；.
- 如果存在多种答案，你只需实现并返回其中任意一种.

## 解题思路

可以将整个区间分为两部分来考虑

### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0667.Beautiful-Arrangement-II/)

如果要使得 `k` 最大，此时为 n - 1, 则将整个范围对半交替插入 `[1, n - 1, 2, n - 2, 3...]`，如果要使 k 最小，此时为 1, 则将整个范围按照升序输出 `[1, 2, 3, ...]`

若要使得 `1 < k < n - 1`，则我们可以将整个区间范围划分为两部分，前一部分按照 k 最小来处理，后一部分按照 k 最大来处理，

即 `[1, 2, 3, ..., n - k - 1]` 形成 1 中差值，`[n - k, n - 1, n - k + 1, ...]`[ 产生 k - 1 种

````c++
class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<int> res;
        // 利用前 n - k - 1 个数，形成一种差值
        for (int i = 0; i < n - k - 1; ++i) {
            res.push_back(i + 1);
        }
        
        // 利用后面的 k + 1 个数来形成 k + 1 中差值
        // 这里利用交替插入
        for (int i = n - k; i < n - k + (k + 1) / 2; ++i) {
            res.push_back(i);
            // 2 * n - k - i = n - i + n - k
            res.push_back(2 * n - k - i);
        }
        
        // 如果是奇数，刚好对半插，
        // 如果是偶数，还需要多插一个
        if (k % 2 == 0) {
            res.push_back(n - k + (k + 1) / 2);
        }
        
        return res;
    }
};
````
````c++

````
