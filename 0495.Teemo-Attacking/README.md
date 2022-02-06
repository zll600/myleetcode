# [495. Teemo Attacking](https://leetcode.com/problems/teemo-attacking/)

## 题目

Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for a exactly `duration` seconds. More formally, an attack at second `t` will mean Ashe is poisoned during the **inclusive** time interval `[t, t + duration - 1]`. If Teemo attacks again **before** the poison effect ends, the timer for it is **reset**, and the poison effect will end `duration` seconds after the new attack.

You are given a **non-decreasing** integer array `timeSeries`, where `timeSeries[i]` denotes that Teemo attacks Ashe at second `timeSeries[i]`, and an integer `duration`.

Return *the **total** number of seconds that Ashe is poisoned*.

 

**Example 1:**

```
Input: timeSeries = [1,4], duration = 2
Output: 4
Explanation: Teemo's attacks on Ashe go as follows:
- At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
- At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.
```

**Example 2:**

```
Input: timeSeries = [1,2], duration = 2
Output: 3
Explanation: Teemo's attacks on Ashe go as follows:
- At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
- At second 2 however, Teemo attacks again and resets the poison timer. Ashe is poisoned for seconds 2 and 3.
Ashe is poisoned for seconds 1, 2, and 3, which is 3 seconds in total.
```

 

**Constraints:**

- `1 <= timeSeries.length <= 104`
- `0 <= timeSeries[i], duration <= 107`
- `timeSeries` is sorted in **non-decreasing** order.

## 题目大意

在《英雄联盟》的世界中，有一个叫 “提莫” 的英雄。他的攻击可以让敌方英雄艾希（编者注：寒冰射手）进入中毒状态
当提莫攻击艾希，艾希的中毒状态正好持续 duration 秒

正式地讲，提莫在 `t` 发起发起攻击意味着艾希在时间区间 `[t, t + duration - 1]`（含 `t` 和 `t + duration - 1`）处于中毒状态。如果提莫在中毒影响结束 **前** 再次攻击，中毒状态计时器将会 重置 ，在新的攻击之后，中毒影响将会在 `duration` 秒后结束

给你一个 `非递减` 的整数数组 `timeSeries` ，其中 `timeSeries[i]` 表示提莫在 `timeSeries[i]` 秒时对艾希发起攻击，以及一个表示中毒持续时间的整数 `duration` 

返回艾希处于中毒状态的总秒数。

## 解题思路

这道题目其实可以转化为区间合并问题，只不过题目只给了区间的 start，end 需要自己计算，

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0495.Teemo-Attacking/)

### Solution 1:

这里也可以在遍历的时候再计算，可以省去额外的空间占用

````c++
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        const int len = timeSeries.size();
        // 这里利用一个新的数组，提前算好所有当前位置之后中毒的时间
        vector<int> ends(len, 0);
        for (int i = 0; i < len; ++i) {
            ends[i] = timeSeries[i] + duration - 1;
        }
        
        int res = 0;
        for (int i = 1; i < len; ++i) {
            if (timeSeries[i] > ends[i - 1]) {
                // 如果这两个区间不可以合并
                res += duration;
            } else {
                // 如果这两个区间可以合并
                res += timeSeries[i] - timeSeries[i - 1];
            }
        }
        // 最后一个位置需要单独计算
        res += duration;

        return res;
    }
};

````



