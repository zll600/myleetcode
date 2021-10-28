# [1694. Reformat Phone Number](https://leetcode.com/problems/reformat-phone-number/)

## 题目

You are given a phone number as a string `number`. `number` consists of digits, spaces `' '`, and/or dashes `'-'`.

You would like to reformat the phone number in a certain manner. Firstly, **remove** all spaces and dashes. Then, **group** the digits from left to right into blocks of length 3 **until** there are 4 or fewer digits. The final digits are then grouped as follows:

- 2 digits: A single block of length 2.
- 3 digits: A single block of length 3.
- 4 digits: Two blocks of length 2 each.

The blocks are then joined by dashes. Notice that the reformatting process should **never** produce any blocks of length 1 and produce **at most** two blocks of length 2.

Return *the phone number after formatting.*

 

**Example 1:**

```
Input: number = "1-23-45 6"
Output: "123-456"
Explanation: The digits are "123456".
Step 1: There are more than 4 digits, so group the next 3 digits. The 1st block is "123".
Step 2: There are 3 digits remaining, so put them in a single block of length 3. The 2nd block is "456".
Joining the blocks gives "123-456".
```

**Example 2:**

```
Input: number = "123 4-567"
Output: "123-45-67"
Explanation: The digits are "1234567".
Step 1: There are more than 4 digits, so group the next 3 digits. The 1st block is "123".
Step 2: There are 4 digits left, so split them into two blocks of length 2. The blocks are "45" and "67".
Joining the blocks gives "123-45-67".
```

**Example 3:**

```
Input: number = "123 4-5678"
Output: "123-456-78"
Explanation: The digits are "12345678".
Step 1: The 1st block is "123".
Step 2: The 2nd block is "456".
Step 3: There are 2 digits left, so put them in a single block of length 2. The 3rd block is "78".
Joining the blocks gives "123-456-78".
```

**Example 4:**

```
Input: number = "12"
Output: "12"
```

**Example 5:**

```
Input: number = "--17-5 229 35-39475 "
Output: "175-229-353-94-75"
```

 

**Constraints:**

- `2 <= number.length <= 100`
- `number` consists of digits and the characters `'-'` and `' '`.
- There are at least **two** digits in `number`.

## 题目大意

给定一个字符串表示的电话号码 number，number 由数字、空格 ' ‘、和破折号 ‘-’ 组成。

按照一定格式重新格式化一个电话号码

- 首先，删除 所有的空格和破折号。
- 其次，将数组从左到右 每 3 个一组 分块，直到 剩下 4 个或更少数字。剩下的数字将按下述规定再分块：
  - 2 个数字：单个含 2 个数字的块。
  - 3 个数字：单个含 3 个数字的块。
  - 4 个数字：两个分别含 2 个数字的块。

最后用破折号将这些块连接起来。注意，重新格式化过程中 不应该 生成仅含 1 个数字的块，并且 最多 生成两个含 2 个数字的块。返回格式化后的电话号码。

## 解题思路

### Solution 1:

这种解法可以参考这篇题解：https://books.halfrost.com/leetcode/ChapterFour/1600~1699/1694.Reformat-Phone-Number/

根据题目要求，我们可以发现，字符串最终都会被划分为 3 元组和 2 元组，所以我们要解决的问题就是求出字符串中有多少 3 元组和 2 元组，

先预处理字符串，

然后得出字符串的长度是 3 的多少倍，然后根据 长度对3 取模调整3元组的数量和 2 元组的数量

````c++
class Solution {
public:
    string reformatNumber(string number) {
        // 去除字符串中所有空把和符号
        string num = "";
        for_each(number.begin(), number.end(), [&num](char c) {
            if (c != '-' && c != ' ') {
                num.push_back(c);
            }
        });
        // 如果是2，3，4的情况，直接返回
        if (num.size() == 2 || num.size() == 3) {
            return num;
        } else if (num.size() == 4) {
            num.insert(2, 1, '-');
            return num;
        }
        
        const int size = num.size();
        int three_digits = size / 3;  // 统计有多少对的3 元祖
        int two_digits = 0;  // 多少对的2 元组
        
        switch(size % 3) {  // 对三取余进行判断
            case 1:  // 如果为 1，说明应该有一个四元组，即两个二元组
                --three_digits;
                two_digits = 2;
                break;
            case 2:  // 如果为 2，说明应该有一个二元组
                two_digits = 1;
                break;
            default: // 否则没有二元组
                 two_digits = 0;
        }
        
        string res = "";  // 结果
        int idx = 0;  // 下标
        // 先切分出所有的三元组
        for (int i = 0; i < three_digits; ++i) {
            res += num.substr(idx, 3);  // 切分出一个长度为3的字符串
            idx += 3;  // 下标向右移动，指向下一组的第一个字符
            res += '-';  // 加上连字符
        }
        
        // 切分出所有的二元组
        for (int i = 0; i < two_digits; ++i) {
            res += num.substr(idx, 2);  // 切分出一个长度为 2 的字符串
            idx += 2;  // 下标向右移动，指向下一组的第一个字符
            res += '-';  // 加上连字符
        }
        res.pop_back();  // 删除最后一个多余的连字符
        
        return res;
    }
};
````



