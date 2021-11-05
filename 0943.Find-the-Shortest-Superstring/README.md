# [943. Find the Shortest Superstring](https://leetcode-cn.com/problems/find-the-shortest-superstring/)

## 题目

Given an array of strings `words`, return *the smallest string that contains each string in* `words` *as a substring*. If there are multiple valid strings of the smallest length, return **any of them**.

You may assume that no string in `words` is a substring of another string in `words`.

 

**Example 1:**

```
Input: words = ["alex","loves","leetcode"]
Output: "alexlovesleetcode"
Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
```

**Example 2:**

```
Input: words = ["catg","ctaagt","gcta","ttca","atgcatc"]
Output: "gctaagttcatgcatc"
```

 

**Constraints:**

- `1 <= words.length <= 12`
- `1 <= words[i].length <= 20`
- `words[i]` consists of lowercase English letters.
- All the strings of `words` are **unique**.

## 题目大意

给定一个字符串数组 words，找到以 words 中每个字符串作为子字符串的最短字符串，如果有多个有效的短字符串满足题目条件，返回其中任意一个即可

我们可以假设 words 中没有字符串是另一个字符串的字串

## 解题思路

### Solution 1;(TLE)

这种解法可以参考花花酱的解法：https://zxi.mytechroad.com/blog/searching/leetcode-943-find-the-shortest-superstring/

`````c++
class Solution {
public:
//     string shortestSuperstring(vector<string>& words) {
        
//     }
    string shortestSuperstring(vector<string>& A) {    
    const int n = A.size();
    g_ = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        g_[i][j] = A[j].length();
        for (int k = 1; k <= min(A[i].length(), A[j].length()); ++k)
          if (A[i].substr(A[i].size() - k) == A[j].substr(0, k))            
            g_[i][j] = A[j].length() - k;
      }
    vector<int> path(n);
    best_len_ = INT_MAX;
    dfs(A, 0, 0, 0, path);    
    string ans = A[best_path_[0]];
    for (int k = 1; k < best_path_.size(); ++k) {
      int i = best_path_[k - 1];
      int j = best_path_[k];
      ans += A[j].substr(A[j].length() - g_[i][j]);
    }
    return ans;
  }
private:
  vector<vector<int>> g_;
  vector<int> best_path_;
  int best_len_;
  void dfs(const vector<string>& A, int d, int used, int cur_len, vector<int>& path) {
    if (cur_len >= best_len_) return;
    if (d == A.size()) {
      best_len_ = cur_len;
      best_path_ = path;
      return;
    }
    
    for (int i = 0; i < A.size(); ++i) {
      if (used & (1 << i)) continue;      
      path[d] = i;
      dfs(A,
          d + 1, 
          used | (1 << i),
          d == 0 ? A[i].length() : cur_len + g_[path[d - 1]][i],
          path);
    }
  }
};
`````

