# [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

## 题目

Given a string `s`, find the length of the **longest substring** without repeating characters.

**Example 1:**

```
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
```

**Example 2:**

```
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

**Example 3:**

```
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

**Example 4:**

```
Input: s = ""
Output: 0
```

 

**Constraints:**

- `0 <= s.length <= 5 * 104`
- `s` consists of English letters, digits, symbols and spaces.

## 题目大意

给定一个字符串，寻找字符串中没有重复字符的最长字串的长度

## 解题思路

* 利用滑动窗口的思想，右侧指针不断向右扩，直至遇见重复字符，一旦遇到重复字符，左侧边界需要收缩，直至区间中不含重复字符，重复这个过程，每次迭代都要计算子串的长度，并判断是否要更新最长长度，

### Solution 1: Sliding Window + unordered_map

````
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }

        unordered_map<char, int> ht;
        int left = 0;
        int right = 0;
        int res = 0;
        const int size = s.size();
        // 这里维护的滑动窗口是 [left, right)，是结果
        while (right < size) {
            if (ht.find(s[right]) != ht.end()) {
                left = max(left, ht.at(s[right]) + 1);  // 取二者中最大的，举例：abba
            }
            ht[s[right]] = right;  // 更新映射
            ++right;  // 右移
            res = max(res, right - left);  // 更新结果
        }

        return res;
    }
};
````





````c++
class Solution {
public:
    /*
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }
        
        vector<int> dict(256, -1);
        int len = 0;
        int pre = -1;
        
        for (int i = 0; i < s.size(); ++i) {
            pre = max(pre, dict[s[i]]);
            len = max(len, i - pre);
            dict[s[i]] = i;
        }
        return len;
    }
    */
    
    /* 滑动窗口
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }
        
        int size = s.size();
        int left = 0;
        int right = -1;
        int len = 0;
        
        vector<int> dict(256);
        while (left < size) {
            if (right + 1 < size && dict[s[right + 1]] == 0) {
                ++dict[s[right + 1]];
                ++right;
            } else  {
                --dict[s[left]];
                ++left;
            }
            len = max(len, right - left + 1); // 这个方法是左闭右闭区间
        }
        return len;
    }*/
    
    // 滑动窗口 + 桶优化
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }
        
        int size = s.size();
        int len = 0;
        int left = 0;
        int right = 0;
        
        vector<int> dict(256, -1);
        
        while (left < size) {
            right = max(right, dict[s[left]] + 1);
            dict[s[left]] = left;
            ++left;
            len = max(len, left - right);   // 这个方法是左闭右开区间
        }
        
        return len;
    }
    
};
````

