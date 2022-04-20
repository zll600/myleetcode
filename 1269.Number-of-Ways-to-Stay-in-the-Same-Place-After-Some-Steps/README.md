# [1269. Number of Ways to Stay in the Same Place After Some Steps](https://leetcode-cn.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/)

You have a pointer at index `0` in an array of size `arrLen`. At each step, you can move 1 position to the left, 1 position to the  right in the array, or stay in the same place (The pointer should not be placed outside the array at any time).

Given two integers `steps` and `arrLen`, return the number of ways such that your pointer still at index `0` after **exactly** `steps` steps. Since the answer may be too large, return it **modulo** `109 + 7`.

 

**Example 1:**

```
Input: steps = 3, arrLen = 2
Output: 4
Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
Right, Left, Stay
Stay, Right, Left
Right, Stay, Left
Stay, Stay, Stay
```

**Example 2:**

```
Input: steps = 2, arrLen = 4
Output: 2
Explanation: There are 2 differents ways to stay at index 0 after 2 steps
Right, Left
Stay, Stay
```

**Example 3:**

```
Input: steps = 4, arrLen = 2
Output: 8
```

 

**Constraints:**

- `1 <= steps <= 500`
- `1 <= arrLen <= 106`

## 题目大意

有一个长度为 `arrLen` 的数组，开始有一个指针在索引 `0` 处。

每一步操作中，你可以将指针 *向左或向右移动 1 步，或者停在原地（指针不能被移动到数组范围外）*

给你两个整数 `steps` 和 `arrLen` ，请你计算并返回：在恰好执行 `steps` 次操作以后，指针仍然指向索引 `0` 处的方案数。

由于答案可能会很大，请返回方案数 模 10^9 + 7 后的结果。

## 解题思路

这道题目要求出所有可能的方法，所以可以想到 DFS 来做，另外这里的子问题还很比较明显的，所以也可以考虑使用 dp 来做

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/solution/shu-ju-jie-gou-he-suan-fa-di-gui-ge-dong-glyo/)

### Solution 1: DFS

这种解法因为存在较多的重复计算会导致超时

````c++
class Solution {
public:
    int numWays(int steps, int arr_len) {
        return DFS(steps, arr_len, 0);
    }

 private:
    const int mod_ = 1e9 + 7;

    int DFS(int steps, int arr_len, int pos) {
        if (steps == 0) {
            return pos == 0 ? 1 : 0;
        }

        long res = 0;

        // left
        if (pos > 0) {
            res = (res + DFS(steps - 1, arr_len, pos - 1)) % mod_;
        }
        // right
        if (pos < arr_len - 1) {
            res = (res + DFS(steps - 1, arr_len, pos + 1)) % mod_;
        }
        // stay
        res = (res + DFS(steps - 1, arr_len, pos)) % mod_;

        return res;
    }
};
````

### Solution 2: DFS + Cache

````c++
class Solution {
public:
    int numWays(int steps, int arr_len) {
        return DFS(steps, arr_len, 0);
    }

 private:
    const int mod_ = 1e9 + 7;
    // 缓存
    unordered_map<string, int> cache_;

    int DFS(int steps, int arr_len, int pos) {
        if (steps == 0) {
            return pos == 0 ? 1 : 0;
        }

        string key = to_string(steps) + "+" + to_string(pos);
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            return it->second;
        }

        long res = 0;

        // left
        if (pos > 0) {
            res = (res + DFS(steps - 1, arr_len, pos - 1)) % mod_;
        }
        // right
        if (pos < arr_len - 1) {
            res = (res + DFS(steps - 1, arr_len, pos + 1)) % mod_;
        }
        // stay
        res = (res + DFS(steps - 1, arr_len, pos)) % mod_;

        cache_[key] = res;
        return res;
    }
};
```

### Solutino 3: DP

````c++
class Solution {
public:
    int numWays(int steps, int arr_len) {
        vector<vector<int>> dp(steps + 1, vector<int>(arr_len + 1));
        dp[0][0] = 0;
        dp[1][0] = 1;
        dp[1][1] = 1;

        for (int i = 1; i <= steps; ++i) {
            for (int j = 0; j < arr_len; ++j) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod_;
                if (j > 0) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod_;
                }
                if (j < arr_len - 1) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % mod_;
                }
            }
        }

        return dp[steps][0];
    }

 private:
    const int mod_ = 1e9 + 7;
};
```


