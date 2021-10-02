# [168. Excel Sheet Column Title](https://leetcode.com/problems/excel-sheet-column-title/)

## 题目

Given an integer `columnNumber`, return *its corresponding column title as it appears in an Excel sheet*.

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
Input: columnNumber = 1
Output: "A"
```

**Example 2:**

```
Input: columnNumber = 28
Output: "AB"
```

**Example 3:**

```
Input: columnNumber = 701
Output: "ZY"
```

**Example 4:**

```
Input: columnNumber = 2147483647
Output: "FXSHRXW"
```

 

**Constraints:**

- `1 <= columnNumber <= 231 - 1`

## 题目大意

给定一个整数 `columnNumber` ，返回它在 Excel 表中相对应的列名称

## 解题思路

### 解法1

这道题目其实可以看作是从 1 开始的 26 进制转化，对于一般的进制转化问题其取值范围大多都是 [0, n)，但对于这道题目来说，确实 (0, n],因此在操作的时候，我们需要作减一的操作，

`````c++
class Solution {
public:
    string convertToTitle(int columnNumber) {
        string res = "";
        
        while (columnNumber) {
            columnNumber--;  // 先减一
            res += static_cast<char>(columnNumber % 26 + 'A');  // 进行转化
            columnNumber /= 26;
        }
        
        // 取反
        reverse(res.begin(), res.end());
        
        return res;
    }
};
`````

