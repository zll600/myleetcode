# [551. Student Attendance Record I](https://leetcode.com/problems/student-attendance-record-i/)

## 题目

You are given a string `s` representing an attendance record for a student where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:

- `'A'`: Absent.
- `'L'`: Late.
- `'P'`: Present.

The student is eligible for an attendance award if they meet **both** of the following criteria:

- The student was absent (`'A'`) for **strictly** fewer than 2 days **total**.
- The student was **never** late (`'L'`) for 3 or more **consecutive** days.

Return `true` *if the student is eligible for an attendance award, or* `false` *otherwise*.

 

**Example 1:**

```
Input: s = "PPALLP"
Output: true
Explanation: The student has fewer than 2 absences and was never late 3 or more consecutive days.
```

**Example 2:**

```
Input: s = "PPALLL"
Output: false
Explanation: The student was late 3 consecutive days in the last 3 days, so is not eligible for the award.
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `s[i]` is either `'A'`, `'L'`, or `'P'`.

## 题目大意

给定一饿字符串 s 表示一个学生的出勤记录，其中每个字符表示这个学士是缺课、迟到、到场，这条记录仅仅由下面这三个字符组成：

* 'A'：Absent，缺勤
* 'L'：Late，迟到
* 'P'：Present，到场

如果学生能够**同时**满足下面两个条件，则可以获得出勤奖励：

* 按 总出勤 计，学生缺勤（'A'）严格 少于两天。
* 学生 不会 存在 连续 3 天或 连续 3 天以上的迟到（'L'）记录。

如果学生可以得到奖励返回true，否则返回 false

## 解题思路

这道题目可以转化为：

* 统计字符串中 'A'的数目
* 统计连续的 ‘L’ 的数目,

上面二者任意一个如果无法得到满足直接返回 false

### 解法1

在循环的过程中进行遍历

``````c++
class Solution {
public:
    bool checkRecord(string s) {
        int cnt_a = 0;
        int cnt_l = 0;
        
        bool consecutive = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'A') {  // 计算 A 的数目
                cnt_a++;
                if (cnt_a >= 2) {  // 累计不合理直接返回
                    return false;
                }
            } else if (s[i] == 'L') {  // 计算 L 的数目
                if (cnt_l > 0 && s[i - 1] == 'L') {
                    cnt_l++;
                    if (cnt_l >= 3) {  // 连续不合理直接返回
                        return false;
                    }
                } else {
                    cnt_l = 1;
                }
            } else {
                cnt_l = 0;
            }
        }
        
        return true;
    }
};
``````

