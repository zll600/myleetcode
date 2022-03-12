# [592. Fraction Addition and Subtraction](https://leetcode-cn.com/problems/fraction-addition-and-subtraction/)

## 题目

Given a string `expression` representing an expression of fraction addition and subtraction, return the calculation result in string format.

The final result should be an [irreducible fraction](https://en.wikipedia.org/wiki/Irreducible_fraction). If your final result is an integer, change it to the format of a fraction that has a denominator `1`. So in this case, `2` should be converted to `2/1`.

 

**Example 1:**

```
Input: expression = "-1/2+1/2"
Output: "0/1"
```

**Example 2:**

```
Input: expression = "-1/2+1/2+1/3"
Output: "1/3"
```

**Example 3:**

```
Input: expression = "1/3-1/2"
Output: "-1/6"
```

 

**Constraints:**

- The input string only contains `'0'` to `'9'`, `'/'`, `'+'` and `'-'`. So does the output.
- Each fraction (input and output) has the format `±numerator/denominator`. If the first input fraction or the output is positive, then `'+'` will be omitted.
- The input only contains valid **irreducible fractions**, where the **numerator** and **denominator** of each fraction will always be in the range `[1, 10]`. If the denominator is `1`, it means this fraction is actually an integer in a fraction format defined above.
- The number of given fractions will be in the range `[1, 10]`.
- The numerator and denominator of the **final result** are guaranteed to be valid and in the range of **32-bit** int.

## 题目大意

给定一个表示分数加减运算的字符串 `expression` ，你需要返回一个字符串形式的计算结果。 

这个结果应该是不可约分的分数，即最简分数。 如果最终结果是一个整数，例如 `2`，你需要将它转换成分数形式，其分母为 `1`,所以在上述例子中, `2` 应该被转换为 `2/1`

## 解题思路

开始的思路就是模拟通分，然后将分子进行加减运算得出最终结果，之后再进行化简



### Solution 1:

这里将分子和分母分组之后分别进行计算，然后进行通分，再进行计算，这里还需要注意符号的问题


````c++
class Solution {
 public:
    string fractionAddition(string expression) {
        // 将分母和分子分别解析出来
        vector<int> numerators;
        vector<int> denominators;

        const int len = expression.size();
        int i = 0;
        while (i < len) {
            // 解析分子
            // 判断分子的符号
            bool numerator_is_neg = false;
            if (expression[i] == '-') {
                numerator_is_neg = true;
                ++i;
            } else if (expression[i] == '+') {
                ++i;
            }

            // 解析分子
            int numerator = 0;
            while (isdigit(expression[i])) {
                numerator = numerator * 10 + (expression[i] - '0');
                ++i;
            }
            // 改变符号
            if (numerator_is_neg) {
                numerator *= -1;
            }
            // 跳过 '/'
            ++i;

            numerators.push_back(numerator);

            // 解析分母，这里注意下标可能会越界
            int denominator = 0;
            while (i < len && isdigit(expression[i])) {
                denominator = denominator * 10 + (expression[i] - '0');
                ++i;
            }

            denominators.push_back(denominator);
        }

        // 所有分母的积
        long denominator_multi = 1;
        for_each(denominators.begin(), denominators.end(), [&](int num) {
            denominator_multi *= num;
        });

        // 分子通分之后的结果
        long numerator_sum = 0;
        const int size = numerators.size();
        for (int i = 0; i < size; ++i) {
            numerator_sum += numerators[i] * (denominator_multi / denominators[i]);
        }

        // 最大公约数，这里注意取绝对值
        int tmp = abs(GCD(numerator_sum, denominator_multi));
        // 如果负数
        bool is_neg = numerator_sum < 0 || denominator_multi < 0;
        string res = is_neg ? "-" : "";
        // 这里注意取绝对值
        res += to_string(abs(numerator_sum) / tmp) + '/' + to_string(abs(denominator_multi) / tmp);

        return res;
    }

 private:
    long GCD(long a, long b) {
        return b ? GCD(b, a % b) : a;
    }
};
````

