# [466. Count The Repetitions](https://leetcode-cn.com/problems/count-the-repetitions/)

## 题目

We define `str = [s, n]` as the string `str` which consists of the string `s` concatenated `n` times.

- For example, `str == ["abc", 3] =="abcabcabc"`.

We define that string `s1` can be obtained from string `s2` if we can remove some characters from `s2` such that it becomes `s1`.

- For example, `s1 = "abc"` can be obtained from `s2 = "ab**dbe**c"` based on our definition by removing the bolded underlined characters.

You are given two strings `s1` and `s2` and two integers `n1` and `n2`. You have the two strings `str1 = [s1, n1]` and `str2 = [s2, n2]`.

Return *the maximum integer* `m` *such that* `str = [str2, m]` *can be obtained from* `str1`.

 

**Example 1:**

```
Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
Output: 2
```

**Example 2:**

```
Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
Output: 1
```

 

**Constraints:**

- `1 <= s1.length, s2.length <= 100`
- `s1` and `s2` consist of lowercase English letters.
- `1 <= n1, n2 <= 106`

## 题目大意

我们定义 `str = [s, n]` 作为 `str` 由字符串 `s` 重复 `n` 次构成，

- 例如：`str == ["abc", 3]` == "abcabcabc"

如果可以从 s2 中删除某些字符使其变为 s1，则称字符串 s1 可以从字符串 s2 获得。

例如，根据定义，`s1 = "abc"` 可以从 `s2 = "ab**dbe**c"` 获得，仅需要删除加粗且用斜体标识的字符。

现在给你两个字符串 `s1` 和 `s2` 和两个整数 `n1` 和 `n2` 。由此构造得到两个字符串，其中 `str1 = [s1, n1]、str2 = [s2, n2]` 。

请你找出一个最大整数 m ，以满足 str = [str2, m] 可以从 str1 获得。

## 解题思路

这道题目建议参考以下几篇题解

- [找循环做优化，0ms 2MB 跑双百](https://leetcode-cn.com/problems/count-the-repetitions/solution/zhao-xun-huan-zuo-you-hua-0ms-2mb-pao-shuang-bai-b/)
- [一看就能懂的计数法，有图有真相](https://leetcode-cn.com/problems/count-the-repetitions/solution/yi-kan-jiu-neng-dong-de-ji-shu-fa-you-tu-you-zhen-/)

- [Weiwei](https://leetcode-cn.com/problems/count-the-repetitions/solution/bao-li-jie-fa-you-hua-jie-fa-java-dai-ma-by-liweiw/)
 

先要满足 str1 = [s1, n1] 中有子序列 str2 = [str2, n2] 有下列几个条件

- str1 的长度大于等于 str2
- str2 中的字母 str1 中也有，即 s2 中出现的字母 s1 中都有
- str2 中字母出现的顺序都满足一定的条件

题目中给的例子中 s2 均为 s1 的子序列，且对应字母出现同 s1，但是也有可能 s2 不是 s1 的子序列，但是多个 s1 拼接在一起可以产生 s2，


### Solution 1:

这种解法可以过，但是很难理解

````c++
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        const int len1 = s1.size();
        const int len2 = s2.size();
        
        if (len1 * n1 < len2 * n2) {
            // 此时 str1 不可能组成 str2
            return 0;
        }
        
        int idx1 = 0, idx2 = 0;
        unordered_map<int, int> memo1;
        unordered_map<int, int> memo2;
        
        int ans = 0;
        
        while (idx1 / len1 < n1) {
            if (idx1 % len1 == len1 - 1) {
                if (memo1.find(idx2 % len2) != memo1.end()) {
                    int cycle_len = idx1 / len1 - memo1[idx2 % len2] / len1;
                    int cycle_num = (n1 - 1 - idx1 / len1) / cycle_len;
                    int cycles_2num = idx2 / len2 - memo2[idx2 % len2] / len2;
                    
                    idx1 += cycle_num * cycle_len * len1;
                    ans += cycle_num * cycles_2num;
                } else {
                    memo1[idx2%len2] = idx1;
                    memo2[idx2%len2] = idx2;
                }
            }
            if (s1[idx1 % len1] == s2[idx2 % len2]) {
                if (idx2 % len2 == len2 - 1) {
                    ans += 1;
                }
                idx2 += 1;
            }
            idx1 += 1;
        }
        
        
        return ans / n2;
    }
};
````



### Solution 2: Two Pointers

这种解法最终会超时，但是比较好理解，

````c++
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        const int len1 = s1.size();
        const int len2 = s2.size();
        
        if (len1 * n1 < len2 * n2) {
            // 此时 str1 不可能组成 str2
            return 0;
        }
        
        // 下面做的判断 str1 中有多少个 s2，最后除以 n2 向下取整得到答案
        int idx2 = 0;
        int loops = 0;
        
        for (int i = 0; i < n1; ++i) {
            for (int idx1 = 0; idx1 <= len1; ++idx1) {
                if (s1[idx1] == s2[idx2]) {
                    ++idx2;
                }
                if (idx2 == len2) {
                    ++loops;
                    idx2 = 0;
                }
            }
        }
        
        return loops / n2;
    }
};
````


