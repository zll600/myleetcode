# [552. Student Attendance Record II](https://leetcode-cn.com/problems/student-attendance-record-ii/)

An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:

- `'A'`: Absent.
- `'L'`: Late.
- `'P'`: Present.

Any student is eligible for an attendance award if they meet **both** of the following criteria:

- The student was absent (`'A'`) for **strictly** fewer than 2 days **total**.
- The student was **never** late (`'L'`) for 3 or more **consecutive** days.

Given an integer `n`, return *the **number** of possible attendance records of length* `n` *that make a student eligible for an attendance award. The answer may be very large, so return it **modulo*** `109 + 7`.

 

**Example 1:**

```
Input: n = 2
Output: 8
Explanation: There are 8 records with length 2 that are eligible for an award:
"PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).
```

**Example 2:**

```
Input: n = 1
Output: 3
```

**Example 3:**

```
Input: n = 10101
Output: 183236316
```

 

**Constraints:**

- `1 <= n <= 105`

## 题目大意

可以用字符串表示一个学生的出勤记录，其中的每个字符用来标记当天的出勤情况（缺勤、迟到、到场）。记录中只含下面三种字符：

- `'A'：Absent`，缺勤
- `'L'：Late`，迟到
- `'P'：Present`，到场

如果学生能够 同时 满足下面两个条件，则可以获得出勤奖励：

- 按 **总出勤** 计，学生缺勤`（'A'）`严格 少于两天。
- 学生 **不会** 存在 **连续 3天或 连续 3 天以上** 的迟到`（'L'）`记录。

给你一个整数  `n` ，表示出勤记录的长度（次数）。请你返回记录长度为 `n` 时，可能获得出勤奖励的记录情况 数量 。答案可能很大，所以返回对 `10^9 + 7` 取余 的结果。

## 解题思路

这道题目有明显的重复子问题和状态转移，所以可以考虑使用 DFS 或者 动态规划

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/student-attendance-record-ii/solution/tong-ge-lai-shua-ti-la-yi-ti-liu-jie-dfs-s5fa/)


### Solution 1: DFS(TLE)

这里的每一次状态转移都考虑不同的三种状态

````c++
class Solution {
 public:
    int checkRecord(int n) {
        return DFS(0, n, 0, 0);
    }

 private:
    const int mod_ = 1e9 + 7;

    int DFS(int day, int n, int absent, int late) {
        // 可以提供一种可行的方案了
        if (day >= n) {
            return 1;
        }

        int ans = 0;
        // Present
        ans = (1L * ans + DFS(day + 1, n, absent, 0)) % mod_;

        // Absent
        if (absent < 1) {
            ans = (1L * ans + DFS(day + 1, n, absent + 1, 0)) % mod_;
        }

        // Late
        if (late < 2) {
            ans = (1L * ans + DFS(day + 1, n, absent, late + 1)) % mod_;
        }

        return ans;
    }

};
````

### Solution 2: DFS + memory(TLE)

这里的话，状态转移涉及到三个纬度
- 第几天
- 总计缺勤的天数
- 连续迟到的天数

````c++
class Solution {
 public:
    int checkRecord(int n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    cache_[i][j][k] = -1;
                }
            }
        }

        return DFS(0, n, 0, 0);
    }

 private:
    const int mod_ = 1e9 + 7;
    unordered_map<int, unordered_map<int, unordered_map<int, int>>> cache_;

    int DFS(int day, int n, int absent, int late) {
        // 可以提供一种可行的方案了
        if (day >= n) {
            return 1;
        }

        if (cache_[day][absent][late] != -1) {
            return cache_[day][absent][late];
        }

        int ans = 0;
        // Present
        ans = (1L * ans + DFS(day + 1, n, absent, 0)) % mod_;

        // Absent
        if (absent < 1) {
            ans = (1L * ans + DFS(day + 1, n, absent + 1, 0)) % mod_;
        }

        // Late
        if (late < 2) {
            ans = (1L * ans + DFS(day + 1, n, absent, late + 1)) % mod_;
        }

        cache_[day][absent][late] = ans;
        return ans;
    }

};
````

### Solution 3: DP

这种解法 C++ 竟然超时了

````c++
class Solution {
 public:
    int checkRecord(int n) {
        // dp[i][j][k] 分别表示 第几天，absent 的天数和 late 的天数
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, 0)));
        
        //  第一天有三种状态
        dp[0][0][0] = 1;
        dp[0][1][0] = 1;
        dp[0][0][1] = 1;
        
        for (int i = 1; i < n; ++i) {
            // 这一天的状态为 Present
            // 枚举之前的 absent
            dp[i][0][0] = (1L * dp[i - 1][0][0] + dp[i - 1][0][1] + dp[i - 1][0][2]) % mod_;
            dp[i][1][0] = (1L * dp[i - 1][1][0] + dp[i - 1][1][1] + dp[i - 1][1][2]) % mod_;
            
            // 这一天 absent
            dp[i][1][0] = (1L * dp[i][1][0] + dp[i - 1][0][0] + dp[i - 1][0][1] + dp[i - 1][0][2]) % mod_;
            
            // 这一天 late
            dp[i][0][1] = dp[i - 1][0][0];
            dp[i][1][1] = dp[i - 1][1][0];
            dp[i][0][2] = dp[i - 1][0][1];
            dp[i][1][2] = dp[i - 1][1][1];
        }
        
        int sum = 0;
        // for_each(dp[n - 1].begin(), dp[n - 1].end(), [&](const vector<int>& nums) {
        //     sum = (1L * sum + accumulate(nums.begin(), nums.end(), 0L)) % mod_;
        // });
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                sum = (sum + dp[n - 1][i][j]) % mod_;
            }
        }
            
        return sum;
    }
    
 private:
    const int mod_ = 1e9 + 7;
};
````

````java
class Solution {

    int MOD = 1000000007;

    public int checkRecord(int n) {
        long[][][] dp = new long[n][2][3];
        // 初始值
        dp[0][0][0] = 1;
        dp[0][1][0] = 1;
        dp[0][0][1] = 1;

        for (int i = 1; i < n; i++) {
            // 本次填入P，分成前一天累计了0个A和1个A两种情况
            dp[i][0][0] = (dp[i - 1][0][0] + dp[i - 1][0][1] + dp[i - 1][0][2]) % MOD;
            dp[i][1][0] = (dp[i - 1][1][0] + dp[i - 1][1][1] + dp[i - 1][1][2]) % MOD;
            // 本次填入A，前一天没有累计A都能转移过来
            // 这行可以与上面一行合并计算，为了方便理解，我们分开，下面会合并
            dp[i][1][0] = (dp[i][1][0] + dp[i - 1][0][0] + dp[i - 1][0][1] + dp[i - 1][0][2]) % MOD;
            // 本次填入L，前一天最多只有一个连续的L，分成四种情况
            dp[i][0][1] = dp[i - 1][0][0];
            dp[i][0][2] = dp[i - 1][0][1];
            dp[i][1][1] = dp[i - 1][1][0];
            dp[i][1][2] = dp[i - 1][1][1];
        }

        // 计算结果，即最后一天的所有状态相加
        long ans = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                ans = (ans + dp[n - 1][i][j]) % MOD;
            }
        }

        return (int) ans;
    }
}
````
