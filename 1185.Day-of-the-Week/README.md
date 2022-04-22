# [1185. Day of the Week](https://leetcode.com/problems/day-of-the-week/)

## 题目

Given a date, return the corresponding day of the week for that date.

The input is given as three integers representing the `day`, `month` and `year` respectively.

Return the answer as one of the following values `{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}`.

 

**Example 1:**

```
Input: day = 31, month = 8, year = 2019
Output: "Saturday"
```

**Example 2:**

```
Input: day = 18, month = 7, year = 1999
Output: "Sunday"
```

**Example 3:**

```
Input: day = 15, month = 8, year = 1993
Output: "Sunday"
```

 

**Constraints:**

- The given dates are valid dates between the years `1971` and `2100`.

## 题目大意

给你一个日期，请你设计一个算法来判断它是对应一周中的哪一天。输入为三个整数：`day`、`month` 和 `year`，分别表示日、月、年。

您返回的结果必须是这几个值中的一个 `{“Sunday”, “Monday”, “Tuesday”, “Wednesday”, “Thursday”, “Friday”, “Saturday”}`。

提示：

    给出的日期一定是在 `1971` 到 `2100` 年之间的有效日期。

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/day-of-the-week/solution/dai-ma-jie-de-xiao-bai-javac-jian-dan-ti-egz2/)

这里需要注意的地方有：

- 闰年的情况需要处理
- 找到一个起点，最好选择 1970 年 12 月 31 日
- 还需要避免数组下标越界的情况

### 解题思路


````c++
class Solution {
public:
    string dayOfTheWeek(int day, int month, int year) {
        int sum = 0;
        for (int i = 1971; i < year; ++i) {
            if (IsLeap(i)) {
                sum += 366;
            } else {
                sum += 365;
            }
        }

        for (int i = 0; i < month - 1; ++i) {
            sum += month_days[i];
        }

        if (month > 2 && IsLeap(year)) {
            sum += 1;
        }
        sum += day;

        //  这里对 7 取模
        sum %= 7;
        // 这里可以理解为第 0 天是周四，所以要对应到数组下标中，需要 + 3
        sum += 3;
        // 这里是为了防止数组下标越界
        sum %= 7;
        return week[sum];
    }

 private:
    const vector<string> week = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    const vector<int> month_days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};

    bool IsLeap(int year) {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }
};
`````
