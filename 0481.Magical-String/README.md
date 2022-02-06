# [481. Magical String](https://leetcode-cn.com/problems/magical-string/)

## 题目

A magical string `s` consists of only `'1'` and `'2'` and obeys the following rules:

- The string s is magical because concatenating the number of contiguous occurrences of characters `'1'` and `'2'` generates the string `s` itself.

The first few elements of `s` is `s = "1221121221221121122……"`. If we group the consecutive `1`'s and `2`'s in `s`, it will be `"1 22 11 2 1 22 1 22 11 2 11 22 ......"` and the occurrences of `1`'s or `2`'s in each group are `"1 2 2 1 1 2 1 2 2 1 2 2 ......"`. You can see that the occurrence sequence is `s` itself.

Given an integer `n`, return the number of `1`'s in the first `n` number in the magical string `s`.

 

**Example 1:**

```
Input: n = 6
Output: 3
Explanation: The first 6 elements of magical string s is "122112" and it contains three 1's, so return 3.
```

**Example 2:**

```
Input: n = 1
Output: 1
```

 

**Constraints:**

- `1 <= n <= 105`


## 题目大意

一个魔法字符串 `s` 只含有 `1` 和 `2` 并遵守你下列规则：

- 神奇字符串 `s` 的神奇之处在于，串联字符串中 `'1'` 和 `'2'` 的连续出现次数可以生成该字符串。
s 的前几个元素是 `s = "1221121221221121122……"` 。如果将 `s` 中连续的若干 `1` 和 `2` 进行分组，可以得到 `"1 22 11 2 1 22 1 22 11 2 11 22 ......"` 。每组中 `1` 或者 `2` 的出现次数分别是 `"1 2 2 1 1 2 1 2 2 1 2 2 ......"` 。上面的出现次数正是 `s` 自身。

给你一个整数 `n` ，返回在神奇字符串 `s` 的前 `n` 个数字中 `1` 的数目。


## 解题思路

我们要解决的问题就是按照规律构造一个足够长的满足条件的字符串，然后计算前 n 位的 `1` 的数目，那么这里重点要解决的就是如何生成字符串

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/magical-string/solution/geekplayers-leetcode-ac-qing-xi-yi-dong-2pdyf/)

- 使用两个字符串，根据较短的字符串来生成较长的字符串，
- 记录较长字符串的最后一个字符来决定新插入的字符
- 记录较短字符串的最后一个字符来决定新插入字符的数量

这里的这个 3 是因为从较短的字符的第 2 个字符开始（以 0 开头）可以生成较长的字符串


````c++
class Solution {
public:
    int magicalString(int n) {
        if (n < 3) {
            return 1;
        }
        
        // 构造两个字符串，idx 指向较短的字符串末尾
        // 根据较短的字符串来生成较长的字符串
        string str = "122";
        int idx = 2;
        
        while (str.size() < n) {
            // 取出长字符串结尾的字符
            char last_char = str.back();
            
            if (str[idx] == '1') {
                // 根据短字符串当前结尾的字符，判断要重复的字符的个数
                if (last_char == '1') {
                    str.append(1, '2');
                } else {
                    str.append(1, '1');
                }
            } else {
                if (last_char == '1') {
                    str.append(2, '22');
                } else {
                    str.append(2, '11');
                }
            }
            ++idx;
        }
        
        // 计算 1 的个数
        return count(str.begin(), str.begin() + n, '1');
    }
};
````
