# [166. Fraction to Recurring Decimal](https://leetcode-cn.com/problems/fraction-to-recurring-decimal/)

## 题目

Given two integers representing the `numerator` and `denominator` of a fraction, return *the fraction in string format*.

If the fractional part is repeating, enclose the repeating part in parentheses.

If multiple answers are possible, return **any of them**.

It is **guaranteed** that the length of the answer string is less than `104` for all the given inputs.

 

**Example 1:**

```
Input: numerator = 1, denominator = 2
Output: "0.5"
```

**Example 2:**

```
Input: numerator = 2, denominator = 1
Output: "2"
```

**Example 3:**

```
Input: numerator = 2, denominator = 3
Output: "0.(6)"
```

**Example 4:**

```
Input: numerator = 4, denominator = 333
Output: "0.(012)"
```

**Example 5:**

```
Input: numerator = 1, denominator = 5
Output: "0.2"
```

 

**Constraints:**

- `-231 <= numerator, denominator <= 231 - 1`
- `denominator != 0`

## 题目大意

给定两个整数，分别表示分数的分子 `numerator` 和分母 `denominator`，以 **字符串形式返回小数** 

如果小数部分为循环小数，则将循环的部分括在括号内。

如果存在多个答案，只需返回 **任意一个** 

对于所有给定的输入，**保证** 答案字符串的长度小于 `104` 。

## 解题思路

这道题的就是模拟竖式运算，在计算的过程中，对余数乘 10 然后再做除法，可以得到小数部分

### Solution 1:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/fraction-to-recurring-decimal/solution/gong-shui-san-xie-mo-ni-shu-shi-ji-suan-kq8c4/

这种解法，利用上面的思想，并且利用一个哈希表来做记录，如果出现循环，说明出现了重复，另外这里还有几个问题

* 整数溢出的处理
* 正负数的处理

````c++
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        // 避免溢出，先对分子、分母坐整型提升
        long numer = numerator;
        long denom = denominator;
        // 如果可以整除的话，直接返回即可
        if (numer % denom == 0) {
            return to_string(numer / denom);
        }
        
        // 根据二者的乘积来决定结果的正负
        string res = numer * denom < 0 ? "-" : "";
        // 后面不能受符号影响
        numer = abs(numer);
        denom = abs(denom);
        res += to_string(numer / denom) + ".";  // 添加整数部分，和小数点
        numer %= denom;
        // 存储的是余数出现和 字符串的起始位置的映射
        unordered_map<int, int> record;
        
        while (numer != 0) {
            record.emplace(numer, res.size()); // 做记录
            numer *= 10; // 乘 10
            res += to_string(numer / denom); // 做除法
            numer %= denom; // 取余
            
            if (record.find(numer) != record.end()) {
                // 如果之前已经出现过，说明已经找到了循环
                int idx = record.at(numer);
                return res.substr(0, idx) + "(" + res.substr(idx) + ")";  
            }
        }
        return res;
    }
};
````

