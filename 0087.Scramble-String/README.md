# [87. Scramble String](https://leetcode-cn.com/problems/scramble-string/)

## 题目

We can scramble a string s to get a string t using the following algorithm:

1. If the length of the string is 1, stop.
2. If the length of the string is > 1, do the following:
   - Split the string into two non-empty substrings at a random index, i.e., if the string is `s`, divide it to `x` and `y` where `s = x + y`.
   - **Randomly** decide to swap the two substrings or to keep them in the same order. i.e., after this step, `s` may become `s = x + y` or `s = y + x`.
   - Apply step 1 recursively on each of the two substrings `x` and `y`.

Given two strings `s1` and `s2` of **the same length**, return `true` if `s2` is a scrambled string of `s1`, otherwise, return `false`.

 

**Example 1:**

```
Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at random index.
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at ranom index each of them.
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
The algorithm stops now and the result string is "rgeat" which is s2.
As there is one possible scenario that led s1 to be scrambled to s2, we return true.
```

**Example 2:**

```
Input: s1 = "abcde", s2 = "caebd"
Output: false
```

**Example 3:**

```
Input: s1 = "a", s2 = "a"
Output: true
```

 

**Constraints:**

- `s1.length == s2.length`
- `1 <= s1.length <= 30`
- `s1` and `s2` consist of lower-case English letters.

## 题目大意

按照以下算法，我们可以扰乱字符串 s 得到字符串 t：

1. 如果字符串的长度是 1，停止
2. 如果字符串的长度大于 1，执行下面的操作，
   - 在一个随机下标处将字符串分割成两个非空的子字符串。即，如果已知字符串 `s` ，则可以将其分成两个子字符串 `x` 和 `y` ，且满足 `s = x + y` 。
   - 随机 决定是要「交换两个子字符串」还是要「保持这两个子字符串的顺序不变」。即，在执行这一步骤之后，s 可能是 s = x + y 或者 s = y + x 。
   - 在 x 和 y 这两个子字符串上继续从步骤 1 开始递归执行此算法。

给定两个长度相同的字符串 s1 和 s2，判断 s2 是不是 s1 的扰乱字符串，

## 解题思路

首先这道题目中提到了随机，而且定义了子问题，所以我觉得，我们可能需要列出所有可能的结果，然后再去匹配，然后就可以考虑使用 DFS 的方法来做，进而可以考虑能否使用记忆化优化，还可以思考是否满足无后效性，考虑使用 dp，

### Solution 1:DFS(TLE)

这种解法，枚举所有可能，最终会超时

````c++
class Solution {
public:
    bool isScramble(string s1, string s2) {
        const int len = s1.size();
        if (s1 == s2) {  // 如果两个字符串已经相同直接返回 true
            return true;
        }
        if (CalcFreq(s1) != CalcFreq(s2)) {  // 如果两个字串中的字频数不同，这接返回 false
            return false;
        }
        
        // 第一个子问题，分割字符串
        for (int idx = 1; idx < len; ++idx) {
            // 第二个子问题，是否交换位置
            if ((isScramble(s1.substr(0, idx), s2.substr(0, idx))
                 && isScramble(s1.substr(idx), s2.substr(idx)))
                || (isScramble(s1.substr(0, idx), s2.substr(len - idx, idx))
                   && isScramble(s1.substr(idx, len - idx), s2.substr(0, len - idx)))) {
                return true;        
            }
        }
        return false;
    }
    
 private:
    vector<int> CalcFreq(const string& str) {
        vector<int> freq(26, 0);
        for (char c : str) {
            ++freq[c - 'a'];
        }
        return freq;
    }
};
````

