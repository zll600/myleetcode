# [401. Binary Watch](https://leetcode.com/problems/binary-watch/)

## 题目

A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59). Each LED represents a zero or one, with the least significant bit on the right.

- For example, the below binary watch reads `"4:51"`.

![img](https://assets.leetcode.com/uploads/2021/04/08/binarywatch.jpg)

Given an integer `turnedOn` which represents the number of LEDs that are currently on, return *all possible times the watch could represent*. You may return the answer in **any order**.

The hour must not contain a leading zero.

- For example, `"01:00"` is not valid. It should be `"1:00"`.

The minute must be consist of two digits and may contain a leading zero.

- For example, `"10:2"` is not valid. It should be `"10:02"`.

 

**Example 1:**

```
Input: turnedOn = 1
Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
```

**Example 2:**

```
Input: turnedOn = 9
Output: []
```

 

**Constraints:**

- `0 <= turnedOn <= 10`

## 题目大意

一个二分顶部有4 个led 代表小时，底部有 6 个led代表分钟，每个led代表0 或者 1，最低位在右边，给定一个整数表示亮着的led 灯的数目，返回所有的二进制表可能代表的时间，

## 解题思路

这道题目按理来说，应该使用 dfs枚举所有可能，然后选出符合条件的加入到结果集中，

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/binary-watch/solution/di-gui-hui-su-fa-by-jawhiow/

但是因为这道题的计算量其实可以与输入无关，而且比较小，只有 12 x 60，所以可以穷举，这道题我觉得也可以看看霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0401.Binary-Watch/

### Solution 1:穷举

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/binary-watch/solution/cjian-jian-dan-dan-de-ji-xing-dai-ma-jie-jue-wen-t/

````c++
class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> res;
        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j < 60; ++j) {
                if (count(i) + count(j) == turnedOn) {
                    res.push_back(to_string(i) + ":" +
                                  (j < 10 ? "0"+to_string(j) : to_string(j)));
                }
            }
        }
        
        return res;
    }
 private:
    int count(int n) {
        int res = 0;
        while (n) {
            n &= (n - 1);
            ++res;
        }
        
        return res;
    }
};
````

