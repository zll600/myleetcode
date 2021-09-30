# [8. String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/)

## 题目

Implement the `myAtoi(string s)` function, which converts a string to a 32-bit signed integer (similar to C/C++'s `atoi` function).

The algorithm for `myAtoi(string s)` is as follows:

1. Read in and ignore any leading whitespace.
2. Check if the next character (if not already at the end of the string) is `'-'` or `'+'`. Read this character in if it is either. This determines if the final result is negative or positive respectively. Assume the result is positive if neither is present.
3. Read in next the characters until the next non-digit charcter or the end of the input is reached. The rest of the string is ignored.
4. Convert these digits into an integer (i.e. `"123" -> 123`, `"0032" -> 32`). If no digits were read, then the integer is `0`. Change the sign as necessary (from step 2).
5. If the integer is out of the 32-bit signed integer range `[-231, 231 - 1]`, then clamp the integer so that it remains in the range. Specifically, integers less than `-231` should be clamped to `-231`, and integers greater than `231 - 1` should be clamped to `231 - 1`.
6. Return the integer as the final result.

**Note:**

- Only the space character `' '` is considered a whitespace character.
- **Do not ignore** any characters other than the leading whitespace or the rest of the string after the digits.

 

**Example 1:**

```
Input: s = "42"
Output: 42
Explanation: The underlined characters are what is read in, the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^
The parsed integer is 42.
Since 42 is in the range [-231, 231 - 1], the final result is 42.
```

**Example 2:**

```
Input: s = "   -42"
Output: -42
Explanation:
Step 1: "   -42" (leading whitespace is read and ignored)
            ^
Step 2: "   -42" ('-' is read, so the result should be negative)
             ^
Step 3: "   -42" ("42" is read in)
               ^
The parsed integer is -42.
Since -42 is in the range [-231, 231 - 1], the final result is -42.
```

**Example 3:**

```
Input: s = "4193 with words"
Output: 4193
Explanation:
Step 1: "4193 with words" (no characters read because there is no leading whitespace)
         ^
Step 2: "4193 with words" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "4193 with words" ("4193" is read in; reading stops because the next character is a non-digit)
             ^
The parsed integer is 4193.
Since 4193 is in the range [-231, 231 - 1], the final result is 4193.
```

**Example 4:**

```
Input: s = "words and 987"
Output: 0
Explanation:
Step 1: "words and 987" (no characters read because there is no leading whitespace)
         ^
Step 2: "words and 987" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "words and 987" (reading stops immediately because there is a non-digit 'w')
         ^
The parsed integer is 0 because no digits were read.
Since 0 is in the range [-231, 231 - 1], the final result is 0.
```

**Example 5:**

```
Input: s = "-91283472332"
Output: -2147483648
Explanation:
Step 1: "-91283472332" (no characters read because there is no leading whitespace)
         ^
Step 2: "-91283472332" ('-' is read, so the result should be negative)
          ^
Step 3: "-91283472332" ("91283472332" is read in)
                     ^
The parsed integer is -91283472332.
Since -91283472332 is less than the lower bound of the range [-231, 231 - 1], the final result is clamped to -231 = -2147483648.
```

 

**Constraints:**

- `0 <= s.length <= 200`
- `s` consists of English letters (lower-case and upper-case), digits (`0-9`), `' '`, `'+'`, `'-'`, and `'.'`.

## 题目大意

实现一个将字符串转化为整数的函数，将一个字符串转化为一个三十二位的有符号整数

函数 myAtoi(string s) 的功能如下：

* 读入并取消所有的前导空格，
* 检查下一个字符（加入没有到达最后一个字符）为正号还是为负号，这将决定最后的结果是正数还是负数，如果二者都不存在，则认为结果是正数，
* 读取下一个字符，知道遇到非数字字符或者到达输入的结尾，之后的字符全部舍弃
* 将前面步骤读入的这些数字转换为整数（即，“123” -> 123， “0032” -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
* 如果整数数超过 32 位有符号整数范围 [−231, 231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为 −231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。
* 返回最终的整数结果

本题中的空白字符只包括空格字符 ' ' 。

除**前导空格**或**数字后的其余字符串**外，请勿忽略 任何其他字符。

## 解题思路

按照题目给出的要求，按顺序遍历所有字符，

### 解法1

这种解法就是按照题目的要求来一步一部处理数据，可以参考这篇题解：https://leetcode-cn.com/problems/string-to-integer-atoi/solution/jin-liang-bu-shi-yong-ku-han-shu-nai-xin-diao-shi-/

````c++
class Solution {
public:
    int myAtoi(string str) {
        int start = 0;
        
        // 除去前导空格
        while (start < str.size() && str[start] == ' ') {
            start++;
        }
        // 测试特殊情况，
        if (start == str.size()) {
            return 0;
        }
        
        // 确定正负号，
        // 注意这里要小心，如果没有正负号，默认为正，而且下标是不移动
        int sign = 1;  // 1 表示正数， -1 表示负数
        if (str[start] == '+') {
            start++;
        } else if (str[start] == '-') {
            sign = -1;
            start++;
        }
        
        // 接下来开始对所有的数字字符进行匹配
        int res = 0;
        // 检查下标以及是否合法
        while (start < str.size() && isdigit(str[start])) {
            // 注意这里是带符号的运算
            int cur = (str[start] - '0') * sign;  // 这里计算当前位置的数转化之后得到的十进制数
            
            // 因为有可能会溢出（甚至用 long也会），所以我们在循环的过程中进行判断
            // 正溢出
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && cur > INT_MAX % 10)) {
                return INT_MAX;
            }
            
            // 负溢出
            if (res < INT_MIN / 10 || (res == INT_MIN / 10 && cur < INT_MIN % 10)) {
                return INT_MIN;
            }
            
            res = res * 10 + cur;  // 注意这里加之前一定要乘符号位
            start++;
        }
        
        return res;
    }
};
````

