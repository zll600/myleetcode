# [6. ZigZag Conversion](https://leetcode.com/problems/zigzag-conversion/)

## 题目

The string `"PAYPALISHIRING"` is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

```
P   A   H   N
A P L S I I G
Y   I   R
```

And then read line by line: `"PAHNAPLSIIGYIR"`

Write the code that will take a string and make this conversion given a number of rows:

```
string convert(string s, int numRows);
```

 

**Example 1:**

```
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
```

**Example 2:**

```
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
```

**Example 3:**

```
Input: s = "A", numRows = 1
Output: "A"
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `s` consists of English letters (lower-case and upper-case), `','` and `'.'`.
- `1 <= numRows <= 1000`

## 题目大意

给定一个字符串，将这个字符串按照从上到下，从左到右进行展示

比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：

````P   A   H   N
P   A   H   N
A P L S I I G
Y   I   R
````

之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。

请你实现这个将字符串进行指定行数变换的函数：

`string convert(string s, int numRows);`

## 解题思路

### 解法1

这道题我想不出来什么高效的解法唯一的办法就是只能模拟，用两个变量保持两个方向，一个水平方向，一个竖直方向

* 这道题我们在做到时候，一定要区分我们看到的数据的表达形式，和我们存储是使用的数据结构的区别，在这道题中，我们用的是每个一维数组不一定等长的二维数组来表示，所以实际上每行的字符之间是没有空格的，这里建议自己动手画一下图，会比较清晰
* 很明显，我们要做的就是填充这个二维的字符数组

````c++
class Solution {
public:
    string convert(string str, int numRows) {
        if (str.size() < numRows || numRows < 2) {
            return str;
        }
        
        vector<string> strs(numRows, "");
        int row = 0;
        int down = -1;
        
        for (char c : str) {
            strs[row].push_back(c);
            if (row == 0 || row == numRows - 1) {
                down *= -1;
            }
            row += down;
        }
        
        string res = "";
        for (const string& it : strs) {
            res += it;
        }
        
        return res;
    }
};
````

#### 解法2

这种方法就是利用规律先填满每一行，在填充的过程中不断加记录到最终的结果中去

````c++
class Solution {
public:
    string convert(string str, int numRows) {
        if (str.size() < numRows || numRows < 2) {
            return str;
        }
        
        int step = numRows * 2 - 2;  // 间距
        int idx = 0;  // 记录str的下标
        int size = str.size();
        int add = 0;  // 真实的间距
        string res;
        
        for (int i = 0; i < numRows; i++) {  // i 表示行号
            idx = i;
            add = i * 2;
            while (idx < size) {  // 超出字符篡改长度
                res += str[idx];  // 当前行的第一个字母
                add = step - add;  // 第一次间距是 step - 2 * i，第二次是 2 * i
                idx += (i == 0 || i == numRows - 1) ? step : add;
            }
        }
        
        return res;
    }
};
````





