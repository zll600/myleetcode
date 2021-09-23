# [1221. Split a String in Balanced Strings](https://leetcode.com/problems/split-a-string-in-balanced-strings/)

## 题目

**Balanced** strings are those that have an equal quantity of `'L'` and `'R'` characters.

Given a **balanced** string `s`, split it in the maximum amount of balanced strings.

Return *the maximum amount of split **balanced** strings*.

 

**Example 1:**

```
Input: s = "RLRRLLRLRL"
Output: 4
Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring contains same number of 'L' and 'R'.
```

**Example 2:**

```
Input: s = "RLLLLRRRLR"
Output: 3
Explanation: s can be split into "RL", "LLLRRR", "LR", each substring contains same number of 'L' and 'R'.
```

**Example 3:**

```
Input: s = "LLLLRRRR"
Output: 1
Explanation: s can be split into "LLLLRRRR".
```

**Example 4:**

```
Input: s = "RLRRRLLRLL"
Output: 2
Explanation: s can be split into "RL", "RRRLLRLL", since each substring contains an equal number of 'L' and 'R'
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `s[i]` is either `'L'` or `'R'`.
- `s` is a **balanced** string.

## 题目大意

平很的字符串是指含有相同数量的 ‘R’ 和 ‘L’，给定一个平衡的字符串，返回可以拆为平衡字符串的最大数目

## 解题思路

这是一道贪心的问题，直觉就是尽可能在低位划分，就可以划分出更多的子串

具体的证明见这篇题解：https://leetcode-cn.com/problems/split-a-string-in-balanced-strings/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-wumnk/

后面一定要找时间好好补补数学

## 代码

`````c++
class Solution {
public:
    int balancedStringSplit(string s) {
        int res = 0;
        int cnt = 0;
        for (char c : s) {
            if (c == 'L') { // 做标记，如果是 ‘L’，就 -1
                --cnt;
            } else if (c == 'R') {  // 如果是‘R’，就 +1，
                ++cnt;
            }
            
            if (cnt == 0) { // 如果为0，说明经过了相等数量的 0 和1，可以切分出一个子串了
                ++res;
            }
        }
        
        return res;
    }
};
`````

