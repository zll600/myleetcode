# [839. Similar String Groups](https://leetcode.com/problems/similar-string-groups/)

## 题目

Two strings `X` and `Y` are similar if we can swap two letters (in different positions) of `X`, so that it equals `Y`. Also two strings `X` and `Y` are similar if they are equal.

For example, `"tars"` and `"rats"` are similar (swapping at positions `0` and `2`), and `"rats"` and `"arts"` are similar, but `"star"` is not similar to `"tars"`, `"rats"`, or `"arts"`.

Together, these form two connected groups by similarity: `{"tars", "rats", "arts"}` and `{"star"}`. Notice that `"tars"` and `"arts"` are in the same group even though they are not similar. Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.

We are given a list `strs` of strings where every string in `strs` is an anagram of every other string in `strs`. How many groups are there?

 

**Example 1:**

```
Input: strs = ["tars","rats","arts","star"]
Output: 2
```

**Example 2:**

```
Input: strs = ["omv","ovm"]
Output: 1
```

 

**Constraints:**

- `1 <= strs.length <= 300`
- `1 <= strs[i].length <= 300`
- `strs[i]` consists of lowercase letters only.
- All words in `strs` have the same length and are anagrams of each other.

## 题目大意

如果我们交换字符串 `X` 中的两个不同位置的字母，使得它和字符串 `Y` 相等，那么称 `X` 和 `Y` 两个字符串相似。

例如，`“tars”` 和 `“rats”` 是相似的 (交换 `0` 与 `2` 的位置)； `“rats”` 和 `“arts”` 也是相似的，但是 `“star”` 不与 `“tars”`，`“rats”`，或 `“arts”` 相似。

总之，它们通过相似性形成了两个关联组：{“tars”, “rats”, “arts”} 和 {“star”}。注意，“tars” 和 “arts” 是在同一组中，即使它们并不相似。

形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。

我们给出了一个不包含重复的字符串列表 A。列表中的每个字符串都是 A 中其它所有字符串的一个字母异位词。请问 A 中有多少个相似字符串组？


## 解题思路

这道题目有以下问题需要解决：

- 如何判断两个字符串相似
- 如何将相似的字符串放进一个组中

### Solution 1: UnionFind

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/redundant-connection/solution/zui-rong-yi-li-jie-de-bing-cha-ji-xiang-abg0f/)

因为每个字符串都是字母异位词，所以只要字母不同的地方有零处或者两处，就可以判断为是相似的，然后通过并查集来进行合并，返回最终的组数

因为要形成关联组只需要和组中的一个字符串是相似的即可，所以这里采用枚举所有组合的方法来进行判断，避免发生遗漏


````c++
class UF {
 public:
    UF(int n) : data_(vector<int>(n)), count_(n) {
        for (int i = 0; i < n; ++i) {
            data_[i] = i;
        }
    }

    void Union(int x, int y) {
        int root_x = Find(x);
        int root_y = Find(y);

        if (root_x == root_y) {
            return;
        }
        cout << root_x << " -- " << root_y << endl;
        data_[root_y] = root_x;
        --count_;
    }

    int Find(int x) {
        while (x != data_[x]) {
            x = data_[x];
        }
        return x;
    }

    int Count() {
        return count_;
    }

 private:
    vector<int> data_;
    int count_;
};

class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        const int len = strs.size();
        UF uf(len);
        for (int i = 0; i < len - 1; ++i) {
            for (int j = i + 1; j < len; ++j) {
                if (IsSimilar(strs[i], strs[j])) {
                    uf.Union(i, j);
                }
            }
        }

        return uf.Count();
    }

 private:
    bool IsSimilar(const string& lhs, const string& rhs) {
        const int len = lhs.size();
        int diff = 0;
        for (int i = 0; i < len; ++i) {
            if (lhs[i] != rhs[i]) {
                ++diff;
            }
            if (diff > 2) {
                return false;
            }
        }

        return true;
    }
};
````
