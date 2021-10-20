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
* 建议自己把递归数画出来，去查看题目中有那些要求，
* 这道题一定要注意剪枝

### Solution:

````c++
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.size() < 4 || s.size() > 12) {
            return vector<string>();
        }
        
        DFS(s, 0);
        return res_;
    }

 private:
    vector<string> res_;
    vector<int> ip_;
    
    // 将 ip 结果转化为字符串
    string GetString(const vector<int>& ip) {
        string str = to_string(ip[0]);
        for (int i = 1; i < 4; ++i) {
            str += '.';
            str += to_string(ip[i]);
        }

        return str;
    }

    void DFS(const string& str, int idx) {
        // 终止条件
        if (idx == str.size()) {
            if (ip_.size() == 4) {
                res_.push_back(GetString(ip_));
            }
            return;
        }

        if (idx == 0) {  // 遍历第一个字母直接加入
            ip_.push_back(str[0] - '0');
            DFS(str, idx + 1);
        } else {
            int num = str[idx] - '0';
            int next = ip_.back() * 10 + num;
            
            // 检查能否合并
            // 1. 合并后的值在范围内
            // 2. 上一个数不能为0，为0 不能合并
            if (next <= 255 && ip_.back() != 0) {
                ip_[ip_.size() - 1] = next;  // 更新
                DFS(str, idx + 1);
                ip_[ip_.size() - 1] /= 10;  // 回溯
            }

            if (ip_.size() < 4) {  // 如果没有解析完毕继续解析
                ip_.push_back(str[idx] - '0');  // 加入
                DFS(str, idx + 1);
                ip_.pop_back();  // 撤销
            }
        }
    }
};
````



