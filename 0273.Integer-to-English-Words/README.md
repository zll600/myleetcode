# [273. Integer to English Words](https://leetcode.com/problems/integer-to-english-words/)

## 题目

Convert a non-negative integer `num` to its English words representation.

 

**Example 1:**

```
Input: num = 123
Output: "One Hundred Twenty Three"
```

**Example 2:**

```
Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"
```

**Example 3:**

```
Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
```

**Example 4:**

```
Input: num = 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
```

 

**Constraints:**

- `0 <= num <= 231 - 1`

## 题目大意

将一个非负整数转化为英语的表达形式

## 解题思路

## 解法1（分治）

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/integer-to-english-words/solution/273-cji-hu-shuang-bai-de-de-fen-zhi-jie-82v4g/

从后往前，三个一组进行转化，最后，将结果拼接起来

对于每组三位数：

* 0-20中，0应是一个空字符，除了数字本身是0，其他不会读出 0
* 21 - 99 需要一个表示 “几十” 的数和一个个位数字 
* 100-999，百位是 1-9 + “ Hundren”（这里有一个空格），后面加上 0-99 的转化

这里用 index 表示转化了几组 三位数

`````c++
class Solution {
public:
    string numberToWords(int num) {
        if (num == 0) {
            return "Zero";  // 边界情况
        }
        
        string res = "";  // 存储结果字符串
        int index = 0;  // 从后往前读
        while (num > 0) {
            // 这里忽略可以整除的情况，留到下一次再算
            if (num % 1000 > 0) {  // 可以取三位
                if (index == 0) {  // 倒序遍历的第几组
                    res = Helper(num % 1000);
                } else {
                    res = Helper(num % 1000) + " " + thousands[index] + (res == "" ? "" : (" " + res));
                }
            }
            num /= 1000;
            ++index;
        }
        
        return res;
    }
    
 private:
    // 注意这里不能存 "Zero"，否则，答案里可能会多 "Zero"
    vector<string> lowers = { "", "One", "Two", "Three", "Four", "Five", "Six",
                            "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve",
                            "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                                            "Eighteen", "Nineteen" };
    vector<string> tens = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty",                                                              "Seventy", "Eighty", "Ninety"};
    vector<string> thousands = { "", "Thousand", "Million", "Billion" };
    
    // 处理三位数字
    string Helper(int num) {
        if (num < 20) {
            return lowers[num];
        } else if (num >= 20 && num <= 99) {
            return tens[num / 10] + ((num%10) == 0 ? "" : (" " + lowers[num % 10]));
        } else {
            string lower = Helper(num % 100);
            return lowers[num / 100] + " Hundred"  + (lower == "" ? "" : (" " + lower));
        }
    }
};
`````

