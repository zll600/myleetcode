# [423. Reconstruct Original Digits from English](https://leetcode.com/problems/reconstruct-original-digits-from-english/)

## 题目

Given a string `s` containing an out-of-order English representation of digits `0-9`, return *the digits in **ascending** order*.

 

**Example 1:**

```
Input: s = "owoztneoer"
Output: "012"
```

**Example 2:**

```
Input: s = "fviefuro"
Output: "45"
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is one of the characters `["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"]`.
- `s` is **guaranteed** to be valid.

## 题目大意

给定一个非空字符串，其中包含字母顺序打乱的英文单词表示的数字0-9。按升序输出原始的数字

## 解题思路

这是一道类似找规律的题目，可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0423.Reconstruct-Original-Digits-from-English/

注意这里在解决问题的时候，一定要注意优先级的问题，如果没有处理好，会比较难搞

### Solution1:

````c++
class Solution {
public:
    string originalDigits(string s) {
        vector<int> freq(26);
        for (char c : s) {
            // 统计字符的频数
            ++freq[c - 'a'];
        }
        
        // 这里需要注意这里的顺序是有一定优先级的，不能随便调整
        vector<string> res(10);
        res[0] = Convert('z', freq, "zero", "0"); // 'z' 只在"zero" 中出现
        res[6] = Convert('x', freq, "six", "6"); // 'x' 只在 "six" 中出现
        res[2] = Convert('w', freq, "two", "2"); // 'w' 只在 "two" 中出现
        res[4] = Convert('u', freq, "four", "4"); // 'u' 只在 "four" 中出现
        res[5] = Convert('f', freq, "five", "5"); // 'f' 不再 "five" 就在 "four" 中
        res[1] = Convert('o', freq, "one", "1"); // 'o' 不在 "one"，就在 "zero" 中
        res[7] = Convert('s', freq, "seven", "7"); // 's' 不在 "seven"，就在 "seven" 中
        res[3] = Convert('r', freq, "three", "3"); // 'r' 不在 "threee"，就在 "four" 中
        res[8] = Convert('t', freq, "eight", "8"); // 't' 在 "three","eight"
        res[9] = Convert('i', freq, "nine", "9"); // 'i' 在 "nine", "six", "fix"
        
        string ans = "";
        for (string& str : res) {
            ans += str;
        }
        return ans;
    }
    
 private:
    string Convert(char c, vector<int>& freq, string_view s, string_view num) {
        int val = freq[c - 'a']; // 有多少个数字
        // 扣除其余需要的数字
        const int len = s.size();
        for (int i = 0; i < len; ++i) {
            freq[s[i] - 'a'] -= val;
        }
        // 这个数字出现了多少次
        string res = "";
        for (int i = 0; i < val; ++i) {
            res += num;
        }
        return move(res);
    }
};
````

