#### [831. Masking Personal Information](https://leetcode.cn/problems/masking-personal-information/)

You are given a personal information string `s`, representing either an **email address** or a **phone number**. Return *the **masked** personal information using the below rules*.

**Email address:**

An email address is:

- A **name** consisting of uppercase and lowercase English letters, followed by
- The `'@'` symbol, followed by
- The **domain** consisting of uppercase and lowercase English letters with a dot `'.'` somewhere in the middle (not the first or last character).

To mask an email:

- The uppercase letters in the **name** and **domain** must be converted to lowercase letters.
- The middle letters of the **name** (i.e., all but the first and last letters) must be replaced by 5 asterisks `"*****"`.

**Phone number:**

A phone number is formatted as follows:

- The phone number contains 10-13 digits.
- The last 10 digits make up the **local number**.
- The remaining 0-3 digits, in the beginning, make up the **country code**.
- **Separation characters** from the set `{'+', '-', '(', ')', ' '}` separate the above digits in some way.

To mask a phone number:

- Remove all **separation characters**.
- The masked phone number should have the form: 
  - `"***-***-XXXX"` if the country code has 0 digits.
  - `"+*-***-***-XXXX"` if the country code has 1 digit.
  - `"+**-***-***-XXXX"` if the country code has 2 digits.
  - `"+***-***-***-XXXX"` if the country code has 3 digits.
- `"XXXX"` is the last 4 digits of the **local number**.

 

**Example 1:**

```
Input: s = "LeetCode@LeetCode.com"
Output: "l*****e@leetcode.com"
Explanation: s is an email address.
The name and domain are converted to lowercase, and the middle of the name is replaced by 5 asterisks.
```

**Example 2:**

```
Input: s = "AB@qq.com"
Output: "a*****b@qq.com"
Explanation: s is an email address.
The name and domain are converted to lowercase, and the middle of the name is replaced by 5 asterisks.
Note that even though "ab" is 2 characters, it still must have 5 asterisks in the middle.
```

**Example 3:**

```
Input: s = "1(234)567-890"
Output: "***-***-7890"
Explanation: s is a phone number.
There are 10 digits, so the local number is 10 digits and the country code is 0 digits.
Thus, the resulting masked number is "***-***-7890".
```

 

**Constraints:**

- `s` is either a **valid** email or a phone number.

- If 

  ```
  s
  ```

   is an email: 

  - `8 <= s.length <= 40`
  - `s` consists of uppercase and lowercase English letters and exactly one `'@'` symbol and `'.'` symbol.

- If 

  ```
  s
  ```

   is a phone number: 

  - `10 <= s.length <= 20`
  - `s` consists of digits, spaces, and the symbols `'('`, `')'`, `'-'`, and `'+'`.



给你一条个人信息字符串 s ，可能表示一个 邮箱地址 ，也可能表示一串 电话号码 。返回按如下规则 隐藏 个人信息后的结果：

电子邮件地址：

一个电子邮件地址由以下部分组成：

    一个 名字 ，由大小写英文字母组成，后面跟着
    一个 '@' 字符，后面跟着
    一个 域名 ，由大小写英文字母和一个位于中间的 '.' 字符组成。'.' 不会是域名的第一个或者最后一个字符。

要想隐藏电子邮件地址中的个人信息：

    名字 和 域名 部分的大写英文字母应当转换成小写英文字母。
    名字 中间的字母（即，除第一个和最后一个字母外）必须用 5 个 "*****" 替换。

电话号码：

一个电话号码应当按下述格式组成：

    电话号码可以由 10-13 位数字组成
    后 10 位构成 本地号码
    前面剩下的 0-3 位，构成 国家代码
    利用 {'+', '-', '(', ')', ' '} 这些 分隔字符 按某种形式对上述数字进行分隔

要想隐藏电话号码中的个人信息：

    移除所有 分隔字符
    隐藏个人信息后的电话号码应该遵从这种格式：
        "***-***-XXXX" 如果国家代码为 0 位数字
        "+*-***-***-XXXX" 如果国家代码为 1 位数字
        "+**-***-***-XXXX" 如果国家代码为 2 位数字
        "+***-***-***-XXXX" 如果国家代码为 3 位数字
    "XXXX" 是最后 4 位 本地号码

## 解题思路

### Solution 1:

按照规则模拟即可

````c++
class Solution {
public:
    string maskPII(string s) {
        auto pos = s.find_first_of("@", 0);
        if (pos != string::npos) {
            return ProcessEmail(s);
        }
        return ProcessPhoneNumber(s);
    }

 private:
    string ProcessEmail(const string& email_str) {
        auto pos = email_str.find_first_of("@", 0);
        string tmp(std::move(email_str.substr(0, pos)));
        const int name_len = tmp.size();
        string name = "";
        name += tolower(tmp[0]);
        name += "*****";
        name += tolower(tmp.back());
        string domain(std::move(email_str.substr(pos + 1, email_str.size() - pos + 1)));
        for_each(domain.begin(), domain.end(), [](char& c) {
            c = tolower(c);
        });
        return name + "@" + domain;
    }

    string RemoveSeparation(const string& phone_number) {
        string ans = "";
        for_each(phone_number.begin(), phone_number.end(), [&](char c){
            if (c != '+' && c != '-' && c != '(' && c != ')' && c != '{' && c != '}' && c != ' ') {
                ans += c;
            }
        });
        return ans;
    }

    string ProcessPhoneNumber(const string& phone_number) {
        string str = RemoveSeparation(phone_number);
        string ans = "";
        int idx = 0;
        if (str.size() == 11) {
            idx = 1;
            ans += "+*-";
        } else if (str.size() == 12) {
            idx = 2;
            ans = "+**-";
        } else if (str.size() == 13) {
            idx = 3;
            ans = "+***-";
        }

        ans += "***-***-";
        for(size_t i = str.size() - 4; i < str.size(); ++i) {
            ans += str[i];
        }
        return ans;
    }
};
````
