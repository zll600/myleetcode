# [949. Largest Time for Given Digits](https://leetcode.com/problems/largest-time-for-given-digits/)

## 题目

Given an array `arr` of 4 digits, find the latest 24-hour time that can be made using each digit **exactly once**.

24-hour times are formatted as `"HH:MM"`, where `HH` is between `00` and `23`, and `MM` is between `00` and `59`. The earliest 24-hour time is `00:00`, and the latest is `23:59`.

Return *the latest 24-hour time in `"HH:MM"` format*. If no valid time can be made, return an empty string.

 

**Example 1:**

```
Input: arr = [1,2,3,4]
Output: "23:41"
Explanation: The valid 24-hour times are "12:34", "12:43", "13:24", "13:42", "14:23", "14:32", "21:34", "21:43", "23:14", and "23:41". Of these times, "23:41" is the latest.
```

**Example 2:**

```
Input: arr = [5,5,5,5]
Output: ""
Explanation: There are no valid 24-hour times as "55:55" is not valid.
```

 

**Constraints:**

- `arr.length == 4`
- `0 <= arr[i] <= 9`

## 

给定一个由 `4` 位数字组成的数组，返回可以设置的符合 `24` 小时制的最大时间

最小的 `24` 小时制时间是 `00:00`，而最大的是 `23:59`。从 `00:00` （午夜）开始算起，过得越久，时间越大

以长度为 `5` 的字符串返回答案。如果不能确定有效时间，则返回空字符串

## 解题思路



### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0949.Largest-Time-for-Given-Digits/)

这里暴力枚举所有的可能，然后判断是否合法，之后再用来更新结果

````go
func largestTimeFromDigits(arr []int) string {
    flag, res := false, 0
    for i := 0; i < 4; i++ {
        for j := 0; j < 4; j++ {
            if i == j {
                continue
            }

            for m := 0; m < 4; m++ {
                if m == i || m == j {
                    continue
                }

                n := 6 - i - j - m

                hour := arr[i] * 10 + arr[j]
                min := arr[m] * 10 + arr[n]

                if hour < 24 && min < 60 {
                    if hour * 60 + min >= res {
                        res = hour *  60 + min
                        flag = true
                    }
                }
            }
        }
    }

    if !flag {
        return ""
    }

    return fmt.Sprintf("%02d:%02d", res / 60, res % 60)
}
````
