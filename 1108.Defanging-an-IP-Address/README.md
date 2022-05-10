# [1108. Defanging an IP Address](https://leetcode.com/problems/defanging-an-ip-address/)

## 题目

Given a valid (IPv4) IP `address`, return a defanged version of that IP address.

A *defanged IP address* replaces every period `"."` with `"[.]"`.

 

**Example 1:**

```
Input: address = "1.1.1.1"
Output: "1[.]1[.]1[.]1"
```

**Example 2:**

```
Input: address = "255.100.50.0"
Output: "255[.]100[.]50[.]0"
```

 

**Constraints:**

- The given `address` is a valid IPv4 address.

## 题目大意

给你一个有效的 `IPv4` 地址 `address`，返回这个 `IP` 地址的无效化版本。

所谓无效化 IP 地址，其实就是用 `“[.]”` 代替了每个 `“."`

## 解题思路

按照题意来做就好了

### Solution 1:

这种解法直接使用 go 的api 来做

````Go
func defangIPaddr(address string) string {
    return strings.ReplaceAll(address, ".", "[.]");
}
````

### Solution 1:

这种解法使用 C++ 实现一个 replace 函数

````c++
class Solution {
public:
    string defangIPaddr(string address) {
        return Replace(address, ".", "[.]");
    }

 private:
    string Replace(string str, const string& old_str, const string& new_str) {
        auto pos = str.find_first_of(old_str, 0);
        while (pos != string::npos) {
            str.replace(pos, old_str.size(), new_str);
            pos += new_str.size();
            pos = str.find_first_of(old_str, pos);
        }
        return str;
    }
};
````
