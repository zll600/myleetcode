# [12. Integer to Roman](https://leetcode.com/problems/integer-to-roman/)

## 题目

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D` and `M`.

```
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

For example, `2` is written as `II` in Roman numeral, just two one's added together. `12` is written as `XII`, which is simply `X + II`. The number `27` is written as `XXVII`, which is `XX + V + II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not `IIII`. Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as `IX`. There are six instances where subtraction is used:

- `I` can be placed before `V` (5) and `X` (10) to make 4 and 9. 
- `X` can be placed before `L` (50) and `C` (100) to make 40 and 90. 
- `C` can be placed before `D` (500) and `M` (1000) to make 400 and 900.

Given an integer, convert it to a roman numeral.

 

**Example 1:**

```
Input: num = 3
Output: "III"
```

**Example 2:**

```
Input: num = 4
Output: "IV"
```

**Example 3:**

```
Input: num = 9
Output: "IX"
```

**Example 4:**

```
Input: num = 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.
```

**Example 5:**

```
Input: num = 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
```

 

**Constraints:**

- `1 <= num <= 3999`

## 题目大意

罗马数字由 7种不同的符号组成，通常时按照从左到右，从大到小的顺序来写，然而数字 4 不是 `IIII`，而是`IX`，因为 1 比 5 小，我们用 5 减去 1 可以得到 4，同样的规则也适合于 9，被写作 `IX`，这里用应用这种减法规则的六个特例，：

* `I` 可以放在 `V (5)` 和 `X (10)` 的左边，来表示 4 和 9。
* `X` 可以放在 `L (50)` 和 `C (100)` 的左边，来表示 40 和 90。 
* `C` 可以放在 `D (500)` 和 `M (1000)` 的左边，来表示 400 和 900。

给定一个整数，将其转化为罗马数字

## 解题思路

* 这道题目可以利用贪心算法来求解，优先选择较大的数字（可以类比兑换零钱时，优先使用最大的面值，则最终使用的钱数最少）。

  下面列出所有表示的组合，其余组合都是基于这些组合

  | 罗马数字 | 阿拉伯数字 |
  | -------- | ---------- |
  | M        | 1000       |
  | CM       | 900        |
  | D        | 500        |
  | CD       | 400        |
  | C        | 100        |
  | XC       | 90         |
  | L        | 50         |
  | XL       | 40         |
  | X        | 10         |
  | IX       | 9          |
  | V        | 5          |
  | IV       | 4          |
  | I        | 1          |

  贪心算法的证明比较难，这里放上一篇题解：

  https://leetcode-cn.com/problems/integer-to-roman/solution/tan-xin-suan-fa-by-liweiwei1419/

### Solution 1:

`````c++
class Solution {
public:
    string intToRoman(int num) {
        // 为了遍历时，优先使用最大的，这里按照降序排序数组元素，列出了所有最基本的组合
        vector<int> values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> symbols = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        
        string res = "";
        for (int i = 0; i < values.size(); ++i) {
            while (num >= values[i]) {  // 这里有个等号，不要忘记
                res += symbols[i];
                num -= values[i];
            }
        }
        
        return res;
    }
};
`````

### Solution 2:

这种解法和上面的差不多，但是这里将常量数组不再放在成员函数中，更合理一点

````c++
class Solution {
public:
    string intToRoman(int num) {
        string ans = "";

        int idx = 0;
        while (idx < 13) {
            while (num >= nums[idx]) {
                ans += romans[idx];
                num -= nums[idx];
            }
            ++idx;
        }
        return ans;
    }

 private:
    vector<int> nums = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    vector<string> romans = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
};
````
