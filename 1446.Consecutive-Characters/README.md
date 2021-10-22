# [1446. Consecutive Characters](https://leetcode-cn.com/problems/consecutive-characters/)

## 题目

The **power** of the string is the maximum length of a non-empty substring that contains only one unique character.

Given a string `s`, return *the **power** of* `s`.

 

**Example 1:**

```
Input: s = "leetcode"
Output: 2
Explanation: The substring "ee" is of length 2 with the character 'e' only.
```

**Example 2:**

```
Input: s = "abbcccddddeeeeedcba"
Output: 5
Explanation: The substring "eeeee" is of length 5 with the character 'e' only.
```

**Example 3:**

```
Input: s = "triplepillooooow"
Output: 5
```

**Example 4:**

```
Input: s = "hooraaaaaaaaaaay"
Output: 11
```

**Example 5:**

```
Input: s = "tourist"
Output: 1
```

 

**Constraints:**

- `1 <= s.length <= 500`
- `s` consists of only lowercase English letters.

## 题目

字符串的能量是只含一种字符的非空子串的长度，给定一个字符串，返回字符串的 能量

## 解题思路

### Solution 1:

这道题可以利用双指针来解决，比较简单，需要注意的是，循环外还需要一次判断

````c++
class Solution {
public:
    int maxPower(string s) {
        int left = 0;
        int right = 1;
        
        int res = 1;
        const int size = s.size();
        // [left, right) 循环不变量，表示只含一种字符的非空区间
        while (right < size) {
            if (s[right] != s[left]) {
                res = max(res, right - left);
                left = right;
            }
            ++right;
        }
        
        // 最后出现的子串需要在循环外计算
        return max(res, right - left);
    }
};
````

