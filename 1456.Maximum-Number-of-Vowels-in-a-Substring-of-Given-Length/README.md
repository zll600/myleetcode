# [1456. Maximum Number of Vowels in a Substring of Given Length](https://leetcode-cn.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)

## 题目

Given a string `s` and an integer `k`.

Return *the maximum number of vowel letters* in any substring of `s` with length `k`.

**Vowel letters** in English are (a, e, i, o, u).

 

**Example 1:**

```
Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.
```

**Example 2:**

```
Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.
```

**Example 3:**

```
Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.
```

**Example 4:**

```
Input: s = "rhythms", k = 4
Output: 0
Explanation: We can see that s doesn't have any vowel letters.
```

**Example 5:**

```
Input: s = "tryhard", k = 4
Output: 1
```

 

**Constraints:**

- `1 <= s.length <= 10^5`
- `s` consists of lowercase English letters.
- `1 <= k <= s.length`

## 题目大意

给定一个字符串 s 和一个整数 k，返回在长度为 k 的字串中，可能出现的最多元音字母数，

英语中的元音字母是（a, e, i, o, u）

## 解题思路

### Solution 1: Sliding Window

利用滑动窗口，维护一个定长的滑动窗口，在遍历的过程中，更新结果

````c++
class Solution {
public:
    int maxVowels(string s, int k) {
        int res = 0;
        int sum = 0;
        // 先扩大窗口大小到 k
        for (int i = 0; i < k; ++i) {
            if (IsVowel(s[i])) {  // 统计
                ++sum;
            }
        }
        res = sum;
        
        const int size = s.size();
        for (int i = k; i < size; ++i) {
            if (IsVowel(s[i - k])) {  // 右移左边界
                --sum;
            }
            
            if (IsVowel(s[i])) {  // 右移右边界
                ++sum;
            }
            
            res = max(res, sum);  // 更新 res
        }
        
        return res;
    }
    
 private:
    // 是否是元音字母
    bool IsVowel(char c) {
        if (c == 'a' || c == 'e' || c == 'i'
            || c == 'o' || c == 'u') {
            return true;
        }
        return false;
    }
};
````

### Solution 2: Sliding Window

````c++
class Solution {
public:
    int maxVowels(string s, int k) {
        // 用空间换时间
        vector<int> dict(26, 0);
        dict['a' - 'a'] = 1;
        dict['e' - 'a'] = 1;
        dict['i' - 'a'] = 1;
        dict['o' - 'a'] = 1;
        dict['u' - 'a'] = 1;
        
        int sum = 0;
        int res = 0;
        const int size = s.size();
        for (int i = 0; i < size; ++i) {
            sum += dict[s[i] - 'a'];
            if (i + 1 >= k) {
                res = max(res, sum);
                sum -= dict[s[i - k + 1] - 'a'];
                
            }
        }
        
        return res;
    }
};
````

