# [1736. Latest Time by Replacing Hidden Digits](https://leetcode.com/problems/latest-time-by-replacing-hidden-digits/)

## 题目

You are given a string `time` in the form of `hh:mm`, where some of the digits in the string are hidden (represented by `?`).

The valid times are those inclusively between `00:00` and `23:59`.

Return *the latest valid time you can get from* `time` *by replacing the hidden* *digits*.

 

**Example 1:**

```
Input: time = "2?:?0"
Output: "23:50"
Explanation: The latest hour beginning with the digit '2' is 23 and the latest minute ending with the digit '0' is 50.
```

**Example 2:**

```
Input: time = "0?:3?"
Output: "09:39"
```

**Example 3:**

```
Input: time = "1?:22"
Output: "19:22"
```

 

**Constraints:**

- `time` is in the format `hh:mm`.
- It is guaranteed that you can produce a valid time from the given string.

## 题目大意

给定一个按照搁置`hh:mm`的字符串，字符串中的数字有一些是隐藏的（用 ? 代表），

有效的时间是在 `00:00` 到 `23:59` 内

返回你可以通过替换 time 中的隐藏的字符串得到的最晚有效时间

## 解题思路

* 这道题使用可以利用贪心的想法来求解，每一位尽量取最大值，
* 这里需要注意的第一位和第二位会互相影响，可以现确定任意一个，再确定另一个

## 代码

`````c++
class Solution {
public:
    string maximumTime(string time) {
        if (time[3] == '?') {   // 第三个位置最大值是 '5'
            time[3] = '5';
        }
        if (time[4] == '?') {   // 第四个位置最大值是'9'
            time[4] = '9';
        }
        
        if (time[0] == '?') {   // 第一个位置的值受第二个位置上的值影响
            if (time[1] > '3' && time[1] <= '9') {  // 如果第二个位置在 '4'到'9'之间，
                time[0] = '1';
            } else {    // 如果第二个位置小于 '4'或者是 '?'
                time[0] = '2';
            }
        }
        
        if (time[1] == '?') {   // 不知道第一个的值，默认给到最大
            time[1] = '9';
        }
        
        if (time[0] == '2' && time[1] == '9') { // 这里明显不合法，需要修正
            time[1] = '3';
        }
        
        return time;
    }
};
`````

