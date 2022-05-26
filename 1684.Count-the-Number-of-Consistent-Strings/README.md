# [1684. Count the Number of Consistent Strings](https://leetcode.com/problems/count-the-number-of-consistent-strings/)

## 题目

You are given a string `allowed` consisting of **distinct** characters and an array of strings `words`. A string is **consistent** if all characters in the string appear in the string `allowed`.

Return *the number of **consistent** strings in the array* `words`.

 

**Example 1:**

```
Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
Output: 2
Explanation: Strings "aaab" and "baa" are consistent since they only contain characters 'a' and 'b'.
```

**Example 2:**

```
Input: allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"]
Output: 7
Explanation: All strings are consistent.
```

**Example 3:**

```
Input: allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"]
Output: 4
Explanation: Strings "cc", "acd", "ac", and "d" are consistent.
```

 

**Constraints:**

- `1 <= words.length <= 104`
- `1 <= allowed.length <= 26`
- `1 <= words[i].length <= 10`
- The characters in `allowed` are **distinct**.
- `words[i]` and `allowed` contain only lowercase English letters.

## 题目大意

给你一个由不同字符组成的字符串 `allowed` 和一个字符串数组 `words` 。如果一个字符串的每一个字符都在 `allowed` 中，就称这个字符串是 一致字符串 

请你返回 `words` 数组中 一致字符串 的数目

## 解题思路

这道题目首先想到的大多还是使用哈希来解决，

### Solution 1: Bit wise

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/count-the-number-of-consistent-strings/solution/zhuang-tai-ya-suo-wei-yun-suan-by-zheng-xl00a/)

因为 '`a - z` 这 26 个字母是唯一的，而且在 allowed 中也都是唯一的，所以可以将每个字母对应到 26 位二进制中，进行编码，

那么对 allowed 进行编码，对 words 中的每个字符串也进行编码，就需要解决如何判断两个编码是否相同的问题了


````c++

class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int allowed_code = Code(allowed);
        int ans = 0;
        for (const string& word : words) {
            int word_code = Code(word);
            if ((allowed_code & word_code) == word_code) {
                // cout << word << endl;
                ++ans;
            } 
        }
        
        return ans;
    }
    
 private:
    int Code(const string& word) {
        int code = 0;
        for (char c : word) {
            int shift = static_cast<int>(c - 'a');
            code |= (1 << shift);
        }
        return code;
    }
};
````



