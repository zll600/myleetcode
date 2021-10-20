# [468. Validate IP Address](https://leetcode-cn.com/problems/validate-ip-address/)

## 题目

Given a string `IP`, return `"IPv4"` if IP is a valid IPv4 address, `"IPv6"` if IP is a valid IPv6 address or `"Neither"` if IP is not a correct IP of any type.

**A valid IPv4** address is an IP in the form `"x1.x2.x3.x4"` where `0 <= xi <= 255` and `xi` **cannot contain** leading zeros. For example, `"192.168.1.1"` and `"192.168.1.0"` are valid IPv4 addresses but `"192.168.01.1"`, while `"192.168.1.00"` and `"192.168@1.1"` are invalid IPv4 addresses.

**A valid IPv6** address is an IP in the form `"x1:x2:x3:x4:x5:x6:x7:x8"` where:

- `1 <= xi.length <= 4`
- `xi` is a **hexadecimal string** which may contain digits, lower-case English letter (`'a'` to `'f'`) and upper-case English letters (`'A'` to `'F'`).
- Leading zeros are allowed in `xi`.

For example, "`2001:0db8:85a3:0000:0000:8a2e:0370:7334"` and "`2001:db8:85a3:0:0:8A2E:0370:7334"` are valid IPv6 addresses, while "`2001:0db8:85a3::8A2E:037j:7334"` and "`02001:0db8:85a3:0000:0000:8a2e:0370:7334"` are invalid IPv6 addresses.

 

**Example 1:**

```
Input: IP = "172.16.254.1"
Output: "IPv4"
Explanation: This is a valid IPv4 address, return "IPv4".
```

**Example 2:**

```
Input: IP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
Output: "IPv6"
Explanation: This is a valid IPv6 address, return "IPv6".
```

**Example 3:**

```
Input: IP = "256.256.256.256"
Output: "Neither"
Explanation: This is neither a IPv4 address nor a IPv6 address.
```

**Example 4:**

```
Input: IP = "2001:0db8:85a3:0:0:8A2E:0370:7334:"
Output: "Neither"
```

**Example 5:**

```
Input: IP = "1e1.4.5.6"
Output: "Neither"
```

 

**Constraints:**

- `IP` consists only of English letters, digits and the characters `'.'` and `':'`.

## 题目大意

编写一个函数来验证输入的字符串是否是有效的 IPv4 或 IPv6 地址。

* 如果是有效的 `IPv4` 地址，返回 `"IPv4"` ；
* 如果是有效的 `IPv6` 地址，返回 `"IPv6"` ；
* 如果不是上述类型的 `IP` 地址，返回 `"Neither"` 。

`IPv4` 地址由十进制数和点来表示，每个地址包含 4 个十进制数，其范围为 0 - 255， 用(".")分割。比如，172.16.254.1；

同时，`IPv4` 地址内的数不会以 0 开头。比如，地址 172.16.254.01 是不合法的。

`IPv6` 地址由 8 组 16 进制的数字来表示，每组表示 16 比特。这些组数字通过 (":")分割。比如,  `2001:0db8:85a3:0000:0000:8a2e:0370:7334` 是一个有效的地址。而且，我们可以加入一些以 0 开头的数字，字母可以使用大写，也可以是小写。所以， `2001:db8:85a3:0:0:8A2E:0370:7334` 也是一个有效的 `IPv6` address地址 (即，忽略 0 开头，忽略大小写)。

然而，我们不能因为某个组的值为 0，而使用一个空的组，以至于出现 (::) 的情况。 比如， `2001:0db8:85a3::8A2E:0370:7334` 是无效的 `IPv6` 地址。

同时，在 `IPv6` 地址中，多余的 0 也是不被允许的。比如， `02001:0db8:85a3:0000:0000:8a2e:0370:7334` 是无效的。

## 解题思路

这是一道字符串的模拟的题目，

这里列出几个注意的地方：

* 分割字符串：在分割完字符串之后，需要检查最后一个字符是否还是分割符，如果还是，多给数组中加入一个字符串，后面检查的时候，就可以直接返回
* 检查 IPv4:
  * 数组长度为 4
  * 每一组的长度不能为0，不能含有前导0，长度不能超过 3
  * 不能出现数字以外的字符
  * 数值必须在 [0, 255]
* 检查 IPv6:
  * 数组长度为 8
  * 每一组不能为空，长度不能超过4
  * 每一组只能含有十六进制数的表示方式，数值 0 - 9，小写字母 a - f，大写字母 A -F

就是细节比较多，仔细一点，

````c++
class Solution {
public:
    string validIPAddress(string IP) {
        if (IsIPv4(IP)) {
            return "IPv4";
        }
        if (IsIPv6(IP)) {
            return "IPv6";
        }
        return "Neither";
        
    }
    
 private:
    void Split(const string& str, vector<string>& ip, char delim) {
        stringstream ss(str);
        string tmp = "";
        while (getline(ss, tmp, delim)) {
            ip.push_back(tmp);
        }
        // 如果结尾字符是一个分割字符，则再加入一个空字符串
        if (!str.empty() && str.back() == delim) {
            ip.push_back({});
        }
    }
    
    bool IsIPv4(const string& str) {
        vector<string> ip;
        Split(str, ip, '.');
        // 划分为 4 
        if (ip.size() != 4) {
            return false;
        }
        
        for (const string& s : ip) {
            // 字符串为空
            // 字符串至少含有两个字符，但是有前导0
            // 字符串的长度大于 3
            if (s.empty() || (s.size() > 1 && s[0] == '0') || s.size() > 3) {
                return false;
            }
            for (char c : s) {
                // 不是数字直接返回
                if (!isdigit(c)) {
                    return false;
                }
            }
            
            int num = stoi(s);
            // 数值不合法直接返回
            if (num < 0 || num > 255) {
                return false;
            }
        }
        
        return true;
    }
    
    bool IsIPv6(const string& str) {
        vector<string> ip;
        Split(str, ip, ':');
        // 如果数目不是 8，直接返回
        if (ip.size() != 8) {
            return false;
        }
        
        for (const string& s : ip) {
            // 如果为空，或者长度大于等于 4
            if (s.empty() || s.size() > 4) {
                return false;
            }
            
            for (char c : s) {
                // 不是数字，且不是小写，且不是大写
                if (!isdigit(c) && (c < 'a' || c > 'f') && (c < 'A' || c > 'F')) {
                    return false;
                }
            }
        }
        return true;
    }
};
````

