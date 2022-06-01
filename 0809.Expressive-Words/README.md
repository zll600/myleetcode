# [809. Expressive Words](https://leetcode.cn/problems/expressive-words/)

Sometimes people repeat letters to represent extra feeling. For example:

- `"hello" -> "heeellooo"`
- `"hi" -> "hiiii"`

In these strings like `"heeellooo"`, we have groups of adjacent letters that are all the same: `"h"`, `"eee"`, `"ll"`, `"ooo"`.

You are given a string `s` and an array of query strings `words`. A query word is **stretchy** if it can be made to be equal to `s` by any number of applications of the following extension operation: choose a group consisting of characters `c`, and add some number of characters `c` to the group so that the size of the group is **three or more**.

- For example, starting with `"hello"`, we could do an extension on the group `"o"` to get `"hellooo"`, but we cannot get `"helloo"` since the group `"oo"` has a size less than three. Also, we could do another extension like `"ll" -> "lllll"` to get `"helllllooo"`. If `s = "helllllooo"`, then the query word `"hello"` would be **stretchy** because of these two extension operations: `query = "hello" -> "hellooo" -> "helllllooo" = s`.

Return *the number of query strings that are **stretchy***.

 

**Example 1:**

```
Input: s = "heeellooo", words = ["hello", "hi", "helo"]
Output: 1
Explanation: 
We can extend "e" and "o" in the word "hello" to get "heeellooo".
We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.
```

**Example 2:**

```
Input: s = "zzzzzyyyyy", words = ["zzyy","zy","zyy"]
Output: 3
```

 

**Constraints:**

- `1 <= s.length, words.length <= 100`
- `1 <= words[i].length <= 100`
- `s` and `words[i]` consist of lowercase letters.

## 题目大意

有时候人们会用重复写一些字母来表示额外的感受，比如 `"hello" -> "heeellooo"`, `"hi" -> "hiii"`。我们将相邻字母都相同的一串字符定义为相同字母组，例如：`"h"`, `"eee"`, `"ll"`, `"ooo"`

对于一个给定的字符串 `S` ，如果另一个单词能够通过将一些字母组扩张从而使其和 `S` 相同，我们将这个单词定义为可扩张的`（stretchy）`。

扩张操作定义如下：选择一个字母组（包含字母 c ），然后往其中添加相同的字母 c 使其长度达到 3 或以上。

- 例如，以 `"hello"` 为例，我们可以对字母组 `"o"` 扩张得到 `"hellooo"`，但是无法以同样的方法得到 `"helloo"` 因为字母组 `"oo"` 长度小于 `3`。此外，我们可以进行另一种扩张 `"ll" -> "lllll"` 以获得 `"helllllooo"`。如果 `S = "helllllooo"`，那么查询词 `"hello"` 是可扩张的，因为可以对它执行这两种扩张操作使得 `query = "hello" -> "hellooo" -> "helllllooo" = S`

输入一组查询单词，输出其中可扩张的单词数量

## 解题思路

### Solution !: Two Pointers

这虹解法，使用双指针来遍历两个字符串，并分别统计字符串连续的相同的字符的数目，

如果 word 不能转化为 str ，则有：

- word 中连续的字符数不等于 str 中连续的字符数，且 str 中连续的字符数小于 3
- word 中连续的字符数 大于 str 中连续的字符数

`````c++
class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        int ans = 0;

        for (const string& word : words) {
            if (CanStretchy(word, s)) {
                ++ans;
            }
        }
        return ans;
    }

 private:
    bool CanStretchy(const string& word, const string& str) {
        if (word.size() >= str.size()) {
            return false;
        }

        int idx1 = 0, idx2 = 0;
        while (idx1 < word.size() && idx2 < str.size()) {
            int cnt1 = 1;
            while(idx1 < word.size() - 1 && word[idx1] == word[idx1 + 1]) {
                ++idx1;
                ++cnt1;
            }
            ++idx1;

            int cnt2 = 1;
            while (idx2 < str.size() - 1 && str[idx2] == str[idx2 + 1]) {
                ++idx2;
                ++cnt2;
            }
            ++idx2;

            if (cnt1 != cnt2 && cnt2 < 3)  {
                return false;
            }
            if (cnt1 > cnt2) {
                return false;
            }
        }

        if (idx2 < str.size()) {
            return false;
        }

        return true;
    }
};
````

