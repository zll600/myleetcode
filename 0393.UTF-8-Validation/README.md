# [393. UTF-8 Validation](https://leetcode.com/problems/utf-8-validation/)

## 题目

Given an integer array `data` representing the data, return whether it is a valid **UTF-8** encoding.

A character in **UTF8** can be from **1 to 4 bytes** long, subjected to the following rules:

1. For a **1-byte** character, the first bit is a `0`, followed by its Unicode code.
2. For an **n-bytes** character, the first `n` bits are all one's, the `n + 1` bit is `0`, followed by `n - 1` bytes with the most significant `2` bits being `10`.

This is how the UTF-8 encoding would work:

```
   Char. number range  |        UTF-8 octet sequence
      (hexadecimal)    |              (binary)
   --------------------+---------------------------------------------
   0000 0000-0000 007F | 0xxxxxxx
   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
```

**Note:** The input is an array of integers. Only the **least significant 8 bits** of each integer is used to store the data. This means each integer represents only 1 byte of data.

 

**Example 1:**

```
Input: data = [197,130,1]
Output: true
Explanation: data represents the octet sequence: 11000101 10000010 00000001.
It is a valid utf-8 encoding for a 2-bytes character followed by a 1-byte character.
```

**Example 2:**

```
Input: data = [235,140,4]
Output: false
Explanation: data represented the octet sequence: 11101011 10001100 00000100.
The first 3 bits are all one's and the 4th bit is 0 means it is a 3-bytes character.
The next byte is a continuation byte which starts with 10 and that's correct.
But the second continuation byte does not start with 10, so it is invalid.
```

 

**Constraints:**

- `1 <= data.length <= 2 * 104`
- `0 <= data[i] <= 255`

## 题目大意

给定一个整数数组 data表示数据，判断其是否是有效的 utf-8 编码。

根据以下规则，一个字符按照 `utf-8` 可以编码为 `1` 到` 4 `个字符

* 对于 1 字节字符串，第一个 `bit` 为0，其余为它的 `unicode` 表示
* 对于 n 字节的字符 `(n > 1)`，第一个字节的前 `n` 位都设为`1`，第 `n+1` 位设为 `0` ，后面字节的前两位一律设为 10 。剩下的没有提及的二进制位，全部为这个符号的 unicode 码。

````
 Char. number range  |        UTF-8 octet sequence
      (hexadecimal)    |              (binary)
   --------------------+---------------------------------------------
   0000 0000-0000 007F | 0xxxxxxx
   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
````

注意: 输入是整数数组。只有每个整数的最低 8 个有效位用来存储数据。这意味着每个整数只表示 1 字节的数据

## 解题思路

这道题我的思路是，给定数据可以有多组字符的编码，所以对每一组进行判断，

* 判断第一个字节，确定后面的编码方式
* 利用临界值来做判断

### Solution 1:

这种解法可以参考霜神的解法：https://books.halfrost.com/leetcode/ChapterFour/0300~0399/0393.UTF-8-Validation/



```c++
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int count = 0;
        for (int d : data) {
            if (count == 0) {
                if (d >= 248) { // 11111000 = 248
                    return false;
                } else if (d >= 240) { // 11110000 = 240
                    count = 3;
                } else if (d >= 224) { // 11100000 = 224
                    count = 2;
                } else if (d >= 192){ // 11000000 = 198
                    count = 1;
                } else if (d > 127) { // 01111111 = 127
                    return false;
                }
            } else {
                if (d <= 127 || d >= 192) {
                    return false;
                }
                --count;
            }
        }
        
        return count == 0;
    }
};
```

