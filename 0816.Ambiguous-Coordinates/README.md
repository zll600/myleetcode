# [816. Ambiguous Coordinates](https://leetcode.com/problems/ambiguous-coordinates/)

## 题目

We had some 2-dimensional coordinates, like `"(1, 3)"` or `"(2, 0.5)"`. Then, we removed all commas, decimal points, and spaces and ended up with the string s.

- For example, `"(1, 3)"` becomes `s = "(13)"` and `"(2, 0.5)"` becomes `s = "(205)"`.

Return *a list of strings representing all possibilities for what our original coordinates could have been*.

Our original representation never had extraneous zeroes, so we never started with numbers like `"00"`, `"0.0"`, `"0.00"`, `"1.0"`, `"001"`, `"00.01"`, or any other number that can be represented with fewer digits. Also, a  decimal point within a number never occurs without at least one digit  occurring before it, so we never started with numbers like `".1"`.

The final answer list can be returned in any order. All coordinates  in the final answer have exactly one space between them (occurring after the comma.)

 

**Example 1:**

```
Input: s = "(123)"
Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
```

**Example 2:**

```
Input: s = "(0123)"
Output: ["(0, 1.23)","(0, 12.3)","(0, 123)","(0.1, 2.3)","(0.1, 23)","(0.12, 3)"]
Explanation: 0.0, 00, 0001 or 00.01 are not allowed.
```

**Example 3:**

```
Input: s = "(00011)"
Output: ["(0, 0.011)","(0.001, 1)"]
```

 

**Constraints:**

- `4 <= s.length <= 12`
- `s[0] == '('` and `s[s.length - 1] == ')'`.
- The rest of `s` are digits.

## 题目大意

我们有一些二维坐标，如 `"(1, 3)"` 或 `"(2, 0.5)"`，然后我们移除所有逗号，小数点和空格，得到一个字符串S。返回所有可能的原始字符串到一个列表中。

原始的坐标表示法不会存在多余的零，所以不会出现类似于 `"00", "0.0", "0.00", "1.0", "001", "00.01"` 或一些其他更小的数来表示坐标。此外，一个小数点前至少存在一个数，所以也不会出现 `“.1”` 形式的数字。

最后返回的列表可以是任意顺序的。而且注意返回的两个数字中间（逗号之后）都有一个空格

## 解题思路



### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0816.Ambiguous-Coordinates/)

这种解法就是产生左右可能的解，然后进行组合

````c++
class Solution {
public:
    vector<string> ambiguousCoordinates(string s) {
        vector<string> res;
        
        string word = s.substr(1, s.size() - 2);
        const int len = word.size();
        for (int i = 1; i < len; ++i) {
            // 前半段产生的集合和后半段产生的集合组合
            vector<string> ahead = Process(word.substr(0, i));
            vector<string> behind = Process(word.substr(i));
            
            for (const string& str1 : ahead) {
                for (const string& str2 : behind) {
                    // cout << str1 << "--" << str2 << endl;
                    res.emplace_back("(" + str1 + ", " + str2 + ")");
                }
            }
        }
        
        return res;
    }
    
 private:
    vector<string> Process(const string& str) {
        // cout << str << "--";
        vector<string> res;
        
        const int len = str.size();
        // 长度为 1，或者 不能分
        if (len == 1 || str[0] != '0') {
            res.push_back(str);
        }
        
        // 如果最后一个位置是 '0'
        if (str.back() == '0') {
            return res;
        }
        
        // 如果第一个位置是 '0'
        if (str[0] == '0') {
            res.emplace_back("0." + str.substr(1));
            return res;
        }
        
        // 加入小数点
        for (int i = 1; i < len; ++i) {
            res.emplace_back(str.substr(0, i) + '.' + str.substr(i));
        }
        
        return res;
    }
};
````
