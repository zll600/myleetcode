# [539. Minimum Time Difference](https://leetcode-cn.com/problems/minimum-time-difference/)

## 题目

Given a list of 24-hour clock time points in **"HH:MM"** format, return *the minimum **minutes** difference between any two time-points in the list*.

 

**Example 1:**

```
Input: timePoints = ["23:59","00:00"]
Output: 1
```

**Example 2:**

```
Input: timePoints = ["00:00","23:59","00:00"]
Output: 0
```

 

**Constraints:**

- `2 <= timePoints <= 2 * 104`
- `timePoints[i]` is in the format **"HH:MM"**.

## 题目大意

按照 "HH:MM"的格式给出一组时间，按照分钟数返回列表中最小时间差

## 解题思路

这道题目的难点在于，时间是循环的，即如果用数组表示，首尾的处理是难点

### Solution1:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/minimum-time-difference/solution/539-cjian-dan-yi-dong-zhuan-huan-pai-xu-pwuib/

其实并没有想象的那么难，建议多懂脑子吧（给我自己说的）

````c++
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        const int size = timePoints.size();
        vector<int> points;
        // 将所有的时间转化为分钟数
        for (int i = 0; i < size; ++i) {
            int time = ((timePoints[i][0] - '0') * 10 + (timePoints[i][1] - '0')) * 60
                       + (timePoints[i][3] - '0') * 10 + timePoints[i][4] - '0';
            points.push_back(time);
        }
        
        // 排序
        sort(points.begin(), points.end());
        int res = INT_MAX;  // 结果
        // 两两做差更新结果
        for (int i = 1; i < size; ++i) {
            res = min(res, points[i] - points[i - 1]);
        }
        // 最后还需要将第一项和最后一项做比较
        res = min(res, 24 * 60 + points.front() - points.back());
        
        return res;
    }
};
````

