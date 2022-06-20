#### [1247. Minimum Swaps to Make Strings Equal](https://leetcode.cn/problems/minimum-swaps-to-make-strings-equal/)

You are given two strings `s1` and `s2` of equal length consisting of letters `"x"` and `"y"` **only**. Your task is to make these two strings equal to each other. You can swap any two characters that belong to **different** strings, which means: swap `s1[i]` and `s2[j]`.

Return the minimum number of swaps required to make `s1` and `s2` equal, or return `-1` if it is impossible to do so.

 

**Example 1:**

```
Input: s1 = "xx", s2 = "yy"
Output: 1
Explanation: Swap s1[0] and s2[1], s1 = "yx", s2 = "yx".
```

**Example 2:**

```
Input: s1 = "xy", s2 = "yx"
Output: 2
Explanation: Swap s1[0] and s2[0], s1 = "yy", s2 = "xx".
Swap s1[0] and s2[1], s1 = "xy", s2 = "xy".
Note that you cannot swap s1[0] and s1[1] to make s1 equal to "yx", cause we can only swap chars in different strings.
```

**Example 3:**

```
Input: s1 = "xx", s2 = "xy"
Output: -1
```

 

**Constraints:**

- `1 <= s1.length, s2.length <= 1000`
- `s1, s2` only contain `'x'` or `'y'`.

## 题目大意

有两个长度相同的字符串 `s1` 和 `s2`，且它们其中 只含有 字符 `"x"` 和 `"y"`，你需要通过 *「交换字符* 的方式使这两个字符串相同

每次 *「交换字符」* 的时候，你都可以在两个字符串中各选一个字符进行交换

交换只能发生在两个不同的字符串之间，绝对不能发生在同一个字符串内部。也就是说，我们可以交换 `s1[i]` 和 `s2[j]`，但不能交换 `s1[i]` 和 `s1[j]`

最后，请你返回使 `s1` 和 `s2` 相同的最小交换次数，如果没有方法能够使得这两个字符串相同，则返回 `-1`

## 解题思路

### Solution 1: Greedy

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/minimum-swaps-to-make-strings-equal/solution/cpython-tan-xin-suan-fa-by-bandari-6-ecch/)

这道题目还是挺难的 qwq

````c++
class Solution {
public:
    int minimumSwap(string s1, string s2) {
        const int len = s1.size();
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < len; ++i) {
            if (s1[i] == 'x' && s2[i] == 'y') {
                ++cnt1;
            } else if (s1[i] == 'y' && s2[i] == 'x') {
                ++cnt2;
            }
        }
        if ((cnt1 + cnt2) % 2 != 0) {
            return -1;
        }

        return cnt1 / 2 + cnt2 / 2 + 2 * (cnt1 % 2);
    }
};
````

