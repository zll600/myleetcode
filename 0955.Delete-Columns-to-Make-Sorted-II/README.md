# [955. Delete Columns to Make Sorted II](https://leetcode.cn/problems/delete-columns-to-make-sorted-ii/)

## 题目

You are given an array of `n` strings `strs`, all of the same length.

We may choose any deletion indices, and we delete all the characters in those indices for each string.

For example, if we have `strs = ["abcdef","uvwxyz"]` and deletion indices `{0, 2, 3}`, then the final array after deletions is `["bef", "vyz"]`.

Suppose we chose a set of deletion indices `answer` such that after deletions, the final array has its elements in **lexicographic** order (i.e., `strs[0] <= strs[1] <= strs[2] <= ... <= strs[n - 1]`). Return *the minimum possible value of* `answer.length`.

 

**Example 1:**

```
Input: strs = ["ca","bb","ac"]
Output: 1
Explanation: 
After deleting the first column, strs = ["a", "b", "c"].
Now strs is in lexicographic order (ie. strs[0] <= strs[1] <= strs[2]).
We require at least 1 deletion since initially strs was not in lexicographic order, so the answer is 1.
```

**Example 2:**

```
Input: strs = ["xc","yb","za"]
Output: 0
Explanation: 
strs is already in lexicographic order, so we do not need to delete anything.
Note that the rows of strs are not necessarily in lexicographic order:
i.e., it is NOT necessarily true that (strs[0][0] <= strs[0][1] <= ...)
```

**Example 3:**

```
Input: strs = ["zyx","wvu","tsr"]
Output: 3
Explanation: We have to delete every column.
```

 

**Constraints:**

- `n == strs.length`
- `1 <= n <= 100`
- `1 <= strs[i].length <= 100`
- `strs[i]` consists of lowercase English letters.

## 题目大意

给定由 `n` 个字符串组成的数组 `strs`，其中每个字符串长度相等

选取一个删除索引序列，对于 `strs` 中的每个字符串，删除对应每个索引处的字符

比如，有 `strs = ["abcdef", "uvwxyz"]`，删除索引序列 `{0, 2, 3}`，删除后 strs 为 `["bef", "vyz"]`

假设，我们选择了一组删除索引 `answer`，那么在执行删除操作之后，最终得到的数组的元素是按 字典序（`strs[0]` <= `strs[1]` <= `strs[2]` ... <= `strs[n - 1]）`排列的，然后请你返回 `answer.length` 的最小可能值

## 解题思路

这道题目很容易想到每一列单独去判断，但是往往当前列会依赖于前一列，所以最方便的解法就是保存构造的字符串，整个去判断，而不是分割每一列

### Solution 1:

````c++
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        const int n = strs.size();
        const int len = strs[0].size();
        
        vector<string> records(n, "");
        
        for (int j = 0; j < len; ++j) {
            // 累加这一列的字符
            for (int i = 0; i < n; ++i) {
                records[i] += strs[i][j];
            }
            
            // 如果这一列无序
            if (!IsSorted(records)) {
                for (auto& record : records) {
                    record.pop_back();
                }
            }
        }
        return len - records[0].size();
    }
    
 private:
    // 判断每一行是否有序
    bool IsSorted(const vector<string>& records) {
        for (size_t i = 0; i < records.size() - 1; ++i) {
            if (records[i] > records[i + 1]) {
                return false;
            }
        }
        return true;
    }
};
````
