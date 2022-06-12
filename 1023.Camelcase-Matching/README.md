# [1023. Camelcase Matching](https://leetcode.cn/problems/camelcase-matching/)

## 题目

Given an array of strings `queries` and a string `pattern`, return a boolean array `answer` where `answer[i]` is `true` if `queries[i]` matches `pattern`, and `false` otherwise.

A query word `queries[i]` matches `pattern` if  you can insert lowercase English letters pattern so that it equals the  query. You may insert each character at any position and you may not  insert any characters.

 

**Example 1:**

```
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
Output: [true,false,true,true,false]
Explanation: "FooBar" can be generated like this "F" + "oo" + "B" + "ar".
"FootBall" can be generated like this "F" + "oot" + "B" + "all".
"FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".
```

**Example 2:**

```
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
Output: [true,false,true,false,false]
Explanation: "FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
"FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".
```

**Example 3:**

```
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
Output: [false,true,false,false,false]
Explanation: "FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r" + "T" + "est".
```

 

**Constraints:**

- `1 <= pattern.length, queries.length <= 100`
- `1 <= queries[i].length <= 100`
- `queries[i]` and `pattern` consist of English letters.

## 题目大意

如果我们可以将 *小写字母* 插入模式串 `pattern` 得到待查询项 `query`，那么待查询项与给定模式串匹配。（我们可以在任何位置插入每个字符，也可以插入 0 个字符。）

给定待查询列表 `queries`，和模式串 `pattern`，返回由布尔值组成的答案列表 `answer`。只有在待查项 `queries[i]` 与模式串 `pattern` 匹配时， `answer[i]` 才为 `true`，否则为 `false`

## 解题思路

### Solution 1: Two Pointers

这里使用双指针遍历即可，需要注意的就是遍历的时候的判断规则，

这道题目是可以在任意位置插入小写字符，那么在其他不能插入的地方如果不相等，就直接报错即可

````c++
class Solution {
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        const int len = queries.size();
        vector<bool> res(len);
        for (int i = 0; i < len; ++i) {
            if (Check(queries[i], pattern)) {
                res[i] = true;
            }
        }
        return res;
    }

 private:
    bool Check(const string& query, const string& pattern) {
        int idx1 = 0, idx2 = 0;

        while (idx1 < query.size() && idx2 < pattern.size()) {
            if (isupper(query[idx1]) && isupper(pattern[idx2])) {
                // 如果都是大写

                // 大写字符一旦不相等就可以直接报错
                if (query[idx1] != pattern[idx2]) {
                    return false;
                }

                // 双指针同时移动
                ++idx1;
                ++idx2;
            } else if (islower(query[idx1]) && islower(pattern[idx2])) {
                // 如果都是小写

                // 如果两个相同粗要移动 idx2
                if (query[idx1] == pattern[idx2]) {
                    ++idx2;
                }

                ++idx1;
            } else {
                // 其余情况移动 idx1 下标，就是插入情况
                ++idx1;
            }
        }

        // 如果 idx2 没有遍历完，直接报错
        if (idx2 < pattern.size()) {
            return false;
        }

        // 如果 query 还没有遍历完，还需要做判断
        while (idx1 < query.size()) {
            if (isupper(query[idx1])) {
                return false;
            }
            ++idx1;
        }

        return true;
    }
};
````
