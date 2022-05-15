# [1249. Minimum Remove to Make Valid Parentheses](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/)

## 题目

Given a string s of `'('` , `')'` and lowercase English characters.

Your task is to remove the minimum number of parentheses ( `'('` or `')'`, in any positions ) so that the resulting *parentheses string* is valid and return **any** valid string.

Formally, a *parentheses string* is valid if and only if:

- It is the empty string, contains only lowercase characters, or
- It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are valid strings, or
- It can be written as `(A)`, where `A` is a valid string.

 

**Example 1:**

```
Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
```

**Example 2:**

```
Input: s = "a)b(c)d"
Output: "ab(c)d"
```

**Example 3:**

```
Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is either`'('` , `')'`, or lowercase English letter`.`

## 题目大意

给你一个由 `‘('`、`')’` 和 *小写字母* 组成的字符串 `s`。你需要从字符串中删除最少数目的 `‘(’` 或者 `‘)’` （可以删除任意位置的括号)，使得剩下的`「括号字符串」`有效。

请返回任意一个合法字符串。有效「括号字符串」应当符合以下 任意一条 要求：

- 空字符串或只包含小写字母的字符串
- 可以被写作 AB（A 连接 B）的字符串，其中 A 和 B 都是有效「括号字符串」
- 可以被写作 (A) 的字符串，其中 A 是一个有效的「括号字符串」

## 解题思路

这道题目涉及到括号匹配，可以想到使用 栈来左匹配，

这道题目要解决问题就是如何找出字符串不符合条件的括号的位置，另外这里必须找到所有要删除的位置之后再做删除，不能找到一个删一个

### Solution 1: Stack

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1200~1299/1249.Minimum-Remove-to-Make-Valid-Parentheses/)

这种解法使用栈来存储所有需要删除位置的下标，然后在构造结果字符串的时候跳过这些位置，代码也有注释，也可以看看注释

````c++
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> sta;

        const int len = s.size();
        for (int i = 0; i < len; ++i) {
            if (s[i] == '(') {
                // 如果之左括号直接如栈，
                sta.push(i);
            } else if (s[i] == ')' && !sta.empty() && s[sta.top()] == '(') {
                // 如果是有括号查看栈顶是否有配对的左括号
                sta.pop();
            } else if (s[i] == ')') {
                // 不符合条件的左括号也需要删除
                sta.push(i);
            }


        string res = "";
        for (int i = len - 1; i >= 0; --i) {
            // 跳过栈内的值
            if (!sta.empty() && sta.top() == i) {
                sta.pop();
                continue;
            }
            res.push_back(s[i]);
        }
        // 记得反转
        reverse(res.begin(), res.end());

        return res;
    }
};
````
