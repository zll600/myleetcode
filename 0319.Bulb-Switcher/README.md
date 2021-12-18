# [319. Bulb Switcher](https://leetcode.com/problems/bulb-switcher/) 

## 题目

There are `n` bulbs that are initially off. You first turn on all the bulbs, then you turn off every second bulb.

On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on). For the `ith` round, you toggle every `i` bulb. For the `nth` round, you only toggle the last bulb.

Return *the number of bulbs that are on after `n` rounds*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/05/bulb.jpg)

```
Input: n = 3
Output: 1
Explanation: At first, the three bulbs are [off, off, off].
After the first round, the three bulbs are [on, on, on].
After the second round, the three bulbs are [on, off, on].
After the third round, the three bulbs are [on, off, off]. 
So you should return 1 because there is only one bulb is on.
```

**Example 2:**

```
Input: n = 0
Output: 0
```

**Example 3:**

```
Input: n = 1
Output: 1
```

 

**Constraints:**

- `0 <= n <= 109`

## 题目大意

初始时你有 n 个灯泡处于关闭状态，第一轮，你打开所有的灯泡，第二轮你每两个灯泡关闭一个，第三轮，你每三个灯泡切换一个灯泡的状态，第 i 轮，你每 i 个灯泡就切换一个灯泡的开关。直到第 n 轮，你只需要切换最后一个灯泡的开关。

返回 n 轮之后你还有几个亮着的灯

## 解题思路

我们可以发现一个规律，第 i 轮改变所有编号为 i 的倍数的灯泡的状态，这里的下标是从 1 开始，

一个编号为 x 的灯泡经过 n 轮后处于打开状态的充要条件为『该灯泡被切换的状态次数为奇数次』，同时一个灯泡切换状态的次数为其约数的个数（去重），

所以这里就是要在 [1, n] 中找约数为奇数的数的数目

这里可以参考这篇题解：https://leetcode-cn.com/problems/bulb-switcher/solution/gong-shui-san-xie-jing-dian-shu-lun-tui-upnnb/

同时也可以看霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0300~0399/0319.Bulb-Switcher/

### Solution 1:

```c++
class Solution {
public:
    int bulbSwitch(int n) {
        // return static_cast<int>(sqrt(static_cast<double>(n)));
        return static_cast<int>(sqrt(n));
    }
};
```

