# [1154. Day of the Year](https://leetcode.com/problems/day-of-the-year/)

Given a string `date` representing a [Gregorian calendar](https://en.wikipedia.org/wiki/Gregorian_calendar) date formatted as `YYYY-MM-DD`, return *the day number of the year*.

 

**Example 1:**

```
Input: date = "2019-01-09"
Output: 9
Explanation: Given date is the 9th day of the year in 2019.
```

**Example 2:**

```
Input: date = "2019-02-10"
Output: 41
```

 

**Constraints:**

- `date.length == 10`
- `date[4] == date[7] == '-'`, and all other `date[i]`'s are digits
- `date` represents a calendar date between Jan 1st, 1900 and Dec 31th, 2019.

## 题目大意

给定一个字符串 `date` 按照格式 `YYYY-MM-DD` 的日期，返回这一年的天数，

## 解题思路

这道题目我们是可以通过前缀和打表来解决的，本身数据量也不是很大

### Solution 1: PrefixSum


````c++
class Solution {
public:
    int dayOfYear(string date) {
        // 处理年分
        auto first = date.find_first_of("-", 0);
        int year = stoi(date.substr(0, first));
        // 处理月份
        auto second = date.find_first_of("-", first + 1);
        int month = stoi(date.substr(first + 1, second - first - 1));
        int day = stoi(date.substr(second + 1));

        int total = prefix_sum_[month - 1] + day;
        if (IsSpecial(year) && month > 2) {
            ++total;
        }

        return total;
    }

 private:
    // 每个月份的天数
    const vector<int> nums_ = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // 前缀和用来加速求解
    const vector<int> prefix_sum_ = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

    // 判断是否是闰年
    bool IsSpecial(int year) {
        // 能被 4 整除但不能被 400 整除
        if (year % 4 == 0 && year % 100 != 0) {
            return true;
        }
        // 能被 400 整除
        if (year % 400 == 0) {
            return true;
        }

        return false;
    }
};
````
