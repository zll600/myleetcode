[937. Reorder Data in Log Files](https://leetcode.com/problems/reorder-data-in-log-files/)

You are given an array of `logs`. Each log is a space-delimited string of words, where the first word is the **identifier**.

There are two types of logs:

- **Letter-logs**: All words (except the identifier) consist of lowercase English letters.
- **Digit-logs**: All words (except the identifier) consist of digits.

Reorder these logs so that:

1. The **letter-logs** come before all **digit-logs**.
2. The **letter-logs** are sorted lexicographically by  their contents. If their contents are the same, then sort them  lexicographically by their identifiers.
3. The **digit-logs** maintain their relative ordering.

Return *the final order of the logs*.

 

**Example 1:**

```
Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]
Explanation:
The letter-log contents are all different, so their ordering is "art can", "art zero", "own kit dig".
The digit-logs have a relative order of "dig1 8 1 5 1", "dig2 3 6".
```

**Example 2:**

```
Input: logs = ["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"]
Output: ["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"]
```

 

**Constraints:**

- `1 <= logs.length <= 100`
- `3 <= logs[i].length <= 100`
- All the tokens of `logs[i]` are separated by a **single** space.
- `logs[i]` is guaranteed to have an identifier and at least one word after the identifier.

## 题目大意

给定一个 `logs` 数组，每条日志都是空格分割的字符串，其中第一个字符串是标识符

有两种日志:

- **Letter-logs**: 除了标识符之外只含小写字符
- **Digit-logs**: 除了标识符只含数字

重新排序这些日志来满足下列条件：

1. **letter-logs** 出现在 **digit-logs** 之前
2. **letter-logs** 根据他们的内容按照字典序排序，如果内容是一样的，按照他们标识符的字典序排序
3. **digit-logs** 保留他们的相对顺序

返回最终的 logs

## 解题思路

这里要做的有：

- 根据日志内容来进行分类，数字在后
- 根据日志内容和标识符来排序，按照字典序排序


### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/reorder-data-in-log-files/solution/937-cji-hu-shuang-bai-de-bi-jiao-jie-fa-h43pv/)

````c++
class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        // 这里使用稳定排序来做
        stable_sort(logs.begin(), logs.end(), [](const string& lhs, const string& rhs) {
            // 找到第一个分隔符
            auto pos1 = lhs.find(' ');
            auto pos2 = rhs.find(' ');

            // 根据内容来进行判断
            bool flag1 = ::isalpha(lhs[pos1 + 1]);
            bool flag2 = ::isalpha(rhs[pos2 + 1]);

            if (flag1 && !flag2) {
                // letters-log 在 digit-logs 的前面
                return true;
            } else if (flag1 && flag2) {
                // letters-log 之间的排序
                return pair{lhs.substr(pos1 + 1), lhs.substr(0, pos1)} < pair{rhs.substr(pos2 + 1), rhs.substr(0, pos2)};
            }

            return false;
        });

        return logs;
    }
};
````
````c++

````
