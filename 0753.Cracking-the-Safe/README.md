# [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/)

## 题目

There is a safe protected by a password. The password is a sequence of `n` digits where each digit can be in the range `[0, k - 1]`.

The safe has a peculiar way of checking the password. When you enter in a sequence, it checks the **most recent** `n` **digits** that were entered each time you type a digit.

- For example, the correct password is 

  ```
  "345"
  ```

   and you enter in 

  ```
  "012345"
  ```

  : 	

  - After typing `0`, the most recent `3` digits is `"0"`, which is incorrect.
  - After typing `1`, the most recent `3` digits is `"01"`, which is incorrect.
  - After typing `2`, the most recent `3` digits is `"012"`, which is incorrect.
  - After typing `3`, the most recent `3` digits is `"123"`, which is incorrect.
  - After typing `4`, the most recent `3` digits is `"234"`, which is incorrect.
  - After typing `5`, the most recent `3` digits is `"345"`, which is correct and the safe unlocks.

Return *any string of **minimum length** that will unlock the safe **at some point** of entering it*.

 

**Example 1:**

```
Input: n = 1, k = 2
Output: "10"
Explanation: The password is a single digit, so enter each digit. "01" would also unlock the safe.
```

**Example 2:**

```
Input: n = 2, k = 2
Output: "01100"
Explanation: For each possible password:
- "00" is typed in starting from the 4th digit.
- "01" is typed in starting from the 1st digit.
- "10" is typed in starting from the 3rd digit.
- "11" is typed in starting from the 2nd digit.
Thus "01100" will unlock the safe. "01100", "10011", and "11001" would also unlock the safe.
```

 

**Constraints:**

- `1 <= n <= 4`
- `1 <= k <= 10`
- `1 <= kn <= 4096`

## 题目大意
有一个需要密码才能打开的保险箱。密码是 `n` 位数, 密码的每一位是 `[0, k-1]` 中的一个 。

你可以随意输入密码，保险箱会自动记住 *最后 n 位输入* ，如果匹配，则能够打开保险箱。

举个例子，假设密码是 “345”，你可以输入 “012345” 来打开它，只是你输入了 6 个字符.请返回一个能打开保险箱的最短字符串。

## 解题思路

这道题目显然要枚举出所有可能的结果，所以这里可以使用 dfs 来做，

题目求的是最短的字符串，那么就要最大化的复用之前产生的字符串来进行状态转移

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0700~0799/0753.Cracking-the-Safe/)


````c++
class Solution {
public:
    string crackSafe(int n, int k) {
        // 如果只有一位的话
        if (n == 1) {
            return nums.substr(0, k);
        }
        
        // 做记录，
        unordered_set<string> visited;
        // 所有可能的结果
        int total = static_cast<int>(pow(k, n));
        // 初始化一个递归的起点，这里初始化前 n - 1 位
        string str = "";
        for (int i = 1; i < n; ++i) {
            str.append(1, '0');
        }
        
        dfs_crack(n, k, total, str, visited);
        
        return str;
    }
    
 private:
    const string nums = "0123456789";
    
    bool dfs_crack(int n, int k, int depth, string& str,
                  unordered_set<string>& visited) {
        // 递归终止条件
        if (depth == 0) {
            return true;
        }
        
        for (int i = 0; i < k; ++i) {
            // 复用前 n - 1 个字符
            str.append(1, '0' + i);
            string cur = str.substr(str.size() - n);
            // 递归
            if (visited.find(cur) == visited.end()) {
                visited.insert(cur);
                if (dfs_crack(n, k, depth - 1, str, visited)) {
                    return true;
                }
                visited.erase(cur);
            }
            // 回溯
            str.pop_back();
        }
        
        return false;
    }
};
`````
