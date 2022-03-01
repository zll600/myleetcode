# [830. Positions of Large Groups](https://leetcode.com/problems/positions-of-large-groups/)

## 题目

In a string `s` of lowercase letters, these letters form consecutive groups of the same character.

For example, a string like `s = "abbxxxxzyy"` has the groups `"a"`, `"bb"`, `"xxxx"`, `"z"`, and `"yy"`.

A group is identified by an interval `[start, end]`, where `start` and `end` denote the start and end indices (inclusive) of the group. In the above example, `"xxxx"` has the interval `[3,6]`.

A group is considered **large** if it has 3 or more characters.

Return *the intervals of every **large** group sorted in **increasing order by start index***.

 

**Example 1:**

```
Input: s = "abbxxxxzzy"
Output: [[3,6]]
Explanation: "xxxx" is the only large group with start index 3 and end index 6.
```

**Example 2:**

```
Input: s = "abc"
Output: []
Explanation: We have groups "a", "b", and "c", none of which are large groups.
```

**Example 3:**

```
Input: s = "abcdddeeeeaabbbcd"
Output: [[3,5],[6,9],[12,14]]
Explanation: The large groups are "ddd", "eeee", and "bbb".
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `s` contains lowercase English letters only.

## 题目大意

在一个由小写字母构成的字符串 s 中，包含由一些连续的相同字符所构成的分组。例如，在字符串 s = “abbxxxxzyy” 中，就含有 “a”, “bb”, “xxxx”, “z” 和 “yy” 这样的一些分组。分组可以用区间 [start, end] 表示，其中 start 和 end 分别表示该分组的起始和终止位置的下标。上例中的 “xxxx” 分组用区间表示为 [3,6] 。我们称所有包含大于或等于三个连续字符的分组为 较大分组 。

找到每一个 较大分组 的区间，按起始位置下标递增顺序排序后，返回结果。

## 解题思路



````c++
class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s) {
        const int len = s.size();
        if (len < 3) {
            return {};
        }

        vector<vector<int>> ans;

        // [start，end) 维护一个有效区间
        int start = 0, end = 0;
        while (end < len) {
            while (end + 1 <= len && s[end] == s[start]) {
                ++end;
            }
            if (end - start >= 3) {
                ans.push_back({start, end - 1});
            }

            start = end;
        }

        return ans;
    }
};
````
