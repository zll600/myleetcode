# [1796. Second Largest Digit in a String](https://leetcode-cn.com/problems/second-largest-digit-in-a-string/)

## 题目

Given an alphanumeric string `s`, return *the **second largest** numerical digit that appears in* `s`*, or* `-1` *if it does not exist*.

An **alphanumeric** string is a string consisting of lowercase English letters and digits.

 

**Example 1:**

```
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.
```

**Example 2:**

```
Input: s = "abc1111"
Output: -1
Explanation: The digits that appear in s are [1]. There is no second largest digit. 
```

 

**Constraints:**

- `1 <= s.length <= 500`
- `s` consists of only lowercase English letters and/or digits.

## 题目大意

给定一个只包含字母和数字的字符串 s，返回 s 中防护现的第二大的数字，如果不存在返回 -1

## 解题思路

### Solution 1: Set

````c++
class Solution {
public:
    int secondHighest(string s) {
        // 这里可以利用 set 的有序性和不重复性来做
        set<int> res;
        
        for (char c : s) {
            // 如果是数字，则直接加入到结果集中
            if (isdigit(c)) {
                res.insert(c - '0');
            }
        }
        
        // 如果 size < 2
        // 直接返回 -1
        // 否则，返回倒数第二大的数
        return res.size() < 2 ? -1 : *++res.crbegin();
    }
};
````

### Solution 2: 利用两个变量记录

````c++
class Solution {
public:
    int secondHighest(string s) {
        int first = -1;
        int second = -1;  // 初始化为 -1
        
        for (char c : s) {
            if (isdigit(c)) {
                int num = c - '0';
                
                if (num > first) {  // 如果比最大的大，两个都需要更新
                    second = first;
                    first = num;
                } else if (num > second && num < first) {  // 这里必须是严格的小于 first才可以
                    second = num;
                }
            }
        }
        
        return second;
    }
};
````

