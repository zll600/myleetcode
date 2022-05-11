# [1111. Maximum Nesting Depth of Two Valid Parentheses Strings](https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/)

## 题目

A string is a *valid parentheses string* (denoted VPS) if and only if it consists of `"("` and `")"` characters only, and:

- It is the empty string, or
- It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are VPS's, or
- It can be written as `(A)`, where `A` is a VPS.

We can similarly define the *nesting depth* `depth(S)` of any VPS `S` as follows:

- `depth("") = 0`
- `depth(A + B) = max(depth(A), depth(B))`, where `A` and `B` are VPS's
- `depth("(" + A + ")") = 1 + depth(A)`, where `A` is a VPS.

For example, `""`, `"()()"`, and `"()(()())"` are VPS's (with nesting depths 0, 1, and 2), and `")("` and `"(()"` are not VPS's.

 

Given a VPS seq, split it into two disjoint subsequences `A` and `B`, such that `A` and `B` are VPS's (and `A.length + B.length = seq.length`).

Now choose **any** such `A` and `B` such that `max(depth(A), depth(B))` is the minimum possible value.

Return an `answer` array (of length `seq.length`) that encodes such a choice of `A` and `B`: `answer[i] = 0` if `seq[i]` is part of `A`, else `answer[i] = 1`. Note that even though multiple answers may exist, you may return any of them.

 

**Example 1:**

```
Input: seq = "(()())"
Output: [0,1,1,1,1,0]
```

**Example 2:**

```
Input: seq = "()(())()"
Output: [0,0,0,1,1,0,1,1]
```

 

**Constraints:**

- `1 <= seq.size <= 10000`

## 题目大意

有效括号字符串 仅由 `“(”` 和 `“)”` 构成，并符合下述几个条件之一：

- 空字符串
- 连接，可以记作 `AB`（`A` 与 `B` 连接），其中 `A` 和 `B` 都是有效括号字符串
- 嵌套，可以记作 `(A)`，其中 `A` 是有效括号字符串

类似地，我们可以定义任意有效括号字符串 `s` 的 嵌套深度 `depth(S)`：

- `s` 为空时，`depth("") = 0`
- `s` 为 `A` 与 `B` 连接时，`depth(A + B) = max(depth(A)`, `depth(B))`，其中 `A` 和 `B` 都是有效括号字符串
- `s` 为嵌套情况，`depth("(” + A + “)") = 1 + depth(A)`，其中 `A` 是有效括号字符串

例如：`""`，`"()()"`，和 `“()(()())”` 都是有效括号字符串，嵌套深度分别为 `0`，`1`，`2`，而 `“)(”` 和 `“(()”` 都不是有效括号字符串



给你一个有效括号字符串 `seq`，将其分成两个不相交的子序列 `A` 和 `B`，且 `A` 和 `B` 满足有效括号字符串的定义（注意：`A.length` + B.length = seq.length`）。

现在，你需要从中选出 任意 一组有效括号字符串 `A` 和 `B`，使 `max(depth(A), depth(B))` 的可能取值最小。

返回长度为 `seq.length` 答案数组 `answer` ，选择 `A` 还是 `B` 的编码规则是：如果 `seq[i]` 是 `A` 的一部分，那么 `answer[i] = 0`。否则，`answer[i] = 1`。即便有多个满足要求的答案存在，你也只需返回 一个。

## 解题思路

有题目可以知道只有发生嵌套才会增加深度，形式上来看，就是连续出现了多个做括号就表示深度增加，所以我们只需要贪心的将连续出现的左括号分配给 A 和 B，然后将剩余的部分做好匹配就可以了

接下来难点就是在这个过程中，如果根据已经分配的左括号来匹配右括号，利用栈的思想，右括号匹配的一定是上一次已经出现的，还没有匹配的左括号

### Solution 1: Greedy

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/solution/qian-tao-shen-du-wan-cheng-gua-hao-pi-pei-wen-ti-s/)

````Java
class Solution {
    public int[] maxDepthAfterSplit(String seq) {
        int len = seq.length();
        int[] res = new int[len];
        
        int depth = 0;
        
        // 在 Java 里，seq.charAt(i) 函数会做下标越界检查，
        // 因此先转换成字符数组是常见的做法
        char[] charArr = seq.toCharArray();
        
        for (int i = 0; i < len; ++i) {
            if (charArr[i] == '(') {
                // 相邻的 '(' 不放在一起，先增加深度再更新数组
                ++depth;
                res[i] = depth % 2;
            } else {
                // ')' 匹配上一个 '('，所以先更新数组，再减少深度
                res[i] = depth % 2;
                depth--;
            }
        }
        return res;
    }
}
````
