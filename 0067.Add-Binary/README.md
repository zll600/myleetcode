# [67. Add Binary](https://leetcode.com/problems/add-binary/)

## 题目

Given two binary strings `a` and `b`, return *their sum as a binary string*.

 

**Example 1:**

```
Input: a = "11", b = "1"
Output: "100"
```

**Example 2:**

```
Input: a = "1010", b = "1011"
Output: "10101"
```

 

**Constraints:**

- `1 <= a.length, b.length <= 104`
- `a` and `b` consist only of `'0'` or `'1'` characters.
- Each string does not contain leading zeros except for the zero itself.

## 题目大意

给定两个二进制字符串，按照二进制字符串的格式返回二者相加后的结果

## 解题思路

### Solution 1:

这种解法，先将所有的字符串转化为数字，相加得到结果后，在转化为二进制字符串

但是对于这道题目来说，会溢出

````c++
class Solution {
public:
    string addBinary(string a, string b) {
        long long a_dec = 0;
        for (char c : a) {
            a_dec = a_dec * 2 + (c - '0');
        }
        long long b_dec = 0;
        for (char c : b) {
            b_dec = b_dec * 2 + (c - '0');
        }
        
        long long sum = a_dec + b_dec;
        // cout << a_dec << " " << b_dec << " " << sum << endl;
        if (sum == 0) {
            return "0";
        }
        string str = "";
        while (sum) {
            str = to_string(sum % 2) + str;
            sum /= 2;
        }
        
        return str;
    }
};
````



### Solution 2:

这道题目可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0001~0099/0067.Add-Binary/，

这道题目可作为进制转化的一道入门题目来做

```c++
class Solution {
public:
    string addBinary(string a, string b) {
        if (a.size() < b.size()) {  // 始终让 a 是比较长的那一个
            swap(a, b);
        }
        const int len1 = a.size();
        const int len2 = b.size();
        
        vector<char> res(len1 + 1, 0);  // 比最长的字符串长1，存储进位
        int k = len1;
        int i = len1 - 1;
        int j = len2 - 1;
        int carry = 0;
        while (i >= 0 || j >= 0 || carry > 0) {  // 直到遍历完所有
            int first = i >= 0 ? a[i] - '0' : 0;
            int second = j >= 0 ? b[j] - '0' : 0;
            
            res[k] = (first + second + carry) % 2 + '0';
            // cout << res[k] << endl;
            carry = (first + second + carry) / 2 ;
            --i;
            --j;
            --k;
        }
        // 如果第一位为0，则说明不需要第一位，跳过
        return string(res[0] == 0 ? res.begin() + 1 : res.begin(), res.end());
    }
};
```

