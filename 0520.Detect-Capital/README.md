# [520. Detect Capital](https://leetcode.com/problems/detect-capital/)

## 题目

We define the usage of capitals in a word to be right when one of the following cases holds:

- All letters in this word are capitals, like `"USA"`.
- All letters in this word are not capitals, like `"leetcode"`.
- Only the first letter in this word is capital, like `"Google"`.

Given a string `word`, return `true` if the usage of capitals in it is right.

 

**Example 1:**

```
Input: word = "USA"
Output: true
```

**Example 2:**

```
Input: word = "FlaG"
Output: false
```

 

**Constraints:**

- `1 <= word.length <= 100`
- `word` consists of lowercase and uppercase English letters.

## 题目大意

我们定义在以下情况下单词的首字母大写的用法是正确的，全部字母都是大写，比如 "USA" 。

* 单词中所有字母都不是大写，比如 "leetcode" 。
* 如果单词不只含有一个字母，只有首字母大写， 比如 "Google" 。
* 给你一个字符串 word 。如果大写用法正确，返回 true ；否则，返回 false。

## 解题思路

利用条件划分出三种不同的分类即可，

### Solution 1:

这种解法，并不难理解，重点是要划分出来，这里利用一个标志变量来解决

```c++
class Solution {
public:
    bool detectCapitalUse(string word) {
        // 这里定义三种状态，
        // -1，表示全大写
        // 0，表示首字母大写
        // 1，表示全小写
        int flag = -1;
        
        const int len = word.size();
        if (isupper(word[0])) {
            flag = -1;
            if (len > 1) {
                if (isupper(word[1]) && flag == -1) {
                    flag = -1;
                } else if (islower(word[1]) && flag == -1){
                    flag = 0;
                } else {
                    return false;
                }
            }
        } else {
            flag = 1;
        }
        
        for (int i = 1; i < len; ++i) {
            if ((flag == 1 || flag == 0) && isupper(word[i])) {
                return false;
            } else if (flag == -1 && islower(word[i])) {
                return false;
            }
        }
        
        return true;
    }
};
```

