# [93. Restore IP Addresses](https://leetcode.com/problems/restore-ip-addresses/)

## 题目

Given a string `s` containing only digits, return all possible valid IP addresses that can be obtained from `s`. You can return them in **any** order.

A **valid IP address** consists of exactly four integers, each integer is between `0` and `255`, separated by single dots and cannot have leading zeros. For example, "0.1.2.201" and "192.168.1.1" are **valid** IP addresses and "0.011.255.245", "192.168.1.312" and "192.168@1.1" are **invalid** IP addresses. 

 

**Example 1:**

```
Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]
```

**Example 2:**

```
Input: s = "0000"
Output: ["0.0.0.0"]
```

**Example 3:**

```
Input: s = "1111"
Output: ["1.1.1.1"]
```

**Example 4:**

```
Input: s = "010010"
Output: ["0.10.0.10","0.100.1.0"]
```

**Example 5:**

```
Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
```

 

**Constraints:**

- `0 <= s.length <= 3000`
- `s` consists of digits only.

## 题目大意

给定一个只包含数字的字符串，复原并返回所有可能出的 IP 地址

## 解题思路

* 这道题目可以利用回溯法来解决，问题的难点在于剪枝的条件，真的不是很好想

## 代码

````c++
class Solution {
 public:    
    vector<string> restoreIpAddresses(string s) {
        DFS(s, 0);
        return res;
    }
    
 private:
    vector<string> res;
    vector<int> ip;
    
    string GetString() {
        string str = to_string(ip[0]);
        for (int i = 1; i < ip.size(); ++i) {
            str += '.';
            str += to_string(ip[i]);
        }
        return str;
    }
    
    void DFS(const string& str, int idx) {  // 将四个元素转化位字符串，
        if (idx == str.size()) {
            if (ip.size() == 4) {
                res.push_back(GetString());
            }
            return;
        }
        
        if (idx == 0) { // 第一个数字，直接加入进 ip中
            int num = str[idx] - '0';
            ip.push_back(num);
            DFS(str, idx + 1);
        } else {    // 先将当前递归到的数字加入到
            int num = str[idx] - '0';
            int next = ip.back() * 10 + num;
            if (next <= 255 && ip.back() != 0) { // 新的数字小于255，且不是以 0 开头，就可以继续递归
                ip[ip.size() - 1] = next;
                DFS(str, idx + 1);
                ip[ip.size() - 1] /= 10;    // 去掉当前递归到的数字，不能删除最后一个元素（可能是多层递归的结果）
            }
            
            if (ip.size() < 4) {    // 如果不能和上一段加在一起，而且可以新创建一个段，就新创建一个段
                ip.push_back(num);
                DFS(str, idx + 1);
                ip.pop_back();
            }
        }
    }
};
````



