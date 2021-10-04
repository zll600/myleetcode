# [345. Reverse Vowels of a String](https://leetcode.com/problems/reverse-vowels-of-a-string/)

## 题目

Given a string `s`, reverse only all the vowels in the string and return it.

The vowels are `'a'`, `'e'`, `'i'`, `'o'`, and `'u'`, and they can appear in both cases.

 

**Example 1:**

```
Input: s = "hello"
Output: "holle"
```

**Example 2:**

```
Input: s = "leetcode"
Output: "leotcede"
```

 

**Constraints:**

- `1 <= s.length <= 3 * 105`
- `s` consist of **printable ASCII** characters.

## 题目大意

给定一个字符串 s，反转字符串中的所有元音字母，然后返回

元音字母是 'a', 'e', 'i', 'o', 和 ‘u’, 并且大小写都有可能出现

## 解题思路

### 解法1（双指针）

这道题和第 344 题比较像，不过多了一个限制条件

````c++
class Solution {
public:
    string reverseVowels(string s) {
        int i = 0;
        int j = s.size() - 1;
        
        // 循环不变量 [i, j] 表示至少有两个元素的区间
        while (i < j) {
            // 从左向右找到元音字母
            if (!IsVowel(s[i])) {
                i++;
                continue;
            }
            
            // 从右往左找到元音字母
            if (!IsVowel(s[j])) {
                j--;
                continue;
            }
            
            // 找到字母就交换
            swap(s[i], s[j]);
            i++;
            j--;
        }
        
        return s;
    }
    
 private:
    bool IsVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
            || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
};
````



