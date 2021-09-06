# [216. Combination Sum III](https://leetcode.com/problems/combination-sum-iii/)

## 题目

Find all valid combinations of `k` numbers that sum up to `n` such that the following conditions are true:

- Only numbers `1` through `9` are used.
- Each number is used **at most once**.

Return *a list of all possible valid combinations*. The list must not contain the same combination twice, and the combinations may be returned in any order.

**Example 1:**

```
Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.
```

**Example 2:**

```
Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.
```

**Example 3:**

```
Input: k = 4, n = 1
Output: []
Explanation: There are no valid combinations.
Using 4 different numbers in the range [1,9], the smallest sum we can get is 1+2+3+4 = 10 and since 10 > 1, there are no valid combination.
```

**Example 4:**

```
Input: k = 3, n = 2
Output: []
Explanation: There are no valid combinations.
```

**Example 5:**

```
Input: k = 9, n = 45
Output: [[1,2,3,4,5,6,7,8,9]]
Explanation:
1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 = 45
There are no other valid combinations.
```

 

**Constraints:**

- `2 <= k <= 9`
- `1 <= n <= 60`

## 题目大意

找到所有 和为 k 的 n 个数的组合，只能用数字1到9，每个数只能用一次，

## 解题思路

* 这是一道组合的题目，可以使用回溯法来解决

## 代码

````c++
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        Backtracking(k, n, 1);
        return res;
    }
    
 private:
    vector<vector<int>> res;
    vector<int> path;
    
    void Backtracking(int k, int n, int idx) {
        if (n == 0) {
            if (path.size() == k) {
                res.push_back(path);
            }
            return;
        }
        
        for (int i = idx; i <= 9; ++i) {
            if (i > n) {   // 剪枝
                break;
            }
            
            path.push_back(i);
            Backtracking(k, n - i, i + 1);
            path.pop_back();
        }
    }
};
````

