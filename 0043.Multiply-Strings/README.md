# [43. Multiply Strings](https://leetcode.com/problems/multiply-strings/)

Given two non-negative integers `num1` and `num2` represented as strings, return the product of `num1` and `num2`, also represented as a string.

**Note:** You must not use any built-in BigInteger library or convert the inputs to integer directly.

 

**Example 1:**

```
Input: num1 = "2", num2 = "3"
Output: "6"
```

**Example 2:**

```
Input: num1 = "123", num2 = "456"
Output: "56088"
```

 

**Constraints:**

- `1 <= num1.length, num2.length <= 200`
- `num1` and `num2` consist of digits only.
- Both `num1` and `num2` do not contain any leading zero, except the number `0` itself.

## 题目大意

给定两个用字符串表示的非负整数 num1 和num2，用字符串返回二者的乘积，

## 解题思路

### 解法1（列竖式）

将 num2 的每一个位都与 num1 相乘，只能说这道题细节是魔鬼，

````c++
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1[0] == '0' || num2[0] == '0') {  // 处理边界情况
            return "0";
        }
        
        string res = "";
        for (int i = num2.size() - 1; i >= 0; i--) {
            int carry = 0;  // 保留进位
            
            string tmp = "";  // 保存中间结果
            // 补 '0'，用于后面做计算
            for (int j = 0; j < num2.size() - 1 - i; j++) {
                tmp.push_back('0');
            }
            
            int digit2 = num2[i] - '0'; // num2 当前的位数
            for (int k = num1.size() - 1; k >= 0 || carry != 0; --k) {
                int digit1 = k < 0 ? 0 : num1[k] - '0';
                int product = (digit1 * digit2 + carry) % 10;
                tmp += to_string(product);
                carry = (digit1 * digit2 + carry) / 10;
            }
            res = AddString(res, tmp);
        }
        return res;
    }
    
 private:
    // 将两个字符串相加
    string AddString(string& str1, string& str2) {
        reverse(str2.begin(), str2.end());
        
        string res = "";
        int carry = 0;
        
        for (int i = str1.size() - 1, j = str2.size() - 1;
            i >= 0 || j >= 0 || carry > 0; i--, j--) {
            int digit1 = i < 0 ? 0 : str1[i] - '0';
            int digit2 = j < 0 ? 0 : str2[j] - '0';
            int sum = digit1 + digit2 + carry;
            res += to_string(sum % 10);
            carry = sum / 10;
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};
````

### 解法2（优化后的列竖式）

这个思路并不好想，这里放上这篇思路的题解，可以看一下题解中的分析：https://leetcode-cn.com/problems/multiply-strings/solution/you-hua-ban-shu-shi-da-bai-994-by-breezean/

`````c++
class Solution {
 public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        
        vector<int> res(num1.size() + num2.size(), 0);
        for (int i = num1.size() - 1; i >= 0; i--) {
            int digit1 = num1[i] - '0';
            for (int j = num2.size() - 1; j >= 0; j--) {
                int digit2 = num2[j] - '0';
                int sum = res[i + j + 1] + (digit1 * digit2);
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }
        
        string ans = "";
        for (int i = 0; i < res.size(); i++) {
            if (i == 0 && res[i] == 0) {  // 这里跳过所有的前导0
                continue;
            }
            ans.push_back(res[i] + '0');
        }
        
        return string(it, res.end());
    }
};
`````

### 解法2

这里放上霜神的写法

`````c++
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1[0] == '0' || num2[0] == '0') {
            return "0";
        }

        const int len1 = num1.size();
        const int len2 = num2.size();
        vector<int> res(len1 + len2);
        for (int i = 0; i < len1; ++i) {
            for (int j = 0; j < len2; ++j) {
                // 将第 i 位和 第 j 位的乘积的结果，放在第 i + j + 1 位上
                res[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
            }
        }

        for (int i = len1 + len2 - 1; i > 0; --i) {
            // 处理进位
            res[i - 1] += res[i] / 10;
            res[i] %= 10;
        }

        // 处理前导0
        int i = 0;
        if (res[0] == 0) {
            ++i;
        }
        // 生成字符串
        string str = "";
        while (i < len1 + len2) {
            str += to_string(res[i]);
            ++i;
        }

        return str;
    }
};
`````

