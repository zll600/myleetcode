# [443. String Compression](https://leetcode.com/problems/string-compression/)

## 题目

Given an array of characters `chars`, compress it using the following algorithm:

Begin with an empty string `s`. For each group of **consecutive repeating characters** in `chars`:

- If the group's length is `1`, append the character to `s`.
- Otherwise, append the character followed by the group's length.

The compressed string `s` **should not be returned separately**, but instead, be stored **in the input character array `chars`**. Note that group lengths that are `10` or longer will be split into multiple characters in `chars`.

After you are done **modifying the input array**, return *the new length of the array*.

You must write an algorithm that uses only constant extra space.

 

**Example 1:**

```
Input: chars = ["a","a","b","b","c","c","c"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".
```

**Example 2:**

```
Input: chars = ["a"]
Output: Return 1, and the first character of the input array should be: ["a"]
Explanation: The only group is "a", which remains uncompressed since it's a single character.
```

**Example 3:**

```
Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".
```

**Example 4:**

```
Input: chars = ["a","a","a","b","b","a","a"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","3","b","2","a","2"].
Explanation: The groups are "aaa", "bb", and "aa". This compresses to "a3b2a2". Note that each group is independent even if two groups have the same character.
```

 

**Constraints:**

- `1 <= chars.length <= 2000`
- `chars[i]` is a lowercase English letter, uppercase English letter, digit, or symbol.

## 题目大意

给定一个字符串数组，使用如下算法对其进行压缩，

从一个空字符开始，对每组连续重复的字符：

* 如果这组字符串的数量为 1，直接附加到 s 中，
* 否则追加这个字符并在后面加上这组字符的数量，

压缩后得到的字符串 s 不应该直接返回 ，需要转储到字符数组 chars 中。需要注意的是，如果组长度为 10 或 10 以上，则长度值在 chars 数组中会被拆分为多个字符。

在你修改完输入数组后，返回数组的长度，

你必须使用仅仅使用了常数空间的算法

## 解题思路

### 解法1

这道题目的整体思路并不难，主要在于程序的各个细节，因为只能使用常数的空间，所以这里先将重复的数量的每一位填入数组中，然后再进行反转操作。

`````c++
class Solution {
public:
    int compress(vector<char>& chars) {
        int idx = 0;
        int i = 0;
        while (i < chars.size()) {
            int cnt = 0;
            // 循环不变量，[idx, i)表示同一个重复的字符
            while (i < chars.size() && chars[i] == chars[idx]) {
                i++;
                cnt++;
            }
            
            if (cnt > 1) {
                int len = 0;
                while (cnt) {
                    idx++;
                    chars[idx] = static_cast<char>(cnt % 10 + '0');
                    cnt /= 10;
                    ++len;
                }
                // 将填入的数字反转
                reverse(chars.begin() + idx - len + 1, chars.begin() + idx + 1);
            }
            
            // 如果已经越界，不应再更新下一个字符
            if (i == chars.size()) {
                break;
            }
            
            idx++;
            chars[idx] = chars[i];
        }
        
        return idx + 1;
    }
};
`````

