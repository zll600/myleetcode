# [420. Strong Password Checker](https://leetcode-cn.com/problems/strong-password-checker/)

## 题目

A password is considered strong if the below conditions are all met:

- It has at least `6` characters and at most `20` characters.
- It contains at least **one lowercase** letter, at least **one uppercase** letter, and at least **one digit**.
- It does not contain three repeating characters in a row (i.e., `"...aaa..."` is weak, but `"...aa...a..."` is strong, assuming other conditions are met).

Given a string `password`, return *the minimum number of steps required to make `password` strong. if `password` is already strong, return `0`.*

In one step, you can:

- Insert one character to `password`,
- Delete one character from `password`, or
- Replace one character of `password` with another character.

 

**Example 1:**

```
Input: password = "a"
Output: 5
```

**Example 2:**

```
Input: password = "aA1"
Output: 3
```

**Example 3:**

```
Input: password = "1337C0d3"
Output: 0
```

 

**Constraints:**

- `1 <= password.length <= 50`
- `password` consists of letters, digits, dot `'.'` or exclamation mark `'!'`.

## 题目大意

如果一个密码满足下述所有条件，则认为这个密码是强密码：

* 由至少 6 个，至多 20 个字符组成。
* 至少包含 一个小写 字母，一个大写 字母，和 一个数字 。
* 同一字符 不能 连续出现三次 (比如 "`...aaa...`" 是不允许的, 但是 "`...aa...a...`" 如果满足其他条件也可以算是强密码)。

给你一个字符串 `password` ，返回 将 `password` 修改到满足强密码条件需要的最少修改步数。如果 `password` 已经是强密码，则返回 0 。

在一步修改操作中，你可以：

* 插入一个字符到 `password` ，
* 从 `password` 中删除一个字符，或
* 用另一个字符来替换 `password` 中的某个字符。



## 解题思路


这道题目难在需要很多分类讨论，分析清楚每一种情况

- 需要满足 有数字、有小写、有大写
- 长度小于 6 ，
- 长度大于等于 6，小于等于 20
- 长度大于 20，删除时，怎样减少后面修改的次数

### Solution 1:

这种解法可以参考这篇 [题解](https://leetcode-cn.com/problems/strong-password-checker/solution/shi-jian-onkong-jian-o10mssi-lu-by-jriver/)

这里比较难处理的就是：如果长度大于 20，那么删除时需要尽可能的减少后面修改的次数

````c++
class Solution {
public:
    int strongPasswordChecker(string password) {
        // 统计缺失的类型，作为下界
        bool has_digit = false, has_lower = false, has_upper = false;
        const int len = password.size(); // 长度

        vector<int> cnt(3, 0); // 统计不同的连续的字符
        int modify = 0; // 统计替换的次数
        for (int i = 0; i < len; ) {
            char c = password[i];

            /*
            if (isdigit(c)) {
                has_digit = true;
            } else if (islower(c)) {
                has_lower = true;
            } else if (isupper(c)) {
                has_upper = true;
            }*/

            // 这里使用 或 运算
            has_digit = has_digit || isdigit(c);
            has_lower = has_lower || islower(c);
            has_upper = has_upper || isupper(c);

            // 这里招到第一个不连续的字符
            int pos = i;
            while (pos < len && password[pos] == c) {
                ++pos;
            }

            const int repeat = pos - i; // 重复的次数
            if (repeat >= 3) {
                modify += repeat / 3;
                ++cnt[repeat % 3];
            }

            i = pos; // 从新的字符重新开始
        }

        // 缺失的类型
        int missing_types = !has_digit + !has_lower + !has_upper;

        if (len < 6) {
            // 如果长度小于 6
            return max(6 - len, missing_types);
        }
        if (len <= 20) {
            // 如果长度小于等于 20
            return max(modify, missing_types);
        }

        // 需要删除 多余的字符
        int remove = len - 20;

        if (remove < cnt[0]) {
            // 3n 形式的字符，只需要修改一次
            return max(modify - remove, missing_types) + len - 20;
        }

        // 在删除的时候，解决连续的 3n
        remove -= cnt[0];
        modify -= cnt[0];

        if (remove < cnt[1] * 2) {
            return max(modify - remove / 2, missing_types) + len - 20;
        }

        // 在连续的时候解决 3n+1 的问题
        remove -= cnt[1] * 2;
        modify -= cnt[1];

        return max(modify - remove / 3, missing_types) + len - 20;
    }
};
````
