# [1239. Maximum Length of a Concatenated String with Unique Characters](https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/)

You are given an array of strings `arr`. A string `s` is formed by the **concatenation** of a **subsequence** of `arr` that has **unique characters**.

Return *the **maximum** possible length* of `s`.

A **subsequence** is an array that can be derived from  another array by deleting some or no elements without changing the order of the remaining elements.

 

**Example 1:**

```
Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All the valid concatenations are:
- ""
- "un"
- "iq"
- "ue"
- "uniq" ("un" + "iq")
- "ique" ("iq" + "ue")
Maximum length is 4.
```

**Example 2:**

```
Input: arr = ["cha","r","act","ers"]
Output: 6
Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").
```

**Example 3:**

```
Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
Output: 26
Explanation: The only string in arr has all 26 characters.
```

 

**Constraints:**

- `1 <= arr.length <= 16`
- `1 <= arr[i].length <= 26`
- `arr[i]` contains only lowercase English letters.

## 题目大意

给定一个字符串数组 `arr`，字符串 `s` 是将 `arr` 某一子序列字符串连接所得的字符串，如果 `s` 中的每一个字符都只出现过一次，那么它就是一个可行解

请返回所有可行解 `s` 中最长长度

## 解题思路

这道题目可以考虑是使用 DFS 来求解，具体办法就是对 arr 中每个元素选或者不选，递归树就是一棵二叉树，树的深度就是 arr 中的元素个数

### Solution 1:

这种解法也可以参考 [这篇题解](https://leetcode.cn/problems/maximum-length-of-a-concatenated-string-with-unique-characters/solution/jian-ji-de-chui-su-yi-dong-by-huwt/)

````c++
class Solution {
public:
    int maxLength(vector<string>& arr) {
        vector<int> visited(26, 0);

        return DFS(arr, 0, visited);
    }

 private:

    // 这里因为父节点需要子树遍历的结果来做判断，换句话说就是后序遍历，需要返回值
    int DFS(const vector<string>& arr, size_t idx, vector<int>& visited) {
        if (idx == arr.size()) {
            return 0;
        }

        vector<int> tmp(visited);
        int len1 = 0;
        // 递归的两个分支
        if (IsUnique(arr[idx], tmp)) {
            int cur_len = arr[idx].size();
            len1 = cur_len + DFS(arr, idx + 1, tmp);
        }

        int len2 = DFS(arr, idx + 1, visited);
        return max(len1, len2);
    }

    // 判断当前字符串是否可用
    bool IsUnique(const string& str, vector<int>& visited) {
        for (char c : str) {
            ++visited[c - 'a'];
        }

        for (int i = 0; i < 26; ++i) {
            if (visited[i] > 1) {
                return false;
            }
        }
        return true;
    }
};
````
