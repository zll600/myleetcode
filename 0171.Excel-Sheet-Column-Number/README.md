# [171. Excel Sheet Column Number](https://leetcode.com/problems/excel-sheet-column-number/)

## 题目

Given a string `columnTitle` that represents the column title as appear in an Excel sheet, return *its corresponding column number*.

For example:

```
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...
```

 

**Example 1:**

```
Input: columnTitle = "A"
Output: 1
```

**Example 2:**

```
Input: columnTitle = "AB"
Output: 28
```

**Example 3:**

```
Input: columnTitle = "ZY"
Output: 701
```

**Example 4:**

```
Input: columnTitle = "FXSHRXW"
Output: 2147483647
```

 

**Constraints:**

- `1 <= columnTitle.length <= 7`
- `columnTitle` consists only of uppercase English letters.
- `columnTitle` is in the range `["A", "FXSHRXW"]`.

## 题目大意

给你一个字符串 `columnTitle` ，表示 Excel 表格中的列名称。返回该列名称对应的列序号。

## 解题思路

这道题的思路类似于将一个十进制的字符串转化为整数的

### 解法1

这道题进行的是 26 进制。

`````c++
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int res = 0;
        
        // 这里就是利用了 26 进制的转换
        for (char c : columnTitle) {
            res = res * 26 + static_cast<int>(c - 'A' + 1);
        }
        
        return res;
    }
};
`````



