# [318. Maximum Product of Word Lengths](https://leetcode.com/problems/maximum-product-of-word-lengths/)

## 题目

Given a string array `words`, return *the maximum value of* `length(word[i]) * length(word[j])` *where the two words do not share common letters*. If no such two words exist, return `0`.

 

**Example 1:**

```
Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16
Explanation: The two words can be "abcw", "xtfn".
```

**Example 2:**

```
Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4
Explanation: The two words can be "ab", "cd".
```

**Example 3:**

```
Input: words = ["a","aa","aaa","aaaa"]
Output: 0
Explanation: No such pair of words.
```

 

**Constraints:**

- `2 <= words.length <= 1000`
- `1 <= words[i].length <= 1000`
- `words[i]` consists only of lowercase English letters.

## 题目大意

给定一个字符串数组 words，返回 length(word[i]) * length(word[j])的最大值，且两个单词不含有共同的字母，如果这样的两个单词不存在，返回0，

## 解题思路

* 这道题目先试着暴力解一下，就会发现瓶颈在如果有效判断两个字符串是否含有相同的字母上
* 利用 与 运算的性质 val1 & val2 == 0 说明 val1 和 val2 完全不一样，也就可以判断两个字符串不含有相同的字母了
* 这里将需要将字符串映射为一个整数，映射的方法采用的是每个字母距离 'a'多远，就将 1 左移多少位即可

## 代码

`````c++
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int size = words.size();
        
        vector<int> val(size);
        for (int i = 0; i < size; ++i) {
            val[i] = 0;
            string tmp = words[i];
            
            for (int j = 0; j < tmp.size(); ++j) {  // 这里将 字符串映射为一个整数，
                val[i] |= 1 << (tmp[j] - 'a');
            }
        }
        
        int res = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if ((val[i] & val[j]) == 0) {   // 利用 与 运算来判断两个字符串是否相同，如果为0，就说明完全不相同
                    res = max(res, static_cast<int>(words[i].size() * words[j].size()));
                }
            }
        }
        return res;
    }
};
`````

