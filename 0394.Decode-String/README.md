# [394. Decode String](https://leetcode.com/problems/decode-string/)

## 题目

Given an encoded string, return its decoded string.

The encoding rule is: `k[encoded_string]`, where the `encoded_string` inside the square brackets is being repeated exactly `k` times. Note that `k` is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, `k`. For example, there won't be input like `3a` or `2[4]`.

 

**Example 1:**

```
Input: s = "3[a]2[bc]"
Output: "aaabcbc"
```

**Example 2:**

```
Input: s = "3[a2[c]]"
Output: "accaccacc"
```

**Example 3:**

```
Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"
```

**Example 4:**

```
Input: s = "abc3[cd]xyz"
Output: "abccdcdcdxyz"
```

 

**Constraints:**

- `1 <= s.length <= 30`
- `s` consists of lowercase English letters, digits, and square brackets `'[]'`.
- `s` is guaranteed to be **a valid** input.
- All the integers in `s` are in the range `[1, 300]`.

## 题目大意

给定一个经过编码的字符串，返回解码的字符串，

编码规则是k[encoded_string，[] 里的endcoding_string 确定重复了 k 次，k 保证是一个正整数

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

## 解题思路

* 可以两个栈来分别存储 **次数** 和**字母**，遇到 ‘[’ 就开始里重复字母，题目有一个地方需要注意，那就是重复次数可能是一个多位数，必须要加上所有的位
* 这个题也可以用一个栈来实现

## 代码

````c++
class Solution {
public:
    string decodeString(string str) {
        stack<int> nums;
        stack<string> sta;
        
        int size = str.size();
        for (int i = 0; i < size; ++i) {
            if (isdigit(str[i])) {
                string tmp = "";
                while (i < size && str[i] != '[') {
                    tmp += str[i++];
                }
                i -= 1; // 调整 i 指向最后一个数字，因为后面要用括号做判断，所以不能丢失
                nums.push(stoi(tmp));
            } else if (str[i] == ']') {
                string tmp = "";
                while (!sta.empty() && sta.top() != "[") {
                    tmp = sta.top() + tmp;
                    sta.pop();
                }
                sta.pop();
                
                int count = nums.top();
                nums.pop();
                
                string copy = tmp;
                for (int i = 1; i < count; ++i) {
                    tmp += copy;
                }
                sta.push(tmp);
            } else {
                sta.push(string(1, str[i]));
            }
        }
        
        string res = "";
        while (!sta.empty()) {
            res = sta.top() + res;
            sta.pop();
        }
        
        return res;
        
    }
};
````



