# [14. Longest Common Prefix](https://leetcode.com/problems/longest-common-prefix/)

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string `""`.

 

**Example 1:**

```
Input: strs = ["flower","flow","flight"]
Output: "fl"
```

**Example 2:**

```
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
```

 

**Constraints:**

- `1 <= strs.length <= 200`
- `0 <= strs[i].length <= 200`
- `strs[i]` consists of only lower-case English letters.

## 题目大意

编写一个函数，寻找最长的公共前缀，

如果没有公共前缀，返回一个空字符串

## 解题思路

这道题知道需要遍历所有的字符串一遍

### 解法1（暴力匹配）

选取任意一个字符串作为前缀开始匹配，这里选的是第一个，每次匹配从后往前进行匹配，必须遍历两个字符串，不能只遍历局部，更多细节，可以参考代码中的注释

这种办法是字符串两两进行比较，

`````c++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res = strs[0];
        int last = strs[0].size() - 1;  // 初始化字符串的最后一字符
        
        for (int i = 1; i < strs.size(); i++) {
            last = Match(res, last, strs[i]);
            if (last < 0) {
                return "";
            }
        }
        
        return res.substr(0, last + 1);  // 只在这一步才需要截取出字符串，可以减少空间消耗
    }
    
 private:
    // 这里从后向前进行匹配
    int Match(const string& prefix, int last, const string& match) {
        int size = match.size();  // 这里不能直接和 last 进行比较，二者的类型不匹配不能直接调研那个 min() 函数取最小值
        int i = min(last, size - 1);  // 选择较短的字符串的最后一个下标作为起点
        
        last = i;
        while (i >= 0) {  // 这里必须遍历两个字符串的公共长度，防止出现 'cir' 和 'car' 这种两端匹配，中间不匹配
            if (prefix[i] != match[i]) {
                last = i - 1;  // 如果当前下标不匹配，则左边的可能会匹配
            }
            i--;
        }
        
        return last;  // 返回最后在前缀中匹配的下标
    }
};
`````

### 解法2

这种办法是每个字符和所有字符串固定位置上的字符进行比较。

``````c++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res = "";
        
        // 遍历每一个字符
        for (int i = 0; i <= 200; i++) {
            string prefix = strs[0];
            
            // 如果发生越界，则直接返回
            if (i >= prefix.size()) {
                return res;
            }
            
            char c = prefix[i];
            
            for (const string& str : strs) {
                // 一旦发生越界或者不匹配，表示前缀已经无法再进行扩展，直接返回
                if (i >= str.size() || str[i] != c) {
                    return res;
                }
            }
            
            res += c;  // 扩展字符串
        }
        
        return res;
    }
};
``````

