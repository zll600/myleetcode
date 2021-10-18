# [1525. Number of Good Ways to Split a String](https://leetcode-cn.com/problems/number-of-good-ways-to-split-a-string/)

## 题目

You are given a string `s`, a split is called *good* if you can split `s` into 2 non-empty strings `p` and `q` where its concatenation is equal to `s` and the number of distinct letters in `p` and `q` are the same.

Return the number of *good* splits you can make in `s`.

 

**Example 1:**

```
Input: s = "aacaba"
Output: 2
Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.
```

**Example 2:**

```
Input: s = "abcd"
Output: 1
Explanation: Split the string as follows ("ab", "cd").
```

**Example 3:**

```
Input: s = "aaaaa"
Output: 4
Explanation: All possible splits are good.
```

**Example 4:**

```
Input: s = "acbadbaada"
Output: 2
```

 

**Constraints:**

- `s` contains only lowercase English letters.
- `1 <= s.length <= 10^5`

## 题目

给你一个字符串 s ，一个分割被称为 「好分割」 当它满足：将 s 分割成 2 个字符串 p 和 q ，它们连接起来等于 s 且 p 和 q 中不同字符的数目相同。

请你返回 s 中好分割的数目。

## 解题思路

遍历字符串，统计字符串中 字母出现的频数和字母的种类

再次遍历字符串，增加字母在左侧部分出现的频数和左侧字幕的种类，减少字母在右侧部分出现的频数和右侧字母的种类

这里要注意的地方在于

* 只有当字母的频数为 1 时，才增加字母的种类数
* 只有当字母的频数为 0 时，才减少字母的种类数

第二次遍历中，比较两部分个字的字母种类数

````c++
class Solution {
public:
    int numSplits(string s) {
        vector<int> right_dict(26, 0);  // 这里直接用字符数组来做统计
        int right_counter = 0;
        
        for (char c : s) {
            ++right_dict[c - 'a'];
            right_counter += (right_dict[c - 'a'] == 1);   // 每个字符变为 1 时，增加
        }
        
        int res = 0;
        int left_counter = 0;
        vector<int> left_dict(26, 0);
        for (char c : s) {
            ++left_dict[c - 'a'];
            left_counter += (left_dict[c - 'a'] == 1);
            
            --right_dict[c - 'a'];
            right_counter -= (right_dict[c - 'a'] == 0);  // 字符数量变为 0 时，减少
            
            res += (left_counter == right_counter);
        }
        
        return res; 
    }
};
````

