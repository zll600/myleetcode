# [1507. Reformat Date](https://leetcode-cn.com/problems/reformat-date/)

## 题目

Given a `date` string in the form `Day Month Year`, where:

- `Day` is in the set `{"1st", "2nd", "3rd", "4th", ..., "30th", "31st"}`.
- `Month` is in the set `{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}`.
- `Year` is in the range `[1900, 2100]`.

Convert the date string to the format `YYYY-MM-DD`, where:

- `YYYY` denotes the 4 digit year.
- `MM` denotes the 2 digit month.
- `DD` denotes the 2 digit day.

 

**Example 1:**

```
Input: date = "20th Oct 2052"
Output: "2052-10-20"
```

**Example 2:**

```
Input: date = "6th Jun 1933"
Output: "1933-06-06"
```

**Example 3:**

```
Input: date = "26th May 1960"
Output: "1960-05-26"
```

 

**Constraints:**

- The given dates are guaranteed to be valid, so no error handling is necessary.

## 题目大意

给定一个日期字符串 `date` 按照 `Day Month Year`，其中：

- `Day` 在集合 `{"1st", "2nd", "3rd", ...."30th", "31th"}`
- `Month` 在集合 `{"Jan", "Feb", "Mar", ..., "Apr"}`
- `Year` 在集合 `{1900, 2100}`

将日期字符串转化为 `YYYY-MM-DD` 格式：

- `YYYY` 表示4位的年，
- `MM` 表示两位数的月
- `DD` 表示2 位的天
## 解题思路

这道题目我觉得本身数据量并不大，所以完全可以考虑提前构造好查询的映射，然后直接查就可以了

### Solution 1:



````c++
class Solution {
public:
    string reformatDate(string date) {
        vector<string> data;
        Split(date, data, " ");

        // 注意因为这里的 unordered_map 均为 const 所以这里只能使用 at 来访问其中的元素
        return data[2] + "-" + months_.at(data[1]) + "-" + days_.at(data[0]);
    }

 private:
    const unordered_map<string, string> days_ = {
        { "1st", "01" },
        { "2nd", "02" },
        { "3rd", "03" },
        { "4th", "04" },
        { "5th", "05" },
        { "6th", "06" },
        { "7th", "07" },
        { "8th", "08" },
        { "9th", "09" },
        { "10th", "10" },
        { "11th", "11" },
        { "12th", "12" },
        { "13th", "13" },
        { "14th", "14" },
        { "15th", "15" },
        { "16th", "16" },
        { "17th", "17" },
        { "18th", "18" },
        { "19th", "19" },
        { "20th", "20" },
        { "21st", "21" },
        { "22nd", "22" },
        { "23rd", "23" },
        { "24th", "24" },
        { "25th", "25" },
        { "26th", "26" },
        { "27th", "27" },
        { "28th", "28" },
        { "29th", "29" },
        { "30th", "30" },
        { "31st", "31"}
    };

    const unordered_map<string, string> months_ = {
        { "Jan", "01" },
        { "Feb", "02" },
        { "Mar", "03" },
        { "Apr", "04" },
        { "May", "05" },
        { "Jun", "06" },
        { "Jul", "07" },
        { "Aug", "08" },
        { "Sep", "09" },
        { "Oct", "10" },
        { "Nov", "11" },
        { "Dec", "12" }
    };

    void Split(const string& str, vector<string>& tokens,
              const string delim = " ") {
        tokens.clear();

        auto start = str.find_first_not_of(delim, 0);
        auto pos = str.find_first_of(delim, start);
        while (start != string::npos || pos != string::npos) {
            tokens.emplace_back(std::move(str.substr(start, pos - start)));
            start = str.find_first_not_of(delim, pos);
            pos = str.find_first_of(delim, start);
        }
    }
};
````
