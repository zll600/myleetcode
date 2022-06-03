#### [833. Find And Replace in String](https://leetcode.cn/problems/find-and-replace-in-string/)

You are given a **0-indexed** string `s` that you must perform `k` replacement operations on. The replacement operations are given as three **0-indexed** parallel arrays, `indices`, `sources`, and `targets`, all of length `k`.

To complete the `ith` replacement operation:

1. Check if the **substring** `sources[i]` occurs at index `indices[i]` in the **original string** `s`.
2. If it does not occur, **do nothing**.
3. Otherwise if it does occur, **replace** that substring with `targets[i]`.

For example, if `s = "abcd"`, `indices[i] = 0`, `sources[i] = "ab"`, and `targets[i] = "eee"`, then the result of this replacement will be `"eeecd"`.

All replacement operations must occur **simultaneously**, meaning the replacement operations should not affect the indexing of  each other. The testcases will be generated such that the replacements  will **not overlap**.

- For example, a testcase with `s = "abc"`, `indices = [0, 1]`, and `sources = ["ab","bc"]` will not be generated because the `"ab"` and `"bc"` replacements overlap.

Return *the **resulting string** after performing all replacement operations on* `s`.

A **substring** is a contiguous sequence of characters in a string.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/06/12/833-ex1.png)

```
Input: s = "abcd", indices = [0, 2], sources = ["a", "cd"], targets = ["eee", "ffff"]
Output: "eeebffff"
Explanation:
"a" occurs at index 0 in s, so we replace it with "eee".
"cd" occurs at index 2 in s, so we replace it with "ffff".
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/06/12/833-ex2-1.png)

```
Input: s = "abcd", indices = [0, 2], sources = ["ab","ec"], targets = ["eee","ffff"]
Output: "eeecd"
Explanation:
"ab" occurs at index 0 in s, so we replace it with "eee".
"ec" does not occur at index 2 in s, so we do nothing.
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `k == indices.length == sources.length == targets.length`
- `1 <= k <= 100`
- `0 <= indexes[i] < s.length`
- `1 <= sources[i].length, targets[i].length <= 50`
- `s` consists of only lowercase English letters.
- `sources[i]` and `targets[i]` consist of only lowercase English letters.



你会得到一个字符串 s (索引从 0 开始)，你必须对它执行 k 个替换操作。替换操作以三个长度均为 k 的并行数组给出：indices, sources,  targets。

要完成第 i 个替换操作:

    检查 子字符串  sources[i] 是否出现在 原字符串 s 的索引 indices[i] 处。
    如果没有出现， 什么也不做 。
    如果出现，则用 targets[i] 替换 该子字符串。

例如，如果 s = "abcd" ， indices[i] = 0 , sources[i] = "ab"， targets[i] = "eee" ，那么替换的结果将是 "eeecd" 。

所有替换操作必须 同时 发生，这意味着替换操作不应该影响彼此的索引。测试用例保证元素间不会重叠 。

    例如，一个 s = "abc" ，  indices = [0,1] ， sources = ["ab"，"bc"] 的测试用例将不会生成，因为 "ab" 和 "bc" 替换重叠。

在对 s 执行所有替换操作后返回 结果字符串 。

子字符串 是字符串中连续的字符序列。

## 解题思路

### Solution 1:

这里需要注意的是，题目中并没有说 indices 是有序，所以有可能是需要排序的，但是 indices 和 sources 和 targets 又存在映射关系，所以这里在排序之前需要保存一个 映射，用于保留这种关系

剩下就是一下细节的处理，主要思路就是 遍历排序后的 indices 数组，判断是否可以 replace，就可以了

````c++
class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        // 保存 indice --> source | target 的映射
        unordered_map<int, pair<string, string>> bucket;
        for (int i = 0; i < indices.size(); ++i) {
            bucket[indices[i]] = {sources[i], targets[i]};
        }
        // 将 indice 排序
        sort(indices.begin(), indices.end());

        int source_idx = 0;
        // 先拼接之前的字符串
        string ans(std::move(s.substr(0, indices[0])));
        while (source_idx < indices.size()) {
            int indice_idx = indices[source_idx];
            string source = bucket[indice_idx].first;
            string target = bucket[indice_idx].second;

            if (IsSame(s, indice_idx, source)) {
                // replace
                ans += target;
                int pos = indice_idx + source.size();

                if (source_idx < indices.size() - 1) {
                    ans += s.substr(pos, indices[source_idx + 1] - pos);
                } else {
                    ans += s.substr(pos, s.size() - pos);
                }
            } else {
                if (source_idx < indices.size() - 1) {
                    ans += s.substr(indices[source_idx], indices[source_idx + 1] - indices[source_idx]);
                } else {
                    ans += s.substr(indices[source_idx], s.size() - indices[source_idx]);
                }
            }

            ++source_idx;
        }

        return ans;
    }

 private:
    bool IsSame(const string& s, int idx, const string& source) {
        for (size_t i = 0; i < source.size(); ++i) {
            if (s[idx] != source[i]) {
                return false;
            }
            ++idx;
        }
        return true;
    }
};
````


