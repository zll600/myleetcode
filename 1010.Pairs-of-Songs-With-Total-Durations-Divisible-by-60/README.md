# [1010. Pairs of Songs With Total Durations Divisible by 60](https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/)

## 题目

You are given a list of songs where the `ith` song has a duration of `time[i]` seconds.

Return *the number of pairs of songs for which their total duration in seconds is divisible by* `60`. Formally, we want the number of indices `i`, `j` such that `i < j` with `(time[i] + time[j]) % 60 == 0`.

 

**Example 1:**

```
Input: time = [30,20,150,100,40]
Output: 3
Explanation: Three pairs have a total duration divisible by 60:
(time[0] = 30, time[2] = 150): total duration 180
(time[1] = 20, time[3] = 100): total duration 120
(time[1] = 20, time[4] = 40): total duration 60
```

**Example 2:**

```
Input: time = [60,60,60]
Output: 3
Explanation: All three pairs have a total duration of 120, which is divisible by 60.
```

 

**Constraints:**

- `1 <= time.length <= 6 * 104`
- `1 <= time[i] <= 500`

## 题目大意

在歌曲列表中，第 `i` 首歌曲的持续时间为 `time[i]` 秒。

返回其总持续时间（以秒为单位）可被 `60` 整除的歌曲对的数量

形式上，我们希望下标数字 i 和 j 满足  i < j 且有 (time[i] + time[j]) % 60 == 0

## 解题思路


### Solution 1: Brute force(TLE)

暴力解法最终会超时

````c++
class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int res = 0;
        
        const int len = time.size();
        for (int i = 0; i < len - 1; ++i) {
            for (int j = i + 1; j < len; ++j) {
                if ((time[i] + time[j]) % 60 == 0) {
                    ++res;
                }
            }
        }
        
        return res;
    }
};
````
