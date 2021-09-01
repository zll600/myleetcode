# [1190. Reverse Substrings Between Each Pair of Parentheses](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/)

## 题目

You are given a string `s` that consists of lower case English letters and brackets. 

Reverse the strings in each pair of matching parentheses, starting from the innermost one.

Your result should **not** contain any brackets.

 

**Example 1:**

```
Input: s = "(abcd)"
Output: "dcba"
```

**Example 2:**

```
Input: s = "(u(love)i)"
Output: "iloveu"
Explanation: The substring "love" is reversed first, then the whole string is reversed.
```

**Example 3:**

```
Input: s = "(ed(et(oc))el)"
Output: "leetcode"
Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.
```

**Example 4:**

```
Input: s = "a(bcdefghijkl(mno)p)q"
Output: "apmnolkjihgfedcbq"
```

 

**Constraints:**

- `0 <= s.length <= 2000`
- `s` only contains lower case English characters and parentheses.
- It's guaranteed that all parentheses are balanced.

## 题目大意

给定一个仅包含小写字母和括号的字符串，从最里面的括号开始，反转没对括号中的字符串，你的结果不能包含任何括号

## 解题思路

* 使用栈来模拟
* 坐标记（这个方法目前还不是很熟）

## 代码

````c++
class Solution {
public:
    // 解法一：用双端队列来模拟栈的应用，是将复杂度 O(n^2)，空间复杂度O(n)
    /*
    string reverseParentheses(string str) {
        int size = str.size();
        deque<char> sta;
        
        for (char c : str) {
            if (c == ')') {
                deque<char> tmp;
                while (!sta.empty() && sta.back() != '(') {
                    tmp.push_back(sta.back());
                    sta.pop_back();
                }
                sta.pop_back();
                
                while (!tmp.empty()) {
                    sta.push_back(tmp.front());
                    tmp.pop_front();
                }
                
            } else {
                sta.push_back(c);
            }
        }
        
        return string(sta.begin(), sta.end());
    }*/
    
    // 解法二：使用做标记，减少字符串的进出次数，时间复杂度 O(n)，空间复杂度O(n)
    string reverseParentheses(string str) {
        int size = str.size();
        stack<int> sta;
        vector<int> pair(size);
        
        for (int i = 0; i < size; ++i) {
            if (str[i] == '(') {
                sta.push(i);
            } else if (str[i] == ')') {
                int j = sta.top();
                sta.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }
        
        string res = "";
        int i = 0;
        int step = 1;
        for (; i < size; i += step) {
            if (str[i] == '(' || str[i] == ')') {
                i = pair[i];
                step = -step;
            } else {
                res += str[i];
            }
        }
        
        return res;
    }
};c
````

