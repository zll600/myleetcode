# [944. Delete Columns to Make Sorted](https://leetcode-cn.com/problems/delete-columns-to-make-sorted/)

## 题目

You are given an array of `n` strings `strs`, all of the same length.

The strings can be arranged such that there is one on each line, making a grid. For example, `strs = ["abc", "bce", "cae"]` can be arranged as:

```
abc
bce
cae
```

You want to **delete** the columns that are **not sorted lexicographically**. In the above example (0-indexed), columns 0 (`'a'`, `'b'`, `'c'`) and 2 (`'c'`, `'e'`, `'e'`) are sorted while column 1 (`'b'`, `'c'`, `'a'`) is not, so you would delete column 1.

Return *the number of columns that you will delete*.

 

**Example 1:**

```
Input: strs = ["cba","daf","ghi"]
Output: 1
Explanation: The grid looks as follows:
  cba
  daf
  ghi
Columns 0 and 2 are sorted, but column 1 is not, so you only need to delete 1 column.
```

**Example 2:**

```
Input: strs = ["a","b"]
Output: 0
Explanation: The grid looks as follows:
  a
  b
Column 0 is the only column and is sorted, so you will not delete any columns.
```

**Example 3:**

```
Input: strs = ["zyx","wvu","tsr"]
Output: 3
Explanation: The grid looks as follows:
  zyx
  wvu
  tsr
All 3 columns are not sorted, so you will delete all 3.
```

 

**Constraints:**

- `n == strs.length`
- `1 <= n <= 100`
- `1 <= strs[i].length <= 1000`
- `strs[i]` consists of lowercase English letters.

## 题目大意

给定 n 个 长度相等的字符串 strs，

这些字符串可以每个一行，排成一个网格,例如，`strs = ["abc", "bce", "cae"]` 可以排列为：

```
abc
bce
cae
```

你需要找出并删除 不是按**字典序升序**排列的 列。在上面的例子（下标从 0 开始）中，列 0（`'a', 'b', 'c'`）和列 2（`'c', 'e', 'e'`）都是按升序排列的，而列 1（`'b', 'c', 'a'`）不是，所以要删除列 1，



## 解题思路

遍历每一列，记录不合法的列

### Solution 1:

````c++
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int res = 0;
        const int rows = strs.size();
        const int cols = strs[0].length();
        
        for (int j = 0; j < cols; ++j) {
            for (int i = 0; i < rows - 1; ++i) {
                if (strs[i][j] > strs[i + 1][j]) {
                    ++res;
                    break;
                }
            }
        }
        return res;
    }
};
````

