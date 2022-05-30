# [788. Rotated Digits](https://leetcode.cn/problems/rotated-digits/)

An integer `x` is a **good** if after rotating each digit individually by 180 degrees, we get a valid number that is different from `x`. Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. For example:

- `0`, `1`, and `8` rotate to themselves,
- `2` and `5` rotate to each other (in this case they are rotated in a different direction, in other words, `2` or `5` gets mirrored),
- `6` and `9` rotate to each other, and
- the rest of the numbers do not rotate to any other number and become invalid.

Given an integer `n`, return *the number of **good** integers in the range* `[1, n]`.

 

**Example 1:**

```
Input: n = 10
Output: 4
Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
```

**Example 2:**

```
Input: n = 1
Output: 0
```

**Example 3:**

```
Input: n = 2
Output: 1
```

 

**Constraints:**

- `1 <= n <= 104`

## 题目大意

我们称一个数 X 为好数, 如果它的每位数字逐个地被旋转 180 度后，我们仍可以得到一个有效的，且和 X 不同的数。要求每位数字都要被旋转。

如果一个数的每位数字被旋转以后仍然还是一个数字， 则这个数是有效的。0, 1, 和 8 被旋转后仍然是它们自己；2 和 5 可以互相旋转成对方（在这种情况下，它们以不同的方向旋转，换句话说，2 和 5 互为镜像）；6 和 9 同理，除了这些以外其他的数字旋转以后都不再是有效的数字。

现在我们有一个正整数 N, 计算从 1 到 N 中有多少个数 X 是好数？

## 解题思路

根据题目要求，需要满足

- 数字中不可以出现 0, 1, 8, 2, 5, 6, 9 之外的数字，否则旋转后数字无效
- 数字中至少含有一个 2, 5, 6，9，否则旋转后数字与原来相同


### Solution 1:

````c++
class Solution {
public:
    int rotatedDigits(int n) {
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (Check(i)) {
                ++ans;
            }
        }
        return ans;
    }

 private:
    bool Check(int num) {
        string str = to_string(num);
        bool flag = false;
        for (char c : str) {
            // 只能包含这几个数字
            if (c != '0' && c != '1' && c != '8' && c != '2' && c != '5' && c != '6' && c != '9') {
                return false;
            }
            // 出现下列其中一个即可
            if (c == '2' || c == '5' || c == '6' || c == '9') {
                flag = true;
            }
        }
        if (!flag) {
            return false;
        }
        return true;
    }
};
````

