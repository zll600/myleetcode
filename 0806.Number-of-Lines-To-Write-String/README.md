# [806. Number of Lines To Write String](https://leetcode-cn.com/problems/number-of-lines-to-write-string/)

## 题目

You are given a string `s` of lowercase English letters and an array `widths` denoting **how many pixels wide** each lowercase English letter is. Specifically, `widths[0]` is the width of `'a'`, `widths[1]` is the width of `'b'`, and so on.

You are trying to write `s` across several lines, where **each line is no longer than** `100` **pixels**. Starting at the beginning of `s`, write as many letters on the first line such that the total width does not exceed `100` pixels. Then, from where you stopped in `s`, continue writing as many letters as you can on the second line. Continue this process until you have written all of `s`.

Return *an array* `result` *of length 2 where:*

- `result[0]` *is the total number of lines.*
- `result[1]` *is the width of the last line in pixels.*

 

**Example 1:**

```
Input: widths = [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10], s = "abcdefghijklmnopqrstuvwxyz"
Output: [3,60]
Explanation: You can write s as follows:
abcdefghij  // 100 pixels wide
klmnopqrst  // 100 pixels wide
uvwxyz      // 60 pixels wide
There are a total of 3 lines, and the last line is 60 pixels wide.
```

**Example 2:**

```
Input: widths = [4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10], s = "bbbcccdddaaa"
Output: [2,4]
Explanation: You can write s as follows:
bbbcccdddaa  // 98 pixels wide
a            // 4 pixels wide
There are a total of 2 lines, and the last line is 4 pixels wide.
```

 

**Constraints:**

- `widths.length == 26`
- `2 <= widths[i] <= 10`
- `1 <= s.length <= 1000`
- `s` contains only lowercase English letters.

## 题目大意

给定一个只含有小写字母的字符串 s， 和一个宽度数组 width 表明每个字母占多少像素的宽度，我们要把给定的字符串 S 从左到右写到每一行上，每一行的最大宽度为100个单位，如果我们在写某个字母的时候会使这行超过了100 个单位，那么我们应该把这个字母写到下一行，

按照以下格式返回你的结果：

* `result[0]` 是总行数
* `result[1]` 是最后一行的像素数

## 解题思路

这道题目算是比较简单，

### Solution 1:

遍历整个字符串，来进行计数即可

```c++
class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string s) {
        const int len = s.size();
        int lines = 1; // 至少需要一行
        int pixels = 0;
        for (int i = 0; i < len; ++i) {
            pixels += widths[s[i] - 'a'];
            if (pixels > 100) {
                // 如果像素数超过 100，就换行
                ++lines;
                pixels = widths[s[i] - 'a'];
            }
        }
        
        return vector<int>({lines, pixels});
    }
};
```

