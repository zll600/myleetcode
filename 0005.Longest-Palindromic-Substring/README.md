# [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)

## 题目

Given a string `s`, return *the longest palindromic substring* in `s`.

 

**Example 1:**

```
Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.
```

**Example 2:**

```
Input: s = "cbbd"
Output: "bb"
```

**Example 3:**

```
Input: s = "a"
Output: "a"
```

**Example 4:**

```
Input: s = "ac"
Output: "a"
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `s` consist of only digits and English letters.

## 题目大意

给定一个字符串，返回 s 中最长回文字串



### 解法1(暴力解法)

这个方法有下面几点需要注意

* 根据回文子串的定义，枚举所有长度大于等于2 的字串，选出最长的
* 我们只需要记录下 子串的左右端点即可，不用真的去截下来一个子串
* 只需要对长度最长的那个符合条件的子串做验证

````c++
class Solution {
public:
    string longestPalindrome(string str) {
        if (str.size() < 2) {
            return str;
        }
        
        int left = 0;  // 记录子串开始的位置
        int len = 1;  // 记录子串的长度，注意这里已经包含了一个字符进去了，所以初始化不为0，
        for (int i = 0; i < str.size() - 1; i++) {
            for (int j = i + 1; j < str.size(); j++) {
                if (j - i + 1 > len && IsPalindrome(str, i, j)) {
                    len = j - i + 1;
                    left = i;
                }
            }
        }
        
        return str.substr(left, len);
    }
    
 private:
    // 验证字符串是否回文
    bool IsPalindrome(const string& str, int left, int right) {
        while (left <= right) {
            if (left >= 0 && right < str.size() && str[left] != str[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};
````

### 解法2（动态规划）

一个回文字串如果删掉头和尾的字符，依旧是一个回文子串，而如果一个子串的头和尾不相等，那么这个子串一定不是回文子串，这也就是回文子串的动态转移方程

* 定义状态 `dp[i][j]`表示`str[i...j]` 的子串是否是回文子串，注意这里是左闭右闭区间
* 动态转移方程：

`````
dp[i][j] = (s[i] == s[j]) && (j - i + 1 < 3 || dp[i + 1][j - 1])
`````

* 初始化：如果 i == j 说明此时区间中只有一个元素，那么一定为 true，这里可以利用这一点来让整个过程可以递推
* 下面的写法，是优化之后，如果做出动态规划要填写的表格，可以发现其实我们只需要对角线上方的部分，而不需要对角线下方的部分，所以这里用外层循环遍历 j，内层循环遍历 i,

````c++
class Solution {
public:
    string longestPalindrome(string str) {
        if (str.size() < 2) {
            return str;
        }
        
        int left = 0;
        int len = 1;
        
        int size =  str.size();
        vector<vector<int>> dp(size, vector<int>(size, false));
        
        for (int i = 0; i < size; i++) {
            dp[i][i] = true;
        }
        
        for (int j = 1; j < size; j++) {
            for (int i = 0; i < j; i++) {
                /*
                if (str[i] != str[j]) {
                    dp[i][j] = false;
                } else {
                    if (j - i + 1 < 3) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                } */
                
                dp[i][j] = (str[i] == str[j]) && ((j - i + 1 < 3) || dp[i + 1][j - 1]);
                
                if (dp[i][j] && j - i + 1 > len) {
                    len = j - i + 1;
                    left = i;
                }
            }
        }
        
        return str.substr(left, len);
    }
};
````

### 解法3(中心扩散)

这种解法的具体思路，就是利用回文串的特点，从中间向两边扩，知道不能扩为止

不过这里有一个需要注意的地方：

* 如果最终的子串是奇数串，则必定是从中间字符扩展出来的
* 如果最终子串是偶数串，则必定是从中间的两个字符扩展出来的，

这里提供的解决方法是：

* 如果提供重合的下标，将得到奇数的子串
* 如果提供相邻的下标，将得到偶数的子串

``````c++
class Solution {
public:
    string longestPalindrome(string str) {
        if (str.size() < 2) {
            return str;
        }
        
        pair<int, int> res;
        int max_len = 0;
        for (int i = 0; i < str.size() - 1; i++) {
            pair<int, int> odd = CenterSpread(str, i, i);  // 这里表示奇数回文串
            pair<int, int> even = CenterSpread(str, i, i + 1);  // 这里表示偶数回文串
            pair<int, int> bigger = even.second > odd.second ? even : odd;
            
            if (bigger.second > max_len) {
                res = bigger;
                max_len = bigger.second;
            }
        }
        
        return str.substr(res.first, res.second);
    }
    
 private:
    // 中心扩散
    pair<int, int> CenterSpread(const string& str, int left, int right) {
        int size = str.size();
        
        while (left >= 0 && right < size) {
            if (str[left] == str[right]) {
                left--;
                right++;
            } else {
                break;
            }
        }
        
        // 这里注意计算长度的时候是左开右开区间，我们要转化为左闭右闭区间
        return pair<int, int>(left + 1, right - left - 1);
    }
};
``````



