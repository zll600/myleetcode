# [1003. Check If Word Is Valid After Substitutions](https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/)

## 题目

Given a string `s`, determine if it is **valid**.

A string `s` is **valid** if, starting with an empty string `t = ""`, you can **transform** `t` **into** `s` after performing the following operation **any number of times**:

- Insert string `"abc"` into any position in `t`. More formally, `t` becomes `tleft + "abc" + tright`, where `t == tleft + tright`. Note that `tleft` and `tright` may be **empty**.

Return `true` *if* `s` *is a **valid** string, otherwise, return* `false`.

 

**Example 1:**

```
Input: s = "aabcbc"
Output: true
Explanation:
"" -> "abc" -> "aabcbc"
Thus, "aabcbc" is valid.
```

**Example 2:**

```
Input: s = "abcabcababcc"
Output: true
Explanation:
"" -> "abc" -> "abcabc" -> "abcabcabc" -> "abcabcababcc"
Thus, "abcabcababcc" is valid.
```

**Example 3:**

```
Input: s = "abccba"
Output: false
Explanation: It is impossible to get "abccba" using the operation.
```

 

**Constraints:**

- `1 <= s.length <= 2 * 104`
- `s` consists of letters `'a'`, `'b'`, and `'c'`

## 题目大意

假设 `abc` 是有效的字符串，对于任何 字符串 `t`，如果用 `abc` 把字符串 `t` 切成 `2 半`，`tleft` 和 `tright`，组成 `tleft + abc + tright` 的字符串，`tleft + abc + tright` 的这个字符串依旧是有效的。`tleft` 和 `tright` 可以是空字符串

## 解题思路


### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1000~1099/1003.Check-If-Word-Is-Valid-After-Substitutions/)

````c++
class Solution {
public:
    bool isValid(string s) {
        // 特殊情况
        if (s.size() < 3) {
            return false;
        }

        vector<char> sta;
        for (char c : s) {
            if (c == 'a') {
                // 如果是 ‘a’，入栈
                sta.push_back(c);
            } else if (c == 'b') {
                if (!sta.empty() && sta.back() == 'a') {
                    // 如果是 'b'，栈不能为空，且栈顶必须是 'a'
                    sta.push_back(c);
                } else {
                    return false;
                }
            } else {
                if (sta.size() > 1 && sta.back() == 'b' && sta[sta.size() - 2] == 'a') {
                    // 如果是 'c'.
                    // 栈的大小不能小于 1, 栈顶必须是 'b' 和 'a'
                    sta.pop_back();
                    sta.pop_back();
                } else {
                    return false;
                }
            }
        }

        return sta.empty();
    }
};
````
