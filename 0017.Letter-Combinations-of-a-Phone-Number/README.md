# [17. Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)

## 题目

Given a string containing digits from `2-9` inclusive, return all possible letter combinations that the number could represent. Return the answer in **any order**.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-keypad2.svg/200px-Telephone-keypad2.svg.png)

 

**Example 1:**

```
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
```

**Example 2:**

```
Input: digits = ""
Output: []
```

**Example 3:**

```
Input: digits = "2"
Output: ["a","b","c"]
```

 

**Constraints:**

- `0 <= digits.length <= 4`
- `digits[i]` is a digit in the range `['2', '9']`.

## 题目大意

* 给定一个包含数字2-9的字符串，返回这个数字表示的所有字母的组合，1 不对应任何字母

## 解题思路

* 这是一道组合题目，可以使用回溯法来解决，终止条件是取够了数字个字母，

## 代码

````c++
class Solution {
public:
    const vector<string> dict = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz" // 9
    };
    
    // 回溯法
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return res;
        }
        
        Backtracking(digits, 0);
        
        return res;
    }
    
 private:
    vector<string> res;
    string path;
    
    void Backtracking(string& digits, int idx) {
        if (idx == digits.size()) {
            res.push_back(path);
            return;
        }
        
        int digit = digits[idx] - '0';
        string letters = dict[digit];
        int size = letters.size();
        for (int i = 0; i < size; ++i) {
            path.append(1, letters[i]);
            Backtracking(digits, idx + 1);
            path.pop_back();
        }
    }
};
````

